#include <bits/stdc++.h>
using namespace std;
using ld = long double;

const ld pi = acos(-1);

ld dist(ld x1, ld y1, ld x2, ld y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

ld getArea(ld x1, ld y1, ld r1, ld x2, ld y2, ld r2) {
    ld d, f1, f2, s1, s2;
    d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    f1 = 2.0 * acos((r1 * r1 - r2 * r2 + d * d) / (2.0 * r1 * d));
    f2 = 2.0 * acos((r2 * r2 - r1 * r1 + d * d) / (2.0 * r2 * d));
    s1 = (r1 * r1 * (f1 - sin(f1))) / 2.0;
    s2 = (r2 * r2 * (f2 - sin(f2))) / 2.0;
    return s1 + s2;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int t;
    cin >> t;
    cout.precision(4);
    cout << fixed;
    while (t--) {
        char type;
        cin >> type;
        if (type == 'S') {
            ld w, h, r;
            cin >> w >> h >> r;
            r = sqrt(pi * r * r / 2.0 / pi);
            ld x1 = r, y1 = r, x2 = w - r, y2 = h - r;
            if (x1 > x2 || y1 > y2 || dist(x1, y1, x2, y2) < 2.0 * r) cout << "Not enough space for fission.\n\n";
            else cout << dist(x1, y1, x2, y2) << "\n\n";
        } else {
            ld r1, r2, d;
            cin >> r1 >> r2 >> d;
            ld S = pi * r1 * r1 + pi * r2 * r2;
            ld s = getArea(0, 0, r1, d, 0, r2);
            int answer = round((S - s) / S * 10000);
            if (d >= r1 + r2 || answer == 10000) {
                cout << "1.0000\n";
                cout << "No compaction has occurred.\n\n";
                continue;
            }
            cout << (S - s) / S << "\n\n";
        }
    }
    return 0;
}
