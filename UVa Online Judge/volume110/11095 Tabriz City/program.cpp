// Tabriz City
// UVa ID: 11095
// Verdict: Accepted
// Submission Date: 2023-06-17
// UVa Run Time: 2.390s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include<bits/stdc++.h>

using namespace std;

int bits[1 << 20];
int n, m, bestn, bestm, g[32][32];
int x[1024], y[1024], linked[32];

inline int getBits(int mask) {
    return bits[mask & ((1 << 20) - 1)] + bits[mask >> 20];
}

void dfs(int mask, int cnt) {
    if (getBits(mask) >= bestn) return;
    if (cnt == m) {
        if (getBits(mask) < bestn) {
            bestn = getBits(mask);
            bestm = mask;
        }
        return;
    }
    if ((mask & (1 << x[cnt])) || (mask & (1 << y[cnt]))) dfs(mask, cnt + 1);
    else {
        dfs(mask | (1 << x[cnt]), cnt + 1);
        dfs(mask | (1 << y[cnt]), cnt + 1);
        dfs(mask | (1 << x[cnt]) | (1 << y[cnt]), cnt + 1);
        dfs(mask | linked[x[cnt]], cnt + 1);
        dfs(mask | linked[y[cnt]], cnt + 1);
        dfs(mask | linked[x[cnt]] | linked[y[cnt]], cnt + 1);
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    for (int i = 0; i < (1 << 20); i++) bits[i] = bits[i >> 1] + (i & 1);
    int T; cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cout << "Case #" << cs << ": ";
        cin >> n >> m;
        if (n == 0 || m == 0) {
            cout << "0\n\n";
            continue;
        }
        memset(g, 0, sizeof g);
        for (int i = 0, u, v; i < m; i++) {
            cin >> u >> v;
            g[u][v] = g[v][u] = 1;
        }
        memset(linked, m = 0, sizeof linked);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (g[i][j]) {
                    x[m] = i, y[m] = j, m++;
                    linked[i] |= (1 << j);
                    linked[j] |= (1 << i);
                }
        bestn = min(n, 16);
        dfs(0, 0);
        cout << bestn << '\n';
        int printed = false;
        for (int i = 0; i < n; i++)
            if (bestm & (1 << i)) {
                if (printed) cout << ' ';
                cout << i;
                printed = true;
            }
        cout << '\n';
    }
    return 0;
}
