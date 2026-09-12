#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m, s;
        cin >> n >> m >> s;
        vector<vector<pair<int, int>>> graph(n);
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges[i] = {u, v, w};
            graph[u].push_back({v, w});
            graph[v].push_back({u, w});
        }
        const double inf = 1e100;
        vector<double> dis(n, inf);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> que;
        dis[s] = 0;
        que.push({0, s});
        while (!que.empty()) {
            double curDis = que.top().first;
            int u = que.top().second;
            que.pop();
            if (curDis != dis[u]) continue;
            for (auto item : graph[u]) {
                int v = item.first, w = item.second;
                if (dis[v] > curDis + w) {
                    dis[v] = curDis + w;
                    que.push({dis[v], v});
                }
            }
        }
        bool ok = true;
        for (int i = 0; i < n; i++)
            if (dis[i] == inf) ok = false;
        if (!ok) {
            cout << "Sorry Amoo, your domino does not complete!\n";
            continue;
        }
        double ans = 0;
        for (auto edge : edges) {
            double a = dis[edge.u], b = dis[edge.v], w = edge.w;
            if (fabs(a - b) >= w) ans = max(ans, min(a, b) + w);
            else ans = max(ans, (a + b + w) / 2.0);
        }
        cout << fixed << setprecision(2) << ans << '\n';
    }
    return 0;
}
