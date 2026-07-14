// Peach Blossom Spring
// UVa ID: 1496
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.100s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m, k;
        scanf("%d%d%d", &n, &m, &k);
        vector<vector<int>> dist(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
        }
        // Floyd-Warshall 求全源最短路
        for (int mid = 0; mid < n; ++mid)
            for (int i = 0; i < n; ++i) {
                if (dist[i][mid] >= INF) continue;
                for (int j = 0; j < n; ++j)
                    if (dist[mid][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][mid] + dist[mid][j]);
            }

        int totalTerminals = 2 * k;
        vector<int> termNode(totalTerminals);
        for (int i = 0; i < k; ++i) {
            termNode[i] = i;                     // 家庭 0..k-1
            termNode[k + i] = n - k + i;        // 藏身处 n-k .. n-1
        }

        int fullTermMask = (1 << totalTerminals) - 1;
        vector<vector<int>> dp(1 << totalTerminals, vector<int>(n, INF));
        // 初始化单个终端
        for (int i = 0; i < totalTerminals; ++i)
            dp[1 << i][termNode[i]] = 0;

        // 斯坦纳树 DP
        for (int mask = 1; mask <= fullTermMask; ++mask) {
            // 合并子集
            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
                int other = mask ^ sub;
                if (sub > other) continue; // 避免重复
                for (int u = 0; u < n; ++u) {
                    if (dp[sub][u] < INF && dp[other][u] < INF)
                        dp[mask][u] = min(dp[mask][u], dp[sub][u] + dp[other][u]);
                }
            }
            // 用全源最短路松弛，相当于取一次 min-plus 闭包
            vector<int> tmp(n, INF);
            for (int u = 0; u < n; ++u) {
                if (dp[mask][u] >= INF) continue;
                for (int v = 0; v < n; ++v)
                    if (dist[u][v] < INF)
                        tmp[v] = min(tmp[v], dp[mask][u] + dist[u][v]);
            }
            for (int v = 0; v < n; ++v)
                dp[mask][v] = min(dp[mask][v], tmp[v]);
        }

        // steiner[mask] 表示终端集合 mask 整体连通的最小成本
        vector<int> steiner(1 << totalTerminals, INF);
        for (int mask = 0; mask <= fullTermMask; ++mask) {
            int best = INF;
            for (int u = 0; u < n; ++u) best = min(best, dp[mask][u]);
            steiner[mask] = best;
        }

        int answer = INF;
        vector<int> perm(k);
        for (int i = 0; i < k; ++i) perm[i] = i;

        // 枚举所有匹配（家庭 i 匹配藏身处 perm[i]）
        do {
            // 预处理每个 pairMask 对应的终端掩码
            int pairCnt = 1 << k;
            vector<int> termMaskOfPair(pairCnt, 0);
            for (int pm = 0; pm < pairCnt; ++pm) {
                int fmask = pm; // 家庭位就是 pm 自身
                int smask = 0;
                for (int i = 0; i < k; ++i)
                    if (pm & (1 << i))
                        smask |= (1 << (k + perm[i]));
                termMaskOfPair[pm] = fmask | smask;
            }

            // 森林 DP：forest[mask] 表示满足这些对的最小总成本（允许分成多个分量）
            vector<int> forest(pairCnt, INF);
            forest[0] = 0;
            for (int mask = 1; mask < pairCnt; ++mask) {
                // 先假设整体连通
                forest[mask] = steiner[termMaskOfPair[mask]];
                // 尝试分割
                for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
                    int other = mask ^ sub;
                    if (forest[sub] < INF && forest[other] < INF)
                        forest[mask] = min(forest[mask], forest[sub] + forest[other]);
                }
            }
            answer = min(answer, forest[pairCnt - 1]);
        } while (next_permutation(perm.begin(), perm.end()));

        if (answer >= INF) puts("No solution");
        else printf("%d\n", answer);
    }
    return 0;
}
