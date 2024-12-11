// [LUOGU P2042](https://www.luogu.com.cn/problem/P2042)
// Splay Tree

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 500010;

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

int cache[MAXN >> 4];
int idx = 0, cidx = 0;
int root = 0;

void pushUp(int x) {
    int u = tr[x].s[0], v = tr[x].s[1];
    tr[x].size = tr[u].size + tr[v].size + 1;
    tr[x].sum = tr[u].sum + tr[v].sum + tr[x].w;
    tr[x].sub = max(max(tr[u].sub, tr[v].sub), tr[u].suffix + tr[x].w + tr[v].prefix); 
    tr[x].prefix = max(tr[u].prefix, tr[u].sum + tr[x].w + tr[v].prefix);
    tr[x].suffix = max(tr[v].suffix, tr[u].suffix + tr[x].w + tr[v].sum);
}

void pushDown(int x) {
    if (tr[x].same) {
        tr[x].sum = tr[x].size * tr[x].w;
        if (tr[x].w >= 0) tr[x].prefix = tr[x].suffix = tr[x].sub = tr[x].sum;
        else {
            tr[x].prefix = tr[x].suffix = 0;
            tr[x].sub = tr[x].w;
        }
        tr[tr[x].s[0]].same = tr[tr[x].s[1]].same = 1;
    }
    if (tr[x].reversed && !tr[x].same) {
        swap(tr[x].prefix, tr[x].suffix);
        tr[tr[x].s[0]].reversed ^= 1;
        tr[tr[x].s[1]].reversed ^= 1;
    }
    tr[x].same = tr[x].reversed = 0;
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

int find(int k) {
    int u = root;
    while (true) {
        pushDown(u);
        if (k <= tr[tr[u].s[0]].size) u = tr[u].s[0];
        else if (k <= tr[tr[u].s[0]].size + 1) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
}

int data[MAXN];

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
    int posi, tot;
    cin >> posi >> tot;
    for (int i = 0; i < tot; i++) cin >> data[i];
    int u = build(0, 0, tot - 1);
    int left = posi, right = posi + 1;
    if (left == 0) {
        right = find(left + 1);
        splay(right, 0);
        tr[right].s[0] = u;
        tr[u].p = right;
        pushUp(right);
    } else if (left == tr[root].size) {
        left = find(left);
        splay(left, 0);
        tr[left].s[1] = u;
        tr[u].p = left;
        pushUp(left);
    } else {
        left = find(left), right = find(right);
        splay(left, 0);
        splay(right, left);
        tr[right].s[0] = u;
        tr[u].p = right;
        pushUp(right);
        pushUp(left);
    }
}

void recycle(int u) {
    if (!u) return;
    recycle(tr[u].s[0]);
    cache[cidx++] = u;
    recycle(tr[u].s[1]);
}

void remove() {
    int posi, tot;
    cin >> posi >> tot;
    int left = posi - 1, right = posi + tot;
    if (left == 0) {
        right = find(right);
        splay(right, 0);
        int u = tr[right].s[0];
        tr[right].s[0] = 0;
        pushUp(right);
        recycle(u);
    } else {
        left = find(left), right = find(right);
        splay(left, 0);
        splay(right, left);
        int u = tr[right].s[0];
        tr[right].s[0] = 0;
        pushUp(right);
        pushUp(left);
        recycle(u);
    }
}

void makeSame() {
    int posi, tot;
    cin >> posi >> tot;
    int left = posi - 1, right = posi + tot;
    if (left == 0) {
        right = find(right);
        splay(right, 0);
        int u = tr[right].s[0];
        tr[u].same = 1;
    } else {
        left = find(left), right = find(right);
        splay(left, 0);
        splay(right, left);
        int u = tr[right].s[0];
        tr[u].same = 1;
    }
}

void reverse() {
    int posi, tot;
    cin >> posi >> tot;
    int left = posi - 1, right = posi + tot;
    if (left == 0) {
        right = find(right);
        splay(right, 0);
        int u = tr[right].s[0];
        tr[u].reversed ^= 1;
    } else {
        left = find(left), right = find(right);
        splay(left, 0);
        splay(right, left);
        int u = tr[right].s[0];
        tr[u].reversed ^= 1;
    }
}

void getSum() {
    int posi, tot;
    cin >> posi >> tot;
    int left = posi - 1, right = posi + tot;
    if (left == 0) {
        right = find(right);
        splay(right, 0);
        int u = tr[right].s[0];
        cout << tr[u].sum << '\n';
    } else {
        left = find(left), right = find(right);
        splay(left, 0);
        splay(right, left);
        int u = tr[right].s[0];
        cout << tr[u].sum << '\n';
    }
}

void maxSum() {
    cout << tr[root].sub << '\n';
}

void traversal(int u) {
    if (!u) return;
    traversal(tr[u].s[0]);
    cout << "u = " << u << " leftChild = " << tr[u].s[0] << " rightChild = " << tr[u].s[1] << '\n';
    cout << "tr[u].w = " << tr[u].w << '\n';
    cout << "tr[u].sum = " << tr[u].sum << '\n';
    cout << "tr[u].sub = " << tr[u].sub << '\n';
    cout << "tr[u].prefix = " << tr[u].prefix << '\n';
    cout << "tr[u].suffix = " << tr[u].suffix << '\n';
    cout << '\n';
    traversal(tr[u].s[1]);
}

int main(int argc, char *argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int N, M;
    tr[0].set(0, 0);
    tr[0].size = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> data[i];
    root = build(0, 0, N - 1);
    //traversal(root);
    string cmd;
    for (int i = 0; i < M; i++) {
        cin >> cmd;
        if (cmd == "INSERT") insert();
        else if (cmd == "DELETE") remove();
        else if (cmd == "MAKE-SAME") makeSame();
        else if (cmd == "REVERSE") reverse();
        else if (cmd == "GET-SUM") getSum();
        else maxSum();
    }
    return 0;
}
