#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseId = 1;
    while (cin >> n && n != -1) {
        vector<int> clue(n);
        int maxSum = 0;
        for (int i = 0; i < n; i++) {
            cin >> clue[i];
            maxSum += clue[i];
        }
        vector<bool> isPrime(maxSum + 1, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i * i <= maxSum; i++)
            if (isPrime[i])
                for (int j = i * i; j <= maxSum; j += i)
                    isPrime[j] = false;
        int totalMask = 1 << n, inf = maxSum + 1;
        vector<int> sum(totalMask, 0);
        for (int mask = 1; mask < totalMask; mask++) {
            int lowBit = mask & -mask;
            int index = __builtin_ctz(lowBit);
            sum[mask] = sum[mask ^ lowBit] + clue[index];
        }
        vector<vector<int>> dp(n, vector<int>(totalMask, inf));
        dp[0][0] = 0;
        for (int group = 1; group < n; group++) {
            for (int mask = 1; mask < totalMask; mask++) {
                if (__builtin_popcount(mask) < group)
                    continue;
                int lowBit = mask & -mask, sub;
                for (sub = mask; sub; sub = (sub - 1) & mask) {
                    if ((sub & lowBit) == 0 || !isPrime[sum[sub]])
                        continue;
                    int previous = dp[group - 1][mask ^ sub];
                    if (previous == inf)
                        continue;
                    dp[group][mask] = min(dp[group][mask], max(previous, sum[sub]));
                }
            }
        }
        int answer = 0, fullMask = totalMask - 1;
        for (int removed = 0; removed < n; removed++) {
            int r = clue[removed];
            if (r < 1 || r >= n)
                continue;
            int rest = fullMask ^ (1 << removed), sub;
            for (sub = rest; sub; sub = (sub - 1) & rest) {
                if (!isPrime[sum[sub]])
                    continue;
                if (dp[r - 1][rest ^ sub] <= sum[sub])
                    answer = max(answer, sum[sub]);
            }
        }
        cout << "Case " << caseId++ << ": ";
        if (answer == 0)
            cout << "not a valid clue\n";
        else
            cout << answer << '\n';
    }
    return 0;
}
