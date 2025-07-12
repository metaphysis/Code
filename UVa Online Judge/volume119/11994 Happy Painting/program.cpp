// Happy Painting
// UVa ID: 11994
// Verdict: Accepted
// Submission Date: 2025-06-14
// UVa Run Time: 0.490s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

#define LC(x) tr[x].s[0]
#define RC(x) tr[x].s[1]

struct NODE { int s[2], p, v, mask, size, lazy, reversed; } tr[MAXN];

bool isRoot(int x) { return LC(tr[x].p) != x && RC(tr[x].p) != x; }

void pushUp(int x) {
    if (!x) return;
    tr[x].mask = tr[x].v, tr[x].size = 1;
    if (LC(x)) tr[x].size += tr[LC(x)].size, tr[x].mask |= tr[LC(x)].mask;
    if (RC(x)) tr[x].size += tr[RC(x)].size, tr[x].mask |= tr[RC(x)].mask;
}

void commitReversed(int x) {
    if (!x) return;
    swap(LC(x), RC(x));
    tr[x].reversed ^= 1;
}

void pushDown(int x) {
    if (tr[x].reversed) {
        commitReversed(LC(x));
        commitReversed(RC(x));
        tr[x].reversed = 0;
    }
    if (tr[x].lazy) {
        if (LC(x)) tr[LC(x)].v = tr[LC(x)].mask = tr[LC(x)].lazy = tr[x].lazy;
        if (RC(x)) tr[RC(x)].v = tr[RC(x)].mask = tr[RC(x)].lazy = tr[x].lazy;
        tr[x].lazy = 0;
    }
}

void updatePath(int x) {
    if (!isRoot(x)) updatePath(tr[x].p);
    pushDown(x);
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    if (!isRoot(y)) tr[z].s[tr[z].s[1] == y] = x;
    tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushUp(y); pushUp(x);
}

void splay(int x) {
    updatePath(x);
    while (!isRoot(x)) {
        int y = tr[x].p, z = tr[y].p;
        if (!isRoot(y)) {
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

void access(int x) {
    for (int p = 0; x; p = x, x = tr[x].p) {
        splay(x);
        tr[x].s[1] = p;
        pushUp(x);
    }
}

void makeRoot(int x) {
    access(x);
    splay(x);
    commitReversed(x);
}

int findRoot(int x) {
    access(x);
    splay(x);
    while (tr[x].s[0]) {
        pushDown(x);
        x = tr[x].s[0];
    }
    splay(x);
    return x;
}

void link(int x, int y) {
    makeRoot(x);
    if (findRoot(y) != x) tr[x].p = y;
}

void cut(int x, int y) {
    makeRoot(x);
    if (findRoot(y) == x && tr[y].p == x && !tr[y].s[0]) {
        tr[y].p = tr[x].s[1] = 0;
        pushUp(x);
    }
}

int _cut(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
    int fy = LC(y);
    while (RC(fy)) fy = RC(fy);
    tr[LC(y)].p = tr[y].p;
    tr[y].p = LC(y) = 0;
    return fy;
}

void change(int x, int y, int c) {
    if (x == y) return;
    int rx = findRoot(x), fx = 0;
    if (rx != x) fx = _cut(rx, x);
    if (x == findRoot(y)) {
        if (fx) link(x, fx);
    } else {
        link(x, y);
        tr[x].v = c;
    }
}

void paint(int x, int y, int c) {
    if (x == y || findRoot(x) != findRoot(y)) return;
    access(x), splay(x);
    for (int a = y, b = 0; a; a = tr[a].p) {
        splay(a);
        if (!tr[a].p) {
            if (RC(a)) tr[RC(a)].v = tr[RC(a)].mask = tr[RC(a)].lazy = c;
            if (b) tr[b].v = tr[b].mask = tr[b].lazy = c;
        }
        RC(a) = b;
        b = a;
        pushUp(b);
    }
}

pair<int, int> query(int x, int y) {
    if (x == y || findRoot(x) != findRoot(y)) return {0, 0};
    access(x), splay(x);
    pair<int, int > r = {0, 0};
    for (int a = y, b = 0; a; a = tr[a].p) {
        splay(a);
        pushDown(a);
        if (!tr[a].p) r = {tr[RC(a)].size + tr[b].size, tr[RC(a)].mask | tr[b].mask};
        RC(a) = b;
        b = a;
        pushUp(b);
    }
    return r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m, cmd, x, y, c;
    int f[MAXN];
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        tr[i].p = tr[i].s[0] = tr[i].s[1] = 0;
        tr[i].v = tr[i].mask = tr[i].reversed = 0;
        tr[i].size = i ? 1 : 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> f[i];
        if (f[i]) tr[i].p = f[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> c;
        if (f[i]) tr[i].v = 1 << (c - 1);
    }

    for (int i = 1; i <= m; i++) {
        cin >> cmd;
        if (cmd == 1) {
            cin >> x >> y >> c;
            change(x, y, 1 << (c - 1));
        }
        if (cmd == 2) {
            cin >> x >> y >> c;
            paint(x, y, 1 << (c - 1));
        }
        if (cmd == 3) {
            cin >> x >> y;
            pair<int, int> r = query(x, y);
            cout << r.first << ' ' << __builtin_popcount(r.second) << '\n';
        }
    }
    return 0;
}
