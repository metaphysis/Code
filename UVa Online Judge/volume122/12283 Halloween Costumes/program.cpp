// Halloween Costumes
// UVa ID: 12283
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	for (int caseNum = 1; caseNum <= t; caseNum++) {
		int n, m;
		cin >> n >> m;
		vector<int> costume(n);
		for (int i = 0; i < n; i++) cin >> costume[i];
		vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
		for (int i = 0; i < n; i++) dp[i][i] = 1;
		for (int len = 2; len <= n; len++)
			for (int i = 0; i + len <= n; i++) {
				int j = i + len - 1;
				dp[i][j] = dp[i + 1][j] + 1;
				for (int k = i + 1; k <= j; k++)
					if (costume[i] == costume[k])
						dp[i][j] = min(dp[i][j], dp[i][k - 1] + dp[k + 1][j]);
			}
		cout << "Case " << caseNum << ": " << dp[0][n - 1] << '\n';
	}
	return 0;
}
