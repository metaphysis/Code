// Planning Mobile Robot on Tree
// UVa ID: 12569
// Verdict: Accepted
// Submission Date: 2023-04-16
// UVa Run Time: 2.660s
//
// 版权所有（C）2023，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;
struct block { int m, r, c; };
struct edge { int m, r, a, b; };
int d[1 << 16][16];
edge p[1 << 16][16];
vector<int> g[16];

void dfs(int m, int r) {
    if (p[m][r].a >= 0) {
        dfs(p[m][r].m, p[m][r].r);
        cout << p[m][r].a + 1 << ' ' << p[m][r].b + 1 << '\n';
    }
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T, n, M, s, t;
    cin >> T;
    for (int cs = 1; cs <= T; cs++) {
        cin >> n >> M >> s >> t;
        for (int i = 0; i < n; i++) g[i].clear();
        s--, t--;
        int mask = 0;
        for (int i = 0, b; i < M; i++) {
            cin >> b;
            b--;
            mask |= (1 << b);
        }
        for (int i = 1, u, v; i < n; i++) {
            cin >> u >> v;
            u--, v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for (int i = 0; i < (1 << n); i++)
            for (int j = 0; j < n; j++)
                d[i][j] = 0x3f3f3f3f;
        d[mask][s] = 0;
        queue<block> q;
        q.push(block{mask, s, 0});
        p[mask][s] = edge{mask, s, -1, -1};
        while (!q.empty()) {
            block blk = q.front(); q.pop();
            for (auto v : g[blk.r])
                if (!(blk.m & (1 << v)) && d[blk.m][v] > blk.c + 1) {
                    d[blk.m][v] = blk.c + 1;
                    p[blk.m][v] = edge{blk.m, blk.r, blk.r, v};
                    q.push(block{blk.m, v, blk.c + 1});
                }
            for (int i = 0; i < n; i++)
                if (blk.m & (1 << i))
                    for (auto v : g[i])
                        if (v != blk.r && !(blk.m & (1 << v)) && d[(blk.m ^ (1 << i)) | (1 << v)][blk.r] > blk.c + 1) {
                            d[(blk.m ^ (1 << i)) | (1 << v)][blk.r] = blk.c + 1;
                            p[(blk.m ^ (1 << i)) | (1 << v)][blk.r] = edge{blk.m, blk.r, i, v};
                            q.push(block{(blk.m ^ (1 << i)) | (1 << v), blk.r, blk.c + 1});
                        }
        }
        cout << "Case " << cs << ": ";
        int r = 0x3f3f3f3f, u;
        for (int i = 0; i < (1 << n); i++)
            if (__builtin_popcount(i) == M)
                if (r > d[i][t]) {
                    r = d[i][t];
                    u = i;
                }
        if (r == 0x3f3f3f3f) cout << "-1\n";
        else {
            cout << r << '\n';
            dfs(u, t);
        }
        cout << '\n';
    }
    return 0;
}
