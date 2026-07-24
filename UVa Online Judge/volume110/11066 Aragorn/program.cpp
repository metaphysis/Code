// Aragorn
// UVa ID: 11066
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

double getY(const vector<Point>& pts, double x) {
    int n = (int)pts.size();
    for (int i = 0; i < n; ++i)
        if (fabs(pts[i].x - x) < 1e-12)
            return pts[i].y;
    int lo = 0, hi = n - 1;
    while (lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        if (pts[mid].x <= x) lo = mid;
        else hi = mid;
    }
    double t = (x - pts[lo].x) / (pts[hi].x - pts[lo].x);
    return pts[lo].y + t * (pts[hi].y - pts[lo].y);
}

int main() {
    cout << fixed << setprecision(2);
    int c;
    while (cin >> c && c != 0) {
        vector<Point> cloud(c);
        for (int i = 0; i < c; ++i) cin >> cloud[i].x >> cloud[i].y;
        int m;
        cin >> m;
        vector<Point> mountain(m);
        for (int i = 0; i < m; ++i) cin >> mountain[i].x >> mountain[i].y;

        vector<double> xs;
        for (auto& p : cloud) xs.push_back(p.x);
        for (auto& p : mountain) xs.push_back(p.x);
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end(), [](double a, double b) {
            return fabs(a - b) < 1e-12;
        }), xs.end());

        double area = 0.0;
        for (int i = 0; i + 1 < (int)xs.size(); ++i) {
            double l = xs[i], r = xs[i + 1];
            double len = r - l;
            double cl = getY(cloud, l), cr = getY(cloud, r);
            double ml = getY(mountain, l), mr = getY(mountain, r);
            double dl = ml - cl, dr = mr - cr;

            if (dl <= 0 && dr <= 0)
                continue;
            if (dl >= 0 && dr >= 0) {
                area += len * (dl + dr) / 2.0;
            } else if (dl > 0 && dr < 0) {
                double x0 = l + len * dl / (dl - dr);
                area += (x0 - l) * dl / 2.0;
            } else {
                double x0 = l + len * (-dl) / (dr - dl);
                area += (r - x0) * dr / 2.0;
            }
        }

        if (fabs(area) < 0.005) area = 0.0;
        cout << area << endl;
    }
    return 0;
}
