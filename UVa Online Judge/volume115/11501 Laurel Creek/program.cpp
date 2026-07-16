// Laurel Creek
// UVa ID: 11501
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
struct Edge { int u, v, len; bool hor; };
struct State { int u, hand; vector<int> pos; bool operator<(const State& o) const { return u != o.u ? u < o.u : hand != o.hand ? hand < o.hand : pos < o.pos; } };
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        int r, c; cin >> r >> c;
        vector<string> g(r);
        for (int i = 0; i < r; ++i) cin >> g[i];
        vector<pair<int,int>> st;
        map<pair<int,int>, int> id;
        int S = -1, E = -1;
        for (int i = 0; i < r; ++i) for (int j = 0; j < c; ++j) {
            char ch = g[i][j];
            if (ch == 'S' || ch == 'B' || ch == 'E') {
                int nid = st.size(); st.push_back({i, j}); id[{i, j}] = nid;
                if (ch == 'B') S = nid; if (ch == 'E') E = nid;
            }
        }
        int n = st.size();
        vector<Edge> logs, edges;
        auto addLog = [&](int u, int v, int len) { logs.push_back({u, v, len, false}); };
        for (int i = 0; i < r; ++i) {
            int j = 0;
            while (j < c) if (g[i][j] == '-') {
                int l = j; while (j < c && g[i][j] == '-') ++j; int rr = j - 1;
                int L = l - 1, R = rr + 1;
                if (L >= 0 && R < c && (g[i][L] == 'S' || g[i][L] == 'B' || g[i][L] == 'E') &&
                    (g[i][R] == 'S' || g[i][R] == 'B' || g[i][R] == 'E'))
                    addLog(id[{i, L}], id[{i, R}], rr - l + 1);
            } else ++j;
        }
        for (int j = 0; j < c; ++j) {
            int i = 0;
            while (i < r) if (g[i][j] == '|') {
                int u = i; while (i < r && g[i][j] == '|') ++i; int d = i - 1;
                int U = u - 1, D = d + 1;
                if (U >= 0 && D < r && (g[U][j] == 'S' || g[U][j] == 'B' || g[U][j] == 'E') &&
                    (g[D][j] == 'S' || g[D][j] == 'B' || g[D][j] == 'E'))
                    addLog(id[{U, j}], id[{D, j}], d - u + 1);
            } else ++i;
        }
        for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) {
            bool hr = (st[i].first == st[j].first), vc = (st[i].second == st[j].second);
            if (!hr && !vc) continue;
            bool blk = false;
            if (hr) {
                int row = st[i].first, lc = min(st[i].second, st[j].second), rc = max(st[i].second, st[j].second);
                for (int k = 0; k < n; ++k) if (k != i && k != j && st[k].first == row && st[k].second > lc && st[k].second < rc) { blk = true; break; }
            } else {
                int col = st[i].second, ur = min(st[i].first, st[j].first), dr = max(st[i].first, st[j].first);
                for (int k = 0; k < n; ++k) if (k != i && k != j && st[k].second == col && st[k].first > ur && st[k].first < dr) { blk = true; break; }
            }
            if (!blk) {
                int len = hr ? abs(st[i].second - st[j].second) - 1 : abs(st[i].first - st[j].first) - 1;
                if (len > 0) edges.push_back({i, j, len, hr});
            }
        }
        int m = logs.size(), e = edges.size();
        vector<int> init(m, -1);
        for (int i = 0; i < m; ++i) for (int j = 0; j < e; ++j)
            if ((logs[i].u == edges[j].u && logs[i].v == edges[j].v || logs[i].u == edges[j].v && logs[i].v == edges[j].u) && logs[i].len == edges[j].len)
                { init[i] = j; break; }
        if (S == E) { cout << 0 << '\n'; continue; }
        State st0{S, -1, init};
        set<State> vis; queue<State> q; queue<int> dq;
        vis.insert(st0); q.push(st0); dq.push(0);
        int ans = -1;
        while (!q.empty()) {
            State cur = q.front(); q.pop();
            int d = dq.front(); dq.pop();
            if (cur.u == E) { ans = d; break; }
            int u = cur.u, hand = cur.hand;
            auto &pos = cur.pos;
            // walk
            for (int i = 0; i < m; ++i) if (pos[i] != -1) {
                int eid = pos[i];
                int a = edges[eid].u, b = edges[eid].v;
                int v = (a == u ? b : (b == u ? a : -1));
                if (v != -1) {
                    State ns = cur; ns.u = v;
                    if (!vis.count(ns)) { vis.insert(ns); q.push(ns); dq.push(d + 1); }
                }
            }
            // pick
            if (hand == -1) for (int i = 0; i < m; ++i) if (pos[i] != -1) {
                int eid = pos[i];
                if (edges[eid].u == u || edges[eid].v == u) {
                    State ns = cur; ns.hand = i; ns.pos[i] = -1;
                    if (!vis.count(ns)) { vis.insert(ns); q.push(ns); dq.push(d + 1); }
                }
            }
            // put
            if (hand != -1) {
                int lid = hand, len = logs[lid].len;
                for (int eid = 0; eid < e; ++eid) {
                    int a = edges[eid].u, b = edges[eid].v;
                    if ((a != u && b != u) || edges[eid].len != len) continue;
                    bool occ = false;
                    for (int i = 0; i < m; ++i) if (i != lid && pos[i] == eid) { occ = true; break; }
                    if (occ) continue;
                    bool cross = false;
                    for (int i = 0; i < m; ++i) if (i != lid && pos[i] != -1) {
                        Edge e1 = edges[eid], e2 = edges[pos[i]];
                        if (e1.hor == e2.hor) continue;
                        Edge *h = e1.hor ? &e1 : &e2, *v = e1.hor ? &e2 : &e1;
                        int hr = st[h->u].first, hc1 = st[h->u].second, hc2 = st[h->v].second;
                        if (hc1 > hc2) swap(hc1, hc2);
                        int vc = st[v->u].second, vr1 = st[v->u].first, vr2 = st[v->v].first;
                        if (vr1 > vr2) swap(vr1, vr2);
                        if (hc1 < vc && vc < hc2 && vr1 < hr && hr < vr2) { cross = true; break; }
                    }
                    if (cross) continue;
                    State ns = cur; ns.hand = -1; ns.pos[lid] = eid;
                    if (!vis.count(ns)) { vis.insert(ns); q.push(ns); dq.push(d + 1); }
                }
            }
        }
        cout << (ans == -1 ? 0 : ans) << '\n';
    }
    return 0;
}
