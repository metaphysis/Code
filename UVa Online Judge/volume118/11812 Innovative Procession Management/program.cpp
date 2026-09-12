#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);

struct Edge {
    int u, v, w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n, m, s;
        cin >> n >> m >> s;
        vector<int> src(s), dis(n + 1), vis(n + 1), got(n + 1);
        for (int i = 0; i < s; i++) cin >> src[i];
        int tar;
        cin >> tar;
        vector<Edge> ed(m);
        vector<vector<int>> adj(n + 1), rev(n + 1);
        vector<bool> ban(m, false);
        for (int i = 0; i < m; i++) {
            cin >> ed[i].u >> ed[i].v >> ed[i].w;
            adj[ed[i].u].push_back(i);
            rev[ed[i].v].push_back(i);
        }
        cout << "Case " << cs << ":\n";
        bool any = false;
        while (true) {
            vector<long long> d(n + 1, inf);
            fill(vis.begin(), vis.end(), 0);
            d[tar] = 0;
            for (int i = 1; i <= n; i++) {
                int u = -1;
                for (int j = 1; j <= n; j++)
                    if (!vis[j] && (u == -1 || d[j] < d[u])) u = j;
                if (u == -1 || d[u] == inf) break;
                vis[u] = 1;
                for (int id : rev[u]) {
                    if (ban[id]) continue;
                    int v = ed[id].u;
                    if (d[v] > d[u] + ed[id].w) d[v] = d[u] + ed[id].w;
                }
            }
            long long best = inf;
            for (int x : src) best = min(best, d[x]);
            if (best == inf) break;
            vector<int> que;
            fill(got.begin(), got.end(), 0);
            for (int x : src)
                if (d[x] == best) {
                    got[x] = 1;
                    que.push_back(x);
                }
            vector<int> cut;
            for (int p = 0; p < (int)que.size(); p++) {
                int u = que[p];
                for (int id : adj[u]) {
                    int v = ed[id].v;
                    if (ban[id] || d[u] != d[v] + ed[id].w) continue;
                    cut.push_back(id);
                    if (!got[v]) {
                        got[v] = 1;
                        que.push_back(v);
                    }
                }
            }
            sort(cut.begin(), cut.end(), [&](int a, int b) {
                if (ed[a].u != ed[b].u) return ed[a].u < ed[b].u;
                return ed[a].v < ed[b].v;
            });
            cout << "The path cost is " << best << '\n';
            for (int id : cut) {
                ban[id] = true;
                cout << ed[id].u << ' ' << ed[id].v << ' ' << ed[id].w << '\n';
            }
            any = true;
        }
        if (!any) cout << "No road to block\n";
    }
    return 0;
}
