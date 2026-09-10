#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007LL;

long long powInt(int base, int exp) {
    long long res = 1;
    for (int i = 0; i < exp; ++i) res *= base;
    return res;
}

// 计算 1..N 中数字集合是 mask 的子集的个数
long long countSubset(int mask, int N) {
    string s = to_string(N);
    int len = s.size();
    long long ans = 0;
    int cntDig = __builtin_popcount(mask);
    // 长度小于 len 的数字
    for (int L = 1; L < len; ++L) {
        int firstChoices = cntDig - ((mask & 1) ? 1 : 0); // 首位不能为 0
        if (firstChoices <= 0) continue;
        long long ways = firstChoices * powInt(cntDig, L - 1);
        ans += ways;
    }
    // 长度等于 len，逐位确定
    for (int i = 0; i < len; ++i) {
        int cur = s[i] - '0';
        int start = (i == 0) ? 1 : 0;
        for (int d = start; d < cur; ++d) {
            if ((mask >> d) & 1) {
                int rem = len - i - 1;
                ans += powInt(cntDig, rem);
            }
        }
        if (((mask >> cur) & 1) == 0) return ans;
        if (i == len - 1) ans += 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N;
        cin >> N;
        long long F[1024] = {0};
        long long G[1024] = {0};
        // 计算所有 mask 的 F 值
        for (int mask = 1; mask < 1024; ++mask)
            F[mask] = countSubset(mask, N);
        // 容斥得到恰好等于 mask 的个数
        for (int mask = 1; mask < 1024; ++mask) {
            long long val = F[mask];
            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask)
                val -= G[sub];
            G[mask] = val;
        }
        long long dp[1024] = {0};
        dp[0] = 1;
        // 状压 DP，枚举并集 mask
        for (int mask = 1; mask < 1024; ++mask) {
            int low = mask & -mask;
            long long sum = 0;
            for (int sub = mask; sub; sub = (sub - 1) & mask) {
                if (sub & low) {
                    int other = mask ^ sub;
                    if (G[sub] > 0)
                        sum = (sum + (G[sub] % MOD) * dp[other]) % MOD;
                }
            }
            dp[mask] = sum;
        }
        long long ans = 0;
        for (int mask = 1; mask < 1024; ++mask)
            ans = (ans + dp[mask]) % MOD;
        cout << "Case " << tc << ": " << ans << "\n";
    }
    return 0;
}
