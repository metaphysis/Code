// LA Encoding
// UVa ID: 11410
// Verdict: Accepted
// Submission Date: 2026-05-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算长度为 L 的 LA 可编码字符串数量
// L = 0 时返回 1（空串）
long long countLen(int L, int alphaSize) {
    if (L == 0) return 1;
    if (L == 1) return alphaSize - 1;
    long long res = alphaSize - 1;
    for (int i = 1; i < L; ++i) res *= alphaSize;
    return res;
}

// 计算字符串 s 在字母表 alpha 中的排名（排名从 1 开始，空串为第 1）
long long getRank(const string &s, const string &alpha, char special) {
    int m = alpha.size();
    int L = s.size();
    long long rank = 1; // 空串
    
    // 所有长度小于 L 的字符串数量
    for (int len = 1; len < L; ++len) {
        rank += countLen(len, m);
    }
    
    // 计算后缀的组合数：m^(L-1)
    long long suffix = 1;
    for (int i = L - 1; i >= 1; --i) suffix *= m;
    
    int specialIdx = alpha.find(special);
    int firstIdx = alpha.find(s[0]);
    
    // 第 1 位：统计比 s[0] 小且不是 special 的字符个数
    int cntBefore = 0;
    for (int i = 0; i < firstIdx; ++i) {
        if (i != specialIdx) cntBefore++;
    }
    rank += cntBefore * suffix; // 所有比 s[0] 小的首字母对应的字符串
    rank++; // s[0] 本身
    
    // 第 2 位及以后
    for (int pos = 1; pos < L; ++pos) {
        suffix /= m;
        int idx = alpha.find(s[pos]);
        rank += idx * suffix;
    }
    
    return rank;
}

// 根据排名构造字符串（排名从 1 开始，空串为第 1）
string buildString(long long rank, const string &alpha, char special) {
    if (rank == 1) return "";
    
    int m = alpha.size();
    long long remain = rank - 1; // 去掉空串
    
    // 确定长度
    int len = 1;
    while (true) {
        long long cnt = countLen(len, m);
        if (remain <= cnt) break;
        remain -= cnt;
        len++;
    }
    
    string res;
    
    // 构造第 1 位（不能是 special）
    long long block = 1;
    for (int i = 1; i < len; ++i) block *= m;
    int pos = (remain - 1) / block;
    int cnt2 = 0;
    for (int i = 0; i < m; ++i) {
        if (alpha[i] == special) continue;
        if (cnt2 == pos) {
            res += alpha[i];
            break;
        }
        cnt2++;
    }
    remain = (remain - 1) % block + 1;
    
    // 构造第 2 位及以后（可以任意选，包括 special）
    for (int i = 1; i < len; ++i) {
        block /= m;
        int idx = (remain - 1) / block;
        res += alpha[idx];
        remain = (remain - 1) % block + 1;
    }
    
    return res;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string msg, broken;
        cin >> msg >> broken;
        
        string full = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string avail;
        for (char c : full) {
            if (broken.find(c) == string::npos) avail += c;
        }
        
        long long r = getRank(msg, full, 'A');
        string ans = buildString(r, avail, avail[0]);
        cout << ans << endl;
    }
    return 0;
}
