#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

int64 getPow(int64 base, int64 exponent) {
    int64 result = 1;
    while (exponent > 0) {
        if (exponent & 1) result *= base;
        base *= base;
        exponent >>= 1;
    }
    return result;
}

int64 getPhi(int64 value) {
    int64 result = value, temp = value;
    for (int64 factor = 2; factor * factor <= temp; factor++) {
        if (temp % factor == 0) {
            result = result / factor * (factor - 1);
            while (temp % factor == 0) temp /= factor;
        }
    }
    if (temp > 1) result = result / temp * (temp - 1);
    return result;
}

int64 solve(int64 m, int64 n) {
    int64 total = 0;
    for (int64 divisor = 1; divisor * divisor <= m; divisor++) {
        if (m % divisor != 0) continue;
        int64 other = m / divisor;
        total += getPhi(divisor) * getPow(n, other);
        if (divisor != other) total += getPhi(other) * getPow(n, divisor);
    }
    if (m & 1) {
        total += m * getPow(n, (m + 1) / 2);
    } else {
        total += m / 2 * getPow(n, m / 2 + 1);
        total += m / 2 * getPow(n, m / 2);
    }
    return total / (2 * m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int64 m, n;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        cout << solve(m, n) << '\n';
    }
    return 0;
}
