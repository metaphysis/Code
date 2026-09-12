#include <bits/stdc++.h>
using namespace std;

void dfs(int u, const vector<vector<int>>& graph, vector<char>& vis, vector<int>& order) {
    if (vis[u]) return;
    vis[u] = 1;
    for (int v : graph[u])
        dfs(v, graph, vis, order);
    order.push_back(u);
}

int calcGrundy(int u, const vector<vector<int>>& graph, const vector<int>& k, vector<int>& sg) {
    if (graph[u].empty()) return 0;
    vector<int> vals;
    for (int v : graph[u])
        vals.push_back(sg[v]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    int lim = 1 << vals.size();
    vector<char> has(1 << 16, 0);
    for (int mask = 0; mask < lim; ++mask) {
        int x = 0, cnt = 0;
        for (int j = 0; j < (int)vals.size(); ++j) {
            if (((mask >> j) & 1) != 0) {
                x ^= vals[j];
                ++cnt;
            }
        }
        if (cnt <= k[u] && (cnt % 2 == k[u] % 2))
            has[x] = 1;
    }
    int res = 0;
    while (has[res])
        ++res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int game = 1; game <= t; ++game) {
        int v, e;
        cin >> v >> e;
        vector<vector<int>> graph(v);
        for (int i = 0; i < e; ++i) {
            int from, to;
            cin >> from >> to;
            graph[from].push_back(to);
        }
        vector<int> k(v);
        for (int i = 0; i < v; ++i)
            cin >> k[i];
        vector<char> vis(v, 0);
        vector<int> order;
        for (int i = 0; i < v; ++i)
            dfs(i, graph, vis, order);
        vector<int> sg(v, 0);
        for (int u : order)
            sg[u] = calcGrundy(u, graph, k, sg);
        int r;
        cin >> r;
        cout << "Game#" << game << ":\n";
        for (int round = 1; round <= r; ++round) {
            int allXor = 0;
            for (int i = 0; i < v; ++i) {
                int value;
                cin >> value;
                if (value % 2 == 1)
                    allXor ^= sg[i];
            }
            cout << "Round#" << round << ": ";
            if (allXor == 0)
                cout << "LOSING\n";
            else
                cout << "WINNING\n";
        }
        cout << '\n';
    }
    return 0;
}
