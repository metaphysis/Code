#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int to, id;
};

int n, e, b, tim, tag;
vector<int> val, toy, dfn, low, inCycle, mat, vis;
vector<vector<Edge>> graph;
vector<pair<int, int>> stk;
vector<long long> sumVal;
vector<vector<int>> can;

void addRegion(int a, int c) {
    vector<int> nodes;
    ++tag;
    while (true) {
        pair<int, int> ed = stk.back();
        stk.pop_back();
        if (vis[ed.first] != tag) {
            vis[ed.first] = tag;
            nodes.push_back(ed.first);
        }
        if (vis[ed.second] != tag) {
            vis[ed.second] = tag;
            nodes.push_back(ed.second);
        }
        if (ed.first == a && ed.second == c) break;
    }
    if (nodes.size() < 3) return;
    long long total = 0;
    for (int x : nodes) {
        inCycle[x] = 1;
        total += val[x];
    }
    sumVal.push_back(total);
}

void tarjan(int u, int pe) {
    dfn[u] = low[u] = ++tim;
    for (Edge ed : graph[u]) {
        int v = ed.to;
        if (ed.id == pe) continue;
        if (!dfn[v]) {
            stk.push_back({u, v});
            tarjan(v, ed.id);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) addRegion(u, v);
        } else if (dfn[v] < dfn[u]) {
            stk.push_back({u, v});
            low[u] = min(low[u], dfn[v]);
        }
    }
}

bool findPath(int u) {
    for (int v : can[u]) {
        if (vis[v] == tag) continue;
        vis[v] = tag;
        if (mat[v] == -1 || findPath(mat[v])) {
            mat[v] = u;
            return true;
        }
    }
    return false;
}

bool canMatch(long long lim) {
    int cnt = sumVal.size();
    can.assign(cnt, vector<int>());
    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < b; ++j) {
            long long dif = abs(sumVal[i] - toy[j]);
            if (dif <= lim) can[i].push_back(j);
        }
    }
    mat.assign(b, -1);
    vis.assign(b, 0);
    tag = 0;
    for (int i = 0; i < cnt; ++i) {
        ++tag;
        if (!findPath(i)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; ++cs) {
        cin >> n >> e >> b;
        val.assign(n, 0);
        toy.assign(b, 0);
        graph.assign(n, vector<Edge>());
        for (int i = 0; i < n; ++i) cin >> val[i];
        for (int i = 0; i < b; ++i) cin >> toy[i];
        for (int i = 0; i < e; ++i) {
            int u, v;
            cin >> u >> v;
            --u;
            --v;
            graph[u].push_back({v, i});
            graph[v].push_back({u, i});
        }
        dfn.assign(n, 0);
        low.assign(n, 0);
        inCycle.assign(n, 0);
        vis.assign(n, 0);
        sumVal.clear();
        stk.clear();
        tim = 0;
        tag = 0;
        for (int i = 0; i < n; ++i)
            if (!dfn[i]) tarjan(i, -1);
        for (int i = 0; i < n; ++i)
            if (!inCycle[i]) sumVal.push_back(val[i]);
        cout << "Buzz Mission " << cs << ": " << sumVal.size();
        if (sumVal.size() > (size_t)b) {
            cout << " No\n";
            continue;
        }
        long long left = 0, right = 100000;
        while (left < right) {
            long long mid = (left + right) / 2;
            if (canMatch(mid)) right = mid;
            else left = mid + 1;
        }
        cout << " " << left << '\n';
    }
    return 0;
}
