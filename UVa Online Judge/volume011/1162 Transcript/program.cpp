#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, top, srcLen, dstLen, i, j;
    while (cin >> n) {
        string line;
        getline(cin, line);
        vector<string> keyboard(n);
        for (i = 0; i < n; i++)
            getline(cin, keyboard[i]);
        m = keyboard[0].size();
        top = max(n, m);
        vector<vector<int>> score(256, vector<int>(256, -1000000000));
        vector<pair<int, int>> pos(256, {-1, -1});
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                pos[(unsigned char)keyboard[i][j]] = {i, j};
        for (i = 0; i < n; i++)
            for (j = 0; j < m; j++)
                for (int p = 0; p < n; p++)
                    for (int q = 0; q < m; q++) {
                        int dis = max(abs(i - p), abs(j - q));
                        score[(unsigned char)keyboard[i][j]][(unsigned char)keyboard[p][q]] = top - dis;
                    }
        string src, dst;
        getline(cin, src);
        getline(cin, dst);
        srcLen = src.size();
        dstLen = dst.size();
        const int negInf = -1000000000;
        vector<vector<int>> dp(srcLen + 1, vector<int>(dstLen + 1, negInf));
        dp[0][0] = 0;
        for (i = 1; i <= srcLen; i++)
            dp[i][0] = dp[i - 1][0] - top;
        for (i = 1; i <= srcLen; i++)
            for (j = 1; j <= dstLen; j++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] - top);
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + score[(unsigned char)src[i - 1]][(unsigned char)dst[j - 1]]);
            }
        cout << dp[srcLen][dstLen] << '\n';
    }
    return 0;
}
