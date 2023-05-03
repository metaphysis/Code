// The Flyover Construction
// UVa ID: 10331
// Verdict: Accepted
// Submission Date: 2023-05-03
// UVa Run Time: 0.130s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int cnt[100010];
struct edge { int u, v, w; } g[100010];
int gc;
int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int V, E, d[110][110];
    while (cin >> V >> E) {
        memset(d, 0x3f, sizeof d);
        gc = 0;
        for (int i = 0, u, v, w; i < E; i++) {
            cin >> u >> v >> w;
            d[u][v] = d[v][u] = min(d[u][v], w);
            g[gc++] = edge{u, v, w};
        }
        for (int i = 1; i <= V; i++) d[i][i] = 0;
        for (int k = 1; k <= V; k++)
            for (int i = 1; i <= V; i++)
                for (int j = 1; j <= V; j++)
                    if (d[i][j] > d[i][k] + d[k][j])
                        d[i][j] = d[i][k] + d[k][j];
        memset(cnt, 0, sizeof cnt);
        for (int i = 0; i < gc; i++)
            for (int j = 1; j <= V; j++)
                for (int k = 1; k <= V; k++)
                    if (d[j][g[i].u] + g[i].w + d[g[i].v][k] == d[j][k])
                        cnt[i]++;
        int mc = *max_element(cnt, cnt + 100010);
        int printed = 0;
        for (int i = 0; i < gc; i++) {
            if (cnt[i] == mc) {
                if (printed) cout << ' ';
                cout << i + 1;
                printed = 1;
            }
        }
        cout << '\n';
    }
    return 0;
}
