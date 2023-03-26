// Directed Forest
// UVa ID: 13038
// Verdict: Accepted
// Submission Date: 2023-03-26
// UVa Run Time: 0.420s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;
int N, E, in[MAXN], r;
vector<int> g[MAXN];

void dfs(int u, int depth) {
    r = max(r, depth);
    for (auto v : g[u])
        dfs(v, depth + 1);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> N >> E;
        for (int i = 1; i <= N; i++) {
            g[i].clear();
            in[i] = 0;
        }
        for (int i = 0, u, v; i < E; i++) {
            cin >> u >> v;
            g[u].push_back(v);
            in[v]++;
        }
        r = 0;
        for (int i = 1; i <= N; i++)
            if (!in[i])
                dfs(i, 1);
        cout << "Case " << cs << ": " << r << '\n';
    }
    return 0;
}
