// Jaguar King
// UVa ID: 11163
// Verdict: Accepted
// Submission Date: 2018-07-22
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Transform the problem to 15-Puzzle problem.

#include <bits/stdc++.h>

using namespace std;

struct nextPos
{
    int hn, dir, r, c;
    bool operator<(const nextPos &p) const
    {
        return hn < p.hn;
    }
};

int offset[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
int tiger[15][5], jumps[45][15][5] = {}, distDiff[45][15][5][15][5] = {}, n;
int restored, maxDepth;

void dfs(int hn, int gn, int dir, int kingR, int kingC)
{
    if (hn + gn > maxDepth) return;
    if (hn == 0)
    {
        restored = 1;
        return;
    }

    // Get candidate next position.
    int cnt = 0;
    nextPos saved[4];
    for (int k = 0; k < 4; k++)
    {
        if (k == dir) continue;
        int nextR = kingR + offset[k][0], nextC = kingC + offset[k][1];
        if (nextR < 1 || nextR > n) continue;
        if (nextC == 0) nextC = 4;
        if (nextC == 5) nextC = 1;
        saved[cnt].hn = hn + distDiff[tiger[nextR][nextC]][kingR][kingC][nextR][nextC];
        saved[cnt].dir = k, saved[cnt].r = nextR, saved[cnt].c = nextC;
        cnt++;
    }

    // Less H(n), search first.
    sort(saved, saved + cnt);
    for (int k = 0; k < cnt; k++)
    {
        swap(tiger[kingR][kingC], tiger[saved[k].r][saved[k].c]);
        dfs(saved[k].hn, gn + 1, 3 - saved[k].dir, saved[k].r, saved[k].c);
        if (restored) return;
        swap(tiger[kingR][kingC], tiger[saved[k].r][saved[k].c]);
    }
}

void idaStar(int kingR, int kingC)
{
    int hn = 0;
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= 4; c++)
            // Don't count king self.
            if (tiger[r][c] > 1)
                hn += jumps[tiger[r][c]][r][c];

    maxDepth = 0;
    while (true)
    {
        restored = 0;
        dfs(hn, 0, -1, kingR, kingC);
        if (restored)
        {
            cout << maxDepth << '\n';
            break;
        }
        maxDepth++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    // Manhattan distance.
    for (int r1 = 1; r1 <= 10; r1++)
        for (int c1 = 1; c1 <= 4; c1++)
            for (int r2 = 1; r2 <= 10; r2++)
                for (int c2 = 1; c2 <= 4; c2++)
                {
                    int rDiff = abs(r1 - r2), cDiff = abs(c1 - c2);
                    if (cDiff == 3) cDiff = 1;
                    jumps[(r1 - 1) * 4 + c1][r2][c2] = rDiff + cDiff;
                }
    
    for (int i = 1; i <= 40; i++)
        for (int j = 1; j <= 10; j++)
            for (int k = 1; k <= 4; k++)
                for (int l = 1; l <= 10; l++)
                    for (int m = 1; m <= 4; m++)
                        // A tiger at [l][m] jumps to [j][k], the difference of Manhattan distance.
                        distDiff[i][j][k][l][m] = jumps[i][j][k] - jumps[i][l][m];

    int cases = 0, kingR, kingC;
    while (cin >> n, n > 0)
    {
        cout << "Set " << ++cases << ":\n";
        n /= 4;
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= 4; c++)
            {
                cin >> tiger[r][c];
                if (tiger[r][c] == 1) kingR = r, kingC = c;
            }
        idaStar(kingR, kingC);
    }

    return 0;
}
