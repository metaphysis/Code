#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, id;
};

vector<int> getComp(int n, const vector<vector<Edge>> &graph, const vector<int> &open, int start) {
    vector<int> comp(n, 0), stk;
    stk.push_back(start);
    comp[start] = 1;
    while (!stk.empty()) {
        int u = stk.back();
        stk.pop_back();
        for (const Edge &e : graph[u]) {
            if (!open[e.id] || comp[e.to]) continue;
            comp[e.to] = 1;
            stk.push_back(e.to);
        }
    }
    return comp;
}

vector<int> getPath(int n, const vector<vector<Edge>> &graph, const vector<int> &open, int start, int target) {
    vector<int> par(n, -1), path;
    queue<int> que;
    que.push(start);
    par[start] = start;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == target) break;
        for (const Edge &e : graph[u]) {
            if (!open[e.id] || par[e.to] != -1) continue;
            par[e.to] = u;
            que.push(e.to);
        }
    }
    for (int u = target; u != start; u = par[u]) path.push_back(u);
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

void addPath(vector<int> &ans, const vector<int> &path) {
    for (int i = 1; i < (int)path.size(); i++) ans.push_back(path[i]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int v, c, x, y;
    while (cin >> v >> c >> x >> y) {
        if (v == 0 && c == 0 && x == 0 && y == 0) break;
        vector<int> keyPos(c), lockEdge(c, -1);
        for (int i = 0; i < c; i++) cin >> keyPos[i];
        vector<vector<Edge>> graph(v);
        vector<int> edgeU(v - 1), edgeV(v - 1), edgeLock(v - 1), open(v - 1, 0);
        for (int i = 0; i < v - 1; i++) {
            int a, b, l;
            cin >> a >> b >> l;
            edgeU[i] = a;
            edgeV[i] = b;
            edgeLock[i] = l;
            graph[a].push_back({b, i});
            graph[b].push_back({a, i});
            if (l == -1) open[i] = 1;
            else lockEdge[l] = i;
        }
        vector<int> ans(1, x);
        int cur = x;
        while (true) {
            vector<int> comp = getComp(v, graph, open, x);
            if (comp[y]) break;
            int choose = -1;
            for (int i = 0; i < c; i++) {
                int id = lockEdge[i];
                if (id == -1 || open[id] || !comp[keyPos[i]]) continue;
                bool inU = comp[edgeU[id]];
                bool inV = comp[edgeV[id]];
                if (inU == inV) continue;
                choose = i;
                break;
            }
            if (choose == -1) break;
            int id = lockEdge[choose];
            int inside = comp[edgeU[id]] ? edgeU[id] : edgeV[id];
            int outside = comp[edgeU[id]] ? edgeV[id] : edgeU[id];
            vector<int> path = getPath(v, graph, open, cur, keyPos[choose]);
            addPath(ans, path);
            cur = keyPos[choose];
            path = getPath(v, graph, open, cur, inside);
            addPath(ans, path);
            cur = inside;
            ans.push_back(outside);
            cur = outside;
            open[id] = 1;
        }
        vector<int> comp = getComp(v, graph, open, x);
        if (!comp[y]) {
            cout << "Impossible\n";
            continue;
        }
        cout << ans.size() - 1 << ":";
        for (int node : ans) cout << " " << node;
        cout << "\n";
    }
    return 0;
}
