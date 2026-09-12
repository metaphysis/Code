#include <bits/stdc++.h>
using namespace std;

struct Info {
    long long len, sum, sq, mn, mx;
    Info() : len(0), sum(0), sq(0), mn(0), mx(0) {}
    Info(long long l, long long s, long long q, long long a, long long b) : len(l), sum(s), sq(q), mn(a), mx(b) {}
};

class SegTree {
private:
    int n;
    vector<long long> sum, sq, mn, mx, addTag, setVal;
    vector<char> hasSet;

    void applySet(int p, int l, int r, long long v) {
        long long len = r - l + 1;
        sum[p] = len * v;
        sq[p] = len * v * v;
        mn[p] = v;
        mx[p] = v;
        setVal[p] = v;
        addTag[p] = 0;
        hasSet[p] = 1;
    }

    void applyAdd(int p, int l, int r, long long v) {
        long long len = r - l + 1;
        sq[p] += 2 * v * sum[p] + len * v * v;
        sum[p] += len * v;
        mn[p] += v;
        mx[p] += v;
        if (hasSet[p]) setVal[p] += v;
        else addTag[p] += v;
    }

    void pushDown(int p, int l, int r) {
        if (l == r) return;
        int mid = (l + r) / 2, left = p * 2, right = p * 2 + 1;
        if (hasSet[p]) {
            applySet(left, l, mid, setVal[p]);
            applySet(right, mid + 1, r, setVal[p]);
            hasSet[p] = 0;
        }
        if (addTag[p] != 0) {
            applyAdd(left, l, mid, addTag[p]);
            applyAdd(right, mid + 1, r, addTag[p]);
            addTag[p] = 0;
        }
    }

    void pushUp(int p) {
        int left = p * 2, right = p * 2 + 1;
        sum[p] = sum[left] + sum[right];
        sq[p] = sq[left] + sq[right];
        mn[p] = min(mn[left], mn[right]);
        mx[p] = max(mx[left], mx[right]);
    }

    void build(int p, int l, int r, const vector<long long>& a) {
        hasSet[p] = 0;
        addTag[p] = 0;
        if (l == r) {
            sum[p] = a[l];
            sq[p] = a[l] * a[l];
            mn[p] = a[l];
            mx[p] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(p * 2, l, mid, a);
        build(p * 2 + 1, mid + 1, r, a);
        pushUp(p);
    }

    void updateSet(int p, int l, int r, int ql, int qr, long long v) {
        if (ql <= l && r <= qr) {
            applySet(p, l, r, v);
            return;
        }
        pushDown(p, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid) updateSet(p * 2, l, mid, ql, qr, v);
        if (qr > mid) updateSet(p * 2 + 1, mid + 1, r, ql, qr, v);
        pushUp(p);
    }

    void updateAdd(int p, int l, int r, int ql, int qr, long long v) {
        if (ql <= l && r <= qr) {
            applyAdd(p, l, r, v);
            return;
        }
        pushDown(p, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid) updateAdd(p * 2, l, mid, ql, qr, v);
        if (qr > mid) updateAdd(p * 2 + 1, mid + 1, r, ql, qr, v);
        pushUp(p);
    }

    Info mergeInfo(const Info& a, const Info& b) {
        return Info(a.len + b.len, a.sum + b.sum, a.sq + b.sq, min(a.mn, b.mn), max(a.mx, b.mx));
    }

    Info query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return Info(r - l + 1, sum[p], sq[p], mn[p], mx[p]);
        pushDown(p, l, r);
        int mid = (l + r) / 2;
        if (qr <= mid) return query(p * 2, l, mid, ql, qr);
        if (ql > mid) return query(p * 2 + 1, mid + 1, r, ql, qr);
        Info left = query(p * 2, l, mid, ql, qr), right = query(p * 2 + 1, mid + 1, r, ql, qr);
        return mergeInfo(left, right);
    }

public:
    SegTree(int size) : n(size) {
        int total = n * 4 + 5;
        sum.assign(total, 0);
        sq.assign(total, 0);
        mn.assign(total, 0);
        mx.assign(total, 0);
        addTag.assign(total, 0);
        setVal.assign(total, 0);
        hasSet.assign(total, 0);
    }

    void build(const vector<long long>& a) {
        build(1, 1, n, a);
    }

    void updateSet(int l, int r, long long v) {
        updateSet(1, 1, n, l, r, v);
    }

    void updateAdd(int l, int r, long long v) {
        updateAdd(1, 1, n, l, r, v);
    }

    Info query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};

long long gcdVal(long long a, long long b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, caseNum = 1;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<long long> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        SegTree tree(n);
        tree.build(a);
        cout << "Case " << caseNum++ << ":\n";
        while (q--) {
            int type, st, nd;
            long long x;
            cin >> type >> st >> nd;
            if (type == 0) {
                cin >> x;
                tree.updateSet(st, nd, x);
            } else if (type == 1) {
                cin >> x;
                tree.updateAdd(st, nd, x);
            } else {
                Info res = tree.query(st, nd);
                long long numerator = res.len * res.sq - res.sum * res.sum;
                long long denominator = res.len * res.len;
                long long g = gcdVal(numerator, denominator);
                cout << numerator / g << '/' << denominator / g << ' ' << res.mx - res.mn << '\n';
            }
        }
    }
    return 0;
}
