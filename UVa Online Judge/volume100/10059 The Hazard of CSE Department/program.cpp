// The Hazard of CSE Department
// UVa ID: 10059
// Verdict: Wrong Answer
// Submission Date: 2026-09-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

struct Equation {
    double a, b, c;
};

Equation normalizeEquation(double a, double b, double c) {
    if (fabs(a) >= fabs(b)) return {1.0, b / a, c / a};
    return {a / b, 1.0, c / b};
}

void printEquation(const Equation &eq) {
    cout << eq.a << ' ' << eq.b << ' ' << eq.c << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    cout << fixed << setprecision(3);
    while (testCount--) {
        long long p, q, r, s, t, u, d, e;
        cin >> p >> q >> r;
        cin >> s >> t >> u;
        cin >> d >> e;
        if (d == 0 || e == 0 || (p == 0 && q == 0) || (s == 0 && t == 0)) {
            cout << "Equation not found.\n";
            continue;
        }
        long long det = p * t - q * s;
        if (det == 0) {
            if (p * u == r * s && q * u == r * t) printEquation(normalizeEquation(p, q, r));
            else cout << "Equation not found.\n";
            continue;
        }
        if (p * s + q * t < 0) {
            s = -s;
            t = -t;
            u = -u;
        }
        double normOne = sqrt(static_cast<double>(p * p + q * q));
        double normTwo = sqrt(static_cast<double>(s * s + t * t));
        double pOne = p / normOne, qOne = q / normOne, rOne = r / normOne;
        double pTwo = s / normTwo, qTwo = t / normTwo, rTwo = u / normTwo;
        Equation firstEq = normalizeEquation(pOne + pTwo, qOne + qTwo, rOne + rTwo);
        Equation secondEq = normalizeEquation(pOne - pTwo, qOne - qTwo, rOne - rTwo);
        if (fabs(firstEq.a) < fabs(secondEq.a)) swap(firstEq, secondEq);
        else if (fabs(firstEq.a) == fabs(secondEq.a) && firstEq.b > secondEq.b) swap(firstEq, secondEq);
        printEquation(firstEq);
        printEquation(secondEq);
    }
    return 0;
}
