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

int root = 0;
int idx = 0;

void pushup(int x) {
    tr[x].size = tr[tr[x].s[0]].size + tr[tr[x].s[1]].size + tr[x].cnt;
}

void rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushup(y), pushup(x);
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

void split(int &x, int &y, int k) {

}

void merge(int x, int y) {

}


void traversal(int u) {
    if (!u) return;
    traversal(tr[u].s[0]);
    cout << ' ' << tr[u].w << '[' << tr[u].cnt << ',' << tr[u].size << ']';
    cout << '[';
    if (tr[u].s[0]) cout << tr[tr[u].s[0]].w;
    else cout << -1;
    cout << ',';
    if (tr[u].s[1]) cout << tr[tr[u].s[1]].w;
    else cout << -1;
    cout << ']';
    traversal(tr[u].s[1]);
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
        pushup(v);
    } else {
        tr[tr[u].s[0]].p = tr[tr[u].s[1]].p = 0;
        splay(tr[u].s[0] | tr[u].s[1], 0);
    }
    return u;
}

int getkth(int k) {
    int u = root;
    if (k > tr[u].size) return -1;
    while (u) {
        if (k <= tr[tr[u].s[0]].size) u = tr[u].s[0];
        else if (k <= tr[tr[u].s[0]].size + tr[u].cnt) return u;
        else k -= tr[tr[u].s[0]].size + tr[u].cnt, u = tr[u].s[1];
    }
    return -1;
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    for (int i = 1; i <= 1000; i++) {
        int cases = rand() % 4;
        if (cases == 0) {
            cout << "INSERT:\n";
            int w = rand() % 20;
            cout << w << '\n';
            insert(w);
            traversal(root);
            cout << '\n';
        } else if (cases == 1) {
            cout << "FIND:\n";
            int w = rand() % 20;
            cout << w << '\n';
            int u = find(w);
            cout << w << ' ' << u << '\n';
        } else if (cases == 2) {
            cout << "REMOVE:\n";
            int w = rand() % 20;
            cout << w << '\n';
            int u = remove(w);
            cout << u << '\n';
            traversal(root);
            cout << '\n';
        } else if (cases == 3) {
            cout << "GET KTH:\n";
            int k = rand() % 20;
            int u = getkth(k);
            cout << k;
            if (u != -1) cout << ' ' << tr[u].w;
            else cout << ' ' << -1;
            cout << '\n';
        } else if (cases == 4) {
        
        }
    }
    return 0;
}
