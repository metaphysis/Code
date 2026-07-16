// Boxes
// UVa ID: 12693
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 1.990s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MOD = 10007;

int modPow(int a, int e) {
    int r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int n, W;
        scanf("%d %d", &n, &W);
        vector<int> cnt(W + 1, 0);
        for (int i = 0; i < n; ++i) {
            int w;
            scanf("%d", &w);
            cnt[w]++;
        }
        vector<int> widths;
        for (int w = 1; w <= W; ++w)
            if (cnt[w] > 0) widths.push_back(w);
        int K = (int)widths.size();
        vector<int> cnts(K);
        for (int i = 0; i < K; ++i) cnts[i] = cnt[widths[i]];
        vector<int> fac(n + 1), invFac(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i % MOD;
        invFac[n] = modPow(fac[n], MOD - 2);
        for (int i = n; i >= 1; --i) invFac[i - 1] = invFac[i] * i % MOD;
        vector<vector<vector<int>>> dp(K + 1, vector<vector<int>>(W + 1, vector<int>(n + 1, 0)));
        dp[K][0][0] = 1;
        for (int i = K - 1; i >= 0; --i) {
            int c = widths[i], num = cnts[i];
            for (int s = 0; s <= W; ++s)
                for (int k = 0; k <= n; ++k) {
                    if (dp[i + 1][s][k] == 0) continue;
                    for (int a = 0; a <= num; ++a) {
                        int ns = s + a * c;
                        if (ns > W) break;
                        int nk = k + a;
                        if (nk > n) break;
                        int add = (long long)dp[i + 1][s][k] * invFac[a] % MOD;
                        dp[i][ns][nk] = (dp[i][ns][nk] + add) % MOD;
                    }
                }
        }
        for (int i = 0; i <= K; ++i)
            for (int k = 0; k <= n; ++k)
                for (int s = 1; s <= W; ++s)
                    dp[i][s][k] = (dp[i][s][k] + dp[i][s - 1][k]) % MOD;
        vector<int> preWeight(K + 1, 1), preSumW(K + 1, 0), preSumK(K + 1, 0);
        for (int i = 0; i < K; ++i) {
            preWeight[i + 1] = preWeight[i] * invFac[cnts[i]] % MOD;
            preSumW[i + 1] = preSumW[i] + cnts[i] * widths[i];
            preSumK[i + 1] = preSumK[i] + cnts[i];
        }
        long long ans = 0;
        for (int mid = 0; mid < K; ++mid) {
            int c = widths[mid], num = cnts[mid];
            int baseW = preSumW[mid], baseK = preSumK[mid];
            int baseWeight = preWeight[mid];
            for (int a = 0; a < num; ++a) {
                int addW = a * c;
                int addK = a;
                int factor = invFac[a];
                int curW = baseW + addW;
                int curK = baseK + addK;
                int L = W - c + 1 - curW;
                int R = W - curW;
                if (L < 0) L = 0;
                if (R > W) R = W;
                if (L > R) continue;
                for (int sufK = 0; sufK <= n - curK; ++sufK) {
                    int totalK = curK + sufK;
                    int sum = dp[mid + 1][R][sufK];
                    if (L > 0) sum = (sum - dp[mid + 1][L - 1][sufK] + MOD) % MOD;
                    if (sum == 0) continue;
                    long long contrib = (long long)fac[totalK] * baseWeight % MOD;
                    contrib = contrib * factor % MOD;
                    contrib = contrib * sum % MOD;
                    ans = (ans + contrib) % MOD;
                }
            }
        }
        if (preSumW[K] <= W) {
            long long all = (long long)fac[n] * preWeight[K] % MOD;
            ans = (ans + all) % MOD;
        }
        printf("Case %d: %lld\n", tc, ans % MOD);
    }
    return 0;
}
