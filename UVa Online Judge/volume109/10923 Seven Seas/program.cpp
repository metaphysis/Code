// Seven Seas
// UVa ID: 10923
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct package
{
    int grid[9][8], si, sj, enemies, moves;
};

int offset[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    
bool getNextState(package pack, package &next, int nexti, int nextj)
{
    next.si = nexti, next.sj = nextj, next.enemies = pack.enemies, next.moves = pack.moves + 1;
    memset(next.grid, 0, sizeof(next.grid));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 8; j++)
        {
            if (pack.grid[i][j] != 1) continue;
            int besti = -1, bestj = -1, bestDist = INT_MAX, currentDist;
            for (int k = 0; k < 8; k++)
            {
                int ii = i + offset[k][0], jj = j + offset[k][1];
                if (ii < 0 || ii >= 9 || jj < 0 || jj >= 8) continue;
                if ((currentDist = (ii - nexti) * (ii - nexti) + (jj - nextj) * (jj - nextj)) < bestDist)
                {
                    bestDist = currentDist;
                    besti = ii, bestj = jj;
                }
            }
            if (besti == nexti && bestj == nextj) return false;
            next.grid[besti][bestj]++;
        }
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 8; j++)
        {
            if (next.grid[i][j] == 1)
            {
                if (pack.grid[i][j] == 2)
                {
                    next.enemies -= next.grid[i][j];
                    next.grid[i][j] = 2;
                }
            }
            if (next.grid[i][j] >= 2)
            {
                next.enemies -= next.grid[i][j];
                next.grid[i][j] = 2;
            }
        }

    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        package pack;
        pack.moves = pack.enemies = 0;
        memset(pack.grid, 0, sizeof(pack.grid));
        char c;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 8; j++)
            {
                cin >> c;
                if (c == 'E') pack.grid[i][j] = 1, pack.enemies++;
                else if (c == '#') pack.grid[i][j] = 2;
                else if (c == 'S') pack.si = i, pack.sj = j;
            }

        queue<package> q;
        q.push(pack);
        bool flag = false;
        while (!q.empty())
        {
            pack = q.front(); q.pop();
            if (!pack.enemies)
            {
                flag = true;
                break;
            }
            if (pack.moves >= 9) continue;
            for (int k = 0; k < 8; k++)
            {
                int nexti = pack.si + offset[k][0], nextj = pack.sj + offset[k][1];
                if (nexti < 0 || nexti >= 9 || nextj < 0 || nextj >= 8) continue;
                if (pack.grid[nexti][nextj]) continue;
                package next;
                if (!getNextState(pack, next, nexti, nextj)) continue;
                q.push(next);
            }
        }

        if (flag) cout << "I'm the king of the Seven Seas!\n";
        else cout << "Oh no! I'm a dead man!\n";
    }

    return 0;
}
