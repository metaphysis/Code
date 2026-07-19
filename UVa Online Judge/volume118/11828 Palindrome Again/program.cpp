// Palindrome Again
// UVa ID: 11828
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll MOD = 1000000000LL;
const int MAXN = 1005;

ll C[MAXN][MAXN];
ll pow2[MAXN], pow24[MAXN], pow25[MAXN];

void precompute() {
    for (int i = 0; i < MAXN; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
    }
    pow2[0] = pow24[0] = pow25[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        pow2[i] = (pow2[i-1] * 2) % MOD;
        pow24[i] = (pow24[i-1] * 24) % MOD;
        pow25[i] = (pow25[i-1] * 25) % MOD;
    }
}

int main() {
    precompute();
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N, K;
        char s[MAXN];
        scanf("%d %d", &N, &K);
        scanf("%s", s);
        for (int i = 0; i < N; ++i)
            if (s[i] >= 'A' && s[i] <= 'Z')
                s[i] = s[i] - 'A' + 'a';
        int diff = 0, eq = 0;
        for (int i = 0; i < N / 2; ++i) {
            if (s[i] == s[N-1-i]) ++eq;
            else ++diff;
        }
        vector<ll> A(diff + 1);
        for (int x = 0; x <= diff; ++x)
            A[x] = C[diff][x] * pow2[x] % MOD * pow24[diff - x] % MOD;
        vector<ll> B(eq + 1), pref(eq + 1);
        for (int z = 0; z <= eq; ++z) {
            B[z] = C[eq][z] * pow25[z] % MOD;
            pref[z] = B[z];
            if (z > 0) pref[z] = (pref[z] + pref[z-1]) % MOD;
        }
        ll ans0 = 0, ans1 = 0;
        for (int x = 0; x <= diff; ++x) {
            int baseDist = 2 * diff - x;
            int remain0 = K - baseDist;
            if (remain0 >= 0) {
                int maxZ = min(eq, remain0 / 2);
                if (maxZ >= 0)
                    ans0 = (ans0 + A[x] * pref[maxZ]) % MOD;
            }
            int remain1 = K - 1 - baseDist;
            if (remain1 >= 0) {
                int maxZ = min(eq, remain1 / 2);
                if (maxZ >= 0)
                    ans1 = (ans1 + A[x] * pref[maxZ]) % MOD;
            }
        }
        ll total;
        if (N % 2 == 0) total = ans0;
        else total = (ans0 + 25 * ans1) % MOD;
        printf("Case %d: %lld\n", tc, total);
    }
    return 0;
}
