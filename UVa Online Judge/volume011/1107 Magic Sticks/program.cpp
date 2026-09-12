#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);

double getArea(const vector<int>& a, int l, int r, int mx) {
    double lo = 0.0, hi = 1.0 / mx, mid, val, res;
    int i, id = -1;
    for (i = l; i <= r; i++) {
        if (a[i] == mx) {
            id = i;
            break;
        }
    }
    val = 0.0;
    for (i = l; i <= r; i++)
        val += asin(a[i] * hi);
    bool minor = val >= pi;
    for (i = 0; i < 32; i++) {
        mid = (lo + hi) * 0.5;
        val = 0.0;
        if (minor) {
            for (int j = l; j <= r; j++)
                val += asin(a[j] * mid);
            if (val < pi) lo = mid;
            else hi = mid;
        } else {
            for (int j = l; j <= r; j++) {
                if (j == id) val += asin(a[j] * mid);
                else val -= asin(a[j] * mid);
            }
            if (val < 0.0) lo = mid;
            else hi = mid;
        }
    }
    mid = (lo + hi) * 0.5;
    res = 0.0;
    for (i = l; i <= r; i++) {
        double cur = a[i] * sqrt(max(0.0, 1.0 - a[i] * a[i] * mid * mid));
        if (!minor && i == id) res -= cur;
        else res += cur;
    }
    return res / (4.0 * mid);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, tc = 0;
    while (cin >> n && n) {
        vector<int> a(n + 1);
        vector<double> dp(n + 1, 0.0);
        int i, j;
        for (i = 1; i <= n; i++)
            cin >> a[i];
        for (i = 1; i <= n; i++) {
            double sum = 0.0;
            int mx = 0;
            dp[i] = dp[i - 1];
            for (j = i; j >= 1; j--) {
                sum += a[j];
                mx = max(mx, a[j]);
                if (i - j + 1 < 3) continue;
                if (sum <= 2.0 * mx) continue;
                double up = dp[j - 1] + sum * sum / (4.0 * pi);
                if (up <= dp[i] + 1e-9) continue;
                double area = getArea(a, j, i, mx);
                dp[i] = max(dp[i], dp[j - 1] + area);
            }
        }
        cout << "Case " << ++tc << ": " << fixed << setprecision(10) << dp[n] << '\n';
    }
    return 0;
}
