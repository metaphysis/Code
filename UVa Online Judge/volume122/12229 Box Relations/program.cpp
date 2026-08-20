#include <bits/stdc++.h>
using namespace std;

struct Relation {
    char typ;
    int a, b;
};

class Solver {
private:
    int n, timer, compCnt;
    vector<Relation> rel;
    vector<vector<pair<int, int>>> graph;
    vector<int> dfn, low, inStack, belong, stk;

    void addEdge(int u, int v, int w) {
        graph[u].push_back({v, w});
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++timer;
        stk.push_back(u);
        inStack[u] = 1;
        for (auto e : graph[u]) {
            int v = e.first;
            if (!dfn[v]) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            while (true) {
                int v = stk.back();
                stk.pop_back();
                inStack[v] = 0;
                belong[v] = compCnt;
                if (v == u) break;
            }
            compCnt++;
        }
    }

public:
    Solver(int nn, const vector<Relation> &rr) : n(nn), rel(rr) {
    }

    vector<int> solveAxis(char axis, bool &ok) {
        int tot = n * 2;
        graph.assign(tot, vector<pair<int, int>>());
        for (int i = 0; i < n; i++)
            addEdge(i * 2, i * 2 + 1, 1);
        for (auto r : rel) {
            int l1 = r.a * 2, r1 = r.a * 2 + 1;
            int l2 = r.b * 2, r2 = r.b * 2 + 1;
            if (r.typ == 'I') {
                addEdge(l1, r2, 1);
                addEdge(l2, r1, 1);
            } else if (r.typ == axis) {
                addEdge(r1, l2, 1);
            }
        }
        timer = compCnt = 0;
        dfn.assign(tot, 0);
        low.assign(tot, 0);
        inStack.assign(tot, 0);
        belong.assign(tot, 0);
        stk.clear();
        for (int i = 0; i < tot; i++)
            if (!dfn[i]) tarjan(i);
        for (int u = 0; u < tot; u++) {
            for (auto e : graph[u]) {
                int v = e.first, w = e.second;
                if (belong[u] == belong[v] && w > 0) {
                    ok = false;
                    return vector<int>();
                }
            }
        }
        vector<vector<pair<int, int>>> dag(compCnt);
        vector<int> indeg(compCnt, 0), dist(compCnt, 0);
        for (int u = 0; u < tot; u++) {
            for (auto e : graph[u]) {
                int v = e.first, w = e.second;
                int cu = belong[u], cv = belong[v];
                if (cu != cv) {
                    dag[cu].push_back({cv, w});
                    indeg[cv]++;
                }
            }
        }
        queue<int> que;
        for (int i = 0; i < compCnt; i++)
            if (!indeg[i]) que.push(i);
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            for (auto e : dag[u]) {
                int v = e.first, w = e.second;
                dist[v] = max(dist[v], dist[u] + w);
                indeg[v]--;
                if (!indeg[v]) que.push(v);
            }
        }
        vector<int> val(tot);
        for (int i = 0; i < tot; i++)
            val[i] = dist[belong[i]];
        return val;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, r, tc = 0;
    while (cin >> n >> r) {
        if (n == 0 && r == 0) break;
        vector<Relation> rel(r);
        for (int i = 0; i < r; i++) {
            cin >> rel[i].typ >> rel[i].a >> rel[i].b;
            rel[i].a--;
            rel[i].b--;
        }
        Solver solver(n, rel);
        bool ok = true;
        vector<int> x = solver.solveAxis('X', ok);
        vector<int> y, z;
        if (ok) y = solver.solveAxis('Y', ok);
        if (ok) z = solver.solveAxis('Z', ok);
        cout << "Case " << ++tc << ": ";
        if (!ok) {
            cout << "IMPOSSIBLE\n\n";
            continue;
        }
        cout << "POSSIBLE\n";
        for (int i = 0; i < n; i++) {
            cout << x[i * 2] << ' ' << y[i * 2] << ' ' << z[i * 2] << ' ';
            cout << x[i * 2 + 1] << ' ' << y[i * 2 + 1] << ' ' << z[i * 2 + 1] << '\n';
        }
        cout << '\n';
    }
    return 0;
}
