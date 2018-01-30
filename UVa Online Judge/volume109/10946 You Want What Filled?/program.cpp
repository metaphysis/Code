// You Want What Filled?
// UVa ID: 10946
// Verdict: Accepted
// Submission Date: 2018-01-30
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

int H, W, T, nexti, nextj;
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
char grid[64][64];

struct hole
{
    char letter;
    int number;
    bool operator<(const hole &h) const
    {
        if (number != h.number) return number > h.number;
        return letter < h.letter;
    }
};

void dfs(int i, int j, char old, char replaced)
{
    T++;
    grid[i][j] = replaced;
    for (int k = 0; k < 4; k++)
    {
        nexti = i + offset[k][0], nextj = j + offset[k][1];
        if (nexti >= 0 && nexti < H && nextj >= 0 && nextj < W)
            if (grid[nexti][nextj] == old)
                dfs(nexti, nextj, old, replaced);
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> H >> W)
    {
        if (H == 0 && W == 0) break;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                cin >> grid[i][j];

        vector<hole> holes;
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                if (grid[i][j] != '.')
                {
                    T = 0;
                    char C = grid[i][j];
                    dfs(i, j, grid[i][j], '.');
                    holes.push_back(hole{C, T});
                }

        sort(holes.begin(), holes.end());
        cout << "Problem " << ++cases << ":\n";
        for (auto h : holes)
            cout << h.letter << ' ' << h.number << '\n';
    }

    return 0;
}
