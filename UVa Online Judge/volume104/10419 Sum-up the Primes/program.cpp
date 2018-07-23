// Sum-up the Primes
// UVa ID: 10419
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int flag[1001][15] = {};
int primes[301] = {}, sorted[301], cnt = 0;
int n, t;
int used[64], cache[16];
bool printed = false;

void dfs(int depth, int sum)
{
    if (printed) return;
    if (sum > n) return;
    if (depth == t)
    {
        if (sum == n)
        {
            for (int i = 0; i < t; i++)
            {
                if (i) cout << '+';
                cout << cache[i];
            }
            cout << '\n';
            printed = true;
        }
        return;
    }
    for (int i = 0; i < cnt; i++)
    {
        if (sorted[i] == 2 && used[i] >= 1) continue;
        if (used[i] >= 2) continue;
        if (sum + (t - depth) * 2 > n) break;
        used[i]++, cache[depth] = sorted[i];
        dfs(depth + 1, sum + sorted[i]);
        used[i]--;
    }
}

bool cmp(int a, int b)
{
    return to_string(a) < to_string(b);
}

int main(int argc, char *argv[])
{
    //cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 2; i <= 300; i++)
        if (!primes[i])
        {
            primes[cnt++] = i;
            for (int j = i + i; j <= 300; j += i)
                primes[j] = 1;
        }

    copy(primes, primes + cnt, sorted);
    sort(sorted, sorted + cnt, cmp);

    int yes = 0;
    for (int i = 1; i <= 1000; i++)
        for (int j = 1; j <= 14; j++)
        {
            cout << i << ' ' << j << endl;
            if (i == 4) continue;
            if (j == 1)
            {
                flag[i][j] = binary_search(primes, primes + cnt, i);
            }
            else if (j == 2)
            {
                for (int k = 0; k < cnt; k++)
                {
                    if (binary_search(primes, primes + cnt, i - sorted[k]))
                    {
                        flag[i][j] = 1;
                        break;
                    }
                }
            }
            else
            {
                n = i, t = j;
                printed = false;
                memset(used, 0, sizeof(used));
                dfs(0, 0);
                flag[i][j] = printed;
            }
            yes += flag[i][j];
        }
    cout << "yes = " << yes << '\n';

    return 0;

    int cases = 0;
    while (cin >> n >> t)
    {
        if (n == 0) break;
        cout << "CASE " << ++cases << ":\n";
        if (!flag[n][t]) cout << "No Solution.\n";
        else
        {
            printed = false;
            memset(used, 0, sizeof(used));
            dfs(0, 0);
        }
    }

    return 0;
}
