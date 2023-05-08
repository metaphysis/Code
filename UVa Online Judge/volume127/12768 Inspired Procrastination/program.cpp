// Inspired Procrastination
// UVa ID: 12768
// Verdict: Accepted
// Submission Date: 2023-05-08
// UVa Run Time: 0.020s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

struct edge { int u, v, w; } g[10010];
int d[110];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m, n) {
        for (int i = 0; i < m; i++) cin >> g[i].u >> g[i].v >> g[i].w;
        for (int i = 1; i <= n; i++) d[i] = -INF;
        d[1] = 0;
        int cycled = 0;
        for (int i = 1; i <= n; i++) {
            cycled = 0;
            for (int j = 0; j < m; j++) {
                edge e = g[j];
                if (d[e.u] > -INF && d[e.u] + e.w > d[e.v]) {
                    d[e.v] = d[e.u] + e.w;
                    cycled = 1;
                }
            }
        }
        if (cycled) cout << "Unlimited!\n";
        else {
            int r = 0;
            for (int i = 1; i <= n; i++) r = max(r, d[i]);
            cout << r << '\n';
        }
    }
    return 0;
}
