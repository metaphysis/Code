#include <bits/stdc++.h>
using namespace std;

double calc(double len, double wid, double hei) {
    double x, y;
    x = len + hei, y = wid + hei;
    return 2.0 * sqrt(x * x + y * y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int test, cas;
    double len, wid, hei, ans;
    cin >> test;
    for (cas = 1; cas <= test; cas++) {
        cin >> len >> wid >> hei;
        ans = calc(len, wid, hei);
        cout << "Case " << cas << ": ";
        cout << fixed << setprecision(4) << ans << '\n';
    }
    return 0;
}
