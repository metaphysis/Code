#include <bits/stdc++.h>
using namespace std;

long long exGcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1, g = exGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long p, q, n;
    while (cin >> p >> q >> n) {
        bool first = true;
        if (q == 1) {
            for (long long i = 1; i <= n; i++) {
                long long a = (p == 0 ? 1 : i - 1), b = i;
                if (!first) cout << ' ';
                first = false;
                cout << "M(" << a << "/" << b << ")";
            }
        } else {
            long long x, y;
            exGcd(p, q, x, y);
            long long inv = (x % q + q) % q;
            long long b1 = inv, a1 = (b1 * p - 1) / q;
            long long b2 = q - inv, a2 = (b2 * p + 1) / q;
            for (long long i = 0; i < n; i++) {
                if (b1 < b2 || (b1 == b2 && a1 <= a2)) {
                    if (!first) cout << ' ';
                    first = false;
                    cout << "M(" << a1 << "/" << b1 << ")";
                    b1 += q;
                    a1 = (b1 * p - 1) / q;
                } else {
                    if (!first) cout << ' ';
                    first = false;
                    cout << "M(" << a2 << "/" << b2 << ")";
                    b2 += q;
                    a2 = (b2 * p + 1) / q;
                }
            }
        }
        cout << '\n';
    }
    return 0;
}
