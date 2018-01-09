// Free Spots
// UVa ID: 10703
// Verdict: Accepted
// Submission Date: 2018-01-09
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int grid[510][510], W, H, N, x1, y1, x2, y2;
    
    while (cin >> W >> H >> N)
    {
        if (W == 0 && H == 0 && N == 0) break;
        for (int i = 1; i <= H; i++)
            for (int j = 1; j <= W; j++)
                grid[i][j] = 1;
        for (int i = 1; i <= N; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            int startx = min(x1, x2), endx = max(x1, x2);
            int starty = min(y1, y2), endy = max(y1, y2);
            for (int j = starty; j <= endy; j++)
                for (int k = startx; k <= endx; k++)
                    grid[j][k] = 0;
        }
        int empty = 0;
        for (int i = 1; i <= H; i++)
            for (int j = 1; j <= W; j++)
                empty += grid[i][j];
        if (empty == 0) cout << "There is no empty spots.\n";
        else if (empty == 1) cout << "There is one empty spot.\n";
        else
        {
            cout << "There are " << empty << " empty spots.\n";
        }
    }
    
    return 0;
}
