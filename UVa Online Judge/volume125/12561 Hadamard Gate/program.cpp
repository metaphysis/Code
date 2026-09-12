#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    cout << fixed << setprecision(6);
    for (int tc = 1; tc <= t; tc++) {
        double a0, a1, b0, b1, ans;
        int n;
        cin >> a0 >> a1 >> b0 >> b1 >> n;
        if (n % 2 == 0) ans = a0 * a0 + a1 * a1;
        else ans = ((a0 + b0) * (a0 + b0) + (a1 + b1) * (a1 + b1)) / 2.0;
        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
