// Stammering Aliens
// UVa ID: 12206
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.350s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 构建后缀数组 (Suffix Array)
 * @param s 输入字符串
 * @param sa 输出的后缀数组，sa[i] 表示排名第 i 的后缀的起始位置
 */
void buildSA(const string& s, vector<int>& sa) {
    int n = s.size();
    sa.resize(n);
    vector<int> rank(n), newRank(n);
    
    // 初始排序：按第一个字符排序
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rank[i] = s[i];  // 初始排名就是字符的 ASCII 值
    }
    
    // 倍增法：每次比较长度为 2k 的前缀
    for (int k = 1; k < n; k <<= 1) {
        // 自定义比较函数：先比较前 k 个字符，再比较后 k 个字符
        auto cmp = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            // 如果前 k 个字符相同，比较后 k 个字符
            int ra = (a + k < n) ? rank[a + k] : -1;
            int rb = (b + k < n) ? rank[b + k] : -1;
            return ra < rb;
        };
        
        // 对后缀数组进行排序
        sort(sa.begin(), sa.end(), cmp);
        
        // 重新计算排名
        newRank[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            // 如果当前后缀与前一个后缀完全相同，则排名相同
            newRank[sa[i]] = newRank[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        rank = newRank;  // 更新排名数组
    }
}

/**
 * 构建 LCP 数组 (Longest Common Prefix)
 * @param s 输入字符串
 * @param sa 后缀数组
 * @param lcp 输出的 LCP 数组，lcp[i] 表示 sa[i] 和 sa[i-1] 的最长公共前缀长度
 */
void buildLCP(const string& s, const vector<int>& sa, vector<int>& lcp) {
    int n = s.size();
    vector<int> rank(n);
    
    // 构建 rank 数组：rank[i] 表示以 i 开头的后缀的排名
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    
    lcp.resize(n);
    int h = 0;  // 当前公共前缀长度
    
    // 按原字符串顺序计算 LCP
    for (int i = 0; i < n; i++) {
        if (rank[i] > 0) {  // 不是排名第一的后缀
            int j = sa[rank[i] - 1];  // 前一个排名的后缀起始位置
            
            // 计算公共前缀长度
            while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
            
            lcp[rank[i]] = h;  // 存储 LCP 值
            
            if (h > 0) h--;  // 下一个后缀的公共前缀至少是 h-1
        }
    }
}

/**
 * 检查是否存在长度为 len 的子串出现至少 m 次
 * @param len 要检查的子串长度
 * @param m 最少出现次数
 * @param sa 后缀数组
 * @param lcp LCP 数组
 * @return 如果存在，返回最右起始位置；否则返回 -1
 */
int check(int len, int m, const vector<int>& sa, const vector<int>& lcp) {
    int n = sa.size();
    int cnt = 1;  // 当前公共前缀长度 >= len 的后缀数量
    int rightmost = -1;  // 记录最右起始位置
    
    // 遍历 LCP 数组，寻找连续的 LCP >= len 的区间
    for (int i = 1; i < n; i++) {
        if (lcp[i] >= len) {
            cnt++;  // 当前后缀与前一个后缀的公共前缀足够长
        } else {
            // 当前连续区间结束，检查是否满足条件
            if (cnt >= m) {
                // 遍历这个区间内的所有后缀，更新最右起始位置
                for (int j = i - cnt; j < i; j++) {
                    rightmost = max(rightmost, sa[j]);
                }
            }
            cnt = 1;  // 重置计数器
        }
    }
    
    // 处理最后一个区间
    if (cnt >= m) {
        for (int j = n - cnt; j < n; j++) {
            rightmost = max(rightmost, sa[j]);
        }
    }
    
    return rightmost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    string s;
    
    // 处理多组测试数据，直到 m = 0
    while (cin >> m, m) {
        cin >> s;
        int n = s.size();

        // 特殊情况：m = 1，整个字符串就是答案
        if (m == 1) {
            cout << n << " 0\n";
            continue;
        }

        vector<int> sa, lcp;
        buildSA(s, sa);      // 构建后缀数组
        buildLCP(s, sa, lcp); // 构建 LCP 数组

        int low = 1, high = n;  // 二分查找的上下界
        int bestLen = 0, bestPos = -1;  // 记录最优解

        // 二分查找最长长度
        while (low <= high) {
            int mid = (low + high) / 2;
            int pos = check(mid, m, sa, lcp);  // 检查长度为 mid 的子串
            
            if (pos != -1) {
                // 存在满足条件的子串，尝试更长的长度
                bestLen = mid;
                bestPos = pos;
                low = mid + 1;
            } else {
                // 不存在，尝试更短的长度
                high = mid - 1;
            }
        }

        // 输出结果
        if (bestLen == 0) {
            cout << "none\n";
        } else {
            cout << bestLen << " " << bestPos << "\n";
        }
    }

    return 0;
}
