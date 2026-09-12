#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    const long double eps = 1e-12L;
    while (cin >> n) {
        vector<Point> p(n);
        long double sumCross = 0, sumX = 0, l = 1e30L, r = -1e30L;
        for (int i = 0; i < n; i++) {
            cin >> p[i].x >> p[i].y;
            if (p[i].y == 0) {
                l = min(l, p[i].x);
                r = max(r, p[i].x);
            }
        }
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            long double cross = p[i].x * p[j].y - p[j].x * p[i].y;
            sumCross += cross;
            sumX += (p[i].x + p[j].x) * cross;
        }
        long double area = fabsl(sumCross) / 2, cx = sumX / (3 * sumCross);
        long double low = 0, high = 1e100L;
        bool ok = true;
        long double a[2] = {p[0].x - l, r - p[0].x};
        long double b[2] = {area * (cx - l), area * (r - cx)};
        for (int i = 0; i < 2; i++) {
            if (fabsl(a[i]) < eps) {
                if (b[i] < -eps) ok = false;
            } else if (a[i] > 0) {
                low = max(low, -b[i] / a[i]);
            } else {
                high = min(high, -b[i] / a[i]);
            }
        }
        if (!ok || low > high + eps) {
            cout << "unstable\n";
            continue;
        }
        if (low < 0) low = 0;
        long long ansL = (long long)floorl(low + eps);
        if (high > 1e90L) {
            cout << ansL << " .. inf\n";
        } else {
            long long ansR = (long long)ceill(high - eps);
            cout << ansL << " .. " << ansR << '\n';
        }
    }
    return 0;
}
