// Cyclic Polygons
// UVa ID: 11277
// Verdict: Accepted
// Submission Date: 2026-06-10
// UVa Run Time: 0.210s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-8;

double solveOne(int n, vector<double>& a) {
    double maxSide = *max_element(a.begin(), a.end());
    double low = maxSide / 2.0;
    double high = 1000;
    
    for (int iter = 0; iter < 50; ++iter) {
        double mid = (low + high) / 2.0;
        double sumAngles = 0.0;
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            double ratio = a[i] / (2.0 * mid);
            if (ratio > 1.0 + EPS) { valid = false; break; }
            sumAngles += asin(min(ratio, 1.0));
        }
        if (!valid) { low = mid; continue; }
        if (sumAngles < PI) high = mid;
        else low = mid;
    }
    
    double R = (low + high) / 2.0;
    double totalAngle = 0.0;
    for (int i = 0; i < n; ++i) {
        double ratio = a[i] / (2.0 * R);
        if (ratio > 1.0 + EPS) return 0.0;
        totalAngle += asin(min(ratio, 1.0));
    }
    if (fabs(totalAngle - PI) > 1e-5) return 0.0;
    
    double area = 0.0;
    for (int i = 0; i < n; ++i) {
        double theta = 2.0 * asin(min(a[i] / (2.0 * R), 1.0));
        area += 0.5 * R * R * sin(theta);
    }
    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<double> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        double ans = solveOne(n, a);
        if (ans < 0) ans = 0.0;
        cout << fixed << setprecision(3) << ans << '\n';
    }
    return 0;
}
