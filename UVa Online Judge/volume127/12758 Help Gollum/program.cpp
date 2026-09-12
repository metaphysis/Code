#include <bits/stdc++.h>
using namespace std;

const long long mod = 1000000007LL;
const int maxLen = 1005;
string forbidden;
int weaknessLimit, patternLen;
long long desiredLength;
long long dp[maxLen], nextDp[maxLen];

long long powMod(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

long long calcBadShort() {
    int gapCount = patternLen - 1, limit = (int)desiredLength - 1;
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < gapCount; i++) {
        memset(nextDp, 0, sizeof(nextDp));
        for (int j = 0; j <= limit; j++) {
            if (dp[j] == 0) continue;
            for (int d = 1; d <= weaknessLimit && j + d <= limit; d++)
                nextDp[j + d] = (nextDp[j + d] + dp[j]) % mod;
        }
        memcpy(dp, nextDp, sizeof(dp));
    }
    long long bad = 0;
    for (int length = gapCount; length <= limit; length++) {
        long long ways = dp[length] * powMod(25, length - gapCount) % mod;
        long long suffixWays = (powMod(26, desiredLength - length) - powMod(25, desiredLength - length) + mod) % mod;
        bad = (bad + ways * suffixWays) % mod;
    }
    return bad;
}

long long calcBadLong() {
    int gapCount = patternLen - 1;
    long long inv25 = powMod(25, mod - 2), inv26 = powMod(26, mod - 2);
    long long sum26 = 0, sum25 = 0;
    for (int d = 1; d <= weaknessLimit; d++) {
        sum26 = (sum26 + powMod(25, d - 1) * powMod(inv26, d)) % mod;
        sum25 = (sum25 + powMod(25, d - 1) * powMod(inv25, d)) % mod;
    }
    long long part26 = powMod(26, desiredLength) * powMod(sum26, gapCount) % mod;
    long long part25 = powMod(25, desiredLength) * powMod(sum25, gapCount) % mod;
    return (part26 - part25 + mod) % mod;
}

long long solve() {
    if (desiredLength < patternLen) return powMod(26, desiredLength);
    if (patternLen == 1) return powMod(25, desiredLength);
    int maxGap = weaknessLimit * (patternLen - 1);
    long long bad;
    if (desiredLength >= maxGap)
        bad = calcBadLong();
    else
        bad = calcBadShort();
    return (powMod(26, desiredLength) - bad + mod) % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount;
    cin >> testCount;
    for (int caseId = 1; caseId <= testCount; caseId++) {
        cin >> forbidden >> weaknessLimit >> desiredLength;
        patternLen = (int)forbidden.size();
        cout << "Case " << caseId << ": " << solve() << '\n';
    }
    return 0;
}
