// Ancient Messages
// UVa ID: 1103
// Verdict: Accepted
// Submission Date: 2018-01-31
// UVa Run Time: 0.020s
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

int L, T, H, W, HH, WW;
int grid[210][210], holes;
int code[16][4] = {
    {0, 0, 0, 0}, {0, 0, 0, 1}, {0, 0, 1, 0}, {0, 0, 1, 1}, 
    {0, 1, 0, 0}, {0, 1, 0, 1}, {0, 1, 1, 0}, {0, 1, 1, 1}, 
    {1, 0, 0, 0}, {1, 0, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 1}, 
    {1, 1, 0, 0}, {1, 1, 0, 1}, {1, 1, 1, 0}, {1, 1, 1, 1}
};
int nexti, nextj;
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char symbols[] = {'W', 'A', 'K', 'J', 'S', 'D'};

void dfs(int i, int j, int old, int replaced)
{
    grid[i][j] = replaced;
    for (int k = 0; k < 4; k++)
    {
        nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= L && nexti <= H && nextj >= T && nextj <= W)
        {
            if (grid[nexti][nextj] == old)
                dfs(nexti, nextj, old, replaced);
            else if (grid[nexti][nextj] == 0)
            {
                holes++;
                dfs(nexti, nextj, 0, -1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> HH >> WW, HH > 0)
    {
        cout << "Case " << ++cases << ": ";

        char letter;
        memset(grid, 0, sizeof(grid));
        for (int i = 1; i <= HH; i++)
            for (int j = 0; j < WW; j++)
            {
                cin >> letter;
                if (isdigit(letter))
                {
                    for (int k = 0; k < 4; k++)
                        grid[i][j * 4 + k + 1] = code[letter - '0'][k];
                }
                else
                {
                    for (int k = 0; k < 4; k++)
                        grid[i][j * 4 + k + 1] = code[letter - 'a' + 10][k];
                }
            }

        L = 0, T = 0, H = 209, W = 209;
        dfs(0, 0, 0, -1);
        L = 1, T = 1, H = HH, W = WW * 4;
    
        vector<char> rs;
        for (int i = 1; i <= H; i++)
            for (int j = 1; j <= W; j++)
                if (grid[i][j] == 1)
                {
                    holes = 0;
                    dfs(i, j, 1, -1);
                    rs.push_back(symbols[holes]);
                }
        sort(rs.begin(), rs.end());
        for (auto r : rs) cout << r;
        cout << '\n';
    }
    
    return 0;
}
