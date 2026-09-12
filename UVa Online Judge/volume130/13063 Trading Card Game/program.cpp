#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

int n, m, k;
cpp_int dp[105][105], ntr, dtr;

cpp_int getGcd() {
    cpp_int x = ntr, y = dtr, remainder;
    while (y != 0) {
        remainder = x % y;
        x = y;
        y = remainder;
    }
    return x;
}

void solve() {
    int i, j, maxJ;
    for (i = 0; i <= m; i++)
        for (j = 0; j <= n; j++)
            dp[i][j] = 0;
    dp[0][0] = 1;
    for (i = 1; i <= m; i++) {
        maxJ = min(i, n);
        for (j = 1; j <= maxJ; j++)
            dp[i][j] = dp[i - 1][j] * j + dp[i - 1][j - 1] * (n - j + 1);
    }
    dtr = 1;
    for (i = 0; i < m; i++)
        dtr *= n;
    if (k > n || k > m)
        ntr = 0;
    else
        ntr = dp[m][k];
    if (ntr == 0) {
        cout << "0/1\n";
        return;
    }
    cpp_int gcdValue = getGcd();
    cout << ntr / gcdValue << "/" << dtr / gcdValue << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n >> m >> k) {
        if (n == 0 && m == 0 && k == 0)
            break;
        solve();
    }
    return 0;
}
