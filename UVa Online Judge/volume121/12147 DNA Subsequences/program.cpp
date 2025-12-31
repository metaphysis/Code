// DNA Subsequences
// UVa ID: 12147
// Verdict: Accepted
// Submission Date: 2025-12-29
// UVa Run Time: 0.070s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1010;

int dp[MAXN][MAXN], matched[MAXN][MAXN];

int main() {
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
	int K;
	string A, B;
	while (cin >> K && K) {
		int answer = 0;
		cin >> A >> B;
		int n = A.length(), m = B.length();
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
				if (A[i - 1] == B[j - 1]) matched[i][j] = matched[i - 1][j - 1] + 1;
				else matched[i][j] = 0;
				for (int k = K; k <= matched[i][j]; k++)
				    dp[i][j] = max(dp[i][j], dp[i - k][j - k] + k);
			}
		}
		cout << dp[n][m] << '\n';
	}
	return 0;
}
