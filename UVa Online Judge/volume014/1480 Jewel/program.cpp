#include <bits/stdc++.h>
using namespace std;

struct Oper {
    string typ;
    int a, b, c;
};

vector<int> ls, rs, sm, bit, rt, vals;

int upd(int pre, int l, int r, int p) {
    int cur = ls.size();
    ls.push_back(ls[pre]);
    rs.push_back(rs[pre]);
    sm.push_back(sm[pre] + 1);
    if (l == r) return cur;
    int mid = (l + r) >> 1;
    if (p <= mid) ls[cur] = upd(ls[pre], l, mid, p);
    else rs[cur] = upd(rs[pre], mid + 1, r, p);
    return cur;
}

int kth(int x, int y, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) >> 1;
    int cnt = sm[ls[y]] - sm[ls[x]];
    if (k <= cnt) return kth(ls[x], ls[y], l, mid, k);
    return kth(rs[x], rs[y], mid + 1, r, k - cnt);
}

void add(int p, int n) {
    while (p <= n) {
        bit[p]++;
        p += p & -p;
    }
}

int sum(int p) {
    int res = 0;
    while (p > 0) {
        res += bit[p];
        p -= p & -p;
    }
    return res;
}

int getK(int k, int n) {
    int p = 1;
    while (p < n) p <<= 1;
    int pos = 0;
    for (; p > 0; p >>= 1) {
        int nxt = pos + p;
        if (nxt <= n && bit[nxt] < k) {
            pos = nxt;
            k -= bit[nxt];
        }
    }
    return pos + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, cas = 0;
    while (cin >> n) {
        vector<Oper> ops;
        vector<int> ins;
        int i;
        for (i = 0; i < n; i++) {
            Oper op;
            cin >> op.typ;
            op.a = op.b = op.c = 0;
            if (op.typ == "Insert") {
                cin >> op.a;
                ins.push_back(op.a);
            } else if (op.typ == "Query_1") {
                cin >> op.a >> op.b >> op.c;
            } else {
                cin >> op.a;
            }
            ops.push_back(op);
        }
        vals = ins;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        int m = vals.size();
        ls.clear();
        rs.clear();
        sm.clear();
        rt.clear();
        bit.assign(m + 1, 0);
        ls.push_back(0);
        rs.push_back(0);
        sm.push_back(0);
        rt.push_back(0);
        ls.reserve(m * 32 + 1);
        rs.reserve(m * 32 + 1);
        sm.reserve(m * 32 + 1);
        long long ans1 = 0, ans2 = 0, ans3 = 0;
        int len = 0;
        for (i = 0; i < n; i++) {
            Oper op = ops[i];
            if (op.typ == "Insert") {
                int p = lower_bound(vals.begin(), vals.end(), op.a) - vals.begin() + 1;
                rt.push_back(upd(rt.back(), 1, m, p));
                add(p, m);
                len++;
            } else if (op.typ == "Query_1") {
                int p = kth(rt[op.a - 1], rt[op.b], 1, m, op.c);
                ans1 += vals[p - 1];
            } else if (op.typ == "Query_2") {
                int p = lower_bound(vals.begin(), vals.end(), op.a) - vals.begin() + 1;
                ans2 += sum(p);
            } else {
                int p = getK(op.a, m);
                ans3 += vals[p - 1];
            }
        }
        cas++;
        cout << "Case " << cas << ":\n";
        cout << ans1 << "\n" << ans2 << "\n" << ans3 << "\n";
    }
    return 0;
}
