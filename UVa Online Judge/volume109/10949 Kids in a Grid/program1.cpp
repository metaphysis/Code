// Kids in a Grid
// UVa ID: 10949
// Verdict: Accepted
// Submission Date: 2025-12-02
// UVa Run Time: 0.910s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_LEN = 20005;
const int CHAR_SET = 128;  // ASCII 范围

// Hunt-Szymanski 算法求 LCS
int huntSzymanskiLCS(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    if (n > m) return huntSzymanskiLCS(b, a);  // 确保 n <= m
    
    // 为每个字符记录在 b 中出现的所有位置（逆序）
    vector<vector<int>> pos(CHAR_SET);
    for (int j = m - 1; j >= 0; --j) {
        pos[(unsigned char)b[j]].push_back(j);
    }
    
    // dp[i] 表示长度为 i 的 LCS 的最后一个字符在 b 中的最小位置
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = -1;
    
    for (int i = 0; i < n; ++i) {
        unsigned char c = a[i];
        // 对每个字符在 b 中的位置进行二分查找
        for (int j : pos[c]) {
            // 在 dp 中找到第一个 >= j 的位置
            int k = upper_bound(dp.begin(), dp.end(), j - 1) - dp.begin();
            if (dp[k] > j) dp[k] = j;
        }
    }
    
    // 找到最大的 i 使得 dp[i] < INF
    for (int i = n; i >= 0; --i) 
        if (dp[i] != INT_MAX) return i;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    string dummy;
    getline(cin, dummy);
    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        int h, w;
        cin >> h >> w;
        getline(cin, dummy);
        vector<string> grid(h);
        for (int i = 0; i < h; ++i) getline(cin, grid[i]);
        
        // 处理第一个孩子
        int n, x0, y0;
        cin >> n >> x0 >> y0;
        getline(cin, dummy);
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
        getline(cin, dummy);
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
        
        int lcsLen = huntSzymanskiLCS(sA, sB);
        int deleteA = sA.size() - lcsLen;
        int deleteB = sB.size() - lcsLen;
        
        cout << "Case " << caseNo << ": " << deleteA << " " << deleteB << "\n";
    }
    return 0;
}
