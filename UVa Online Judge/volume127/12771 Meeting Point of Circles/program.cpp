#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-9;

struct Circle {
    double x, y, r;
};

struct Bound {
    double x, y, r;
};

bool isOk(double x, double y, double t, const vector<Circle>& cs) {
    for (const Circle& c : cs) {
        double dx = x - c.x, dy = y - c.y, dis = sqrt(dx * dx + dy * dy);
        if (fabs(dis - c.r) > t + eps) return false;
    }
    return true;
}

bool check(double t, const vector<Circle>& cs) {
    int n = cs.size();
    vector<Bound> bs;
    for (const Circle& c : cs) {
        double inR = max(0.0, c.r - t), outR = c.r + t;
        bs.push_back({c.x, c.y, inR});
        bs.push_back({c.x, c.y, outR});
    }
    for (const Circle& c : cs)
        if (isOk(c.x, c.y, t, cs)) return true;
    for (const Bound& b : bs)
        if (isOk(b.x + b.r, b.y, t, cs)) return true;
    int m = bs.size();
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            double dx = bs[j].x - bs[i].x, dy = bs[j].y - bs[i].y;
            double d = sqrt(dx * dx + dy * dy);
            if (d < eps) continue;
            if (d > bs[i].r + bs[j].r + eps) continue;
            if (d + min(bs[i].r, bs[j].r) < max(bs[i].r, bs[j].r) - eps) continue;
            double a = (bs[i].r * bs[i].r - bs[j].r * bs[j].r + d * d) / (2.0 * d);
            double h2 = bs[i].r * bs[i].r - a * a;
            double h = sqrt(max(0.0, h2));
            double ux = dx / d, uy = dy / d;
            double mx = bs[i].x + a * ux, my = bs[i].y + a * uy;
            double px1 = mx - uy * h, py1 = my + ux * h;
            double px2 = mx + uy * h, py2 = my - ux * h;
            if (isOk(px1, py1, t, cs)) return true;
            if (isOk(px2, py2, t, cs)) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<Circle> cs(n);
        for (int i = 0; i < n; i++)
            cin >> cs[i].x >> cs[i].y >> cs[i].r;
        double low = 0.0, high = 0.0;
        for (const Circle& c : cs) {
            double dx = c.x - cs[0].x, dy = c.y - cs[0].y;
            double dis = sqrt(dx * dx + dy * dy);
            high = max(high, fabs(dis - c.r));
        }
        for (int i = 0; i < 45; i++) {
            double mid = (low + high) / 2.0;
            if (check(mid, cs)) high = mid;
            else low = mid;
        }
        cout << fixed << setprecision(4) << high << '\n';
    }
    return 0;
}
