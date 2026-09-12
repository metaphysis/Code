#include <bits/stdc++.h>
using namespace std;

long long exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

bool canSum(long long n, long long a, long long b) {
    long long g = __gcd(a, b);
    if (n % g != 0) return false;
    long long aa = a / g, bb = b / g, nn = n / g;
    if (bb == 1) return true;
    long long x, y;
    exgcd(aa, bb, x, y);
    long long inv = (x % bb + bb) % bb;
    long long cnt = (nn % bb) * inv % bb;
    return cnt <= nn / aa;
}

bool check(long long w, long long h, long long a, long long b) {
    bool useA = h % b == 0, useB = h % a == 0;
    if (useA && useB) return canSum(w, a, b);
    if (useA) return w % a == 0;
    if (useB) return w % b == 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long a, b, c, d;
        cin >> a >> b >> c >> d;
        if (check(c, d, a, b) || check(d, c, a, b)) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
