// Travel Company
// UVa ID: 11874
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.11s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
    long long w;
};

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N, R, P;
        scanf("%d %d %d", &N, &R, &P);
        vector<Edge> edges;
        edges.reserve(R);
        for (int i = 0; i < R; ++i) {
            int A, B, I, E;
            scanf("%d %d %d %d", &A, &B, &I, &E);
            long long w = (long long)I - (long long)P * E;
            edges.push_back({A, B, w});
        }

        // 检测正环
        vector<long long> dist(N, 0);
        bool hasPositiveCycle = false;
        for (int i = 0; i < N; ++i) {
            bool updated = false;
            for (const auto &e : edges) {
                if (dist[e.v] < dist[e.u] + e.w) {
                    dist[e.v] = dist[e.u] + e.w;
                    updated = true;
                }
            }
            if (i == N - 1 && updated) {
                hasPositiveCycle = true;
                break;
            }
        }

        printf("Case %d: %s\n", caseNo, hasPositiveCycle ? "YES" : "NO");

        // 跳过测试用例后的空行（scanf自动跳过空白，无影响）
    }
    return 0;
}
