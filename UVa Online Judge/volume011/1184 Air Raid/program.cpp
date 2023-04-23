// Air Raid
// UVa ID: 1184
// Verdict: Accepted
// Submission Date: 2018-04-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 256;
int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;
int dfs(int u) {
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v]) {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v])) {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}
int hungarian() {
    int matches = 0;
    memset(cx, -1, sizeof(cx));
    memset(cy, -1, sizeof(cy));
    for (int i = 0; i < tx; i++)
        if (cx[i] == -1) {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++) {
        int n, m, u, v;
        cin >> n >> m;
        memset(g, 0, sizeof(g));
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            u--, v--;
            g[u][v] = 1;
        }
        tx = ty = n;
        cout << n - hungarian() << '\n';
    }
    return 0;
}
