// Repairing a Road
// UVa ID: 11883
// Verdict: Accepted
// Submission Date: 2026-06-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double INF = 1e18;

struct Edge {
    int u, v;
    double w, a;
};

double calc(double distU, double w, double a, double distC) {
    if (a == 1.0) return distU + w + distC; // 修路无意义，t=0
    double lnA = log(a);
    double t0 = log(w * lnA) / lnA;          // 驻点，可能为负
    double tOpt = max(distU, t0);            // 最优修路时间
    return max(distU, tOpt) + w * pow(a, -tOpt) + distC;
}

int main() {
    int C, R;
    while (cin >> C >> R && (C || R)) {
        vector<vector<double>> dist(C, vector<double>(C, INF));
        for (int i = 0; i < C; ++i) dist[i][i] = 0.0;

        vector<Edge> edges;
        for (int i = 0; i < R; ++i) {
            int x, y;
            double v, a;
            cin >> x >> y >> v >> a;
            --x; --y;
            edges.push_back({x, y, v, a});
            dist[x][y] = min(dist[x][y], v);
            dist[y][x] = min(dist[y][x], v);
        }

        // Floyd-Warshall 计算全源最短路
        for (int k = 0; k < C; ++k)
            for (int i = 0; i < C; ++i)
                for (int j = 0; j < C; ++j)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

        vector<double> d1 = dist[0];          // 从 1 出发
        vector<double> dC = dist[C - 1];      // 从 C 出发（无向图）

        double ans = INF;
        for (const auto &e : edges) {
            // 方向 u -> v
            double val1 = calc(d1[e.u], e.w, e.a, dC[e.v]);
            ans = min(ans, val1);
            // 方向 v -> u
            double val2 = calc(d1[e.v], e.w, e.a, dC[e.u]);
            ans = min(ans, val2);
        }

        cout << fixed << setprecision(3) << ans << '\n';
    }
    return 0;
}
