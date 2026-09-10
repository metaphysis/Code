#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll countTriangles(ll n, ll m, ll limit) {
    if (limit < 0) return 0;
    if (n > m) swap(n, m);
    ll ans = 0;
    for (ll r = 1; r <= n; ++r) {
        for (ll c = 1; c <= m; ++c) {
            ll cnt = 0;
            ll rectArea = r * c;
            // 第一类：两点在矩形一条边的两端，第三点在对边上
            if (rectArea <= limit) cnt += 2 * (r + c - 2);
            // 第二类：以对角线为三角形的一边
            for (ll x = 0; x <= r; ++x) {
                ll yMax = (c * x + limit) / r;
                if (yMax > c) yMax = c;
                ll t = c * x - limit;
                ll yMin;
                if (t <= 0) yMin = 0;
                else yMin = (t - 1) / r + 1;
                if (yMin <= yMax) cnt += 2 * (yMax - yMin + 1);
            }
            // 第三类：一个顶点在矩形顶点，另外两点在对应的两条边上
            for (ll x = 1; x < r; ++x) {
                ll tmp = rectArea - x;
                if (tmp <= limit) {
                    cnt += 4 * (c - 1);
                } else {
                    tmp = tmp - limit;
                    ll u = c - 1 - min(tmp / x + (tmp % x != 0), c - 1);
                    cnt += 4 * u;
                }
            }
            ans += cnt * (n - r + 1) * (m - c + 1);
        }
    }
    return ans;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll n, m, A, B;
        scanf("%lld%lld%lld%lld", &n, &m, &A, &B);
        ll ans = countTriangles(n, m, 2 * B) - countTriangles(n, m, 2 * A - 1);
        printf("%lld\n", ans);
    }
    return 0;
}
