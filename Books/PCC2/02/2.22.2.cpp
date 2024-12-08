#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

struct NODE {
    int s[2], p, w;
    int cnt;
    int size;
    void set(int _p, int _w) {
        s[0] = s[1] = 0;
        p = _p, w = _w;
        cnt = size = 1;
    }
}tr[MAXN];

int idx = 0;
int root = 0;

void pushUp(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + tr[x].cnt;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushUp(y), pushUp(x);
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

int find(int w) {
    int u = root;
    while (u) {
        if (w == tr[u].w) break;
        else u = tr[u].s[w > tr[u].w];
    }
    if (u) { splay(u, 0); return u; }
    else return -1;
}

void insert(int w) {
    int u = root, p = 0;
    while (u) {
        if (w == tr[u].w) {
            tr[u].cnt += 1;
            break;
        }
        p = u;
        u = tr[u].s[w > tr[u].w];
    }
    if (!u) {
        u = ++idx;
        if (p) tr[p].s[w > tr[p].w] = u;
        tr[u].set(p, w);
    }
    pushUp(u);
    splay(u, 0);
}

int remove(int w) {
    int u = find(w);
    if (u == -1) return -1;
    tr[u].cnt--;
    if (tr[u].cnt) return u;
    if (tr[u].s[0] && tr[u].s[1]) {
        tr[tr[u].s[0]].p = 0;
        int v = tr[u].s[0];
        while (tr[v].s[1]) v = tr[v].s[1];
        splay(v, 0);
        tr[v].s[1] = tr[u].s[1];
        tr[tr[u].s[1]].p = v;
        pushUp(v);
    } else {
        tr[tr[u].s[0]].p = tr[tr[u].s[1]].p = 0;
        splay(tr[u].s[0] | tr[u].s[1], 0);
    }
    return u;
}

int getRank(int w) {
    insert(w);
    int r = 1;
    if (tr[root].s[0]) r += tr[tr[root].s[0]].size;
    remove(w);
    return r;
}

int getKth(int k) {
    int u = root;
    while (true) {
        if (k <= tr[tr[u].s[0]].size) u = tr[u].s[0];
        else if (k <= tr[tr[u].s[0]].size + tr[u].cnt) return tr[u].w;
        else k -= tr[tr[u].s[0]].size + tr[u].cnt, u = tr[u].s[1];
    }
}

int getPrevious() {
    int u = tr[root].s[0];
    while (tr[u].s[1]) u = tr[u].s[1];
    return tr[u].w;
}

int getNext() {
    int u = tr[root].s[1];
    while (tr[u].s[0]) u = tr[u].s[0];
    return tr[u].w;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n, cmd, x;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cmd >> x;
        if (cmd == 1) insert(x);
        if (cmd == 2) remove(x);
        if (cmd == 3) cout << getRank(x) << '\n';
        if (cmd == 4) cout << getKth(x) << '\n';
        if (cmd == 5) { insert(x); cout << getPrevious() << '\n'; remove(x); }
        if (cmd == 6) { insert(x); cout << getNext() << '\n'; remove(x); }
    }
    return 0;
}
