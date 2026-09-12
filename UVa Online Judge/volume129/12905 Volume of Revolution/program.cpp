#include <bits/stdc++.h>
using namespace std;

const long double pi = acosl(-1.0L);

long double getValue(const vector<long double>& coef, int n, long double x) {
    long double value = 0;
    for (int i = n; i >= 0; i--)
        value = value * x + coef[i];
    return value;
}

int solve() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, tc;
    cin >> t;
    for (tc = 1; tc <= t; tc++) {
        int n, slices, stacks, i, j;
        cin >> n;
        vector<long double> coef(n + 1);
        for (i = n; i >= 0; i--)
            cin >> coef[i];
        long double a, b;
        cin >> a >> b >> slices >> stacks;
        vector<long double> square(2 * n + 1, 0);
        for (i = 0; i <= n; i++)
            for (j = 0; j <= n; j++)
                square[i + j] += coef[i] * coef[j];
        long double trueVolume = 0;
        for (i = 0; i <= 2 * n; i++)
            trueVolume += square[i] * (powl(b, i + 1) - powl(a, i + 1)) / (i + 1);
        trueVolume *= pi;
        long double step = (b - a) / stacks;
        long double factor = 0.5L * slices * sinl(2 * pi / slices);
        long double approxVolume = 0;
        long double x = a;
        long double lastArea = 0.5L * slices * sinl(2 * pi / slices) * fabsl(getValue(coef, n, x)) * fabsl(getValue(coef, n, x));
        for (i = 1; i <= stacks; i++) {
            x += step;
            long double curArea = 0.5L * slices * sinl(2 * pi / slices) * fabsl(getValue(coef, n, x)) * fabsl(getValue(coef, n, x));
            approxVolume += (lastArea + curArea + sqrtl(lastArea * curArea)) * step / 3.0L;
            lastArea = curArea;
        }
        long double error = fabsl((trueVolume - approxVolume) / trueVolume * 100.0L);
        cout << "Case " << tc << ": " << fixed << setprecision(4) << (double)error << '\n';
    }
    return 0;
}

int main() {
    return solve();
}
