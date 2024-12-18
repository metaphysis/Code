// [LUOGU P2042](https://www.luogu.com.cn/problem/P2042)
// Splay Tree

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500010, INF = 0x3f3f3f3f;

struct NODE {
    int s[2], p, w;
    int size, same, reversed, sum, prefix, suffix, sub;
    void set(int _p, int _w) {
        s[0] = s[1] = 0;
        p = _p, w = _w;
        size = 1;
        same = reversed = 0;
        sum = sub = _w;
        prefix = suffix = max(_w, 0);
    }
}tr[MAXN];

int cache[MAXN], data[MAXN];
int idx = 0, cidx = 0, root = 0;

void commitSame(int x, int w) {
    if (!x) return;
    tr[x].w = w;
    tr[x].sum = tr[x].size * w;
    if (w >= 0) tr[x].prefix = tr[x].suffix = tr[x].sub = tr[x].sum;
    else {
        tr[x].prefix = tr[x].suffix = 0;
        tr[x].sub = w;
    }
    tr[x].same = 1;
}

void commitReversed(int x) {
    if (!x) return;
    swap(tr[x].s[0], tr[x].s[1]);
    swap(tr[x].prefix, tr[x].suffix);
    tr[x].reversed ^= 1;
}

void pushDown(int x) {
    if (tr[x].same) {
        tr[x].same = tr[x].reversed = 0;
        commitSame(tr[x].s[0], tr[x].w);
        commitSame(tr[x].s[1], tr[x].w);
    }
    if (tr[x].reversed) {
        tr[x].reversed = 0;
        commitReversed(tr[x].s[0]);
        commitReversed(tr[x].s[1]);
    }
}

void pushUp(int x) {
    int u = tr[x].s[0], v = tr[x].s[1];
    tr[x].size = tr[u].size + tr[v].size + 1;
    tr[x].sum = tr[u].sum + tr[v].sum + tr[x].w;
    tr[x].sub = max(max(tr[u].sub, tr[v].sub),
        tr[u].suffix + tr[x].w + tr[v].prefix);
    tr[x].prefix = max(tr[u].prefix, tr[u].sum + tr[x].w + tr[v].prefix);
    tr[x].suffix = max(tr[v].suffix, tr[u].suffix + tr[x].w + tr[v].sum);
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

int malloc() {
    if (cidx) return cache[--cidx];
    return ++idx;
}

int build(int p, int left, int right) {
    if (left > right) return 0;
    int middle = (left + right) >> 1;
    int u = malloc();
    tr[u].set(p, data[middle]);
    tr[u].s[0] = build(u, left, middle - 1);
    tr[u].s[1] = build(u, middle + 1, right);
    pushUp(u);
    return u;
}

int split(int posi, int tot) {
    int left = find(posi), right = find(posi + tot + 1);
    splay(left, 0); splay(right, left);
    return right;
}

void insert(int posi, int tot) {
    for (int i = 0; i < tot; i++) cin >> data[i];
    int v = build(0, 0, tot - 1);
    int left = find(posi + 1), right = find(posi + 2);
    splay(left, 0); splay(right, left);
    tr[right].s[0] = v;
    tr[v].p = right;
    pushUp(right); pushUp(left);
}

void recycle(int u) {
    if (!u) return;
    recycle(tr[u].s[0]);
    cache[cidx++] = u;
    recycle(tr[u].s[1]);
}

void remove(int posi, int tot) {
    int u = split(posi, tot);
    recycle(tr[u].s[0]);
    tr[u].s[0] = 0;
    pushUp(u); pushUp(tr[u].p);
}

void modify(int posi, int tot, int c) {
    int u = split(posi, tot);
    commitSame(tr[u].s[0], c);
    pushUp(u); pushUp(tr[u].p);
}

void reverse(int posi, int tot) {
    int u = split(posi, tot);
    commitReversed(tr[u].s[0]);
    pushUp(u); pushUp(tr[u].p);
}

void getSum(int posi, int tot) {
    int u = split(posi, tot);
    cout << tr[tr[u].s[0]].sum << '\n';
}

void getMaxSum() { cout << tr[root].sub << '\n'; }

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    string cmd;
    int N, M, posi, tot, c;
    cin >> N >> M;
    for (int i = 1; i <= N; i++) cin >> data[i];
    tr[0].set(0, 0), tr[0].size = 0;
    tr[0].sub = data[0] = data[N + 1] = -INF;
    root = build(0, 0, N + 1);
    for (int i = 0; i < M; i++) {
        cin >> cmd;
        if (cmd != "MAX-SUM") cin >> posi >> tot;
        if (cmd == "INSERT") insert(posi, tot);
        else if (cmd == "DELETE") remove(posi, tot);
        else if (cmd == "MAKE-SAME") { cin >> c; modify(posi, tot, c); }
        else if (cmd == "REVERSE") reverse(posi, tot);
        else if (cmd == "GET-SUM") getSum(posi, tot);
        else getMaxSum();
    }
    return 0;
}
