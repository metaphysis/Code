// Chichi's Home Work
// UVa ID: 11379
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 0.010s

#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
const int64 MOD = 1000000000LL;
const int MAXN = 1005;
int64 C[MAXN];      // 卡特兰数
int64 dp[MAXN][MAXN]; // dp[i][j] = sum_{k=0}^{j-1} C[i-1-k]*C[k]

void init() {
    C[0] = C[1] = 1;
    for (int i = 2; i <= 1000; ++i) {
        int64 s = 0;
        for (int j = 0; j < i; ++j) {
            s += C[j] * C[i - 1 - j];
            s %= MOD;
        }
        C[i] = s;
    }
    for (int i = 0; i < 1000; ++i) {
        int64 s = 0;
        for (int j = 0; j <= i; ++j) {
            s += C[i - j] * C[j];
            s %= MOD;
            dp[i + 1][j + 1] = s;
        }
    }
}

int main() {
    init();
    int n, x, y;
    while (scanf("%d %d %d", &n, &x, &y) == 3) {
        int64 ret = 0;
        for (int i = y; i <= n; ++i) {
            ret += dp[n - (i - x)][x] * C[i - x];
            ret %= MOD;
        }
        printf("%lld\n", ret);
    }
    return 0;
}
