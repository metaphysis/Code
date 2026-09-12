#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from, to, id;
    long long w;
};

int edgeCount;

vector<int> findArborescence(int n, int root, const vector<Edge> &edges, bool &ok) {
    vector<int> pre(n, -1);
    vector<long long> inW(n, LLONG_MAX);
    for (int i = 0; i < (int)edges.size(); i++) {
        int u = edges[i].from, v = edges[i].to;
        if (v != root && edges[i].w < inW[v]) {
            inW[v] = edges[i].w;
            pre[v] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        if (i != root && pre[i] == -1) {
            ok = false;
            return {};
        }
    }
    vector<int> vis(n, -1), comp(n, -1);
    int cycleCnt = 0;
    for (int i = 0; i < n; i++) {
        int v = i;
        while (v != root && vis[v] != i && comp[v] == -1) {
            vis[v] = i;
            v = edges[pre[v]].from;
        }
        if (v != root && comp[v] == -1) {
            int u = v;
            do {
                comp[u] = cycleCnt;
                u = edges[pre[u]].from;
            } while (u != v);
            cycleCnt++;
        }
    }
    if (cycleCnt == 0) {
        vector<int> ans;
        for (int i = 0; i < n; i++)
            if (i != root) ans.push_back(edges[pre[i]].id);
        return ans;
    }
    int newN = cycleCnt;
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            comp[i] = newN;
            newN++;
        }
    }
    vector<Edge> newEdges;
    for (const Edge &e : edges) {
        int u = comp[e.from], v = comp[e.to];
        if (u != v) newEdges.push_back({u, v, e.id, e.w - inW[e.to]});
    }
    vector<int> childAns = findArborescence(newN, comp[root], newEdges, ok);
    if (!ok) return {};
    vector<int> pos(edgeCount, -1);
    for (int i = 0; i < (int)edges.size(); i++) pos[edges[i].id] = i;
    vector<int> blocked(n, 0), ans = childAns;
    for (int id : childAns) {
        int idx = pos[id];
        if (idx != -1) blocked[edges[idx].to] = 1;
    }
    for (int i = 0; i < n; i++) {
        if (i != root && !blocked[i]) ans.push_back(edges[pre[i]].id);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m, root;
        cin >> n >> m >> root;
        edgeCount = m;
        vector<Edge> edges(m), original(m);
        for (int i = 0; i < m; i++) {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            edges[i] = {u, v, i, w};
            original[i] = edges[i];
        }
        bool ok = true;
        vector<int> ans = findArborescence(n, root, edges, ok);
        if (!ok || (int)ans.size() != n - 1) {
            cout << "impossible\n";
            continue;
        }
        long long total = 0;
        for (int id : ans) total += original[id].w;
        cout << total << '\n';
        for (int id : ans) {
            cout << original[id].from << ' ' << original[id].to << ' ' << original[id].w << '\n';
        }
    }
    return 0;
}
