// [LUOGU P3369](https://www.luogu.com.cn/problem/P3690)
// Link-Cut Tree

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100010;

struct NODE { int s[2], p, w, v, reversed; } tr[MAXN];

bool isRoot(int x) { return tr[tr[x].p].s[0] != x && tr[tr[x].p].s[1] != x; }

void pushUp(int x) {
    tr[x].v = tr[tr[x].s[0]].v ^ tr[tr[x].s[1]].v ^ tr[x].w;
}

void commitReversed(int x) {
    if (!x) return;
    swap(tr[x].s[0], tr[x].s[1]);
    tr[x].reversed ^= 1;
}

void pushDown(int x) {
    if (tr[x].reversed) {
        commitReversed(tr[x].s[0]);
        commitReversed(tr[x].s[1]);
        tr[x].reversed = 0;
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

void split(int x, int y) {
    makeRoot(x);
    access(y);
    splay(y);
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

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, m, cmd, x, y;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        tr[i].s[0] = tr[i].s[1] = tr[i].p = tr[i].reversed = tr[i].v = 0;
        if (i) cin >> tr[i].w;
    }
    for (int i = 1; i <= m; i++) {
        cin >> cmd >> x >> y;
        if (cmd == 0) { split(x, y); cout << tr[y].v << '\n'; }
        if (cmd == 1) link(x, y);
        if (cmd == 2) cut(x, y);
        if (cmd == 3) { splay(x); tr[x].w = y; }
    }
    return 0;
}
