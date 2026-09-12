#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, cost, type;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, s, d, p, m, a, b, c;
        cin >> n >> s >> d >> p >> m;
        vector<vector<Edge>> g(n);
        while (m--) {
            cin >> a >> b >> c;
            g[a].push_back({b, c, 0});
            g[b].push_back({a, c, 0});
        }
        cin >> m;
        while (m--) {
            cin >> a >> b >> c;
            g[a].push_back({b, c, 1});
            g[b].push_back({a, c, 1});
        }
        const long long inf = (1LL << 60);
        vector<vector<long long>> dis(p + 1, vector<long long>(n, inf));
        using Node = tuple<long long, int, int>;
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        dis[0][s] = 0;
        pq.push({0, s, 0});
        while (!pq.empty()) {
            long long cur;
            int u, used;
            tie(cur, u, used) = pq.top();
            pq.pop();
            if (cur != dis[used][u]) continue;
            for (const Edge &e : g[u]) {
                int nextUsed = used + e.type;
                if (nextUsed > p) continue;
                long long nextDis = cur + e.cost;
                if (nextDis < dis[nextUsed][e.to]) {
                    dis[nextUsed][e.to] = nextDis;
                    pq.push({nextDis, e.to, nextUsed});
                }
            }
        }
        long long ans = inf;
        for (int i = 0; i <= p; i++) ans = min(ans, dis[i][d]);
        cout << ans << '\n';
    }
    return 0;
}
