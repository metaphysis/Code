#include <bits/stdc++.h>
using namespace std;

const long long inf = (1LL << 60);
long long allDist[30][30], dp[256][30];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && (n || m)) {
        map<string, int> cityId;
        for (int i = 0; i < n; i++) {
            string name;
            cin >> name;
            cityId[name] = i;
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                allDist[i][j] = (i == j ? 0 : inf);
        for (int i = 0; i < m; i++) {
            string a, b;
            int c;
            cin >> a >> b >> c;
            int u = cityId[a], v = cityId[b];
            allDist[u][v] = min(allDist[u][v], (long long)c);
            allDist[v][u] = min(allDist[v][u], (long long)c);
        }
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (allDist[i][k] + allDist[k][j] < allDist[i][j])
                        allDist[i][j] = allDist[i][k] + allDist[k][j];
        int term[8];
        for (int i = 0; i < 4; i++) {
            string a, b;
            cin >> a >> b;
            term[i * 2] = cityId[a];
            term[i * 2 + 1] = cityId[b];
        }
        for (int mask = 0; mask < 256; mask++)
            for (int v = 0; v < n; v++)
                dp[mask][v] = inf;
        for (int i = 0; i < 8; i++)
            dp[1 << i][term[i]] = 0;
        for (int mask = 1; mask < 256; mask++) {
            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask)
                for (int v = 0; v < n; v++)
                    if (dp[sub][v] + dp[mask ^ sub][v] < dp[mask][v])
                        dp[mask][v] = dp[sub][v] + dp[mask ^ sub][v];
            long long nxt[30];
            for (int v = 0; v < n; v++) {
                nxt[v] = inf;
                for (int u = 0; u < n; u++)
                    nxt[v] = min(nxt[v], dp[mask][u] + allDist[u][v]);
            }
            for (int v = 0; v < n; v++)
                dp[mask][v] = nxt[v];
        }
        int termMask[16];
        long long treeCost[16], partCost[16];
        termMask[0] = 0;
        treeCost[0] = 0;
        for (int mask = 1; mask < 16; mask++) {
            termMask[mask] = 0;
            for (int i = 0; i < 4; i++)
                if (mask & (1 << i))
                    termMask[mask] |= 3 << (i * 2);
            treeCost[mask] = inf;
            for (int v = 0; v < n; v++)
                treeCost[mask] = min(treeCost[mask], dp[termMask[mask]][v]);
        }
        for (int mask = 0; mask < 16; mask++)
            partCost[mask] = inf;
        partCost[0] = 0;
        for (int mask = 1; mask < 16; mask++) {
            int lowBit = mask & -mask;
            for (int sub = mask; sub; sub = (sub - 1) & mask)
                if (sub & lowBit)
                    partCost[mask] = min(partCost[mask], partCost[mask ^ sub] + treeCost[sub]);
        }
        cout << partCost[15] << '\n';
    }
    return 0;
}
