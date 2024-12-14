// Permutation Transformer
// UVa ID: 11922
// Verdict: Accepted
// Submission Date: 2024-12-14
// UVa Run Time: 0.240s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010, INF = 0x3f3f3f3f;

struct NODE {
    int s[2], p, w;
    int size, reversed;
    void set(int _p, int _w) {
        s[0] = s[1] = 0;
        p = _p, w = _w;
        size = 1;
        reversed = 0;
    }
}tr[MAXN];

int data[MAXN], idx = 0, root = 0;

void commitReversed(int x) {
    if (!x) return;
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].reversed ^= 1;
}

void pushDown(int x) {
    if (tr[x].reversed) {
        tr[x].reversed = 0;
        commitReversed(tr[x].s[0]);
        commitReversed(tr[x].s[1]);
    }
}

void pushUp(int x) {
    int u = tr[x].s[0], v = tr[x].s[1];
    tr[x].size = tr[u].size + tr[v].size + 1;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushUp(y); pushUp(x);
}

void splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
    if (!k) root = x;
}

int find(int k) {
    int u = root;
    while (true) {
        pushDown(u);
        if (k <= tr[tr[u].s[0]].size) u = tr[u].s[0];
        else if (k <= tr[tr[u].s[0]].size + 1) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
}

int build(int p, int left, int right) {
    if (left > right) return 0;
    int middle = (left + right) >> 1;
    int u = ++idx;
    tr[u].set(p, data[middle]);
    tr[u].s[0] = build(u, left, middle - 1);
    tr[u].s[1] = build(u, middle + 1, right);
    pushUp(u);
    return u;
}

void traversal(int u) {
    if (!u) return;
    pushDown(u);
    traversal(tr[u].s[0]);
    if (tr[u].w > 0) cout << tr[u].w << '\n';
    traversal(tr[u].s[1]);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m, a, b;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) data[i] = i;
    tr[0].set(0, 0); tr[0].size = 0;
    data[0] = data[n + 1] = -INF;
    root = build(0, 0, n + 1);
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        int left = find(a), right = find(b + 2);
        splay(left, 0); splay(right, left);
        int u = tr[right].s[0];
        commitReversed(u);
        tr[right].s[0] = 0;
        pushUp(right); pushUp(left);
        left = find(n - b + a), right = find(n - b + a + 1);
        splay(left, 0); splay(right, left);
        tr[right].s[0] = u;
        tr[u].p = right;
        pushUp(right); pushUp(left);
    }
    traversal(root);
    return 0;
}
