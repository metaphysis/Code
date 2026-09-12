// Knockout Tournaments
// UVa ID: 12285
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

long double getHarm(long long n) {
    if (n <= 0)
        return 0;
    if (n <= 100000) {
        long double sum = 0;
        for (long long i = 1; i <= n; i++)
            sum += 1.0L / i;
        return sum;
    }
    long double x = n, x2 = x * x, x4 = x2 * x2, x6 = x4 * x2;
    const long double gamma = 0.5772156649015328606L;
    return logl(x) + gamma + 1.0L / (2 * x) - 1.0L / (12 * x2) + 1.0L / (120 * x4) - 1.0L / (252 * x6);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long w, l;
    int cs = 1;
    while (cin >> w >> l && (w != 0 || l != 0)) {
        long long low = max(l, (w + l + 7) / 8), high = l + w / 8;
        cout << "Case " << cs++ << ":\n";
        if (low > high) {
            cout << "Situation Impossible.\n";
            continue;
        }
        long long cnt = high - low + 1;
        long double sumInv = getHarm(high) - getHarm(low - 1);
        long double ans = (w + l) * sumInv / cnt;
        cout << fixed << setprecision(2) << "On Average Bob Reaches Round " << (double)ans << '\n';
    }
    return 0;
}
