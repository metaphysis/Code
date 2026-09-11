// Fractions
// UVa ID: 11593
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.050s

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll floorSum(ll n, ll m, ll a, ll b) {
    // sum_{i=0}^{n-1} floor((a*i + b)/m)
    ll ans = 0;
    while (true) {
        if (a >= m) {
            ans += (n - 1) * n * (a / m) / 2;
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }
        ll yMax = a * n + b;
        if (yMax < m) break;
        n = yMax / m;
        b = yMax % m;
        swap(m, a);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    const ll N = 1000000000LL;
    string s;
    while (cin >> s) {
        if (s == "#") break;
        size_t pos = s.find('.');
        string frac = s.substr(pos + 1);
        int nDigit = (int)frac.size();
        ll A = stoll(frac);
        ll D = 1;
        for (int i = 0; i <= nDigit; ++i) D *= 10;          // D = 10^(n+1)
        ll a = 10 * A - 5;
        ll b = 10 * A + 5;
        ll tb = floorSum(N, D, b, b + D - 1);
        ll ta = floorSum(N, D, a, a + D - 1);
        cout << (tb - ta) << '\n';
    }
    return 0;
}
