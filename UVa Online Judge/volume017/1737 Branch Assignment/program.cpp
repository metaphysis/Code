// Branch Assignment
// UVa ID: 1737
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 3.070s

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

struct Edge {
    int to;
    int len;
};

vector<vector<Edge>> adj, radj;

vector<ll> dijkstra(int src, const vector<vector<Edge>>& graph) {
    int n = (int)graph.size() - 1;
    vector<ll> dist(n + 1, INF);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        pair<ll, int> cur = pq.top();
        pq.pop();
        ll d = cur.first;
        int u = cur.second;
        if (d != dist[u]) continue;
        for (int i = 0; i < (int)graph[u].size(); ++i) {
            const Edge& e = graph[u][i];
            if (dist[e.to] > d + e.len) {
                dist[e.to] = d + e.len;
                pq.push({dist[e.to], e.to});
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, b, s, r;
    while (cin >> n >> b >> s >> r) {
        adj.assign(n + 1, {});
        radj.assign(n + 1, {});
        for (int i = 0; i < r; ++i) {
            int u, v;
            ll l;
            cin >> u >> v >> l;
            adj[u].push_back({v, (int)l});
            radj[v].push_back({u, (int)l});
        }

        int H = b + 1;
        vector<ll> distToH = dijkstra(H, radj);   // 反向图上H到各点 = 各点到H的最短路
        vector<ll> distFromH = dijkstra(H, adj);  // 原图上H到各点

        vector<ll> w(b + 1);
        for (int i = 1; i <= b; ++i) w[i] = distToH[i] + distFromH[i];

        sort(w.begin() + 1, w.end(), greater<ll>());

        vector<ll> pref(b + 1, 0);
        for (int i = 1; i <= b; ++i) pref[i] = pref[i - 1] + w[i];

        ll totalWeight = pref[b];

        if (s == 1) {
            cout << (b - 1) * totalWeight << '\n';
            continue;
        }
        if (s == b) {
            cout << 0 << '\n';
            continue;
        }

        vector<ll> prev(b + 1, INF), cur(b + 1, INF);

        // j = 1 时，一组包含前 i 个权重
        for (int i = 1; i <= b; ++i) prev[i] = (ll)i * pref[i];

        // 分治优化，计算当前层的 dp[i][j]
        function<void(int, int, int, int)> solve = [&](int l, int r, int optL, int optR) {
            if (l > r) return;
            int mid = (l + r) >> 1;
            ll bestVal = INF;
            int bestK = -1;
            int kL = max(optL, 1);
            int kR = min(optR, mid - 1);
            for (int k = kL; k <= kR; ++k) {
                if (prev[k] >= INF) continue;
                ll val = prev[k] + (ll)(mid - k) * (pref[mid] - pref[k]);
                if (val < bestVal) {
                    bestVal = val;
                    bestK = k;
                }
            }
            cur[mid] = bestVal;

            solve(l, mid - 1, optL, bestK);
            solve(mid + 1, r, bestK, optR);
        };

        for (int j = 2; j <= s; ++j) {
            fill(cur.begin(), cur.end(), INF);
            solve(j, b, j - 1, b - 1);
            swap(prev, cur);
        }

        ll ans = prev[b] - totalWeight;
        cout << ans << '\n';
    }

    return 0;
}
