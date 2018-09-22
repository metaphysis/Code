// Blobs in the Board
// UVa ID: 11391
// Verdict: Accepted
// Submission Date: 2018-09-22
// UVa Run Time: 1.090s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int R, C, N;
int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
int dp[1 << 16];

int dfs(int mask, int blobs)
{
    if (blobs == 1) return dp[mask] = 1LL;
    if (~dp[mask]) return dp[mask];
    int r = 0, i, j, ii, jj, iii, jjj, b1, b2, b3;
    for (int bit = 0; bit < R * C; bit++)
        if (mask & (1 << bit))
        {
            i = bit / C, j = bit % C;
            b1 = (1 << bit);
            for (int k = 0; k < 8; k++)
            {
                ii = i + offset[k][0], jj = j + offset[k][1];
                iii = ii + offset[k][0], jjj = jj + offset[k][1];
                if (ii < 0 || ii >= R || jj < 0 || jj >= C) continue;
                if (iii < 0 || iii >= R || jjj < 0 || jjj >= C) continue;
                b2 = (1 << (ii * C + jj)), b3 = (1 << (iii * C + jjj));
                if (!(mask & b2) || (mask & b3)) continue;
                r += dfs((mask ^ (b1 | b2)) | b3, blobs - 1);
            }
        }
    return dp[mask] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> R >> C >> N;
        int mask = 0;
        for (int i = 0, x, y; i < N; i++)
        {
            cin >> x >> y;
            mask |= (1 << ((x - 1) * C + (y - 1)));
        }
        cout << "Case " << cs << ": ";
        memset(dp, -1, sizeof(dp));
        cout << dfs(mask, N) << '\n';
    }

    return 0;
}
