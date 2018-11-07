// Triangle War
// UVa ID: 751
// Verdict: Accepted
// Submission Date: 2018-11-07
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int getIdx[10][10] = {};
int triangleMask[9] = {
    (1 << 0) | (1 << 1) | (1 << 2),
    (1 << 3) | (1 << 4) | (1 << 5),
    (1 << 2) | (1 << 4) | (1 << 6),
    (1 << 6) | (1 << 7) | (1 << 8),
    (1 << 9) | (1 << 10) | (1 << 11),
    (1 << 5) | (1 << 10) | (1 << 12),
    (1 << 12) | (1 << 13) | (1 << 14),
    (1 << 8) | (1 << 13) | (1 << 15),
    (1 << 15) | (1 << 16) | (1 << 17),
};

inline int checkFilled(int mask, int next)
{
    int newFilled = 0;
    for (int i = 0; i < 9; i++)
        if ((mask & triangleMask[i]) != triangleMask[i] && (next & triangleMask[i]) == triangleMask[i])
            newFilled++;
    return newFilled;
}

int dp[1 << 18];

int dfs(int mask, int triangles)
{
    if (~dp[mask]) return dp[mask];
    int r = 0;
    for (int i = 0; i < 18; i++)
    {
        if (mask & (1 << i)) continue;
        int next = mask | (1 << i);
        int x = checkFilled(mask, next);
        if (x)
            r = max(r, x + dfs(next, triangles - x));
        else
            r = max(r, triangles - dfs(next, triangles));
    }
    return dp[mask] = r;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    getIdx[1][2] = 0, getIdx[1][3] = 1, getIdx[2][3] = 2;
    getIdx[2][4] = 3, getIdx[2][5] = 4, getIdx[4][5] = 5;
    getIdx[3][5] = 6, getIdx[3][6] = 7, getIdx[5][6] = 8;
    getIdx[4][7] = 9, getIdx[4][8] = 10, getIdx[7][8] = 11;
    getIdx[5][8] = 12, getIdx[5][9] = 13, getIdx[8][9] = 14;
    getIdx[6][9] = 15, getIdx[6][10] = 16, getIdx[9][10] = 17;

    int cases, n;
    cin >> cases;
    memset(dp, -1, sizeof(dp));
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> n;
        int MASK = 0, A = 0, B = 0, PLAYER = 1, REMAIN = 9;
        for (int step = 1, i, j; step <= n; step++)
        {
            cin >> i >> j;
            int x = checkFilled(MASK, MASK | (1 << (getIdx[i][j])));
            if (PLAYER) A += checkFilled(MASK, MASK | (1 << (getIdx[i][j])));
            else B += checkFilled(MASK, MASK | (1 << (getIdx[i][j])));
            MASK |= (1 << (getIdx[i][j]));
            if (!x) PLAYER = !PLAYER;
        }
        REMAIN -= A + B;
        dfs(MASK, REMAIN);
        if (PLAYER)
        {
            A += dp[MASK];
            B += REMAIN - dp[MASK];
        }
        else
        {
            B += dp[MASK];
            A += REMAIN - dp[MASK];
        }
        cout << "Game " << cs << ": ";
        if (A > B) cout << "A wins.\n";
        else cout << "B wins.\n";
    }

    return 0;
}
