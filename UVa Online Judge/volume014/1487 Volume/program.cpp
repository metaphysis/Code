#include <bits/stdc++.h>
using namespace std;

int solve() {
    int r, h;
    double a, b, inter, uni;
    const double pi = acos(-1.0);
    while (cin >> r >> h) {
        a = h / 2.0;
        if (a >= r) inter = 16.0 * r * r * r / 3.0;
        else {
            b = sqrt(r * r - a * a);
            inter = 16.0 * (r * r * r - b * b * b) / 3.0;
        }
        uni = 2.0 * pi * r * r * h - inter;
        cout << fixed << setprecision(4) << uni << '\n';
    }
    return 0;
}

int main() {
    return solve();
}
