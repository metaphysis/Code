#include <bits/stdc++.h>
using namespace std;

int mod10(long long x) {
    x %= 10;
    if (x < 0) x += 10;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        int a, b, c, na, nb, nc, sum, val[3], ans;
        cin >> n >> a >> b >> c;
        sum = 0;
        for (int i = 0; i < 3; i++) {
            na = mod10(4 * a - 3 * b - 3 * c);
            nb = mod10(5 * a - 4 * b - 4 * c);
            nc = mod10(b - a);
            a = na;
            b = nb;
            c = nc;
            val[i] = mod10(a + b + c);
            sum = mod10(sum + val[i]);
        }
        ans = mod10((n / 3 % 10) * sum);
        for (int i = 0; i < n % 3; i++)
            ans = mod10(ans + val[i]);
        cout << ans << '\n';
    }
    return 0;
}
