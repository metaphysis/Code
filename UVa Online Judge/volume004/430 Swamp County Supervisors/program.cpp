// Swamp County Supervisors
// UVa ID: 430
// Verdict: Accepted
// Submission Date: 2018-03-19
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10010;

int dp[MAXN];
int votes[30], majority = 0, members = 0, cnt = 0;
        
int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string line;
    while (getline(cin, line))
    {
        // Read input.
        istringstream iss(line);
        iss >> majority;
        cnt = 0;
        while (iss >> members)
            votes[cnt++] = members;
        
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
            if (k) cout << ' ';
            cout << powerIndex;
        }
        cout << '\n';
    }
    
	return 0;
}
