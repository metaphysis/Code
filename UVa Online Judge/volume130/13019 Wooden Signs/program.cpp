// Wooden Signs
// UVa ID: 13019
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

const long long mod = 2147483647LL;

long long solve(int n, const vector<int> &pos) {
    vector<long long> dp(n + 1), nextDp(n + 1);
    dp[0] = 1;
    for (int i = 2; i <= n; i++) {
        fill(nextDp.begin(), nextDp.end(), 0);
        for (int j = 0; j < i - 1; j++) {
            if ((pos[i] - pos[i - 1]) * (pos[j] - pos[i - 1]) > 0)
                nextDp[i - 1] = (nextDp[i - 1] + dp[j]) % mod;
            if ((pos[i] - pos[j]) * (pos[i - 1] - pos[j]) > 0)
                nextDp[j] = (nextDp[j] + dp[j]) % mod;
        }
        dp.swap(nextDp);
    }
    long long answer = 0;
    for (int j = 0; j < n; j++) answer = (answer + dp[j]) % mod;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> pos(n + 1);
        for (int i = 0; i <= n; i++) cin >> pos[i];
        cout << solve(n, pos) << '\n';
    }
    return 0;
}
