// Nim
// UVa ID: 1559
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int N, S, mi, M[2], cache[1 << 13];

int dfs(int s, int player)
{
    if (s <= 1) return cache[s] = 0;
    if (~cache[s]) return cache[s];
    for (int i = min(s, N); i <= min(s, M[player]); i++)
        if (!dfs(s - i, !player)) return cache[s] = 1;
    return cache[s] = 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N, N > 0)
    {
        cin >> S;
        M[0] = M[1] = 0;
        for (int i = 0; i < 2 * N; i++)
        {
            cin >> mi;
            M[i % 2] += mi;
        }
        memset(cache, -1, sizeof(cache));
        cout << dfs(S, 0) << '\n';
    }

    return 0;
}
