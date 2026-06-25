// Flight Control
// UVa ID: 1408
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.260s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, caseNo = 1;
    while (cin >> N >> M && (N || M)) {
        vector<vector<int>> val(N, vector<int>(M));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                cin >> val[i][j];

        // 三进制幂
        vector<int> pow3(M + 1, 1);
        for (int i = 1; i <= M; ++i) pow3[i] = pow3[i - 1] * 3;
        int totalVert = pow3[M];
        int totalState = totalVert * 3; // vert * 3 + horiz (0,1,2)

        vector<int> dp(totalState, INF), ndp(totalState, INF);
        dp[0] = 0;

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                fill(ndp.begin(), ndp.end(), INF);
                int v = val[i][j];

                for (int s = 0; s < totalState; ++s) {
                    if (dp[s] >= INF) continue;
                    int vert = s / 3;
                    int horiz = s % 3;
                    int up = (vert / pow3[j]) % 3;

                    if (v <= 0) {
                        if (horiz == 0 && up == 0) {
                            int ns = vert * 3;
                            ndp[ns] = min(ndp[ns], dp[s]);
                        }
                        continue;
                    }

                    // 1. 有左插头
                    if (horiz != 0) {
                        if (up != 0) continue;
                        bool can = false;
                        if (j > 0) {
                            if (horiz == 1 && v > val[i][j-1]) can = true;
                            if (horiz == 2 && v < val[i][j-1]) can = true;
                        }
                        if (!can) continue;

                        // 结束
                        {
                            int ns = vert * 3;
                            ndp[ns] = min(ndp[ns], dp[s]);
                        }
                        // 延续
                        if (j + 1 < M) {
                            int ns = vert * 3 + horiz;
                            ndp[ns] = min(ndp[ns], dp[s]);
                        }
                        continue;
                    }

                    // 2. 有上插头
                    if (up != 0) {
                        if (horiz != 0) continue;
                        bool can = false;
                        if (i > 0) {
                            if (up == 1 && v > val[i-1][j]) can = true;
                            if (up == 2 && v < val[i-1][j]) can = true;
                        }
                        if (!can) continue;

                        // 结束
                        {
                            int newVert = vert - up * pow3[j];
                            int ns = newVert * 3;
                            ndp[ns] = min(ndp[ns], dp[s]);
                        }
                        // 延续
                        if (i + 1 < N) {
                            int ns = vert * 3;
                            ndp[ns] = min(ndp[ns], dp[s]);
                        }
                        continue;
                    }

                    // 3. 无左无上
                    // 3a. 单独一段
                    {
                        int ns = vert * 3;
                        ndp[ns] = min(ndp[ns], dp[s] + 1);
                    }
                    // 3b. 开始水平段
                    if (j + 1 < M) {
                        for (int dir = 1; dir <= 2; ++dir) {
                            int ns = vert * 3 + dir;
                            ndp[ns] = min(ndp[ns], dp[s] + 1);
                        }
                    }
                    // 3c. 开始垂直段
                    if (i + 1 < N) {
                        for (int dir = 1; dir <= 2; ++dir) {
                            int newVert = vert + dir * pow3[j];
                            int ns = newVert * 3;
                            ndp[ns] = min(ndp[ns], dp[s] + 1);
                        }
                    }
                }
                dp.swap(ndp);
            }
        }

        cout << "Case " << caseNo++ << ": " << dp[0] << '\n';
    }
    return 0;
}
