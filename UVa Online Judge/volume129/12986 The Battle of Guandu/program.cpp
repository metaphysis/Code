#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; tc++) {
        int n, m;
        cin >> n >> m;
        vector<int> x(n), y(n), c(n), w(m + 1);
        for (int i = 0; i < n; i++)
            cin >> x[i];
        for (int i = 0; i < n; i++)
            cin >> y[i];
        for (int i = 0; i < n; i++)
            cin >> c[i];
        for (int i = 1; i <= m; i++)
            cin >> w[i];
        vector<vector<Edge>> graph(m + 1);
        for (int i = 0; i < n; i++)
            graph[y[i]].push_back({x[i], c[i]});
        const long long inf = LLONG_MAX / 4;
        vector<long long> dis(m + 1, inf);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
        for (int i = 1; i <= m; i++) {
            if (w[i] == 0) {
                dis[i] = 0;
                pq.push({0, i});
            }
        }
        while (!pq.empty()) {
            long long curDis = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (curDis != dis[u])
                continue;
            for (const Edge &edge : graph[u]) {
                long long nextDis = curDis + edge.cost;
                if (nextDis < dis[edge.to]) {
                    dis[edge.to] = nextDis;
                    pq.push({nextDis, edge.to});
                }
            }
        }
        long long ans = 0;
        bool ok = true;
        for (int i = 1; i <= m; i++) {
            if (w[i] == 2) {
                if (dis[i] == inf) {
                    ok = false;
                    break;
                }
                ans += dis[i];
            }
        }
        if (!ok)
            cout << "Case #" << tc << ": -1\n";
        else
            cout << "Case #" << tc << ": " << ans << '\n';
    }
    return 0;
}
