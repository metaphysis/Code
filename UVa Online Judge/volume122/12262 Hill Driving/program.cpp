#include <bits/stdc++.h>
using namespace std;

struct Seg {
    double d, q;
};

double getFuel(const vector<Seg>& segs, double a, double v) {
    double sum = 0.0;
    for (const Seg& seg : segs) sum += seg.d * a * max(0.0, v - seg.q);
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    cout << fixed << setprecision(10);
    while (t--) {
        double a, b, vmax, fuel;
        int r;
        cin >> a >> b >> vmax >> fuel >> r;
        vector<Seg> segs(r);
        double need0 = 0.0;
        bool zeroImpossible = false;
        for (int i = 0; i < r; i++) {
            double x, y, s;
            cin >> x >> y;
            s = y / x;
            segs[i].d = hypot(x, y) / 1000.0;
            segs[i].q = -b * s / a;
            need0 += segs[i].d * max(0.0, b * s);
            if (segs[i].q <= 0.0) zeroImpossible = true;
        }
        double needMax = getFuel(segs, a, vmax);
        if (fuel + 1e-11 < need0) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        if (fuel <= need0 + 1e-11) {
            if (zeroImpossible) {
                cout << "IMPOSSIBLE\n";
                continue;
            }
            double ans = 0.0;
            for (const Seg& seg : segs) ans += seg.d / min(vmax, seg.q);
            cout << ans << '\n';
            continue;
        }
        double v;
        if (fuel >= needMax) {
            v = vmax;
        } else {
            double l = 0.0, h = vmax;
            for (int i = 0; i < 100; i++) {
                double m = (l + h) / 2.0;
                if (getFuel(segs, a, m) <= fuel) l = m;
                else h = m;
            }
            v = l;
        }
        double ans = 0.0;
        for (const Seg& seg : segs) ans += seg.d / min(vmax, max(v, seg.q));
        cout << ans << '\n';
    }
    return 0;
}
