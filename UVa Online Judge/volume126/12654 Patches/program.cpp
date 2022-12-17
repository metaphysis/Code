// Patches
// UVa ID: 12654
// Verdict: Accepted
// Submission Date: 2022-12-04
// UVa Run Time: 0.290s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n, c, t1, t2;
int fi[2010], dp[1010], bias;
int dfs(int idx)
{
    if (idx == n) return 0;
    if (~dp[idx]) return dp[idx];
    int r1 = t1 + dfs(upper_bound(fi + bias, fi + bias + n, fi[bias + idx] + t1) - fi - bias);
    int r2 = t2 + dfs(upper_bound(fi + bias, fi + bias + n, fi[bias + idx] + t2) - fi - bias);
    return dp[idx] = min(r1, r2);
}
int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	while (cin >> n >> c >> t1 >> t2)	{
	    for (int i = 0; i < n; i++) cin >> fi[i];
	    for (int i = 0; i < n; i++) fi[n + i] = fi[i] + c;
	    int r = 0x7f7f7f7f;
	    for (int i = 0; i < n; i++)
	    {
	        bias = i;
	        memset(dp, -1, sizeof dp);
	        r = min(r, dfs(0));
	    }
	    cout << r << '\n';
	}
	return 0;
}
