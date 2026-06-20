// Maze Statistics
// UVa ID: 10531
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using VI = vector<int>;
using VD = vector<double>;
using MAP = unordered_map<int, double>;
using TMAP = unordered_map<int, vector<tuple<int, int, double>>>;

int enc(const VI& c, int st, int n) {
    int x = 0;
    for (int j = 0; j < n; ++j) x = x * 7 + c[j];
    return x * 7 + st;
}

void dec(int x, VI& c, int& st, int n) {
    st = x % 7; x /= 7;
    for (int j = n - 1; j >= 0; --j) c[j] = x % 7, x /= 7;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(6);
    int T; cin >> T;
    while (T--) {
        int m, n; cin >> m >> n;
        vector<VD> p(m, VD(n));
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) cin >> p[i][j];

        VI ic(n, 0);
        int is = enc(ic, 0, n);

        vector<MAP> fw(m);
        vector<TMAP> tr(m);

        MAP dpp; dpp[is] = 1.0;
        for (int i = 0; i < m; ++i) {
            MAP dpc;
            TMAP ctr;
            for (auto& e : dpp) {
                int st = e.first; double pp = e.second;
                VI cp(n); int sp;
                dec(st, cp, sp, n);
                for (int mask = 0; mask < (1 << n); ++mask) {
                    double mp = 1.0;
                    for (int j = 0; j < n; ++j) mp *= (mask >> j & 1) ? p[i][j] : 1.0 - p[i][j];
                    if (mp == 0.0) continue;
                    int mx = 0;
                    for (int j = 0; j < n; ++j) if (cp[j] > mx) mx = cp[j];
                    int tot = mx + n;
                    VI pa(tot); iota(begin(pa), end(pa), 0);
                    function<int(int)> f = [&](int x) { return pa[x] == x ? x : pa[x] = f(pa[x]); };
                    auto u = [&](int a, int b) { a = f(a); b = f(b); if (a != b) pa[a] = b; };
                    VI em(n);
                    for (int j = 0; j < n; ++j) em[j] = !(mask >> j & 1);
                    for (int j = 0; j < n; ++j) if (em[j] && cp[j] > 0) u(mx + j, cp[j] - 1);
                    for (int j = 1; j < n; ++j) if (em[j] && em[j - 1]) u(mx + j, mx + j - 1);
                    int ns = 0;
                    if (sp > 0) {
                        int rs = f(sp - 1);
                        bool ok = false;
                        for (int j = 0; j < n; ++j) if (em[j] && f(mx + j) == rs) { ok = true; break; }
                        if (!ok) continue;
                    }
                    VI cc(n, 0);
                    int id = 0; VI rt(tot, 0);
                    for (int j = 0; j < n; ++j) if (em[j]) {
                        int r = f(mx + j);
                        if (!rt[r]) rt[r] = ++id;
                        cc[j] = rt[r];
                    }
                    if (sp > 0) ns = rt[f(sp - 1)];
                    else if (i == 0 && em[0]) ns = rt[f(mx)];
                    int ns_enc = enc(cc, ns, n);
                    dpc[ns_enc] += pp * mp;
                    ctr[st].emplace_back(mask, ns_enc, mp);
                }
            }
            fw[i] = dpc;
            tr[i] = ctr;
            dpp = move(dpc);
        }

        double de = 0.0;
        for (auto& e : fw[m - 1]) {
            VI c(n); int st; dec(e.first, c, st, n);
            if (c[n - 1] > 0 && st == c[n - 1]) de += e.second;
        }

        vector<MAP> bw(m);
        for (auto& e : fw[m - 1]) {
            VI c(n); int st; dec(e.first, c, st, n);
            bw[m - 1][e.first] = (c[n - 1] > 0 && st == c[n - 1]) ? 1.0 : 0.0;
        }
        for (int i = m - 2; i >= 0; --i) for (auto& e : fw[i]) {
            int st = e.first; double sum = 0.0;
            auto it = tr[i + 1].find(st);
            if (it != tr[i + 1].end()) for (auto& t : it->second) {
                int mask, nxt; double prob; tie(mask, nxt, prob) = t;
                auto it2 = bw[i + 1].find(nxt);
                if (it2 != bw[i + 1].end()) sum += prob * it2->second;
            }
            bw[i][st] = sum;
        }

        MAP im; im[is] = 1.0;
        vector<VD> an(m, VD(n, 0.0));
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j) {
            if (p[i][j] == 0.0) continue;
            double nm = 0.0;
            MAP& prv = i == 0 ? im : fw[i - 1];
            for (auto& pe : prv) {
                int pv = pe.first; double pp = pe.second;
                auto it = tr[i].find(pv);
                if (it == tr[i].end()) continue;
                for (auto& t : it->second) {
                    int mask, nxt; double prob; tie(mask, nxt, prob) = t;
                    if (mask & (1 << j)) {
                        auto it2 = bw[i].find(nxt);
                        if (it2 != bw[i].end()) nm += pp * prob * it2->second;
                    }
                }
            }
            an[i][j] = nm / de;
        }
        for (int i = 0; i < m; ++i) for (int j = 0; j < n; ++j)
            cout << an[i][j] << " \n"[j == n - 1];
        if (T > 0) cout << '\n';
    }
}
