// Dudu the Possum
// UVa ID: 12723
// Verdict: Accepted
// Submission Date: 2019-02-18
// UVa Run Time: 0.040s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, K;
double p[16], calories[512], dp[512];

double dfs(int shelf)
{
    if (shelf > N) return 0;
    if (dp[shelf] >= 0) return dp[shelf];
    double r = calories[shelf];
    for (int i = 1; i <= K; i++)
        r += p[i] * dfs(shelf + i);
    return dp[shelf] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N >> K;
        for (int i = 1; i <= N; i++) dp[i] = -1;
        for (int i = 1; i <= K; i++) cin >> p[i];
        for (int i = 1, Qi; i <= N; i++)
        {
            calories[i] = 0;
            cin >> Qi;
            double Cij, Xij;
            for (int j = 1; j <= Qi; j++)
            {
                cin >> Cij >> Xij;
                calories[i] += Cij * Xij;
            }
        }
        dfs(1);
        cout << "Case #" << cs << ": " << fixed << setprecision(6) << dp[1] << '\n';
    }

    return 0;
}
