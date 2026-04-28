// Bulky Process of Bulk Reduction
// UVa ID: 12501
// Verdict: Accepted
// Submission Date: 2026-04-27
// UVa Run Time: 0.590s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100010;

struct Node {
    ll sumA, sumKA, lazy;
} tree[MAXN << 2];

int n, q;

// 计算区间 [l, r] 的下标和
ll getSumK(int l, int r) {
    return (ll)(l + r) * (r - l + 1) / 2;
}

void build(int idx, int l, int r) {
    tree[idx].lazy = 0;
    if (l == r) {
        tree[idx].sumA = 100;
        tree[idx].sumKA = 100LL * l;
        return;
    }
    int mid = (l + r) >> 1;
    build(idx << 1, l, mid);
    build(idx << 1 | 1, mid + 1, r);
    tree[idx].sumA = tree[idx << 1].sumA + tree[idx << 1 | 1].sumA;
    tree[idx].sumKA = tree[idx << 1].sumKA + tree[idx << 1 | 1].sumKA;
}

void pushDown(int idx, int l, int r) {
    if (tree[idx].lazy != 0) {
        ll val = tree[idx].lazy;
        int mid = (l + r) >> 1;
        int leftLen = mid - l + 1, rightLen = r - mid;
        
        // 更新左儿子
        tree[idx << 1].sumA += leftLen * val;
        tree[idx << 1].sumKA += val * getSumK(l, mid);
        tree[idx << 1].lazy += val;
        
        // 更新右儿子
        tree[idx << 1 | 1].sumA += rightLen * val;
        tree[idx << 1 | 1].sumKA += val * getSumK(mid + 1, r);
        tree[idx << 1 | 1].lazy += val;
        
        tree[idx].lazy = 0;
    }
}

void update(int idx, int l, int r, int ql, int qr, ll u) {
    if (ql <= l && r <= qr) {
        int len = r - l + 1;
        tree[idx].sumA += len * u;
        tree[idx].sumKA += u * getSumK(l, r);
        tree[idx].lazy += u;
        return;
    }
    pushDown(idx, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(idx << 1, l, mid, ql, qr, u);
    if (qr > mid) update(idx << 1 | 1, mid + 1, r, ql, qr, u);
    tree[idx].sumA = tree[idx << 1].sumA + tree[idx << 1 | 1].sumA;
    tree[idx].sumKA = tree[idx << 1].sumKA + tree[idx << 1 | 1].sumKA;
}

pair<ll, ll> query(int idx, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return {tree[idx].sumA, tree[idx].sumKA};
    pushDown(idx, l, r);
    int mid = (l + r) >> 1;
    ll sumA = 0, sumKA = 0;
    if (ql <= mid) {
        auto left = query(idx << 1, l, mid, ql, qr);
        sumA += left.first;
        sumKA += left.second;
    }
    if (qr > mid) {
        auto right = query(idx << 1 | 1, mid + 1, r, ql, qr);
        sumA += right.first;
        sumKA += right.second;
    }
    return {sumA, sumKA};
}

void solve() {
    static int caseNo = 0;
    cin >> n >> q;
    build(1, 1, n);
    
    cout << "Case " << ++caseNo << ":\n";
    
    while (q--) {
        string op;
        cin >> op;
        if (op == "change") {
            int i, j, u;
            cin >> i >> j >> u;
            update(1, 1, n, i, j, u);
        } else {
            int i, j;
            cin >> i >> j;
            auto res = query(1, 1, n, i, j);
            ll sumA = res.first, sumKA = res.second;
            ll ans = sumKA + (1 - i) * sumA;
            cout << ans << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    while (T--) solve();
    
    return 0;
}
