// Boss
// UVa ID: 12648
// Verdict: Accepted
// Submission Date: 2023-03-26
// UVa Run Time: 0.050s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 510, INF = 0x3f3f3f3f;

int N, M, I, visited[MAXN], age[MAXN], image[MAXN], R;
vector<int> g[MAXN];

void dfs(int u) {
    visited[u] = 1;
    for (auto v : g[u])
        if (!visited[v]) {
            R = min(R, age[v]);
            dfs(v);
        }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> N >> M >> I) {
        for (int i = 1; i <= N; i++) {
            cin >> age[i];
            g[i].clear();
            image[i] = i;
        }
        for (int i = 0, u, v; i < M; i++) {
            cin >> u >> v;
            g[v].push_back(u);
        }
        for (int i = 0; i < I; i++) {
            char c;
            cin >> c;
            if (c == 'T') {
                int u, v;
                cin >> u >> v;
                swap(age[image[u]], age[image[v]]);
                swap(image[u], image[v]);            
            } else {
                int e;
                cin >> e;
                R = INF;
                memset(visited, 0, sizeof visited);
                dfs(image[e]);
                if (R == INF) cout << '*';
                else cout << R;
                cout << '\n';
            }
        }
    }
    return 0;
}
