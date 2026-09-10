// The Juice Shop
// UVa ID: 1178
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll extendedGcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = extendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll floorDiv(ll a, ll b) { // b > 0
    if (a >= 0) return a / b;
    return - ((-a + b - 1) / b);
}

ll ceilDiv(ll a, ll b) { // b > 0
    if (a >= 0) return (a + b - 1) / b;
    return - ((-a) / b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll m, n;
    bool firstCase = true;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        if (!firstCase) cout << "\n";
        firstCase = false;
        ll x, y;
        ll g = extendedGcd(m, n, x, y);
        ll A = n / g;
        ll B = m / g;
        vector<ll> candidates;
        ll t1 = floorDiv(-x, A);
        ll t2 = ceilDiv(-x, A);
        ll t3 = floorDiv(y, B);
        ll t4 = ceilDiv(y, B);
        vector<ll> base = {t1, t2, t3, t4};
        for (ll t : base) {
            for (ll d = -2; d <= 2; ++d) candidates.push_back(t + d);
        }
        candidates.push_back(0);
        ll bestA = x, bestB = y, bestSum = llabs(x) + llabs(y);
        for (ll t : candidates) {
            ll a = x + A * t;
            ll b = y - B * t;
            ll sum = llabs(a) + llabs(b);
            if (sum < bestSum) {
                bestSum = sum;
                bestA = a;
                bestB = b;
            }
        }
        cout << "minimum volume: " << g << " liter(s)\n";
        if (bestA == 0) cout << m << " liter(s) not needed\n";
        else if (bestA > 0) cout << m << " liter(s) poured " << bestA << " times\n";
        else cout << m << " liter(s) withdrawn " << -bestA << " times\n";
        if (bestB == 0) cout << n << " liter(s) not needed\n";
        else if (bestB > 0) cout << n << " liter(s) poured " << bestB << " times\n";
        else cout << n << " liter(s) withdrawn " << -bestB << " times\n";
    }
    return 0;
}
