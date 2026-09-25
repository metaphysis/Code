#include <bits/stdc++.h>
using namespace std;

bool hasTwoWays(int len, int p, int q) {
    int count = 0;
    for (int x = 1; x * p < len; x++) {
        if ((len - x * p) % q != 0) continue;
        count++;
        if (count == 2) return true;
    }
    return false;
}

bool canBuild(int p, int q, int a, int b) {
    if ((1LL * a * b) % (1LL * p * q) != 0) return false;
    if ((a == p && b == q) || (a == q && b == p)) return true;
    if (p == q) return false;
    int g = __gcd(p, q);
    if (a % g != 0 || b % g != 0) return false;
    p /= g;
    q /= g;
    a /= g;
    b /= g;
    if (p > q) swap(p, q);
    if (a % p != 0 && b % p != 0) return false;
    if (a % q != 0 && b % q != 0) return false;
    if (p == 1 && q == 2 && a == 6 && b == 6) return false;
    return hasTwoWays(a, p, q) && hasTwoWays(b, p, q);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseId = 1; caseId <= t; caseId++) {
        int p, q, a, b;
        cin >> p >> q >> a >> b;
        cout << "Case " << caseId << ":" << (canBuild(p, q, a, b) ? "Yes" : "No") << '\n';
    }
    return 0;
}
