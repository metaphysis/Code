// Triangle Covering
// UVa ID: 10402
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.020s

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
double k2 = (1.0 + tan(PI / 12)) / cos(PI / 12);
// 1 / cos(x + PI / 6) = sqrt(3) * (1 / cos(x) + 1 / cos(PI / 6 - x)) / 3
// x = arctan(-sqrt(3) - 1 + sqrt(1 + 4 * sqrt(3)))
// k3 = 1 / cos(x) + 1 / cos(PI / 6 - x)
double x = atan(-sqrt(3) - 1 + sqrt(1 + 4 * sqrt(3)));
double k3 = 1 / cos(x) + 1 / cos(PI / 6 - x);
double k4 = 2 / cos(PI / 6);
// (1 - tan(x)) / cos(x) + (3 - sqrt(3)) / 3 * tan(PI / 6 - x) = 1
// k6 = 1.0 + 1.0 / cos(PI / 6) + 1.0 / cos(x)
// x = 0.167439672100
// double k6 = 1.0 + 1.0 / cos(PI / 6) + 1.0 / cos(x); 
double k6 = 3.1691932198;

int main() {
    int T;
    cin >> T;
    cout << fixed << setprecision(10);
    for (int cs = 1; cs <= T; cs++) {
        long double a;
        cin >> a;
        cout << a * k2 << ' ' << a * k3 << ' ' << a * k4 << ' ' << a * k6 << '\n';
    }
    return 0;
}
