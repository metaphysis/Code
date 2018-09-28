// Gangsters
// UVa ID: 672
// Verdict: Accepted
// Submission Date: 2018-09-28
// UVa Run Time: 0.260s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct gangster
{
    int ti, pi, si;
} G[101];

int M, N, K, T;
int cache[30001][101], V[30001][101];

int dfs(int t, int s)
{
    if (t > T || s < 0 || s > K) return 0;
    if (~cache[t][s]) return cache[t][s];
    int r = max(dfs(t + 1, s), max(dfs(t + 1, s - 1), dfs(t + 1, s + 1)));
    return cache[t][s] = r + V[t][s];
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> M;
    for (int cs = 1; cs <= M; cs++)
    {
        cin >> N >> K >> T;

        for (int i = 0; i < N; i++) cin >> G[i].ti;
        for (int i = 0; i < N; i++) cin >> G[i].pi;
        for (int i = 0; i < N; i++) cin >> G[i].si;

        for (int i = 0; i <= T; i++)
            for (int j = 0; j <= K; j++)
            {
                cache[i][j] = -1;
                V[i][j] = 0;
            }
        for (int i = 0; i < N; i++)
            V[G[i].ti][G[i].si] += G[i].pi;

        if (cs > 1) cout << '\n';
        cout << dfs(0, 0) << '\n';
    }

    return 0;
}
