// Help Little Laura
// UVa ID: 1659
// Verdict: Accepted
// Submission Date: 2026-01-19
// UVa Run Time: 0.250s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
const int MAXN = 110, MAXE = 2000, INF = 1e9;
const double EPS = 1e-8;
struct Edge { int to, next, cap; double cost; } edge[MAXE * 2];
int head[MAXN], cnt = 0, source, sink;
double result;
void reset(int s, int t) {
    cnt = 0; memset(head, -1, sizeof head); result = 0.0; source = s; sink = t;
}
void addArc(int from, int to, int capacity, double cost) {
    edge[cnt] = {to, head[from], capacity, cost}; head[from] = cnt++;
    edge[cnt] = {from, head[to], 0, -cost}; head[to] = cnt++;
}
bool spfa() {
    vector<double> dist(MAXN, 2.0 * INF); vector<int> flow(MAXN, 0), parent(MAXN, -1);
    vector<bool> in(MAXN, false); queue<int> q;
    dist[source] = 0.0; flow[source] = INF; q.push(source); in[source] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop(); in[u] = false;
        for (int e = head[u]; ~e; e = edge[e].next) {
            int v = edge[e].to;
            if (edge[e].cap > 0 && dist[v] > dist[u] + edge[e].cost + EPS) {
                dist[v] = dist[u] + edge[e].cost; flow[v] = min(flow[u], edge[e].cap);
                parent[v] = e;
                if (!in[v]) { q.push(v); in[v] = true; }
            }
        }
    }
    if (dist[sink] > INF || parent[sink] == -1) return false;
    int f = flow[sink]; result += f * dist[sink];
    for (int node = sink; node != source; node = edge[parent[node] ^ 1].to) {
        int e = parent[node]; edge[e].cap -= f; edge[e ^ 1].cap += f;
    }
    return true;
}
double getD(int x1, int y1, int x2, int y2) {
    double dx = x1 - x2, dy = y1 - y2; return sqrt(dx * dx + dy * dy);
}
int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int n, X, Y, testCase = 0;
    while (scanf("%d", &n) == 1 && n) {
        scanf("%d %d", &X, &Y);
        vector<int> px(n + 1), py(n + 1); vector<vector<int>> g(n + 1);
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &px[i], &py[i]);
            int v; while (scanf("%d", &v) && v != 0) g[i].push_back(v);
        }
        reset(n + 1, n + 2); vector<int> db(n + 1, 0);
        for (int i = 1; i <= n; i++) for (int j : g[i]) {
            double distance = getD(px[i], py[i], px[j], py[j]);
            double profit = distance * X - Y;
            if (profit > 0) {
                addArc(j, i, 1, profit); result -= profit; db[i]--; db[j]++;
            } else addArc(i, j, 1, -profit);
        }
        for (int i = 1; i <= n; i++) {
            if (db[i] > 0) addArc(source, i, db[i], 0.0);
            else if (db[i] < 0) addArc(i, sink, -db[i], 0.0);
        }
        while (spfa()) {}
        result = -result; if (fabs(result) < EPS) result = 0.0;
        printf("Case %d: %.2f\n", ++testCase, result);
    }
    return 0;
}
