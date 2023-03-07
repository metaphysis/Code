// Y-Game
// UVa ID: 11841
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct point { int x, y, z; } ps[410];

int n, m;
int X, Y, Z;
int visited[410];
vector<int> g[410];

bool isConnected(int i, int j) {
    if (ps[i].x == ps[j].x && abs(ps[i].y - ps[j].y) == 1) return true;
    if (ps[i].y == ps[j].y && abs(ps[i].x - ps[j].x) == 1) return true;
    if (ps[i].z == ps[j].z && abs(ps[i].x - ps[j].x) == 1) return true;
    return false;
}

void dfs(int u) {
    visited[u] = 1;
    X |= !ps[u].x, Y |= !ps[u].y, Z |= !ps[u].z;
    for (auto v : g[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> n >> m, m) {
        int x, y, z;
        for (int i = 0; i < m; i++) {
            cin >> x >> y >> z;
            ps[i] = point{x, y, z};
        }
        for (int i = 0; i < m; i++) g[i].clear();
        for (int i = 0; i < m; i++)
            for (int j = i + 1; j < m; j++)
                if (isConnected(i, j)) {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
        memset(visited, 0, sizeof visited);
        for (int i = 0; i < m; i++)
            if (!visited[i]) {
                X = Y = Z = 0;
                dfs(i);
                if (X && Y && Z) break;
            }
        cout << (X && Y && Z ? "Benny" : "Willy") << '\n';
    }
    return 0;
}
