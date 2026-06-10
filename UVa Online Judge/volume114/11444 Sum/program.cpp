// Sum
// UVa ID: 11444
// Verdict: Accepted
// Submission Date: 2026-06-10
// UVa Run Time: 0.110s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1000000009;
const int MAX_N = 100005;
const int MAX_K = 21;

ll seq[MAX_N];
ll prefixSum[MAX_K][MAX_N]; // prefixSum[t][i] = sum_{j=1..i} seq[j] * j^t
ll comb[MAX_K][MAX_K];      // 组合数

void initComb() {
    for (int i = 0; i < MAX_K; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++)
            comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD;
    }
}

ll modPow(ll a, ll e) {
    ll res = 1;
    a %= MOD;
    while (e) {
        if (e & 1) res = res * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    initComb();
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> seq[i];
            seq[i] %= MOD;
        }

        // 预处理前缀和
        for (int t = 0; t < MAX_K; t++) {
            prefixSum[t][0] = 0;
            for (int i = 1; i <= n; i++) {
                ll powI = modPow(i, t);
                prefixSum[t][i] = (prefixSum[t][i-1] + seq[i] * powI) % MOD;
            }
        }

        int q;
        cin >> q;
        while (q--) {
            int k, a, b;
            cin >> k >> a >> b;
            ll ans = 0;
            for (int t = 0; t <= k; t++) {
                ll sumT = (prefixSum[t][b] - prefixSum[t][a-1]) % MOD;
                if (sumT < 0) sumT += MOD;
                ll term = comb[k][t] * sumT % MOD;
                // 计算 (-a+1)^(k-t)
                ll base = (-a + 1) % MOD;
                if (base < 0) base += MOD;
                ll powVal = modPow(base, k - t);
                ans = (ans + term * powVal) % MOD;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
