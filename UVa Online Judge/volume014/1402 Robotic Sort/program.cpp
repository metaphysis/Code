// Robotic Sort
// UVa ID: 1402
// Verdict: Accepted
// Submission Date: 2024-12-14
// UVa Run Time: 0.670s
//
// 版权所有（C）2024，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010, INF = 0x3f3f3f3f;

struct NODE {
    int s[2], p, w, pos, mpos, mid;
    int size, reversed;
    void set(int _p, int _w, int _pos, int _mid) {
        s[0] = s[1] = 0;
        p = _p, w = _w, pos = _pos, mpos = _pos, mid = _mid;
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
    tr[x].mid = x, tr[x].mpos = tr[x].pos;
    if (tr[tr[x].mid].w > tr[tr[u].mid].w ||
        (tr[tr[x].mid].w == tr[tr[u].mid].w && tr[tr[u].mid].pos < tr[x].mpos)) {
            tr[x].mid = tr[u].mid;
            tr[x].mpos = tr[u].mpos;
    }
    if (tr[tr[x].mid].w > tr[tr[v].mid].w ||
        (tr[tr[x].mid].w == tr[tr[v].mid].w && tr[tr[v].mid].pos < tr[x].mpos)) {
            tr[x].mid = tr[v].mid;
            tr[x].mpos = tr[v].mpos;
    }
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
    tr[u].set(p, data[middle], middle, u);
    tr[u].s[0] = build(u, left, middle - 1);
    tr[u].s[1] = build(u, middle + 1, right);
    pushUp(u);
    return u;
}

int path[MAXN], pidx = 0;

int getPos(int x) {
    pidx = 0;
    path[pidx++] = x;
    int u = x;
    while (tr[u].p) {
        path[pidx++] = tr[u].p;
        u = tr[u].p;
    }
    for (int i = pidx - 1; i >= 0; i--) pushDown(path[i]);
    int r = tr[tr[x].s[0]].size;
    while (tr[x].p) {
        if (x == tr[tr[x].p].s[1]) r += tr[tr[tr[x].p].s[0]].size + 1;
        x = tr[x].p;
    }
    return r;
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int n;
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> data[i];
        tr[0].set(0, INF, INF, 0); tr[0].size = 0;
        data[0] = data[n + 1] = INF;
        root = build(0, 0, n + 1);
        for (int i = 1; i <= n; i++) {
            int left = find(i), right = find(n + 2);
            splay(left, 0); splay(right, left);
            int Pi = getPos(tr[tr[right].s[0]].mid);
            cout << Pi << " \n"[i == n];
            right = find(Pi + 2);
            splay(right, left);
            commitReversed(tr[right].s[0]);
        }
    }
    return 0;
}
