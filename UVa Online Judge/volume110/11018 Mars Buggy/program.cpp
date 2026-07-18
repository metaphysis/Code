// Mars Buggy
// UVa ID: 11018
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 地点结构
struct Point {
    string code;
    double lat, lon;
};

const long long INF = 4e18;
const double R_MARS = 3390.0;

// 半正矢距离，返回公里数（浮点）
double haversine(double x) { 
    double s = sin(x / 2.0);
    return s * s;
}

double calcDistanceKm(const Point& a, const Point& b) {
    double dlat = b.lat - a.lat;
    double dlon = b.lon - a.lon;
    double h = haversine(dlat) + cos(a.lat) * cos(b.lat) * haversine(dlon);
    double c = 2.0 * atan2(sqrt(h), sqrt(1.0 - h));
    return R_MARS * c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    int scenarioNo = 1;
    while (cin >> n) {
        if (n == 0) {
            int m;
            cin >> m;
            break;
        }
        vector<Point> points(n);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].code >> points[i].lat >> points[i].lon;
        }
        vector<vector<long long>> dist(n, vector<long long>(n));
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j) {
                long long d = llround(calcDistanceKm(points[i], points[j]));
                dist[i][j] = dist[j][i] = d;
            }
        for (int i = 0; i < n; ++i) dist[i][i] = 0;
        int m;
        cin >> m;
        if (scenarioNo > 1) cout << "\n";
        cout << "Scenario " << scenarioNo << ":\n";
        cout << string(30, '-') << "\n";
        for (int req = 0; req < m; ++req) {
            string startCode, endCode;
            long long range;
            cin >> startCode >> endCode >> range;
            // 找出起点和终点的索引
            int s = -1, t = -1;
            for (int i = 0; i < n; ++i) {
                if (points[i].code == startCode) s = i;
                if (points[i].code == endCode) t = i;
            }
            // --- 1. 计算最小瓶颈（最小所需续航）---
            vector<long long> bottleneck(n, INF);
            vector<bool> vis(n, false);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            bottleneck[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [cur, u] = pq.top(); pq.pop();
                if (vis[u]) continue;
                vis[u] = true;
                for (int v = 0; v < n; ++v) {
                    if (v == u) continue;
                    long long w = dist[u][v];
                    long long nxt = max(bottleneck[u], w);
                    if (nxt < bottleneck[v]) {
                        bottleneck[v] = nxt;
                        pq.push({nxt, v});
                    }
                }
            }
            long long minReq = bottleneck[t];
            // 输出标题
            cout << "From " << startCode << " to " << endCode << " with range " << range << " km:\n";
            if (minReq > range) {
                // 不可达
                cout << "No route for this range, minimum required range is " << minReq << " km.\n";
            } else {
                // --- 2. 在边权 <= range 的子图上求最短路 ---
                vector<long long> dis(n, INF);
                vector<int> pre(n, -1);
                vector<bool> used(n, false);
                priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq2;
                dis[s] = 0;
                pq2.push({0, s});
                while (!pq2.empty()) {
                    auto [d, u] = pq2.top(); pq2.pop();
                    if (used[u]) continue;
                    used[u] = true;
                    for (int v = 0; v < n; ++v) {
                        if (v == u) continue;
                        long long w = dist[u][v];
                        if (w > range) continue; // 不可用
                        if (d + w < dis[v]) {
                            dis[v] = d + w;
                            pre[v] = u;
                            pq2.push({dis[v], v});
                        }
                    }
                }
                // 重建路径
                vector<int> path;
                for (int v = t; v != -1; v = pre[v]) path.push_back(v);
                reverse(path.begin(), path.end());
                // 输出路径及累计距离
                long long cur = 0;
                for (size_t i = 0; i < path.size(); ++i) {
                    int u = path[i];
                    cout << points[u].code << " at " << cur << " km.\n";
                    if (i + 1 < path.size()) {
                        int v = path[i + 1];
                        cur += dist[u][v];
                    }
                }
            }
            // 每个请求后输出连字符
            cout << string(30, '-') << "\n";
        }
        scenarioNo++;
    }
    return 0;
}
