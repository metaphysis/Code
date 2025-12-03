// Kids in a Grid
// UVa ID: 10949
// Verdict: Accepted
// Submission Date: 2025-12-02
// UVa Run Time: 1.580s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 20005;
int dp[2][MAX_LEN];  // 滚动数组用于 LCS 长度计算

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    string dummy;
    getline(cin, dummy);  // 读取第一行末尾的换行符
    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        int h, w;
        cin >> h >> w;
        getline(cin, dummy);  // 读取 h w 后的换行符
        vector<string> grid(h);
        for (int i = 0; i < h; ++i) getline(cin, grid[i]);

        // 处理第一个孩子
        int n, x0, y0;
        cin >> n >> x0 >> y0;
        getline(cin, dummy);  // 读取 n x0 y0 后的换行符
        string movesA;
        getline(cin, movesA);
        string sA = "";
        int x = x0 - 1, y = y0 - 1;
        sA += grid[x][y];
        for (char ch : movesA) {
            if (ch == 'N') x--;
            else if (ch == 'S') x++;
            else if (ch == 'E') y++;
            else if (ch == 'W') y--;
            sA += grid[x][y];
        }

        // 处理第二个孩子
        int m, x1, y1;
        cin >> m >> x1 >> y1;
        getline(cin, dummy);  // 读取 m x1 y1 后的换行符
        string movesB;
        getline(cin, movesB);
        string sB = "";
        x = x1 - 1, y = y1 - 1;
        sB += grid[x][y];
        for (char ch : movesB) {
            if (ch == 'N') x--;
            else if (ch == 'S') x++;
            else if (ch == 'E') y++;
            else if (ch == 'W') y--;
            sB += grid[x][y];
        }

        int lenA = sA.size(), lenB = sB.size();

        // 初始化第一行
        for (int j = 0; j <= lenB; ++j) dp[0][j] = 0;

        // 滚动数组计算 LCS 长度
        for (int i = 1; i <= lenA; ++i) {
            int cur = i % 2, prev = 1 - cur;
            dp[cur][0] = 0;
            for (int j = 1; j <= lenB; ++j) {
                if (sA[i - 1] == sB[j - 1])
                    dp[cur][j] = dp[prev][j - 1] + 1;
                else
                    dp[cur][j] = max(dp[prev][j], dp[cur][j - 1]);
            }
        }

        int lcsLen = dp[lenA % 2][lenB];
        int deleteA = lenA - lcsLen;
        int deleteB = lenB - lcsLen;

        cout << "Case " << caseNo << ": " << deleteA << " " << deleteB << "\n";
    }
    return 0;
}
