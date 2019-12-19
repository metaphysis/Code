// Sum-up the Primes
// UVa ID: 10419
// Verdict: Accepted
// Submission Date: 2019-12-19
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 301;

int primes[MAXN], cnt = 0;
bool dp[MAXN][1010][20];

int main(int argc, char *argv[])
{
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	
	bool aux[MAXN];
	memset(aux, true, sizeof aux);
	for(int i = 2; i < MAXN; i++) {
		if(!aux[i]) continue;
		primes[++cnt] = i;
		if(i > 2) primes[++cnt] = i;
		for(int j = 2; i * j < MAXN; j++) {
			aux[i * j] = false;
		}
	}

	sort(primes + 1, primes + cnt + 1, [](const int &a, const int &b) { return to_string(a) > to_string(b); });

	dp[0][0][0] = true;
	for(int i = 1; i <= cnt; i++) {
		for(int j = 0; j < 1010; j++) {
			for(int k = 0; k < 15; k++) {
				dp[i][j][k] |= dp[i - 1][j][k];
				if(j < primes[i] || !k) continue;
				dp[i][j][k] |= dp[i - 1][j - primes[i]][k - 1];
			}
		}
	}

    int cases = 0, n, t;
	while (cin >> n >> t)
	{
		cout << "CASE " << ++cases << ":\n";
		if(!dp[cnt][n][t]) cout << "No Solution.\n";
		else
		{
			for(int x = cnt, y = n, z = t; y && x && z; x--)
				if(dp[x][y][z] && y - primes[x] >= 0 && dp[x - 1][y - primes[x]][z - 1])
				{
					y -= primes[x];
					cout << primes[x] << "+\n"[!y];
					z--;
				}
		}
	}

	return 0;
}
