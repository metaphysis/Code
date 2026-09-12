#include <bits/stdc++.h>
using namespace std;

int n, timerCnt, blockCnt;
vector<vector<pair<int, int>>> adj;
vector<int> disc, low, bel, stk, compCnt;

long long getKey(int a, int b) {
    if (a > b) swap(a, b);
    return 1LL * a * (n + 1) + b;
}

void tarjan(int u, int pe) {
    disc[u] = low[u] = ++timerCnt;
    for (auto cur : adj[u]) {
        int v = cur.first, id = cur.second;
        if (id == pe) continue;
        if (!disc[v]) {
            stk.push_back(id);
            tarjan(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] >= disc[u]) {
                int cnt = 0;
                ++blockCnt;
                while (true) {
                    int x = stk.back();
                    stk.pop_back();
                    bel[x] = blockCnt;
                    ++cnt;
                    if (x == id) break;
                }
                compCnt.push_back(cnt);
            }
        } else if (disc[v] < disc[u]) {
            stk.push_back(id);
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> n >> m;
        vector<pair<int, int>> edges(m + 1);
        unordered_map<long long, int> idMap;
        for (int i = 1; i <= m; ++i) {
            int a, b;
            cin >> a >> b;
            edges[i] = {a, b};
            idMap[getKey(a, b)] = i;
        }
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int firstId = idMap[getKey(a, b)], secondId = idMap[getKey(c, d)];
        int f;
        cin >> f;
        vector<char> isToll(m + 1, false);
        while (f--) {
            cin >> a >> b;
            isToll[idMap[getKey(a, b)]] = true;
        }
        adj.assign(n + 1, {});
        for (int i = 1; i <= m; ++i) {
            if (isToll[i]) continue;
            a = edges[i].first;
            b = edges[i].second;
            adj[a].push_back({b, i});
            adj[b].push_back({a, i});
        }
        timerCnt = blockCnt = 0;
        disc.assign(n + 1, 0);
        low.assign(n + 1, 0);
        bel.assign(m + 1, 0);
        stk.clear();
        compCnt.assign(1, 0);
        for (int i = 1; i <= n; ++i)
            if (!disc[i]) tarjan(i, 0);
        bool ok;
        if (firstId != secondId) ok = bel[firstId] == bel[secondId];
        else ok = compCnt[bel[firstId]] > 1;
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
