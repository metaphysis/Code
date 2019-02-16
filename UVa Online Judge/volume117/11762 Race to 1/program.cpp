// Race to 1
// UVa ID: 11762
// Verdict: Accepted
// Submission Date: 2019-02-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1000010;

int primes[MAXN] = {}, cnt = 0;
double dp[MAXN];

double dfs(int D)
{
    if (D == 1) return 0;
    if (dp[D] >= 0) return dp[D];
    // Get all different factor of D.
    int d = D;
    vector<int> factors;
    for (int i = 0; primes[i] * primes[i] <= d; i++)
    {
        if (d % primes[i] == 0)
        {
            factors.push_back(primes[i]);
            while (d % primes[i] == 0)
                d /= primes[i];
        }
    }
    if (d > 1) factors.push_back(d);
    // Get count of primes which no bigger than D.
    int x = factors.size();
    int y = upper_bound(primes, primes + cnt, D) - primes;
    double r = y - x;
    for (auto f : factors)
        r += 1 + dfs(D / f);
    r /= x;
    return dp[D] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i < MAXN; i++)
    {
        dp[i] = -1;
        if (!primes[i]) primes[cnt++] = i;
        for (int j = 0; j < cnt && i * primes[j] < MAXN; j++)
        {
            primes[i * primes[j]] = 1;
            if (!(i % primes[j])) break;
        }
    }

    int cases, N;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N;
        cout << "Case " << cs << ": ";
        cout << fixed << setprecision(10) << dfs(N) << '\n';
    }

    return 0;
}
