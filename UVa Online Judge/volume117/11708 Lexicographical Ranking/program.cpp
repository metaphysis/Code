// Lexicographical Ranking
// UVa ID: 11708
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int64 fact[21];
int64 F[21];

// 预处理阶乘和F[m] = sum_{j=0}^{m} P(m, j)
void precompute() {
    fact[0] = 1;
    for (int i = 1; i <= 20; ++i) fact[i] = fact[i - 1] * i;
    for (int m = 0; m <= 20; ++m) {
        int64 sum = 0;
        for (int j = 0; j <= m; ++j)
            sum += fact[m] / fact[m - j];   // P(m, j)
        F[m] = sum;
    }
}

// 计算给定字符串的排名（1‑based）
int64 rankOf(const string& s) {
    int n = (int)s.size();
    bool used[26] = {false};
    int64 rank = 1;
    for (int i = 0; i < n; ++i) {
        if (i > 0) rank += 1;                 // 前缀 s[0..i-1] 本身
        int ch = s[i] - 'a';
        for (int c = 0; c < ch; ++c) {
            if (!used[c]) {
                int remaining = n - i - 1;    // 已用 i 个，当前候选 c，剩余字母数
                rank += F[remaining];
            }
        }
        used[ch] = true;
    }
    return rank;
}

// 根据排名 k 生成对应的单词（字母集合由 s 给出）
string kthWord(const string& s, int64 k) {
    vector<char> avail(s.begin(), s.end());
    sort(avail.begin(), avail.end());
    string pre;
    while (true) {
        if (!pre.empty()) {
            if (k == 1) return pre;
            --k;                              // 跳过当前前缀本身
        }
        int m = (int)avail.size();
        for (size_t idx = 0; idx < avail.size(); ++idx) {
            char c = avail[idx];
            int64 cnt = F[m - 1];             // 选择 c 后剩余 m-1 个字母的所有排列数
            if (k > cnt) {
                k -= cnt;
            } else {
                pre.push_back(c);
                avail.erase(avail.begin() + idx);
                break;
            }
        }
    }
}

// 处理一个测试用例
void processCase(const string& s, const vector<int64>& queries) {
    cout << rankOf(s) << '\n';
    for (int64 q : queries)
        cout << kthWord(s, q) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    string token;
    string currentStr;
    vector<int64> queries;

    while (cin >> token) {
        if (isdigit(token[0])) {               // 数字，作为查询
            queries.push_back(stoll(token));
        } else {                               // 字母，作为新字符串
            if (!currentStr.empty()) {
                processCase(currentStr, queries);
                queries.clear();
            }
            currentStr = token;
        }
    }
    if (!currentStr.empty())
        processCase(currentStr, queries);

    return 0;
}
