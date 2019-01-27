// 15-Puzzle Problem
// UVa ID: 10181
// Verdict: Accepted
// Submission Date: 2019-01-28
// UVa Run Time: 0.150s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct nextPos
{
    int hn, dir, r, c;
    bool operator<(const nextPos &p) const { return hn < p.hn; }
};

string directions = "URLD";
int offset[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};
int puzzle[5][5], Hn[16][5][5] = {}, dHn[16][5][5][5][5] = {};
int done, maxDepth, path[64];

void dfs(int hn, int gn, int dir, int emptyr, int emptyc)
{
    if (hn + gn > maxDepth) return;
    if (hn == 0) {
        done = 1;
        for (int i = 0; i < gn; i++) cout << directions[path[i]];
        cout << '\n';
        return;
    }

    int cnt = 0;
    nextPos saved[4];
    for (int k = 0; k < 4; k++) {
        if (k == dir) continue;
        int nextr = emptyr + offset[k][0], nextc = emptyc + offset[k][1];
        if (nextr < 1 || nextr > 4 || nextc < 1 || nextc > 4) continue;
        saved[cnt].hn = hn + dHn[puzzle[nextr][nextc]][emptyr][emptyc][nextr][nextc];
        saved[cnt].dir = k, saved[cnt].r = nextr, saved[cnt].c = nextc;
        cnt++;
    }

    sort(saved, saved + cnt);
    for (int k = 0; k < cnt; k++) {
        swap(puzzle[emptyr][emptyc], puzzle[saved[k].r][saved[k].c]);
        path[gn] = saved[k].dir;
        dfs(saved[k].hn, gn + 1, 3 - saved[k].dir, saved[k].r, saved[k].c);
        if (done) return;
        swap(puzzle[emptyr][emptyc], puzzle[saved[k].r][saved[k].c]);
    }
}

void idaStar(int emptyr, int emptyc)
{
    int hn = 0;
    for (int r = 1; r <= 4; r++)
        for (int c = 1; c <= 4; c++)
            if (puzzle[r][c])
                hn += Hn[puzzle[r][c]][r][c];

    maxDepth = 0;
    while (true) {
        done = 0;
        dfs(hn, 0, -1, emptyr, emptyc);
        if (done) break;
        maxDepth++;
    }
}

bool solvable(vector<int> tiles)
{
    int sum = 0, row;
    for (int i = 0; i < tiles.size(); i++) {
        int tile = tiles[i];
        if (tile == 0) {
            row = (i / 4 + 1);
            continue;
        }
        for (int j = i; j < tiles.size(); j++)
            if (tiles[j] < tile && tiles[j] != 0)
                sum++;
    }
    return ((sum + row) % 2 == 0);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int r1 = 1; r1 <= 4; r1++)
        for (int c1 = 1; c1 <= 4; c1++)
            for (int r2 = 1; r2 <= 4; r2++)
                for (int c2 = 1; c2 <= 4; c2++)
                    Hn[(r1 - 1) * 4 + c1][r2][c2] = abs(r1 - r2) + abs(c1 - c2);

    for (int t = 1; t <= 15; t++)
        for (int r1 = 1; r1 <= 4; r1++)
            for (int c1 = 1; c1 <= 4; c1++)
                for (int r2 = 1; r2 <= 4; r2++)
                    for (int c2 = 1; c2 <= 4; c2++)
                        dHn[t][r1][c1][r2][c2] = Hn[t][r1][c1] - Hn[t][r2][c2];

    int cases = 0, emptyr, emptyc;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        vector<int> tiles;
        for (int r = 1; r <= 4; r++)
            for (int c = 1; c <= 4; c++)
            {
                cin >> puzzle[r][c];
                tiles.push_back(puzzle[r][c]);
                if (puzzle[r][c] == 0) emptyr = r, emptyc = c;
            }
        if (solvable(tiles)) idaStar(emptyr, emptyc);
        else cout << "This puzzle is not solvable.\n";
    }

    return 0;
}
