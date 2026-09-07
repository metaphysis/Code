#include <bits/stdc++.h>
using namespace std;

const int mod = 10007;

bool canPair(char first, char second) {
    return (first == 'A' && second == 'U') || (first == 'U' && second == 'A') || (first == 'C' && second == 'G') || (first == 'G' && second == 'C');
}

void solveCase(const string &s, int d, int &best, int &count) {
    int n, i, len, l, r, j, candidate, pairWays;
    int dp[255][255], ways[255][255];
    n = static_cast<int>(s.size());
    for (i = 0; i <= n; ++i) {
        dp[i][i] = 0;
        ways[i][i] = 1;
    }
    for (len = 1; len <= n; ++len) {
        for (l = 0; l + len <= n; ++l) {
            r = l + len;
            dp[l][r] = dp[l + 1][r];
            ways[l][r] = ways[l + 1][r];
            for (j = l + d + 1; j < r; ++j) {
                if (!canPair(s[l], s[j])) continue;
                candidate = dp[l + 1][j] + dp[j + 1][r] + 1;
                pairWays = ways[l + 1][j] * ways[j + 1][r] % mod;
                if (candidate > dp[l][r]) {
                    dp[l][r] = candidate;
                    ways[l][r] = pairWays;
                } else if (candidate == dp[l][r]) {
                    ways[l][r] = (ways[l][r] + pairWays) % mod;
                }
            }
        }
    }
    best = dp[0][n];
    count = ways[0][n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, caseId, d, best, count;
    string s;
    cin >> testCount;
    for (caseId = 1; caseId <= testCount; ++caseId) {
        cin >> d >> s;
        solveCase(s, d, best, count);
        cout << "Case " << caseId << ": " << best << ' ' << count << '\n';
    }
    return 0;
}
