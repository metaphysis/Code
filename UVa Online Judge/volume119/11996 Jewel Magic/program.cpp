// Jewel Magic
// UVa ID: 11996
// Verdict: Accepted
// Submission Date: 2024-12-16
// UVa Run Time: 2.390s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500010, BASE = 16777213, MOD = 2147483647;

struct NODE {
    int s[2], p, w;
    long long h[2];
    int size, reversed;
    void set(int _p, int _w) {
        s[0] = s[1] = 0;
        p = _p, h[0] = h[1] = w = _w;
        size = 1;
        reversed = 0;
    }
}tr[MAXN];

long long b[MAXN];
int cache[MAXN], data[MAXN];
int idx = 0, cidx = 0, root = 0;

void commitReversed(int x) {
    if (!x) return;
    swap(tr[x].s[0], tr[x].s[1]);
    swap(tr[x].h[0], tr[x].h[1]);
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
    tr[x].h[0] = (tr[u].h[0] + tr[x].w * b[tr[u].size] + tr[v].h[0] * b[tr[u].size + 1]) % MOD;
    tr[x].h[1] = (tr[v].h[1] + tr[x].w * b[tr[v].size] + tr[u].h[1] * b[tr[v].size + 1]) % MOD;
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

void insert() {
    int p; char c; cin >> p >> c;
    int left = find(p + 1), right = find(p + 2);
    splay(left, 0); splay(right, left);
    int u = malloc();
    tr[u].set(right, (int)c);
    tr[right].s[0] = u;
    pushUp(right); pushUp(left);
}

void recycle(int u) {
    if (!u) return;
    recycle(tr[u].s[0]);
    cache[cidx++] = u;
    recycle(tr[u].s[1]);
}

void remove() {
    int p; cin >> p;
    int left = find(p), right = find(p + 2);
    splay(left, 0); splay(right, left);
    recycle(tr[right].s[0]);
    tr[right].s[0] = 0;
    pushUp(right); pushUp(left);
}

void reverse() {
    int p1, p2; cin >> p1 >> p2;
    int left = find(p1), right = find(p2 + 2);
    splay(left, 0); splay(right, left);
    commitReversed(tr[right].s[0]);
    pushUp(right); pushUp(left);
}

void query() {
    int p1, p2; cin >> p1 >> p2;
    int L = 0, R = tr[root].size - 1 - max(p1, p2), M, A;
    while (L <= R) {
        M = (L + R) >> 1;
        int left = find(p1), right = find(p1 + M + 1);
        splay(left, 0); splay(right, left);
        long long h1 = tr[tr[right].s[0]].h[0];
        left = find(p2), right = find(p2 + M + 1);
        splay(left, 0); splay(right, left);
        long long h2 = tr[tr[right].s[0]].h[0];
        if (h1 == h2) A = M, L = M + 1;
        else R = M - 1;
    }
    cout << A << '\n';
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    b[0] = 1;
    for (int i = 1; i <= MAXN; i++) b[i] = b[i - 1] * BASE % MOD;
    int n, m; cin >> n >> m;
    char c;
    for (int i = 1; i <= n; i++) { cin >> c; data[i] = c; }
    tr[0].set(0, 0), tr[0].size = 0;
    data[0] = data[n + 1] = 0;
    root = build(0, 0, n + 1);
    int cmd;
    for (int i = 0; i < m; i++) {
        cin >> cmd;
        if (cmd == 1) insert();
        if (cmd == 2) remove();
        if (cmd == 3) reverse();
        if (cmd == 4) query();
    }
    return 0;
}
