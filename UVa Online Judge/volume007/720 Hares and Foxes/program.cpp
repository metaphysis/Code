// Hares and Foxes
// UVa ID: 720
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-10;

int sgn(double x) {
    if (x > EPS) return 1;
    if (x < -EPS) return -1;
    return 0;
}

void eigenVector(double a, double b, double c, double d, double lam, double &vx, double &vy) {
    double e11 = a - lam, e12 = -b;
    double e21 = d, e22 = c - lam;
    if (fabs(e11) > fabs(e21)) {
        vx = e12;
        vy = -e11;
    } else {
        vx = e22;
        vy = -e21;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        double a, b, c, d, h0, f0;
        cin >> a >> b >> c >> d >> h0 >> f0;
        double tr = a + c;
        double det = a * c + b * d;
        double disc = tr * tr - 4 * det;
        if (fabs(disc) < EPS) {
            double lam = tr / 2;
            double m = fabs(lam);
            if (m < 1 - EPS) cout << "Ecological balance will develop.\n";
            else if (m > 1 + EPS) {
                if (lam < 0) {
                    cout << "Chaos will develop.\n";
                } else {
                    bool isScalar = (fabs(a - lam) < EPS && fabs(c - lam) < EPS &&
                                     fabs(b) < EPS && fabs(d) < EPS);
                    if (!isScalar) {
                        cout << "Chaos will develop.\n";
                    } else {
                        int hs = sgn(h0), fs = sgn(f0);
                        if (hs == 0 || fs == 0) cout << "Chaos will develop.\n";
                        else if (hs > 0 && fs > 0) cout << "Both hares and foxes will overgrow.\n";
                        else if (hs < 0 && fs < 0) cout << "Both hares and foxes will die out.\n";
                        else if (hs > 0 && fs < 0) cout << "Hares will overgrow while foxes will die out.\n";
                        else cout << "Hares will die out while foxes will overgrow.\n";
                    }
                }
            } else cout << "Chaos will develop.\n";
            continue;
        }
        if (disc < 0) {
            double r = sqrt(det);
            if (r < 1 - EPS) cout << "Ecological balance will develop.\n";
            else cout << "Chaos will develop.\n";
            continue;
        }
        double sqrtDisc = sqrt(disc);
        double lam1 = (tr + sqrtDisc) / 2;
        double lam2 = (tr - sqrtDisc) / 2;
        double m1 = fabs(lam1), m2 = fabs(lam2);
        if (m1 < 1 - EPS && m2 < 1 - EPS) {
            cout << "Ecological balance will develop.\n";
            continue;
        }
        if ((m1 >= 1 - EPS && m1 <= 1 + EPS) || (m2 >= 1 - EPS && m2 <= 1 + EPS)) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double lamDom, lamSub, mDom, mSub;
        if (m1 > m2) {
            lamDom = lam1; mDom = m1;
            lamSub = lam2; mSub = m2;
        } else {
            lamDom = lam2; mDom = m2;
            lamSub = lam1; mSub = m1;
        }
        if (lamDom < 0) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double v1x, v1y, v2x, v2y;
        eigenVector(a, b, c, d, lamDom, v1x, v1y);
        eigenVector(a, b, c, d, lamSub, v2x, v2y);
        double detV1V2 = v1x * v2y - v1y * v2x;
        if (fabs(detV1V2) < EPS) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double detV0V2 = h0 * v2y - f0 * v2x;
        double Cdom = detV0V2 / detV1V2;
        double usedLam, usedVx, usedVy, usedC;
        if (fabs(Cdom) < EPS) {
            if (mSub < 1 + EPS) {
                if (mSub < 1 - EPS) cout << "Ecological balance will develop.\n";
                else cout << "Chaos will develop.\n";
                continue;
            }
            if (lamSub < 0) {
                cout << "Chaos will develop.\n";
                continue;
            }
            usedLam = lamSub;
            usedVx = v2x; usedVy = v2y;
            double detV0V1 = h0 * v1y - f0 * v1x;
            usedC = -detV0V1 / detV1V2;
        } else {
            usedLam = lamDom;
            usedVx = v1x; usedVy = v1y;
            usedC = Cdom;
        }
        if (usedLam < 0) {
            cout << "Chaos will develop.\n";
            continue;
        }
        double hFinal = usedC * usedVx;
        double fFinal = usedC * usedVy;
        int hs = sgn(hFinal), fs = sgn(fFinal);
        if (hs == 0 || fs == 0) cout << "Chaos will develop.\n";
        else if (hs > 0 && fs > 0) cout << "Both hares and foxes will overgrow.\n";
        else if (hs < 0 && fs < 0) cout << "Both hares and foxes will die out.\n";
        else if (hs > 0 && fs < 0) cout << "Hares will overgrow while foxes will die out.\n";
        else cout << "Hares will die out while foxes will overgrow.\n";
    }
    return 0;
}
