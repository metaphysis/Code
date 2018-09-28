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
int n, t, m;

int dfs(int nSong, int mDisk, int tMinute)
{
    if (nSong >= n || mDisk >= m) return 0;
    if (~cache[nSong][mDisk][tMinute]) return cache[nSong][mDisk][tMinute];
    int r = dfs(nSong + 1, mDisk, tMinute);
    if (tMinute + songs[nSong] < t)
        r = max(r, 1 + dfs(nSong + 1, mDisk, tMinute + songs[nSong]));
    if (tMinute + songs[nSong] == t)
        r = max(r, 1 + dfs(nSong + 1, mDisk + 1, 0));
    if (tMinute + songs[nSong] > t)
        r = max(r, dfs(nSong, mDisk + 1, 0));
    return cache[nSong][mDisk][tMinute] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, ti;
    char comma;

    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {  
        cin >> n >> t >> m;
        songs.clear();
        for (int nSong = 0; nSong < n; nSong++)
        {
            if (nSong) cin >> comma;
            cin >> ti;
            songs.push_back(ti);
        }
        if (cs) cout << '\n';
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= m; j++)
                for (int k = 0; k <= t; k++)
                    cache[i][j][k] = -1;
        cout << dfs(0, 0, 0) << '\n';
    }

	return 0;
}
