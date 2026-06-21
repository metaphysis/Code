// Foot Notes
// UVa ID: 12209
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N, S, W;
        scanf("%d%d%d", &N, &S, &W);
        vector<int> lineWords[N + 1];          // 每行出现的关键词编号
        for (int id = 1; id <= W; ++id) {
            int K;
            scanf("%d", &K);
            for (int t = 0; t < K; ++t) {
                int x;
                scanf("%d", &x);
                lineWords[x].push_back(id);
            }
        }

        // 预处理 foot[l][r]：区间[l,r]内不同关键词个数
        vector<vector<int>> foot(N + 1, vector<int>(N + 1, 0));
        for (int l = 1; l <= N; ++l) {
            vector<bool> seen(W + 1, false);
            int cur = 0;
            for (int r = l; r <= N; ++r) {
                for (int id : lineWords[r])
                    if (!seen[id]) {
                        seen[id] = true;
                        ++cur;
                    }
                foot[l][r] = cur;
            }
        }

        const int INF = 1e9;
        vector<int> dp(N + 1, INF);
        dp[0] = 0;
        for (int i = 1; i <= N; ++i)
            for (int j = max(0, i - S); j < i; ++j) {
                int len = i - j;
                int f = foot[j + 1][i];
                if (len + f <= S)
                    dp[i] = min(dp[i], dp[j] + f);
            }

        if (dp[N] >= INF)
            printf("Case %d: -1\n", tc);
        else
            printf("Case %d: %d\n", tc, dp[N]);
    }
    return 0;
}
