// Rotate to Root
// UVa ID: 11688
// Verdict: Accepted
// Submission Date: 2026-06-14
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 100;
int lch[MAXN], rch[MAXN], isChild[MAXN];
int h[MAXN], answer[MAXN];

int dfs1(int u) {
    if (u == 0) return h[u] = 0;
    h[u] = max(dfs1(lch[u]), dfs1(rch[u])) + 1;
    return h[u];
}

void dfs2(int u, int hl, int hr, int dl, int dr) {
    if (u == 0) return;
    int dL = h[lch[u]], dR = h[rch[u]];
    answer[u] = 1 + max(max(hl, hr), max(dL + dl, dR + dr));
    dfs2(lch[u], hl, max(hr, dr + dR + 1), dl, dr + 1);
    dfs2(rch[u], max(hl, dl + dL + 1), hr, dl + 1, dr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n, n) {
        memset(lch, 0, sizeof lch);
        memset(rch, 0, sizeof rch);
        memset(isChild, 0, sizeof isChild);
        for (int i = 1; i <= n; ++i) {
            int l, r;
            cin >> l >> r;
            lch[i] = l;
            rch[i] = r;
            isChild[l] = isChild[r] = 1;
        }
        int root = 1;
        while (root <= n && isChild[root]) root++;
        dfs1(root);
        dfs2(root, 0, 0, 0, 0);
        for (int i = 1; i <= n; ++i) cout << answer[i] << '\n';
    }
    return 0;
}
