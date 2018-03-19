// Block Voting
// UVa ID: 435
// Verdict: Accepted
// Submission Date: 2018-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1010;

int dp[MAXN];
int votes[24], majority = 0, cnt = 0;
        
int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> cnt;
        majority = 0;
        for (int i = 0; i < cnt; i++)
        {
            cin >> votes[i];
            majority += votes[i];
        }
        
        majority = majority / 2 + (majority % 2);
        
        // DP, knapsack, count of different subset sum.
        for (int k = 0; k < cnt; k++)
        {
            memset(dp, 0, sizeof(dp));
            dp[0] = 1;
            for (int i = 0; i < cnt; i++)
            {
                if (i == k) continue;
                for (int j = majority; j >= votes[i]; j--)
                    if (dp[j - votes[i]])
                        dp[j] += dp[j - votes[i]];
            }

            // Print.
            int powerIndex = 0;
            for (int i = max(0, majority - votes[k]); i < majority; i++)
                powerIndex += dp[i];
            cout << "party " << (k + 1) << " has power index " << powerIndex << '\n';
        }
        cout << '\n';
    }
    
	return 0;
}
