// Brothers
// UVa ID: 12187
// Verdict: Accepted
// Submission Date: 2018-01-10
// UVa Run Time: 0.090s
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

    int N, R, C, K, grid[110][110], temp[110][110];
    int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (cin >> N >> R >> C >> K, N > 0)
    {
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                cin >> grid[i][j];

        for (int k = 1; k <= K; k++)
        {
            for (int i = 1; i <= R; i++)
                for (int j = 1; j <= C; j++)
                {
                    temp[i][j] = grid[i][j];
                    for (int z = 0; z < 4; z++)
                    {
                        int ii = i + offset[z][0], jj = j + offset[z][1];
                        if (ii >= 1 && ii <= R && jj >= 1 && jj <= C)
                        {
                            if (((grid[ii][jj] + 1) % N) == grid[i][j])
                            {
                                temp[i][j] = grid[ii][jj];
                                break;
                            }
                        }
                    }
                }
            memcpy(grid, temp, sizeof(temp));
        }
        
        for (int i = 1; i <= R; i++)
        {
            for (int j = 1; j <= C; j++)
            {
                if (j > 1) cout << ' ';
                cout << grid[i][j];
            }
            cout << '\n';
        }
    }

    return 0;
}
