// Raucous Rockers
// UVa ID: 473
// Verdict: Accepted
// Submission Date: 2018-09-28
// UVa Run Time: 1.160s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> songs;
int cache[1024][128][128];
int N, T, M;

int dfs(int n, int t, int m)
{
    if (n >= N || m >= M) return 0;
    if (~cache[n][t][m]) return cache[n][t][m];
    // Skip the song.
    int r = max(dfs(n + 1, t, m), dfs(n + 1, 0, m + 1));
    // Try to record the song on current disk.
    if (t + songs[n] < T)
        r = max(r, 1 + dfs(n + 1, t + songs[n], m));
    else if (t + songs[n] == T)
        r = max(r, 1 + dfs(n + 1, 0, m + 1));
    // Try to record the song on next disk.
    r = max(r, dfs(n, 0, m + 1));
    return cache[n][t][m] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, ti;
    char comma;

    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {  
        cin >> N >> T >> M;
        songs.clear();
        for (int i = 0; i < N; i++)
        {
            if (i) cin >> comma;
            cin >> ti;
            songs.push_back(ti);
        }
        if (cs) cout << '\n';
        for (int i = 0; i <= N; i++)
            for (int j = 0; j <= T; j++)
                for (int k = 0; k <= M; k++)
                    cache[i][j][k] = -1;
        cout << dfs(0, 0, 0) << '\n';
    }

	return 0;
}
