// The Hazard of CSE Department
// UVa ID: 10059
// Verdict: Accepted
// Submission Date: 2026-10-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Line {
    double a, b, c;
};

Line normLine(double a, double b, double c) {
    double dv = fabs(a) >= fabs(b) ? a : b;
    return {a / dv, b / dv, c / dv};
}

bool cmpLine(const Line &x, const Line &y) {
    double ax = fabs(x.a), ay = fabs(y.a);
    if (ax != ay) return ax > ay;
    return x.b < y.b;
}

void prtLine(const Line &ln) {
    cout << fixed << setprecision(3) << ln.a << ' ' << ln.b << ' ' << ln.c << '\n';
}

void solve() {
    long long p, q, r, s, t, u, d, e;
    cin >> p >> q >> r;
    cin >> s >> t >> u;
    cin >> d >> e;
    long long det = p * t - q * s;
    if (det == 0) {
        bool coincident = (p * u == r * s) && (q * u == r * t);
        if (coincident) {
            if (d == 0 && e == 0) {
                cout << "Equation not found.\n";
                return;
            }
            Line res = normLine(p, q, r);
            prtLine(res);
        } else cout << "Equation not found.\n";
        return;
    }
    if (d == 0 || e == 0) {
        cout << "Equation not found.\n";
        return;
    }
    double pv = p, qv = q, rv = r;
    double sv = s, tv = t, uv = u;
    double len1 = sqrt(pv * pv + qv * qv);
    double len2 = sqrt(sv * sv + tv * tv);
    double a1 = pv / len1, b1 = qv / len1, c1 = rv / len1;
    double a2 = sv / len2, b2 = tv / len2, c2 = uv / len2;
    Line l1 = normLine(a1 + a2, b1 + b2, c1 + c2);
    Line l2 = normLine(a1 - a2, b1 - b2, c1 - c2);
    if (!cmpLine(l1, l2)) swap(l1, l2);
    prtLine(l1);
    prtLine(l2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
