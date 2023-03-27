// A Contest to Meet
// UVa ID: 13249
// Verdict: Accepted
// Submission Date: 2023-03-27
// UVa Run Time: 0.230s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 110;

int d[MAXN][MAXN];

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        memset(d, 0x3f, sizeof d);
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            d[u][v] = d[v][u] = min(d[u][v], w);
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int r = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                r = max(r, d[i][j]);
        int sA, sB, sC, s;
        cin >> sA >> sB >> sC;
        s = min(sA, min(sB, sC));
        cout << (r + s - 1) / s << '\n';
    }
    return 0;
}
