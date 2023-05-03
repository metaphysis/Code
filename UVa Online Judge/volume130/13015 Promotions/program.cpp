// Promotions
// UVa ID: 13015
// Verdict: Accepted
// Submission Date: 2023-05-03
// UVa Run Time: 0.370s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
vector<int> g[5100][2];
int tag[5100];
int dfs(int u, int flag, int idx) {
    if (tag[u] == flag) return 0;
    tag[u] = flag;
    int r = 1;
    for (auto v : g[u][idx])
        r += dfs(v, flag, idx);
    return r;
}
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int A, B, E, P;
    while (cin >> A >> B >> E >> P) {
        for (int i = 0; i < E; i++) {
            g[i][0].clear();
            g[i][1].clear();
        }
        for (int i = 0, u, v; i < P; i++) {
            cin >> u >> v;
            g[u][0].push_back(v);
            g[v][1].push_back(u);
        }
        memset(tag, -1, sizeof tag);
        int cA = 0, cB = 0, nC = 0;
        for (int i = 0; i < E; i++) {
            int r = E - dfs(i, i, 0);
            if (r < A) cA++;
            if (r < B) cB++;
            r = dfs(i, E + i, 1);
            if (r > B) nC++;
        }
        cout << cA << '\n';
        cout << cB << '\n';
        cout << nC << '\n';
    }
    return 0;
}
