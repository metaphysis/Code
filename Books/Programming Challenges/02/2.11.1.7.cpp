#include <bits/stdc++.h>

using namespace std;

#define LC(x) (((x) << 1) | 1)
#define RC(x) (((x) + 1) << 1)

const int MAXN = 1000010, INF = 0x7f7f7f7f;

int n, A[MAXN];
vector<int> st[MAXN << 2];

void build(int p, int left, int right) {
    if (left == right) st[p] = vector<int>(1, A[left]);
    else { 
        int mid = (left + right) >> 1;
        build(LC(p), left, mid);
        build(RC(p), mid + 1, right);
        merge(st[LC(p)].begin(), st[LC(p)].end(),
        st[RC(p)].begin(), st[RC(p)].end(), back_inserter(st[p]));
    }
}

int query(int p, int left, int right, int ql, int qr, int x) {
    if (ql > qr) return INF;
    if (ql == left && qr == right) {
        vector<int>::iterator idx = lower_bound(st[p].begin(), st[p].end(), x);
        if (idx != st[p].end())
            return *idx;
        return INF;
    }
    int mid = (left + right) >> 1;
    return min(query(LC(p), left, mid, ql, min(qr, mid), x), 
               query(RC(p), mid + 1, right, max(ql, mid + 1), qr, x));
}

multiset<int> st1[MAXN << 2];

void build1(int p, int left, int right) {
    if (left == right) st1[p].insert(A[left]);
    else { 
        int mid = (left + right) >> 1;
        build1(LC(p), left, mid);
        build1(RC(p), mid + 1, right);
        set_union(st1[LC(p)].begin(), st1[LC(p)].end(),
        st1[RC(p)].begin(), st1[RC(p)].end(), inserter(st1[p], st1[p].begin()));
    }
}

void update(int p, int left, int right, int idx, int value) {
    st1[p].erase(st1[p].find(A[idx]));
    st1[p].insert(value);
    if (left != right) {
        int mid = (left + right) >> 1;
        if (idx <= mid) update(LC(p), left, mid, idx, value);
        else update(RC(p), mid + 1, right, idx, value);
    } else A[idx] = value;
}

int query1(int p, int left, int right, int ql, int qr, int x) {
    if (ql > qr) return INF;
    if (ql == left && qr == right) {
        multiset<int>::iterator idx = st1[p].lower_bound(x);
        if (idx != st1[p].end())
            return *idx;
        return INF;
    }
    int mid = (left + right) >> 1;
    return min(query1(LC(p), left, mid, ql, min(qr, mid), x), 
               query1(RC(p), mid + 1, right, max(ql, mid + 1), qr, x));
}

vector<pair<int, int>> b[MAXN << 2];

void build2(int p, int left, int right) {
    if (left == right) st[p] = vector<int>(1, A[left]);
    else { 
        int mid = (left + right) >> 1;
        build2(LC(p), left, mid);
        build2(RC(p), mid + 1, right);
        int i = 0, j = 0;
        int nlc = st[LC(p)].size(), nrc = st[RC(p)].size();
        while (i < nlc && j < nrc) {
            if (st[LC(p)][i] <= st[RC(p)][j]) {
                st[p].push_back(st[LC(p)][i]);
                b[p].push_back(make_pair(i, j));
                i++;
            } else {
                st[p].push_back(st[RC(p)][j]);
                b[p].push_back(make_pair(i, j));
                j++;
            }
        }
        while (i < nlc) {
            st[p].push_back(st[LC(p)][i]);
            b[p].push_back(make_pair(i, -1));
            i++;
        }
        while (j < nrc) {
            st[p].push_back(st[RC(p)][j]);
            b[p].push_back(make_pair(-1, j));
            j++;
        }
    }
}

int query2(int p, int left, int right, int ql, int qr, int idx) {
    if (ql > qr) return INF;
    if (ql == left && qr == right) {
        if (idx == -1) return INF;
        return st[p][idx];
    }
    int mid = (left + right) >> 1;
    return min(query2(LC(p), left, mid, ql, min(qr, mid), b[p][idx].first), 
        query2(RC(p), mid + 1, right, max(ql, mid + 1), qr, b[p][idx].second));
}

int main(int argc, char *argv[]) {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> A[i];
    int rt = 0;
    build2(0, 0, n - 1);
    int l, r, x;
    while (cin >> l >> r >> x) {
        int idx = lower_bound(st[rt].begin(), st[rt].end(), x) - st[rt].begin();
        if (idx == st[rt].size()) { cout << "Not exists!\n"; continue; }
        int y = query2(rt, 0, n - 1, l, r, idx);
        if (y != INF) cout << y << '\n';
        else cout << "Not exists!\n" << '\n';
    }
    return 0;
}
