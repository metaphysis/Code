// Deadlock Detection
// UVa ID: 840
// Verdict: Accepted
// Submission Date: 2023-05-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
int N, M, E;
vector<int> g[256];
int visited[256], parent[256];
vector<string> cycle;
bool cmp(string a, string b) {
    if (a.length() != b.length()) return a.length() < b.length();
    return a < b;
}
void dfs(int u, int tag) {
    visited[u] = tag;
    for (auto v : g[u])
        if (!visited[v]) {
            parent[v] = u;
            dfs(v, tag);
        } else {
            if (visited[v] == tag) {
                vector<int> path;
                int tmp = u;
                while (tmp != v) {
                    path.insert(path.begin(), tmp);
                    tmp = parent[tmp];
                }
                path.insert(path.begin(), tmp);
                int idx = 0;
                for (int i = 1; i < path.size(); i++)
                    if (path[i] < path[idx])
                        idx = i;
                if (idx) {
                    for (int i = 0; i < idx; i++) path.push_back(path[i]);
                    path.erase(path.begin(), path.begin() + idx);
                }
                path.push_back(path.front());
                string s;
                for (int i = 0; i < path.size(); i++) {
                    if (i) s += '-';
                    s += char(path[i]);
                }
                cycle.push_back(s);
            }
        }
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++) {
        if (cs) cout << '\n';
        for (int i = 'A'; i <= 'Z'; i++) {
            g[i].clear();
            g[i + 32].clear();
        }
        cin >> N >> M >> E;
        string e;
        for (int i = 0; i < E; i++) {
            cin >> e;
            g[e.front()].push_back(e.back());
        }
        cycle.clear();
        memset(visited, 0, sizeof visited);
        memset(parent, -1, sizeof parent);
        for (int i = 'A'; i <= 'Z'; i++)
            if (!visited[i]) {
                parent[i] = -1;
                dfs(i, i);
            }
        if (cycle.size()) {
            cout << "YES\n";
            sort(cycle.begin(), cycle.end(), cmp);
            for (auto c : cycle) cout << c << '\n';
        } else cout << "NO\n";
        
    }
    return 0;
}
