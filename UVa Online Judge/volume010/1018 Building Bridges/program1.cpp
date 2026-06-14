// Building Bridges
// UVa ID: 1018
// Verdict: Accepted
// Submission Date: 2026-06-14
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int N = 105, M = 10005;
int r, c, cnt, comp[N][N], pa[M];
char g[N][N];
int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

struct Bld { int mnr, mxr, mnc, mxc; vector<pair<int,int>> cel; } b[M];
struct Bridge { int u, v, len; bool operator<(const Bridge& o) const { return len < o.len; } };
vector<Bridge> br;

void dfs(int x, int y, int id) {
    if (x < 0 || x >= r || y < 0 || y >= c || g[x][y] != '#' || comp[x][y] != -1) return;
    comp[x][y] = id;
    b[id].cel.push_back({x, y});
    b[id].mnr = min(b[id].mnr, x); b[id].mxr = max(b[id].mxr, x);
    b[id].mnc = min(b[id].mnc, y); b[id].mxc = max(b[id].mxc, y);
    for (int d = 0; d < 8; d++) dfs(x + dx[d], y + dy[d], id);
}

int find(int x) { return pa[x] == x ? x : pa[x] = find(pa[x]); }

void solve(int num) {
    memset(comp, -1, sizeof comp);
    cnt = 0;
    for (int i = 0; i < M; i++) b[i].mnr = b[i].mnc = 1e9, b[i].mxr = b[i].mxc = -1e9, b[i].cel.clear();
    for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) if (g[i][j] == '#' && comp[i][j] == -1) dfs(i, j, cnt++);
    if (cnt < 2) { printf("City %d\nNo bridges are needed.\n", num); return; }
    br.clear();
    for (int i = 0; i < cnt; i++) for (int j = i + 1; j < cnt; j++) {
        int mn = 1e9;
        for (auto& a : b[i].cel) for (auto& bj : b[j].cel) {
            int dr = abs(a.first - bj.first), dc = abs(a.second - bj.second);
            if (dr <= 1) mn = min(mn, dc - 1);
            if (dc <= 1) mn = min(mn, dr - 1);
        }
        if (mn < 1e9) br.push_back({i, j, mn});
    }
    sort(br.begin(), br.end());
    for (int i = 0; i < cnt; i++) pa[i] = i;
    int tot = 0, used = 0;
    for (auto& b : br) {
        int ru = find(b.u), rv = find(b.v);
        if (ru != rv) pa[ru] = rv, tot += b.len, used++;
    }
    int grp = 0;
    for (int i = 0; i < cnt; i++) if (find(i) == i) grp++;
    printf("City %d\n", num);
    if (!used) printf("No bridges are possible.\n");
    else printf("%d bridge%s of total length %d\n", used, used == 1 ? "" : "s", tot);
    if (grp > 1) printf("%d disconnected groups\n", grp);
}

int main() {
    int cas = 0;
    while (scanf("%d %d", &r, &c), r || c) {
        for (int i = 0; i < r; i++) scanf("%s", g[i]);
        if (cas) printf("\n");
        solve(++cas);
    }
    return 0;
}
