// Fire!
// UVa ID: 11624
// Verdict: Accepted
// Submission Date: 2018-02-08
// UVa Run Time: 0.190s
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

const int INF = 0x3fffffff;

struct point
{
    int x, y, m;
    point (int x = 0, int y = 0, int m = 0): x(x), y(y), m(m) {}
};

char grid[1010][1010];
int timing[1010][1010], visited[1010][1010];
int R, C, startr, startc;
int offset[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> R >> C;
        
        queue<point> q;
        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
            {
                cin >> grid[i][j];
                visited[i][j] = 0;
                if (grid[i][j] == 'F')
                {
                    q.push(point(i, j, 0));
                    visited[i][j] = 1;
                }
                if (grid[i][j] == 'J') startr = i, startc = j;
                timing[i][j] = INF;
            }

        while (!q.empty())
        {
            point p = q.front(); q.pop();
            timing[p.x][p.y] = p.m;
            for (int k = 0; k < 4; k++)
            {
                int nexti = p.x + offset[k][0], nextj = p.y + offset[k][1];
                if (nexti >= 0 && nexti < R && nextj >= 0 && nextj < C)
                {
                    if (!visited[nexti][nextj] && grid[nexti][nextj] != '#')
                    {
                        visited[nexti][nextj] = 1;
                        q.push(point(nexti, nextj, p.m + 1));
                    }
                }
            }
        }

        for (int i = 0; i < R; i++)
            for (int j = 0; j < C; j++)
                visited[i][j] = 0;
    
        bool escaped = false;

        q.push(point(startr, startc, 0));
        timing[startr][startc] = 0;
        visited[startr][startc] = 1;

        while (!q.empty())
        {
            point p = q.front(); q.pop();
            if (p.x < 0 || p.x >= R || p.y < 0 || p.y >= C)
            {
                escaped = true;
                cout << p.m << '\n';
                break;
            }
            for (int k = 0; k < 4; k++)
            {
                int nextx = p.x + offset[k][0], nexty = p.y + offset[k][1];
                if (nextx >= 0 && nextx < R && nexty >= 0 && nexty < C)
                {
                    if (!visited[nextx][nexty] && grid[nextx][nexty] == '.')
                        if (timing[nextx][nexty] > p.m + 1)
                        {
                            visited[nextx][nexty] = 1;
                            q.push(point(nextx, nexty, p.m + 1));
                        }
                }
                else
                {
                    q.push(point(nextx, nexty, p.m + 1));
                }
            }
        }
        if (!escaped) cout << "IMPOSSIBLE\n";
    }

    return 0;
}
