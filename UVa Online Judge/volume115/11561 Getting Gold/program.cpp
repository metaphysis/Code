// Getting Gold
// UVa ID: 11561
// Verdict: Accepted
// Submission Date: 2018-01-31
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int H, W, T;
char grid[64][64];
int infected[64][64];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void dfs(int i, int j, string &old, char replaced)
{
    if (grid[i][j] == 'G') T++;
    grid[i][j] = replaced;
    if (infected[i][j]) return;
    for (int k = 0; k < 4; k++)
    {
        int nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= 0 && nexti < H && nextj >= 0 && nextj < W)
            if (old.find(grid[nexti][nextj]) != old.npos)
                dfs(nexti, nextj, old, replaced);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string old = "PG.";
    while (cin >> W >> H)
    {
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                cin >> grid[i][j];
        
        memset(infected, 0, sizeof(infected));
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (grid[i][j] == 'T')
                {
                    for (int k = 0; k < 4; k++)
                    {
                        int nexti = i + offset[k][0], nextj = j + offset[k][1];
                        if (nexti >= 0 && nexti < H && nextj >= 0 && nextj < W)
                            infected[nexti][nextj] = 1;  
                    }
                }
                
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (grid[i][j] == 'P')
                {
                    T = 0;
                    dfs(i, j, old, '#');
                }
        cout << T << '\n';
    }

    return 0;
}
