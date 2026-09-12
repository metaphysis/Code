// Boxes and Stones
// UVa ID: 12525
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.060s

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;

int dp[100][210][210];

int dfs(int position, int sum, int haveCount) {
    if (position == 0) {
        if (sum) return 0;
        return haveCount == 0 ? 1 : 0;
    }
    int &ret = dp[position][sum][haveCount];
    if (ret == -1) {
        ret = dfs(position - 1, sum, haveCount / 2);
        if (sum) ret += dfs(position, sum - 1, haveCount + 1);
        if (ret >= MOD) ret -= MOD;
    }
    return ret;
}

int main() {
    int S, B;
    memset(dp, -1, sizeof dp);
    while (scanf("%d %d", &S, &B) == 2) {
        printf("%d\n", dfs(B - 1, S, 0));
    }
    return 0;
}
