// Few Teams Will Solve This
// UVa ID: 11738
// Verdict: Wrong Answer
// Submission Date: 2026-10-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int mod = 19821202;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNo = 1;
    while (cin >> n && n) {
        vector<int> bfs(n), dfs(n);
        for (int i = 0; i < n; i++)
            cin >> bfs[i];
        for (int i = 0; i < n; i++)
            cin >> dfs[i];
        vector<int> dfsPos(n + 1), bfsOfDfs(n), q(n);
        for (int i = 0; i < n; i++)
            dfsPos[dfs[i]] = i;
        for (int i = 0; i < n; i++) {
            q[i] = dfsPos[bfs[i]];
            bfsOfDfs[q[i]] = i;
        }
        vector<vector<int>> lastEligible(n, vector<int>(n, -1));
        for (int right = 1; right < n; right++) {
            if (bfs[right - 1] > bfs[right] && q[right - 1] < q[right]) {
                int last = -1;
                for (int left = 1; left < n; left++) {
                    int index = left - 1;
                    if (q[index] > q[right - 1] && q[index] < q[right])
                        last = index;
                    lastEligible[right][left] = last;
                }
            }
        }
        vector<vector<int>> dp(n, vector<int>(n, 0));
        if (q[0] == 0)
            dp[0][0] = 1;
        for (int left = 1; left < n; left++) {
            int previousRight = left - 1;
            vector<int> prefix(previousRight + 2, 0);
            for (int previousLeft = 0; previousLeft <= previousRight; previousLeft++) {
                prefix[previousLeft + 1] = prefix[previousLeft] + dp[previousLeft][previousRight];
                if (prefix[previousLeft + 1] >= mod)
                    prefix[previousLeft + 1] -= mod;
            }
            int minPrev = n - 1, siblingUpper = previousRight;
            for (int right = left; right < n; right++) {
                if (right > left && q[right - 1] >= q[right])
                    break;
                minPrev = min(minPrev, bfsOfDfs[q[right] - 1]);
                if (right > left && bfs[right - 1] > bfs[right]) {
                    int candidate = lastEligible[right][left];
                    if (candidate < 0)
                        break;
                    siblingUpper = min(siblingUpper, candidate);
                }
                int upper = min(minPrev, siblingUpper);
                if (upper >= 0)
                    dp[left][right] = prefix[upper + 1];
            }
        }
        int answer = 0;
        for (int left = 0; left < n; left++) {
            answer += dp[left][n - 1];
            if (answer >= mod)
                answer -= mod;
        }
        cout << "Case " << caseNo++ << ": " << answer << '\n';
    }
    return 0;
}
