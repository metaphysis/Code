// Shopping Malls
// UVa ID: 12680
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int floor;
    double x, y, z;
};

double dist3D(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

vector<int> dijkstra(int src, int dst, const vector<vector<pair<int,double>>>& adj) {
    int n = adj.size();
    vector<double> d(n, 1e100);
    vector<int> pre(n, -1);
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<pair<double,int>>> pq;
    d[src] = 0.0;
    pq.push({0.0, src});
    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        double du = cur.first;
        int u = cur.second;
        if (du > d[u] + 1e-12) continue;
        if (u == dst) break;
        for (auto& e : adj[u]) {
            int v = e.first;
            double w = e.second;
            if (d[v] > d[u] + w + 1e-12) {
                d[v] = d[u] + w;
                pre[v] = u;
                pq.push({d[v], v});
            }
        }
    }
    vector<int> path;
    for (int v = dst; v != -1; v = pre[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    if (path.front() != src) path.clear(); // 理论上不会发生
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    bool firstCase = true;
    int N, M;
    while (cin >> N >> M) {
        vector<Point> pts(N);
        for (int i = 0; i < N; ++i) {
            int fl; double x, y;
            cin >> fl >> x >> y;
            pts[i] = {fl, x, y, fl * 5.0};
        }
        vector<vector<pair<int,double>>> adj(N);
        for (int i = 0; i < M; ++i) {
            int a, b; string type;
            cin >> a >> b >> type;
            double d = dist3D(pts[a], pts[b]);
            if (type == "walking" || type == "stairs") {
                adj[a].push_back({b, d});
                adj[b].push_back({a, d});
            } else if (type == "lift") {
                adj[a].push_back({b, 1.0});
                adj[b].push_back({a, 1.0});
            } else if (type == "escalator") {
                adj[a].push_back({b, 1.0});          // 正向（a→b）
                adj[b].push_back({a, d * 3.0});      // 反向（b→a）
            }
        }
        int Q; cin >> Q;
        if (!firstCase) cout << '\n';
        firstCase = false;
        while (Q--) {
            int s, t; cin >> s >> t;
            vector<int> path = dijkstra(s, t, adj);
            for (size_t i = 0; i < path.size(); ++i) {
                if (i) cout << ' ';
                cout << path[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
