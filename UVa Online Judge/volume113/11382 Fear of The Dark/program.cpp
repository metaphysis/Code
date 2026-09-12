#include <bits/stdc++.h>
using namespace std;

const double Pi = acos(-1.0), Eps = 1e-10;
int n, k;
double ox, oy;
vector<pair<double, double>> seg;

bool can(double ang) {
    vector<pair<double, double>> a, b;
    for (auto p : seg) {
        double l = p.first, r = p.second;
        if (l <= r) a.push_back({l, r});
        else {
            a.push_back({l, 360.0});
            a.push_back({0.0, r});
        }
    }
    sort(a.begin(), a.end());
    for (auto p : a) {
        if (b.empty() || p.first > b.back().second + Eps) b.push_back(p);
        else b.back().second = max(b.back().second, p.second);
    }
    if (b.size() == 1 && b[0].first < Eps && b[0].second > 360.0 - Eps)
        return ceil(360.0 / ang - Eps) <= k;
    int m = b.size();
    for (int i = 0; i < m; i++) {
        double reach = -1e100;
        int cnt = 0;
        for (int t = 0; t < m; t++) {
            int id = (i + t) % m;
            double l = b[id].first, r = b[id].second;
            if (id < i) l += 360.0, r += 360.0;
            while (reach + Eps < r) {
                double st = max(l, reach);
                reach = st + ang;
                cnt++;
                if (cnt > k) break;
            }
            if (cnt > k) break;
        }
        if (cnt <= k) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k >> ox >> oy;
        seg.clear();
        for (int i = 0; i < n; i++) {
            double x1, y1, x2, y2, a, b, d;
            cin >> x1 >> y1 >> x2 >> y2;
            a = atan2(y1 - oy, x1 - ox) * 180.0 / Pi;
            b = atan2(y2 - oy, x2 - ox) * 180.0 / Pi;
            if (a < 0.0) a += 360.0;
            if (b < 0.0) b += 360.0;
            d = b - a;
            if (d < 0.0) d += 360.0;
            if (d > 180.0) swap(a, b);
            seg.push_back({a, b});
        }
        if (!can(180.0)) {
            cout << "-1.0000\n";
            continue;
        }
        double l = 1.0, r = 180.0;
        for (int it = 0; it < 70; it++) {
            double mid = (l + r) / 2.0;
            if (can(mid)) r = mid;
            else l = mid;
        }
        cout << fixed << setprecision(4) << r << '\n';
    }
    return 0;
}
