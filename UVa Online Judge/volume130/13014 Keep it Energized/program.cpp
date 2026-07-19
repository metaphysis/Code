// Keep it Energized
// UVa ID: 13014
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.440s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 4e18;

// 线段树，支持点更新和区间最小值查询
struct SegTree {
    int n;
    vector<ll> tree;
    SegTree(int sz) {
        n = sz;
        tree.assign(4 * n + 5, INF);
    }
    void update(int idx, int l, int r, int pos, ll val) {
        if (l == r) { tree[idx] = val; return; }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(idx << 1, l, mid, pos, val);
        else update(idx << 1 | 1, mid + 1, r, pos, val);
        tree[idx] = min(tree[idx << 1], tree[idx << 1 | 1]);
    }
    ll query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[idx];
        int mid = (l + r) >> 1;
        ll res = INF;
        if (ql <= mid) res = min(res, query(idx << 1, l, mid, ql, qr));
        if (qr > mid) res = min(res, query(idx << 1 | 1, mid + 1, r, ql, qr));
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    while (cin >> N >> M) {
        vector<ll> E(N + 1), pref(N + 1, 0);
        for (int i = 1; i <= N; ++i) { cin >> E[i]; pref[i] = pref[i - 1] + E[i]; }

        vector<vector<pair<ll, int>>> shops(N + 1); // shops[i] 存储 (S, C)
        for (int i = 0; i < M; ++i) {
            int L, C; ll S;
            cin >> L >> S >> C;
            shops[L].push_back({S, C});
        }

        SegTree seg(N + 2);          // 下标范围 1..N+1
        seg.update(1, 1, N + 1, N + 1, 0); // dp[N+1] = 0

        vector<ll> dp(N + 2, INF);
        for (int i = N; i >= 1; --i) {
            if (shops[i].empty()) {
                dp[i] = INF;
                seg.update(1, 1, N + 1, i, INF);
                continue;
            }
            ll best = INF;
            for (auto &p : shops[i]) {
                ll S = p.first;
                int C = p.second;
                // 计算最大可通过关卡 R
                ll limit = S + pref[i - 1];
                int R = int(upper_bound(pref.begin() + 1, pref.end(), limit) - pref.begin()) - 1;
                // 注意 pref[0] 未参与，实际有效下标 1..N
                if (R < i) continue; // 连当前关都过不去
                int l = i + 1;
                int r = R + 1;
                if (l > r) continue;
                ll minNext = seg.query(1, 1, N + 1, l, r);
                if (minNext >= INF / 2) continue;
                best = min(best, (ll)C + minNext);
            }
            dp[i] = best;
            seg.update(1, 1, N + 1, i, dp[i]);
        }

        if (dp[1] >= INF / 2) cout << -1 << '\n';
        else cout << dp[1] << '\n';
    }
    return 0;
}
