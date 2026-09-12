#include <bits/stdc++.h>
using namespace std;

struct Graph {
    unordered_map<long long, int> id;
    vector<vector<pair<int, long long>>> adj;
    vector<long long> fixedVal;
    vector<char> hasFixed;
    int getId(long long x) {
        auto it = id.find(x);
        if (it != id.end()) return it->second;
        int p = (int)adj.size();
        id[x] = p;
        adj.push_back(vector<pair<int, long long>>());
        fixedVal.push_back(0);
        hasFixed.push_back(0);
        return p;
    }
    int findId(long long x) {
        auto it = id.find(x);
        if (it == id.end()) return -1;
        return it->second;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, q;
    while (cin >> m >> q, m || q) {
        Graph graph;
        for (int i = 0; i < m; i++) {
            long long x, y, a;
            cin >> x >> y >> a;
            int u = graph.getId(x), v = graph.getId(y);
            if (u == v) {
                graph.hasFixed[u] = 1;
                graph.fixedVal[u] = a;
            } else {
                graph.adj[u].push_back({v, a});
                graph.adj[v].push_back({u, a});
            }
        }
        vector<pair<long long, long long>> queries(q);
        for (int i = 0; i < q; i++) cin >> queries[i].first >> queries[i].second;
        int n = (int)graph.adj.size(), cnt = 0;
        vector<int> comp(n, -1), side(n);
        vector<long long> base(n), rootVal;
        vector<char> compKnown;
        for (int st = 0; st < n; st++) {
            if (comp[st] != -1) continue;
            queue<int> que;
            bool can = false;
            long long t = 0;
            comp[st] = cnt;
            side[st] = 1;
            base[st] = 0;
            que.push(st);
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                if (graph.hasFixed[u]) {
                    long long cur = side[u] * (graph.fixedVal[u] - base[u]);
                    if (!can) {
                        can = true;
                        t = cur;
                    }
                }
                for (auto edge : graph.adj[u]) {
                    int v = edge.first;
                    long long a = edge.second;
                    if (comp[v] == -1) {
                        comp[v] = cnt;
                        side[v] = -side[u];
                        base[v] = a - base[u];
                        que.push(v);
                    } else {
                        int coef = side[u] + side[v];
                        if (coef != 0) {
                            long long cur = (a - base[u] - base[v]) / coef;
                            if (!can) {
                                can = true;
                                t = cur;
                            }
                        }
                    }
                }
            }
            compKnown.push_back(can);
            rootVal.push_back(t);
            cnt++;
        }
        for (auto query : queries) {
            long long x = query.first, y = query.second;
            int u = graph.findId(x), v = graph.findId(y);
            if (u == -1 || v == -1) {
                cout << "*\n";
                continue;
            }
            if (u == v) {
                if (compKnown[comp[u]]) cout << side[u] * rootVal[comp[u]] + base[u] << '\n';
                else cout << "*\n";
                continue;
            }
            if (comp[u] != comp[v]) {
                if (compKnown[comp[u]] && compKnown[comp[v]]) {
                    long long ans = side[u] * rootVal[comp[u]] + base[u] + side[v] * rootVal[comp[v]] + base[v];
                    cout << ans << '\n';
                } else cout << "*\n";
            } else if (compKnown[comp[u]]) {
                long long ans = side[u] * rootVal[comp[u]] + base[u] + side[v] * rootVal[comp[v]] + base[v];
                cout << ans << '\n';
            } else if (side[u] != side[v]) cout << base[u] + base[v] << '\n';
            else cout << "*\n";
        }
        cout << "-\n";
    }
    return 0;
}
