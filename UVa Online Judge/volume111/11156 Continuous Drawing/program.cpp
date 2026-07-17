// Continuous Drawing
// UVa ID: 11156
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

bool onSegment(const Point& p, const Point& a, const Point& b) {
    long long cross = 1LL * (p.x - a.x) * (b.y - a.y) - 1LL * (p.y - a.y) * (b.x - a.x);
    if (cross != 0) return false;
    long long dot = 1LL * (p.x - a.x) * (b.x - a.x) + 1LL * (p.y - a.y) * (b.y - a.y);
    long long len2 = 1LL * (b.x - a.x) * (b.x - a.x) + 1LL * (b.y - a.y) * (b.y - a.y);
    return 0 <= dot && dot <= len2;
}

double distPoint(const Point& a, const Point& b) {
    return sqrt(1.0 * (a.x - b.x) * (a.x - b.x) + 1.0 * (a.y - b.y) * (a.y - b.y));
}

Point parsePoint(const string& s) {
    int x = s[1] - '0';
    int y = s[0] - 'A' + 1;
    return {x, y};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        vector<pair<Point, Point>> segs;
        for (int i = 0; i < N; ++i) {
            string p1s, p2s;
            cin >> p1s >> p2s;
            Point p1 = parsePoint(p1s);
            Point p2 = parsePoint(p2s);
            segs.push_back({p1, p2});
        }
        map<pair<int, int>, int> id;
        auto getIdx = [&](const Point& p) -> int {
            pair<int, int> key = {p.x, p.y};
            if (id.count(key)) return id[key];
            int idx = (int)id.size();
            id[key] = idx;
            return idx;
        };
        vector<tuple<int, int, double>> edges;
        vector<int> deg;
        double totalLen = 0.0;
        for (auto& seg : segs) {
            Point a = seg.first, b = seg.second;
            vector<Point> pts;
            for (int x = 1; x <= 5; ++x)
                for (int y = 1; y <= 5; ++y) {
                    Point p{x, y};
                    if (onSegment(p, a, b)) pts.push_back(p);
                }
            auto distSq = [&](const Point& p) -> long long {
                long long dx = p.x - a.x, dy = p.y - a.y;
                return dx * dx + dy * dy;
            };
            sort(pts.begin(), pts.end(), [&](const Point& p, const Point& q) {
                return distSq(p) < distSq(q);
            });
            for (size_t k = 0; k + 1 < pts.size(); ++k) {
                Point p = pts[k], q = pts[k + 1];
                int u = getIdx(p), v = getIdx(q);
                double w = distPoint(p, q);
                edges.emplace_back(u, v, w);
                totalLen += w;
                if ((int)deg.size() <= u) deg.resize(u + 1, 0);
                if ((int)deg.size() <= v) deg.resize(v + 1, 0);
                deg[u]++, deg[v]++;
            }
        }
        int V = (int)id.size();
        if (V == 0) {
            cout << "Case " << tc << ": 0.00\n";
            continue;
        }
        // 连通性检查
        vector<vector<int>> adj(V);
        for (auto& e : edges) {
            int u = get<0>(e), v = get<1>(e);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool> vis(V, false);
        function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            for (int v : adj[u])
                if (!vis[v]) dfs(v);
        };
        dfs(0);
        bool connected = true;
        for (int i = 0; i < V; ++i)
            if (!vis[i]) { connected = false; break; }
        if (!connected) {
            cout << "Case " << tc << ": ~x(\n";
            continue;
        }
        // Floyd-Warshall算法求所有点对最短路径
        const double INF = 1e100;
        vector<vector<double>> dist(V, vector<double>(V, INF));
        for (int i = 0; i < V; ++i) dist[i][i] = 0.0;
        for (auto& e : edges) {
            int u = get<0>(e), v = get<1>(e);
            double w = get<2>(e);
            if (w < dist[u][v]) dist[u][v] = dist[v][u] = w;
        }
        for (int k = 0; k < V; ++k)
            for (int i = 0; i < V; ++i)
                for (int j = 0; j < V; ++j)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
        // 奇度顶点
        vector<int> odd;
        for (int i = 0; i < V; ++i)
            if (deg[i] % 2 == 1) odd.push_back(i);
        int m = (int)odd.size();
        double repeat = 0.0;
        if (m > 0) {
            // 奇度点之间的距离矩阵
            vector<vector<double>> d(m, vector<double>(m, 0.0));
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < m; ++j)
                    d[i][j] = dist[odd[i]][odd[j]];
            int fullMask = (1 << m) - 1;
            vector<double> dp(1 << m, INF);
            dp[0] = 0.0;
            for (int mask = 1; mask <= fullMask; ++mask) {
                if (__builtin_popcount((unsigned)mask) % 2) continue;
                int p = -1;
                for (int i = 0; i < m; ++i)
                    if (mask & (1 << i)) { p = i; break; }
                for (int q = p + 1; q < m; ++q) {
                    if (!(mask & (1 << q))) continue;
                    int prev = mask ^ (1 << p) ^ (1 << q);
                    dp[mask] = min(dp[mask], dp[prev] + d[p][q]);
                }
            }
            double best = INF;
            for (int i = 0; i < m; ++i)
                for (int j = i + 1; j < m; ++j) {
                    int sub = fullMask ^ (1 << i) ^ (1 << j);
                    best = min(best, dp[sub]);
                }
            repeat = best;
        }
        double ans = totalLen + repeat;
        cout << "Case " << tc << ": " << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
