// Flight Control
// UVa ID: 1408
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.270s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// 计算一行中，在指定掩码（垂直占用）下剩余正数格子所需的最少水平单调段数
int horizontalCost(const vector<int>& row, int mask) {
    vector<int> seg;
    int cost = 0;
    int M = row.size();
    for (int c = 0; c < M; ++c) {
        if ((mask & (1 << c)) || row[c] <= 0) {
            if (!seg.empty()) {
                int n = seg.size();
                vector<int> dp(n + 1, INF);
                dp[n] = 0;
                for (int l = n - 1; l >= 0; --l)
                    for (int r = l; r < n; ++r) {
                        bool inc = true, dec = true;
                        for (int k = l + 1; k <= r; ++k) {
                            if (seg[k] <= seg[k - 1]) inc = false;
                            if (seg[k] >= seg[k - 1]) dec = false;
                        }
                        if (inc || dec)
                            dp[l] = min(dp[l], 1 + dp[r + 1]);
                    }
                cost += dp[0];
                seg.clear();
            }
        } else {
            seg.push_back(row[c]);
        }
    }
    if (!seg.empty()) {
        int n = seg.size();
        vector<int> dp(n + 1, INF);
        dp[n] = 0;
        for (int l = n - 1; l >= 0; --l)
            for (int r = l; r < n; ++r) {
                bool inc = true, dec = true;
                for (int k = l + 1; k <= r; ++k) {
                    if (seg[k] <= seg[k - 1]) inc = false;
                    if (seg[k] >= seg[k - 1]) dec = false;
                }
                if (inc || dec)
                    dp[l] = min(dp[l], 1 + dp[r + 1]);
            }
        cost += dp[0];
    }
    return cost;
}

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
        int totalState = pow3[M];

        // 预处理水平段代价
        vector<vector<int>> hcost(N, vector<int>(1 << M));
        for (int i = 0; i < N; ++i)
            for (int mask = 0; mask < (1 << M); ++mask)
                hcost[i][mask] = horizontalCost(val[i], mask);

        vector<int> dp(totalState, INF), ndp(totalState, INF);

        // 初始化第 0 行
        for (int s = 0; s < totalState; ++s) {
            int mask = 0, cnt = 0;
            bool ok = true;
            for (int c = 0; c < M; ++c) {
                int digit = (s / pow3[c]) % 3;
                if (digit) {
                    mask |= (1 << c);
                    ++cnt;
                    if (val[0][c] <= 0) ok = false;
                }
            }
            if (ok) dp[s] = cnt + hcost[0][mask];
        }

        // 逐行转移
        for (int i = 1; i < N; ++i) {
            fill(ndp.begin(), ndp.end(), INF);

            for (int col = 0; col < M; ++col) {
                vector<int> tmp(totalState, INF);
                int prevVal = val[i - 1][col], curVal = val[i][col];

                for (int s = 0; s < totalState; ++s) {
                    if (dp[s] >= INF) continue;
                    int prevDigit = (s / pow3[col]) % 3;

                    for (int curDigit = 0; curDigit < 3; ++curDigit) {
                        if (curDigit && curVal <= 0) continue;

                        int add;
                        if (curDigit == 0) add = 0;
                        else if (prevDigit == 0) add = 1;
                        else if (prevDigit == curDigit) {
                            if ((curDigit == 1 && curVal > prevVal) ||
                                (curDigit == 2 && curVal < prevVal))
                                add = 0;
                            else add = 1;
                        } else add = 1;

                        int ns = s - prevDigit * pow3[col] + curDigit * pow3[col];
                        tmp[ns] = min(tmp[ns], dp[s] + add);
                    }
                }
                dp.swap(tmp);
            }

            // 加上本行水平段代价
            for (int s = 0; s < totalState; ++s) {
                if (dp[s] < INF) {
                    int mask = 0;
                    for (int c = 0; c < M; ++c)
                        if ((s / pow3[c]) % 3) mask |= (1 << c);
                    dp[s] += hcost[i][mask];
                }
            }
        }

        int ans = INF;
        for (int v : dp) ans = min(ans, v);
        cout << "Case " << caseNo++ << ": " << ans << '\n';
    }
    return 0;
}
