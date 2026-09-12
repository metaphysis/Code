#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
};

vector<Point> cutPoly(const vector<Point>& p, bool up) {
    vector<Point> q;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        Point a = p[i], b = p[(i + 1) % n];
        bool ia = up ? a.y >= 0 : a.y <= 0;
        bool ib = up ? b.y >= 0 : b.y <= 0;
        if (ia) q.push_back(a);
        if (ia != ib) {
            double t = -a.y / (b.y - a.y);
            q.push_back({a.x + (b.x - a.x) * t, 0});
        }
    }
    return q;
}

Point getCentroid(const vector<Point>& p) {
    double sum = 0, sx = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        Point a = p[i], b = p[(i + 1) % n];
        double cross = a.x * b.y - b.x * a.y;
        sum += cross;
        sx += (a.x + b.x) * cross;
    }
    return {sx / (3 * sum), 0};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n;
    cin >> t;
    cout << fixed << setprecision(2);
    while (t--) {
        cin >> n;
        vector<Point> p(n);
        for (Point& a : p) cin >> a.x >> a.y;
        Point ce = getCentroid(cutPoly(p, true));
        Point clr = getCentroid(cutPoly(p, false));
        double d = ce.x - clr.x;
        if (fabs(d) < 1e-9) cout << "Balanced.\n";
        else if (d > 0) cout << "CE is forward of CLR by " << d << " units.\n";
        else cout << "CE is aft of CLR by " << -d << " units.\n";
    }
    return 0;
}
