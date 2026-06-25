// Almost Palindrome
// UVa ID: 12656
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseNo = 0, k;
    string line;
    while (cin >> k) {
        getline(cin, line);                     // 消耗掉 k 后的换行符
        getline(cin, line);                     // 读取原字符串（可能含空格）

        vector<char> letters;                   // 小写字母序列
        vector<int> pos;                        // 每个字母在原串中的位置（0‑based）
        for (int i = 0; i < (int)line.size(); ++i)
            if (isalpha(line[i])) {
                letters.push_back(tolower(line[i]));
                pos.push_back(i);
            }

        int m = letters.size();
        vector<vector<int>> dp(m, vector<int>(m, 0));

        // 按长度递增计算 dp[l][r]（差异位置总数）
        for (int len = 1; len <= m; ++len)
            for (int l = 0; l + len - 1 < m; ++l) {
                int r = l + len - 1;
                if (len == 1) dp[l][r] = 0;
                else {
                    int inner = (len == 2) ? 0 : dp[l + 1][r - 1];
                    dp[l][r] = inner + (letters[l] != letters[r] ? 2 : 0);
                }
            }

        int bestLen = 0, bestStart = INT_MAX;
        int limit = 2 * k;
        for (int l = 0; l < m; ++l)
            for (int r = l; r < m; ++r)
                if (dp[l][r] <= limit) {
                    int curLen = pos[r] - pos[l] + 1;       // 原串中该子串的实际长度
                    int curStart = pos[l] + 1;              // 起始位置（1‑based）
                    if (curLen > bestLen || (curLen == bestLen && curStart < bestStart)) {
                        bestLen = curLen;
                        bestStart = curStart;
                    }
                }

        cout << "Case " << ++caseNo << ": " << bestLen << " " << bestStart << "\n";
    }
    return 0;
}
