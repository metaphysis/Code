// Sentry Robots
// UVa ID: 12549
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

const int MAXV = 10100;

list<int> edges[MAXV];
int visited[2 * MAXV], cx[2 * MAXV], cy[2 * MAXV], tx, ty;

int dfs(int u)
{
    for (auto v : edges[u])
        if (!visited[v])
        {
            visited[v] = 1;
            if (!cy[v] || dfs(cy[v]))
            {
                cx[u] = v, cy[v] = u;
                return 1;
            }
        }
    return 0;
}

int hungarian()
{
    int matches = 0;
    memset(cx, 0, sizeof(cx)); memset(cy, 0, sizeof(cy));
    for (int i = 1; i <= tx; i++)
        if (!cx[i])
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    int Y, X, P, px, py, W, wx, wy;
    char grid[110][110];
    int row[110][110], column[110][110];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        memset(grid, '0', sizeof(grid));
        cin >> Y >> X;

        cin >> P;
        for (int i = 1; i <= P; i++)
        {
            cin >> py >> px;
            grid[py][px] = '*';
        }
        cin >> W;
        for (int i = 1; i <= W; i++)
        {
            cin >> wy >> wx;
            grid[wy][wx] = '#';
        }
     
        tx = 0;
        for (int i = 1; i <= Y; i++)
        {
            tx++;
            for (int j = 1; j <= X; j++)
            {
                row[i][j] = tx;
                if (grid[i][j] == '#') tx++;
            }
        }
            
        ty = Y * X;
        for (int i = 1; i <= X; i++)
        {
            ty++;
            for (int j = 1; j <= Y; j++)
            {
                column[j][i] = ty;
                if (grid[j][i] == '#') ty++;
            }
        }
            
        for (int i = 1; i <= tx; i++)
            edges[i].clear();
        for (int i = 1; i <= Y; i++)
            for (int j = 1; j <= X; j++)
                if (grid[i][j] == '*')
                    edges[row[i][j]].push_back(column[i][j]);
        
        cout << hungarian() << '\n';
    }

    return 0;
}
