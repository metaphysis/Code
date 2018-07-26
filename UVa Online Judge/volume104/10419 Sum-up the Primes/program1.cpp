// Sum-up the Primes
// UVa ID: 10419
// Verdict: Accepted
// Submission Date: 2018-07-26
// UVa Run Time: 0.890s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int primes[301] = {}, cnt = 0;
int n, t;
int cache[16];

bool dfs(int depth, int sum, int idx)
{
    if (sum > n) return false;
    if (depth == t)
    {
        if (sum == n) return true;
        return false;
    }
    for (int i = idx; i < cnt; i++)
    {
        cache[depth] = primes[i];
        if (primes[i] == 2)
        {
            if (dfs(depth + 1, sum + primes[i], i + 1))
                return true;
        }
        else
        {
            if (dfs(depth + 1, sum + primes[i], i + (depth && cache[depth - 1] == cache[depth])))
                return true;
        }
    }
    return false;
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
            primes[cnt++] = i;
            for (int j = i + i; j <= 300; j += i)
                primes[j] = 1;
        }

    sort(primes, primes + cnt, cmp);

    int cases = 0;
    while (cin >> n >> t)
    {
        if (n == 0) break;
        cout << "CASE " << ++cases << ":\n";

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
