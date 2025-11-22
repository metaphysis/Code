// Zeroes Revisited
// UVa ID: 11083
// Verdict: Accepted
// Submission Date: 2025-11-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 获取b的最大质因子
ll getMaxPrimeFactor(ll b) {
    ll maxPrime = 1;
    for (ll p = 2; p * p <= b; ++p) {
        if (b % p == 0) {
            maxPrime = max(maxPrime, p);
            while (b % p == 0) b /= p;
        }
    }
    return max(maxPrime, b);
}

// 计算 ∑_{i=1}^n ⌊i/m⌋
ll sumFloor(ll n, ll m) {
    ll quotient = n / m;
    ll remainder = n % m;
    return m * (quotient - 1) * quotient / 2 + quotient * (remainder + 1);
}

// 计算 soz(n, b)
ll soz(ll n, ll b) {
    if (n == 0) return 0;
    ll maxPrime = getMaxPrimeFactor(b);
    ll sum = 0;
    ll power = maxPrime;
    while (power <= n) {
        sum += sumFloor(n, power);
        if (power > n / maxPrime) break;
        power *= maxPrime;
    }
    return sum;
}

int main() {
    ll n, b;
    while (cin >> n >> b && (n || b)) {
        cout << soz(n, b) << endl;
    }
    return 0;
}
