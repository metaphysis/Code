#include <bits/stdc++.h>
using namespace std;

double dp[101][205];
bool vis[101][205];

double getAns(int l, int s) {
    if (l == 0) return s;
    if (vis[l][s]) return dp[l][s];
    vis[l][s] = true;
    dp[l][s] = 0;
    if (s > 0) dp[l][s] += 1.0 * s / (l + s) * getAns(l, s - 1);
    dp[l][s] += 1.0 * l / (l + s) * getAns(l - 1, s + 1);
    return dp[l][s];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int l, s;
    while (cin >> l >> s) {
        if (l == 0 && s == 0) break;
        double ans, day;
        ans = getAns(l, s);
        day = 2.0 * l + s - ans;
        cout << fixed << setprecision(12) << ans << " " << day << "\n";
    }
    return 0;
}
