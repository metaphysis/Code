// Eleven
// UVa ID: 12672
// Verdict: Accepted
// Submission Date: 2026-05-23
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

ll modPow(ll a, ll e) {
    ll res = 1;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

ll inv(ll x) { return modPow(x, MOD - 2); }

// 计算给定数字频次下，所有排列（允许前导0）中满足模11条件的个数
ll solveWithCnt(vector<int> cnt, int oddLen, int evenLen) {
    int n = oddLen + evenLen;
    vector<ll> fact(n + 5, 1), invFact(n + 5, 1);
    for (int i = 1; i <= n + 4; i++) fact[i] = fact[i - 1] * i % MOD;
    invFact[n + 4] = inv(fact[n + 4]);
    for (int i = n + 3; i >= 0; i--) invFact[i] = invFact[i + 1] * (i + 1) % MOD;

    auto C = [&](int n, int m) -> ll {
        if (m < 0 || m > n) return 0;
        return fact[n] * invFact[m] % MOD * invFact[n - m] % MOD;
    };

    vector<vector<ll>> dp(oddLen + 1, vector<ll>(11, 0));
    dp[0][0] = 1;
    int total = 0;  // 已分配的总数字个数（奇+偶）

    for (int d = 0; d < 10; d++) {
        if (cnt[d] == 0) continue;
        vector<vector<ll>> ndp(oddLen + 1, vector<ll>(11, 0));

        for (int odd = 0; odd <= oddLen; odd++) {
            for (int mod = 0; mod < 11; mod++) {
                if (dp[odd][mod] == 0) continue;
                int even = total - odd;
                int remainOdd = oddLen - odd;
                int remainEven = evenLen - even;

                for (int k = 0; k <= cnt[d]; k++) {
                    if (k > remainOdd) break;
                    int toEven = cnt[d] - k;
                    if (toEven > remainEven) continue;

                    ll ways = C(remainOdd, k) * C(remainEven, toEven) % MOD;
                    int newMod = (mod + d * k - d * toEven) % 11;
                    if (newMod < 0) newMod += 11;

                    ndp[odd + k][newMod] = (ndp[odd + k][newMod] + dp[odd][mod] * ways) % MOD;
                }
            }
        }
        total += cnt[d];
        dp = move(ndp);
    }
    return dp[oddLen][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    while (cin >> s) {
        int n = s.size();
        vector<int> cnt(10, 0);
        for (char c : s) cnt[c - '0']++;

        int oddLen = (n + 1) / 2;
        int evenLen = n / 2;

        // 1. 允许前导0的所有合法重排数
        ll ans = solveWithCnt(cnt, oddLen, evenLen);

        // 2. 减去最高位为0的非法重排数
        if (cnt[0] > 0) {
            cnt[0]--;
            int n2 = n - 1;
            int oddLen2 = (n2 + 1) / 2;
            int evenLen2 = n2 / 2;
            ll invalid = solveWithCnt(cnt, oddLen2, evenLen2);
            ans = (ans - invalid + MOD) % MOD;
        }

        cout << ans << "\n";
    }
    return 0;
}
