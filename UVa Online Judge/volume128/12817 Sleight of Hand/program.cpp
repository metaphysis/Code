#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double r, v, lr, lp, mx, a, b, pr, pp;
    int n, i;
    char g;
    const double inf = numeric_limits<double>::infinity();
    while (cin >> r) {
        cin >> n;
        lr = r == 0 ? -inf : log(r);
        lp = r == 1 ? -inf : log(1 - r);
        for (i = 0; i < n; i++) {
            cin >> g >> v;
            if (g == 'R') {
                lr += log(v);
                lp += log(1 - v);
            } else {
                lr += log(1 - v);
                lp += log(v);
            }
        }
        mx = max(lr, lp);
        a = exp(lr - mx);
        b = exp(lp - mx);
        pr = a / (a + b);
        pp = b / (a + b);
        cout << fixed << setprecision(6) << pr << ' ' << pp << '\n';
    }
    return 0;
}
