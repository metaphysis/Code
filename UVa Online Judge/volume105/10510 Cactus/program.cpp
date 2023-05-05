// Cactus
// UVa ID: 10510
// Verdict: Accepted
// Submission Date: 2023-05-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
struct edge { int v, nxt; } g[10010];
int dfn[10010], low[10010], scc[10010], dfntime, cscc;
int cnt, head[10010];
int yes;
stack<int> s;
void tarjan(int u) {
    dfn[u] = low[u] = ++dfntime;
    s.push(u);
    int counter = 0;
    for (int i = head[u]; ~i; i = g[i].nxt) {
        int v = g[i].v;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) yes = 0;
            if (low[v] < dfn[u]) counter++;
        } else {
            if (!scc[v]) {
                low[u] = min(low[u], dfn[v]); 
                counter++;
            } else yes = 0;
        }
    }
    if (counter > 1) yes = 0;
    if (low[u] == dfn[u]) {
        ++cscc;
        if (cscc > 1) yes = 0;
        while (true) {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (v == u) break;
        }
    }
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        cnt = 0;
        for (int i = 0; i < n; i++) head[i] = -1;
        for (int i = 0, u, v; i < m; i++) {
            cin >> u >> v;
            g[cnt] = edge{v, head[u]};
            head[u] = cnt++;
        }
        if (n <= 1) {
            cout << "YES\n";
            continue;
        }
        yes = 1;
        cscc = dfntime = 0;
        while (!s.empty()) s.pop();
        for (int i = 0; i < n; i++) dfn[i] = 0, scc[i] = 0;
        for (int i = 0; i < n; i++)
            if (!dfn[i])
                tarjan(i);
        if (yes) cout << "YES";
        else cout << "NO";
        cout << '\n';
    }
    return 0;
}
