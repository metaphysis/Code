// Sum-up the Primes
// UVa ID: 10419
// Verdict: Accepted
// Submission Date: 2018-07-26
// UVa Run Time: 3.410s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int primes[301] = {}, cnt = 0;
int n, t;
int marked[128][1001][15], cache[16];

bool dfs(int idx, int sum, int used)
{
    if (marked[idx][sum][used]) return false;
    if (sum > n || idx == cnt) return false;
    if (used == t)
    {
        if (sum == n) return true;
        return false;
    }
    cache[used] = primes[idx];
    if (dfs(idx + 1, sum + primes[idx], used + 1)) return true;
    if (dfs(idx + 1, sum, used)) return true;
    return !(marked[idx][sum][used] = 1);
}

bool cmp(int a, int b)
{
    return to_string(a) < to_string(b);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i <= 300; i++)
        if (!primes[i])
        {
            for (int j = i + i; j <= 300; j += i)
                primes[j] = 1;
        }

    primes[cnt++] = 2;
    for (int i = 3; i <= 300; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            primes[cnt++] = i;
        }

    sort(primes, primes + cnt, cmp);

    int cases = 0;
    while (cin >> n >> t)
    {
        if (n == 0) break;
        cout << "CASE " << ++cases << ":\n";

        for (int i = 0; i < cnt; i++)
            for (int j = 0; j <= n; j++)
                for (int k = 0; k <= t; k++)
                    marked[i][j][k] = 0;

        if (dfs(0, 0, 0))
        {
            for (int i = 0; i < t; i++)
            {
                if (i) cout << '+';
                cout << cache[i];
            }
            cout << '\n';
        }
        else cout << "No Solution.\n";
    }

    return 0;
}
