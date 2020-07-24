// Free Candies
// UVa ID: 10118
// Verdict: Accepted
// Submission Date: 2020-07-24
// UVa Run Time: 0.070s
//
// 版权所有（C）2020，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int N = 45;

int n, candies[5][N], dp[N][N][N][N], top[5];

int dfs(int mask)
{
	int a = top[0], b = top[1], c = top[2], d = top[3];

	if(~dp[a][b][c][d]) return dp[a][b][c][d];
	if(__builtin_popcount(mask) >= 5) return dp[a][b][c][d] = 0;

	int r = 0;
	for(int i = 0; i < 4; i++)
	{
		if(top[i] == n) continue;
		int collected = mask & (1 << candies[i][top[i]]) ? 1 : 0;
		mask ^= (1 << candies[i][top[i]++]);
		collected += dfs(mask);
		mask ^= (1 << candies[i][--top[i]]);
		r = max(r, collected);
	}

	return dp[a][b][c][d] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

	while(cin >> n, n)
	{
		memset(dp, -1, sizeof(dp));
        memset(top, 0, sizeof (top));
    
		for(int i = 0; i < n; i++)
			for(int j = 0; j < 4; j++)
				cin >> candies[j][i];

		cout << dfs(0) << '\n';
	}

	return 0;
}
