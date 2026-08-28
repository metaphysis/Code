#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 4000000000000000000LL;

struct Carpet {
    ll st, en, pri;
    int col;
};

struct Res {
    ll cost, chg;
};

int m;
vector<ll> cst;

void upd(Res &a, Res b) {
    if (b.cost < a.cost || b.cost == a.cost && b.chg < a.chg)
        a = b;
}

Res gapCost(ll len, int a, int b) {
    Res ans = {inf, inf};
    int x;
    for (x = 1; x <= m; x++) {
        Res cur = {len * cst[x], (a != x) + (x != b)};
        upd(ans, cur);
    }
    return ans;
}

Res begCost(ll len, int b) {
    Res ans = {inf, inf};
    int x;
    for (x = 1; x <= m; x++) {
        Res cur = {len * cst[x], x != b};
        upd(ans, cur);
    }
    return ans;
}

Res endCost(ll len, int a) {
    Res ans = {inf, inf};
    int x;
    for (x = 1; x <= m; x++) {
        Res cur = {len * cst[x], a != x};
        upd(ans, cur);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, cs;
    cin >> t;
    for (cs = 1; cs <= t; cs++) {
        ll l, d;
        int n, i, j, r;
        cin >> l >> n >> m >> d;
        cst.assign(m + 1, 0);
        for (i = 1; i <= m; i++)
            cin >> cst[i];
        vector<Carpet> cp(n);
        for (i = 0; i < n; i++)
            cin >> cp[i].st >> cp[i].en >> cp[i].col >> cp[i].pri;
        sort(cp.begin(), cp.end(), [](const Carpet &a, const Carpet &b) {
            if (a.en != b.en) return a.en < b.en;
            return a.st < b.st;
        });
        vector<array<Res, 3> > dp(n);
        ll minC = *min_element(cst.begin() + 1, cst.end());
        Res ans = {l * minC, 0};
        for (i = 0; i < n; i++) {
            for (r = 1; r <= 2; r++)
                dp[i][r] = {inf, inf};
            Res bg = begCost(cp[i].st - 1, cp[i].col);
            dp[i][1] = {bg.cost + cp[i].pri, bg.chg};
            for (j = 0; j < i; j++) {
                if (cp[j].en >= cp[i].st) continue;
                ll len = cp[i].st - cp[j].en - 1;
                Res gc = gapCost(len, cp[j].col, cp[i].col);
                for (r = 1; r <= 2; r++) {
                    if (dp[j][r].cost == inf) continue;
                    ll dis = 0;
                    int nr = 1;
                    if (len == 0 && cp[j].col == cp[i].col) {
                        nr = min(2, r + 1);
                        if (r == 2) dis = min(d, cp[i].pri);
                    }
                    Res cur = {dp[j][r].cost + gc.cost + cp[i].pri - dis, dp[j][r].chg + gc.chg};
                    upd(dp[i][nr], cur);
                }
            }
            for (r = 1; r <= 2; r++) {
                if (dp[i][r].cost == inf) continue;
                Res eg = endCost(l - cp[i].en, cp[i].col);
                Res cur = {dp[i][r].cost + eg.cost, dp[i][r].chg + eg.chg};
                upd(ans, cur);
            }
        }
        cout << "Case " << cs << ": " << ans.cost << ' ' << ans.chg << '\n';
    }
    return 0;
}
