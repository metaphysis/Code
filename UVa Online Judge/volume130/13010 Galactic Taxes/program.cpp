// Galactic Taxes
// UVa ID: 13010
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.280s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;           // 最大节点数
const int MAXM = 10005;          // 最大边数
const double EPS = 1e-12;        // 精度
const double MINUTES = 1440;     // 一天的总分钟数

struct Edge {
    int to, a, b;                // 终点、斜率A、截距B
};

int n, m;                        // 节点数、边数
vector<Edge> graph[MAXN];       // 邻接表
double dist[MAXN];              // 最短路距离数组

// 检查给定时间t下，从源点到汇点的最短路径长度
double dijkstra(double t) {
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
    fill(dist, dist + n + 1, 1e18);
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        double d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d > dist[u]) continue;
        for (const Edge& e : graph[u]) {
            double w = e.a * t + e.b;    // 边权在时间t下的值
            if (dist[u] + w < dist[e.to]) {
                dist[e.to] = dist[u] + w;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist[n];
}

int main() {
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= n; i++) graph[i].clear();
        for (int i = 0; i < m; i++) {
            int u, v, a, b;
            scanf("%d %d %d %d", &u, &v, &a, &b);
            graph[u].push_back({v, a, b});
            graph[v].push_back({u, a, b});
        }
        // 三分法寻找最优时间点
        double left = 0, right = MINUTES;
        while (right - left > EPS) {
            double m1 = left + (right - left) / 3;
            double m2 = right - (right - left) / 3;
            if (dijkstra(m1) <= dijkstra(m2)) left = m1;
            else right = m2;
        }
        double answer = dijkstra((left + right) / 2);
        printf("%.5f\n", answer);
    }
    return 0;
}
