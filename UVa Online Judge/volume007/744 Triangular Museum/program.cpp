// Triangular Museum
// UVa ID: 744
// Verdict: Accepted
// Submission Date: 2026-07-06
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> g[110];

void buildGraph() {
    vector<pair<int, int>> interval = {
        {1, 1}, {2, 4}, {5, 9}, {10, 16}, {17, 25}, {26, 36}, {37, 49}, {50, 64}, {65, 81}, {82, 100}
    };
    for (int i = 1; i < interval.size(); i++) {
        int s = interval[i].first, e = interval[i].second, up = interval[i - 1].first;
        for (int now = s, link = 0; now <= e; now++, link ^= 1) {
            if (now < e) {
                g[now].push_back(now + 1);
                g[now + 1].push_back(now);
            }
            if (link) {
                g[now].push_back(up);
                g[up].push_back(now);
                up += 2;
            }
        }
    }
}

int disabled[110], visited[110], parent[110];

void bfs(int s, int t) {
    memset(visited, 0, sizeof visited);
    memset(parent, -1, sizeof parent);
    queue<int> q;
    q.push(s);
    visited[s] = 1;
    while (!q.empty()) {
        int u = q.front();
        if (u == t) break;
        q.pop();
        for (auto v : g[u]) {
            if (disabled[v] || visited[v]) continue;
            visited[v] = 1;
            parent[v] = u;
            q.push(v);
        }
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    buildGraph();
    int K, cases = 0;
    while (cin >> K && K) {
        if (cases++) cout << '\n';
        int N = K * K;
        string s;
        vector<string> names;
        for (int i = 1; i <= N; i++) {
            cin >> s;
            names.push_back(s);
        }
        memset(disabled, 0, sizeof disabled);
        vector<pair<string, string>> swaps;
        for (int i = 1; i <= N; i++) {
            cin >> s;
            int room = 1 + (find(names.begin(), names.end(), s) - names.begin());
            if (room == i) { disabled[i] = 1; continue; }
            bfs(room, i);
            vector<int> path;
            int u = i;
            while (parent[u] != -1) {
                path.push_back(u);
                u = parent[u];
            }
            path.push_back(u);
            reverse(path.begin(), path.end());
            for (int j = 1; j < path.size(); j++) {
                swaps.push_back({names[path[j - 1] - 1], names[path[j] - 1]});
                swap(names[path[j - 1] - 1], names[path[j] - 1]);
            }
            disabled[i] = 1;
        }
        cout << swaps.size() << '\n';
        for (auto& p : swaps) cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}
