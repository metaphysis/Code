// Constrained Exchange Sort
// UVa ID: 10073 
// Verdict: Accepted
// Submission Date: 2019-01-27
// UVa Run Time: 0.040s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net
//
// Transform the problem to 15-Puzzle problem.

#include <bits/stdc++.h>

using namespace std;

struct nextPos
{
    int hn, dir, x, y, z;
    bool operator<(const nextPos &p) const
    {
        return hn < p.hn;
    }
};

int offset[6][3] = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, -1}, {0, -1, 0}, {1, 0, 0}};
int cube[2][2][3], jumps[16][2][2][3] = {}, distDiff[16][2][2][3][2][2][3] = {}, n;
int moves[64], restored, maxDepth;
string seq;

void dfs(int hn, int gn, int dir, int ex, int ey, int ez)
{
    if (hn + gn > maxDepth) return;
    if (hn == 0)
    {
        for (int i = 0; i < gn; i++)
            cout << char('A' + moves[i]);
        cout << '\n';
        restored = 1;
        return;
    }

    // Get candidate next position.
    int cnt = 0;
    nextPos saved[4];
    for (int k = 0; k < 6; k++)
    {
        if (k == dir) continue;
        int nextx = ex + offset[k][0], nexty = ey + offset[k][1], nextz = ez + offset[k][2];
        if (nextx < 0 || nextx >= 2 || nexty < 0 || nexty >= 2 || nextz < 0 || nextz >= 3) continue;
        saved[cnt].hn = hn + distDiff[cube[nextx][nexty][nextz]][ex][ey][ez][nextx][nexty][nextz];
        saved[cnt].dir = k, saved[cnt].x = nextx, saved[cnt].y = nexty, saved[cnt].z = nextz;
        cnt++;
    }

    // Less H(n), search first.
    sort(saved, saved + cnt);
    for (int k = 0; k < cnt; k++)
    {
        swap(cube[ex][ey][ez], cube[saved[k].x][saved[k].y][saved[k].z]);
        moves[gn] = cube[ex][ey][ez];
        dfs(saved[k].hn, gn + 1, 5 - saved[k].dir, saved[k].x, saved[k].y, saved[k].z);
        if (restored) return;
        swap(cube[ex][ey][ez], cube[saved[k].x][saved[k].y][saved[k].z]);
    }
}

void idaStar(int ex, int ey, int ez)
{
    int hn = 0;
    for (int x = 0; x < 2; x++)
        for (int y = 0; y < 2; y++)
            for (int z = 0; z < 3; z++)
                // Don't count the 'L'.
                if (cube[x][y][z] < 11)
                    hn += jumps[cube[x][y][z]][x][y][z];

    maxDepth = 0;
    while (true)
    {
        restored = 0;
        dfs(hn, 0, -1, ex, ey, ez);
        if (restored) break;
        maxDepth++;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    // Manhattan distance.
    for (int x1 = 0; x1 < 2; x1++)
        for (int y1 = 0; y1 < 2; y1++)
            for (int z1 = 0; z1 < 3; z1++)
                for (int x2 = 0; x2 < 2; x2++)
                    for (int y2 = 0; y2 < 2; y2++)
                        for (int z2 = 0; z2 < 3; z2++)
                        {
                            int dx = abs(x1 - x2), dy = abs(y1 - y2), dz = abs(z1 - z2);
                            jumps[x1 * 6 + y1 * 3 + z1][x2][y2][z2] = dx + dy + dz;
                        }
    for (int c = 0; c < 12; c++)
        for (int x1 = 0; x1 < 2; x1++)
            for (int y1 = 0; y1 < 2; y1++)
                for (int z1 = 0; z1 < 3; z1++)
                    for (int x2 = 0; x2 < 2; x2++)
                        for (int y2 = 0; y2 < 2; y2++)
                            for (int z2 = 0; z2 < 3; z2++)
                                distDiff[c][x1][y1][z1][x2][y2][z2] = jumps[c][x1][y1][z1] - jumps[c][x2][y2][z2];

    int cases = 0, ex, ey, ez;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Permutation #" << cs << '\n';
        cin >> seq;
        int idx = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 3; k++)
                {
                    if (seq[idx] == 'L') ex = i, ey = j, ez = k;
                    cube[i][j][k] = seq[idx] - 'A';
                    idx++;
                }
        idaStar(ex, ey, ez);
        cout << '\n';
    }

    return 0;
}
