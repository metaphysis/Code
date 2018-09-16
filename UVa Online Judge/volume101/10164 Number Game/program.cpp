// Number Game
// UVa ID: 10164
// Verdict: Accepted
// Submission Date: 2018-09-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, number[2050], used[2048], cache[1100][1100];

int dfs(int sum, int taken)
{
    if (taken == N)
    {
        if (sum == 0)
        {
            cout << "Yes\n";
            int printed = 0;
            for (int i = 0; i < (2 * N - 1); i++)
                if (used[i])
                {
                    if (printed++) cout << ' ';
                    cout << number[i];
                }
            cout << '\n';
            return 1;
        }
        return 0;
    }
    if (cache[sum][taken]) return 0;
    cache[sum][taken] = 1;
    for (int i = 0; i < (2 * N - 1); i++)
    {
        if (used[i]) continue;
        used[i] = 1;
        if (dfs((sum + number[i]) % N, taken + 1))
            return 1;
        used[i] = 0;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N)
    {
        if (N == 0) break;
        for (int i = 0; i < (2 * N - 1); i++)
            cin >> number[i];
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= N; j++)
                cache[i][j] = 0;
        memset(used, 0, sizeof(used));
        if (!dfs(found = 0, 0))
            cout << "No\n";
    }

    return 0;
}
