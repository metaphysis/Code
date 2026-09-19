#include <bits/stdc++.h>
using namespace std;

int getLca(int u, int v, const vector<int>& depth, const vector<vector<int>>& up) {
    if (depth[u] < depth[v]) swap(u, v);
    int diff = depth[u] - depth[v], logN = (int)up.size();
    for (int bit = 0; bit < logN; ++bit) if (diff & (1 << bit)) u = up[bit][u];
    if (u == v) return u;
    for (int bit = logN - 1; bit >= 0; --bit) {
        if (up[bit][u] != up[bit][v]) {
            u = up[bit][u];
            v = up[bit][v];
        }
    }
    return up[0][u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; ++caseId) {
        int n, m, logN = 1, queryCount;
        cin >> n >> m;
        vector<vector<pair<int, int>>> graph(n);
        for (int i = 0; i < m; ++i) {
            int u, v, weight;
            cin >> u >> v >> weight;
            graph[u].push_back({v, weight});
            graph[v].push_back({u, weight});
        }
        const long long inf = LLONG_MAX / 4;
        vector<long long> dist(n, inf);
        vector<int> order, depth(n, 0), subSize(n, 0);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> minHeap;
        order.reserve(n);
        dist[0] = 0;
        minHeap.push({0, 0});
        while (!minHeap.empty()) {
            pair<long long, int> cur = minHeap.top();
            minHeap.pop();
            int u = cur.second;
            if (cur.first != dist[u]) continue;
            order.push_back(u);
            for (const auto& edge : graph[u]) {
                int v = edge.first, weight = edge.second;
                long long nextDist = dist[u] + weight;
                if (nextDist < dist[v]) {
                    dist[v] = nextDist;
                    minHeap.push({nextDist, v});
                }
            }
        }
        while ((1 << logN) <= n) ++logN;
        vector<vector<int>> up(logN, vector<int>(n, 0));
        for (int u : order) {
            subSize[u] = 1;
            if (u == 0) continue;
            int parent = -1;
            for (const auto& edge : graph[u]) {
                int v = edge.first, weight = edge.second;
                if (dist[v] + weight == dist[u]) {
                    if (parent == -1) parent = v;
                    else parent = getLca(parent, v, depth, up);
                }
            }
            up[0][u] = parent;
            depth[u] = depth[parent] + 1;
            for (int bit = 1; bit < logN; ++bit) up[bit][u] = up[bit - 1][up[bit - 1][u]];
        }
        for (int i = (int)order.size() - 1; i > 0; --i) {
            int u = order[i];
            subSize[up[0][u]] += subSize[u];
        }
        cin >> queryCount;
        cout << "Case " << caseId << ":\n";
        for (int queryId = 1; queryId <= queryCount; ++queryId) {
            int teamCount, meet = -1;
            cin >> teamCount;
            for (int i = 0; i < teamCount; ++i) {
                int city;
                cin >> city;
                if (dist[city] == inf) continue;
                if (meet == -1) meet = city;
                else meet = getLca(meet, city, depth, up);
            }
            cout << "Query " << queryId << ":\n";
            if (meet == -1) cout << "Will not sabotage.\n";
            else {
                cout << depth[meet] + 1 << " possible way(s) to sabotage the contest.\n";
                cout << "Teams from at least " << subSize[meet] << " cities will be late.\n";
            }
        }
    }
    return 0;
}
