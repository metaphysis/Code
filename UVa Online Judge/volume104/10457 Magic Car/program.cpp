// Magic Car
// UVa ID: 10457
// Verdict: Accepted
// Submission Date: 2023-04-01
// UVa Run Time: 0.100s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 210, MAXE = 1010;

int parent[MAXN];

int findSet(int x) {
    return x == parent[x] ? x : parent[x] = findSet(parent[x]);
}

struct edge {
    int u, v, w;
    bool operator<(const edge &e) const { return w < e.w; }
} g[MAXE];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m;
    while (cin >> n >> m) {
        for (int i = 0, u, v, w; i < m; i++)
            cin >> g[i].u >> g[i].v >> g[i].w;
        sort(g, g + m);
        int estart, estop;
        cin >> estart >> estop;
        int k;
        cin >> k;
        while (k--) {
            int u, v;
            cin >> u >> v;
            int r = 0x3f3f3f3f;
            for (int i = 0; i < m; i++) {
                for (int j = 1; j <= n; j++) parent[j] = j;
                for (int j = i; j < m; j++) {
                    parent[findSet(g[j].u)] = findSet(g[j].v);
                    if (findSet(u) == findSet(v)) {
                        r = min(r, abs(g[i].w - g[j].w));
                        break;
                    }
                }
            }
            cout << r + estart + estop << '\n';
        }
    }
    return 0;
}
