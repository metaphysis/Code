// Nim
// UVa ID: 1559
// Verdict: Accepted
// Submission Date: 2018-06-21
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, S, Mi[21], cache[21][1 << 13];

int dfs(int n, int s)
{
    if (s <= 1) return cache[n][s] = 0;
    if (~cache[n][s]) return cache[n][s];
    for (int i = 1; i <= min(s, Mi[n]); i++)
        if (!dfs((n + 1) % N, s - i)) return cache[n][s] = 1;
    return cache[n][s] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N, N > 0)
    {
        cin >> S;
        for (int i = 0; i < 2 * N; i++)
            cin >> Mi[i];
        N *= 2;
        memset(cache, -1, sizeof(cache));
        cout << dfs(0, S) << '\n';
    }

    return 0;
}
