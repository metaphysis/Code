#include <bits/stdc++.h>
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1, g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

long long floorDiv(long long a, long long b) {
    if (a >= 0) return a / b;
    return -((-a + b - 1) / b);
}

long long ceilDiv(long long a, long long b) {
    return -floorDiv(-a, b);
}

long long countWays(long long m, long long w, long long n1, long long n2, long long n3) {
    long long x, y, g = exgcd(n2, n3, x, y), ans = 0;
    long long p = n3 / g, q = n2 / g;
    for (long long a = -m; a <= m; a++) {
        long long r = w - n1 * a;
        if (r % g != 0) continue;
        long long k = r / g, b0 = x * k, c0 = y * k;
        long long low = max(ceilDiv(-m - b0, p), ceilDiv(c0 - m, q));
        long long high = min(floorDiv(m - b0, p), floorDiv(c0 + m, q));
        if (low <= high) ans += high - low + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long m, w, n1, n2, n3;
    while (cin >> m >> w) {
        cin >> n1 >> n2 >> n3;
        cout << countWays(m, w, n1, n2, n3) << '\n';
    }
    return 0;
}
