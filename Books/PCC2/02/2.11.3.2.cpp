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
    if (left == right) return new node(0);
    int mid = (left + right) / 2;
    return new node(build(left, mid), build(mid + 1, right));
}

node* update(node* p, int left, int right, int idx) {
    if (left == right) return new node(p->sum + 1);
    int mid = (left + right) / 2;
    if (idx <= mid) return new node(update(p->lc, left, mid, idx), p->rc);
    else return new node(p->lc, update(p->rc, mid + 1, right, idx));
}

int findKth(node* pl, node *pr, int left, int right, int k) {
    if (left == right) return left;
    int mid = (left + right) / 2, remain = pr->lc->sum - pl->lc->sum;
    if (remain >= k) return findKth(pl->lc, pr->lc, left, mid, k);
    return findKth(pl->rc, pr->rc, mid + 1, right, k - remain);
}

int main(int argc, char *argv[])
{
    vector<int> B;
    for (int i = 0; i < n; i++) B.push_back(A[i]);
    sort(B.begin(), B.end());
    B.erase(unique(B.begin(), B.end()), B.end());
    map<int, int> A2B, B2A;
    for (int i = 0; i < n; i++) {
        A2B[A[i]] = lower_bound(B.begin(), B.end(), A[i]) - B.begin();
        B2A[A2B[A[i]]] = A[i];
    }
        
    int left = 0, right = B.size() + 1;
    vector<node*> roots;
    roots.push_back(build(left, right));
    for (int i = 0; i < n; i++)
        roots.push_back(update(roots.back(), left, right, A2B[A[i]]));

    int l = 4, r = 32, k = 8;
    int idx = findKth(roots[4], roots[32], left, right, 8);
    cout << B2A[idx] << '\n';

    return 0;
}
