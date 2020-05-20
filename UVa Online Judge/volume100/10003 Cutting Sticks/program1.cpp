// Cutting Sticks （切割木棍）
// PC/UVa IDs: 111105/10003, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2020-04-05
// UVa Run Time: 0.030s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net
//
// 应用四边形不等式优化技巧。

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55, INF = 0x7f7f7f7f;

int dp[MAXN][MAXN], K[MAXN][MAXN], c[MAXN] = {}, n;

int main(int ac, char *av[])
{
	int length, n;

	while (cin >> length, length)
	{
	    cin >> n;
		for (int i = 1; i <= n; i++) cin >> c[i];
		c[++n] = length;
		memset(dp, 0, sizeof dp);
		for (int i = 0; i <= n; i++) K[i][i] = i;
		for (int L = 2; L <= n; L++)
		    for (int i = 1, j = L; j <= n; i++, j++)
		    {
		        dp[i][j] = INF;
		        for (int k = K[i][j - 1]; k <= K[i + 1][j]; k++)
		        {
		            int next = dp[i][k] + dp[k + 1][j] + c[j] - c[i -1];
		            if (next < dp[i][j])
		            {
		                dp[i][j] = next;
		                K[i][j] = k;
		            }
	            }
		    }
	    cout << "The minimum cutting is " << dp[1][n] << ".\n";
	}

	return 0;
}
