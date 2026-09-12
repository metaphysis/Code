#include <bits/stdc++.h>
using namespace std;

class SegTree {
    int n;
    vector<int> cnt, tag;
    void flip(int p, int l, int r) {
        cnt[p] = r - l + 1 - cnt[p];
        tag[p] ^= 1;
    }
    void push(int p, int l, int r) {
        if (!tag[p] || l == r) return;
        int m = (l + r) >> 1;
        flip(p << 1, l, m);
        flip(p << 1 | 1, m + 1, r);
        tag[p] = 0;
    }
    void update(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            flip(p, l, r);
            return;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        if (ql <= m) update(p << 1, l, m, ql, qr);
        if (qr > m) update(p << 1 | 1, m + 1, r, ql, qr);
        cnt[p] = cnt[p << 1] + cnt[p << 1 | 1];
    }
    int query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return cnt[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        if (qr <= m) return query(p << 1, l, m, ql, qr);
        if (ql > m) return query(p << 1 | 1, m + 1, r, ql, qr);
        return query(p << 1, l, m, ql, qr) + query(p << 1 | 1, m + 1, r, ql, qr);
    }
public:
    SegTree(int n) : n(n), cnt(4 * n + 5), tag(4 * n + 5) {}
    void update(int l, int r) {
        update(1, 1, n, l, r);
    }
    int query(int l, int r) {
        return query(1, 1, n, l, r);
    }
    int all() {
        return cnt[1];
    }
};

vector<pair<int, int>> splitSeg(int s, int len, int n) {
    vector<pair<int, int>> seg;
    int e = s + len - 1;
    if (e <= n) seg.push_back({s, e});
    else {
        seg.push_back({s, n});
        seg.push_back({1, e - n});
    }
    return seg;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        int n, m;
        cin >> n >> m;
        vector<vector<pair<int, int>>> evt(n + 2);
        for (int i = 0; i < m; ++i) {
            int row, col, wid, hei;
            cin >> row >> col >> wid >> hei;
            vector<pair<int, int>> rowSeg = splitSeg(row, hei, n), colSeg = splitSeg(col, wid, n);
            for (auto a : rowSeg) {
                for (auto b : colSeg) {
                    evt[a.first].push_back(b);
                    evt[a.second + 1].push_back(b);
                }
            }
        }
        SegTree st(n);
        long long oddAll = 0, oddOn = 0;
        for (int row = 1; row <= n; ++row) {
            for (auto e : evt[row]) st.update(e.first, e.second);
            oddAll += st.all();
            oddOn += st.query(1, row);
        }
        long long init = 1LL * n * (n + 1) / 2;
        long long ans = init + oddAll - 2 * oddOn;
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
