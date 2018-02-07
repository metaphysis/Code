// Bombs! NO They Are Mines!!
// UVa ID: 10653
// Verdict: Accepted
// Submission Date: 2018-02-07
// UVa Run Time: 0.250s
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

int grid[1010][1010], visited[1010][1010], steps[1010][1010];
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int R, C;
int startr, startc, endr, endc;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> R >> C, R > 0)
    {
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                grid[i][j] = visited[i][j] = 0;

        int rows, rs, cs, cln;
        cin >> rows;
        for (int i = 0; i < rows; i++)
        {
            cin >> rs >> cs;
            for (int j = 0; j < cs; j++)
            {
                cin >> cln;
                grid[rs][cln] = 1;
            }
        }
        cin >> startr >> startc >> endr >> endc;
        
        queue<int> q1, q2;
        q1.push(startr), q2.push(startc);
        visited[startr][startc] = 1;
        steps[startr][startc] = 0;

        while (!q1.empty())
        {
            int r = q1.front(); q1.pop();
            int c = q2.front(); q2.pop();
            if (r == endr && c == endc)
            {
                cout << steps[r][c] << '\n';
                break;
            }
            for (int k = 0; k < 4; k++)
            {
                int nextr = r + offset[k][0];
                int nextc = c + offset[k][1];
                if (nextr >= 0 && nextr < R && nextc >= 0 && nextc < C)
                {
                    if (!visited[nextr][nextc] && !grid[nextr][nextc])
                    {
                        visited[nextr][nextc] = 1;
                        q1.push(nextr);
                        q2.push(nextc);
                        steps[nextr][nextc] = steps[r][c] + 1;
                    }
                }
            }
        }
    }    

    return 0;
}
