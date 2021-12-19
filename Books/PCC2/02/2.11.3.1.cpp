#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

struct node {
    int sum;
    node *lc, *rc;

    node(int v): lc(nullptr), rc(nullptr), sum(v) {}
    node(node *lc, node *rc): lc(lc), rc(rc), sum(0) {
        if (lc) sum += lc->sum;
        if (rc) sum += rc->sum;
    }
};

int n, A[MAXN];

node* build(int left, int right) {
    if (left == right) return new node(A[left]);
    int mid = (left + right) >> 1;
    return new node(build(left, mid), build(mid + 1, right));
}

int query(node* p, int left, int right, int ql, int qr) {
    if (ql > qr) return 0;
    if (left == ql && right == qr) return p->sum;
    int mid = (left + right) >> 1;
    return query(p->lc, left, mid, ql, min(qr, mid)) +
        query(p->rc, mid + 1, right, max(left, mid + 1), right);
}

node* update(node* p, int left, int right, int idx, int v) {
    if (left == right) return new node(v);
    int mid = (left + right) >> 1;
    if (idx <= mid) return new node(update(p->lc, left, mid, idx, v), p->rc);
    else return new node(p->lc, update(p->rc, mid + 1, right, idx, v));
}

int main(int argc, char *argv[])
{
    return 0;
}
