#include <bits/stdc++.h>
using namespace std;

double calcVal(int a, int b, double q, double k) {
    double u = exp(k * a), v = exp(k * b), prob = (u - 1.0) / (u * v - 1.0);
    return (b + q * a) * prob - q * a;
}

int bestB(int a, int bMax, double q, double k) {
    int left = 1, right = bMax, mid;
    while (left < right) {
        mid = (left + right) / 2;
        if (calcVal(a, mid, q, k) <= calcVal(a, mid + 1, q, k)) left = mid + 1;
        else right = mid;
    }
    return left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double x, p, q, k, ans, cur;
    while (cin >> x >> p) {
        if (x == 0.0 || p == 0.0) {
            cout << "0.0\n";
            continue;
        }
        p /= 100.0;
        q = 1.0 - x / 100.0;
        k = log((1.0 - p) / p);
        int bMax = (int)(1.0 / k) + 3, aMax = (int)ceil(log(1.0 / q) / k) + bMax + 5, b;
        ans = 0.0;
        for (int a = 1; a <= aMax; a++) {
            b = bestB(a, bMax, q, k);
            cur = calcVal(a, b, q, k);
            if (cur > ans) ans = cur;
        }
        cout << fixed << setprecision(10) << ans << '\n';
    }
    return 0;
}
