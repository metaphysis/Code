#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m) {
        int whiteSum = 0, blackSum = 0, half = n / 2;
        vector<int> ball(n);
        for (int i = 0; i < n; i++) {
            int white, black;
            cin >> white >> black;
            whiteSum += white;
            blackSum += black;
            ball[i] = white;
        }
        if (whiteSum == blackSum) {
            cout << "No solution\n";
            continue;
        }
        char major = 'W';
        int sum = whiteSum;
        if (whiteSum < blackSum) {
            major = 'B';
            sum = blackSum;
            for (int i = 0; i < n; i++) ball[i] = m - ball[i];
        }
        vector<set<int>> dp(half + 1);
        dp[0].insert(0);
        for (int i = 0; i < n; i++) {
            int limit = min(i, half - 1);
            for (int j = limit; j >= 0; j--) {
                for (set<int>::iterator it = dp[j].begin(); it != dp[j].end(); ++it)
                    dp[j + 1].insert(*it + ball[i]);
            }
        }
        int ans = -1, need = half * m / 2;
        for (set<int>::iterator it = dp[half].begin(); it != dp[half].end(); ++it) {
            if (*it > need && *it <= sum / 2) ans = max(ans, *it);
        }
        if (ans < 0) cout << "No solution\n";
        else cout << major << ' ' << fixed << setprecision(2) << ans * 100.0 / (half * m) << '\n';
    }
    return 0;
}
