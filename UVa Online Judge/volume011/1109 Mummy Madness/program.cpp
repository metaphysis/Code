// Mummy Madness
// UVa ID: 1109
// Verdict: Accepted
// Submission Date: 2026-07-19
// UVa Run Time: 0.540s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const long long LIMIT = 1000001LL;

// 检查时间 T 是否必死
bool check(long long T, const vector<pair<long long, long long>>& mummies) {
    using ll = long long;
    ll t = T;
    vector<tuple<ll, ll, ll, ll>> rects; // x1, x2+1, y1, y2+1
    vector<ll> ys;
    ys.push_back(-t);
    ys.push_back(t + 1);
    for (auto& p : mummies) {
        ll x = p.first, y = p.second;
        ll x1 = max(x - t, -t);
        ll x2 = min(x + t, t);
        ll y1 = max(y - t, -t);
        ll y2 = min(y + t, t);
        if (x1 > x2 || y1 > y2) continue;
        rects.push_back({x1, x2 + 1, y1, y2 + 1});
        ys.push_back(y1);
        ys.push_back(y2 + 1);
    }
    if (rects.empty()) return false; // 无覆盖
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    int m = (int)ys.size() - 1; // y 区间数
    if (m <= 0) return false;
    // 线段树：区间加，全局最小值
    struct SegTree {
        int n;
        vector<int> mn, lazy;
        SegTree(int sz) {
            n = sz;
            mn.assign(4 * n, 0);
            lazy.assign(4 * n, 0);
        }
        void push(int p) {
            if (lazy[p] != 0) {
                mn[p<<1] += lazy[p];
                lazy[p<<1] += lazy[p];
                mn[p<<1|1] += lazy[p];
                lazy[p<<1|1] += lazy[p];
                lazy[p] = 0;
            }
        }
        void add(int p, int l, int r, int ql, int qr, int val) {
            if (ql <= l && r <= qr) {
                mn[p] += val;
                lazy[p] += val;
                return;
            }
            push(p);
            int mid = (l + r) >> 1;
            if (ql < mid) add(p<<1, l, mid, ql, qr, val);
            if (qr > mid) add(p<<1|1, mid, r, ql, qr, val);
            mn[p] = min(mn[p<<1], mn[p<<1|1]);
        }
        void add(int l, int r, int val) { if (l < r) add(1, 0, n, l, r, val); }
        int minAll() { return mn[1]; }
    };
    SegTree seg(m);
    vector<tuple<ll, int, int, int>> events; // x, y_lidx, y_ridx, delta
    for (auto& r : rects) {
        ll x1, x2, y1, y2;
        tie(x1, x2, y1, y2) = r;
        int lidx = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
        int ridx = lower_bound(ys.begin(), ys.end(), y2) - ys.begin();
        events.push_back({x1, lidx, ridx, +1});
        events.push_back({x2, lidx, ridx, -1});
    }
    sort(events.begin(), events.end());
    ll curX = -t;
    size_t i = 0;
    while (i < events.size()) {
        ll nx = get<0>(events[i]);
        // 检查区间 [curX, nx) 是否有漏洞
        if (nx > curX && seg.minAll() == 0) return false;
        // 应用所有 x == nx 的事件
        while (i < events.size() && get<0>(events[i]) == nx) {
            ll x; int l, r, d;
            tie(x, l, r, d) = events[i];
            seg.add(l, r, d);
            ++i;
        }
        curX = nx;
    }
    // 检查最后一个区间 [curX, t+1)
    if (curX < t + 1 && seg.minAll() == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNo = 1;
    while (cin >> n && n != -1) {
        vector<pair<long long, long long>> mummies(n);
        for (int i = 0; i < n; ++i) cin >> mummies[i].first >> mummies[i].second;
        if (n == 0) {
            cout << "Case " << caseNo++ << ": never\n";
            continue;
        }
        long long lo = 0, hi = LIMIT;
        if (!check(hi, mummies)) {
            cout << "Case " << caseNo++ << ": never\n";
            continue;
        }
        while (lo < hi) {
            long long mid = (lo + hi) >> 1;
            if (check(mid, mummies)) hi = mid;
            else lo = mid + 1;
        }
        cout << "Case " << caseNo++ << ": " << lo << '\n';
    }
    return 0;
}
