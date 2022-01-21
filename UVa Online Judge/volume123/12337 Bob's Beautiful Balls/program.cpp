// Bob's Beautiful Balls
// UVa ID: 12337
// Verdict: Accepted
// Submission Date: 2022-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

string B;
char g[110][110];
int offset[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool check(int row, int cln)
{
    int direction = 0;
    int r = 0, c = -1, nr, nc;
    memset(g, 0, sizeof g);
    int idx = 0, L = B.length();
    while (true)
    {
        if (idx >= L) break;
        nr = r + offset[direction][0], nc = c + offset[direction][1];
        if (nr < 0 || nr >= row || nc < 0 || nc >= cln) 
        {
            direction = (direction + 1) % 4;
            continue;
        }
        if (g[nr][nc])
        {
            direction = (direction + 1) % 4;
            continue;
        }
        g[nr][nc] = B[idx];
        r = nr, c = nc;
        idx++;
    }
    for (int i = 0; i < cln; i++)
    {
        for (int j = 0; j < row; j++)
            if (j && g[j][i] != g[j - 1][i])
                return false;
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
        cin >> B;
        int L = B.length();
        int best = 0x3f3f3f3f;
        for (int row = 2; row < L; row++)
        {
            if (L % row != 0) continue;
            int cln = L / row;
            if (check(row, cln))
            {
                if (row + cln < best)
                    best = row + cln;
            }
        }
        cout << "Case " << cs << ": ";
        if (best == 0x3f3f3f3f) cout << "-1\n";
        else cout << best << '\n';
    }

    return 0;
}
