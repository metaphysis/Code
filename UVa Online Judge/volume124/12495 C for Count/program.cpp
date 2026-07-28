// C for Count
// UVa ID: 12495
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163265968

#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;
const int MAXN = 1000;
long long C[MAXN + 1][MAXN + 1];
long long invNum[MAXN + 1];

long long modPow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

int main() {
    // 组合数
    for (int i = 0; i <= MAXN; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
    // 逆元
    for (int i = 1; i <= MAXN; ++i) invNum[i] = modPow(i, MOD - 2);
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N, K, D;
        scanf("%d%d%d", &N, &K, &D);
        long long ans;
        if (K == 1) ans = N % MOD;
        else if (N < K * D) ans = 0;
        else {
            int m = N - K * (D - 1);          // 正确分母
            ans = (long long)N * invNum[m] % MOD * C[m][K] % MOD;
        }
        printf("Case %d: %lld\n", caseNo, ans);
    }
    return 0;
}
