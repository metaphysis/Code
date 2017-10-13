// Antenna Placement
// UVa ID: 10349
// Verdict: Accepted
// Submission Date: 2017-10-13
// UVa Run Time: 0.000s
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

const int MAXV = 410;

vector<int> edges[MAXV];
int visited[MAXV], cx[MAXV], cy[MAXV], tx, ty;
char g[50][20];

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

// 匈牙利算法求最大匹配数。
int hungarian()
{
    int matches = 0;
    memset(cx, 0, sizeof(cx)); memset(cy, 0, sizeof(cy));
    for (int u = 1; u <= tx; u++)
        if (!cx[u])
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(u);
        }
    return matches;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        int h, w;
        cin >> h >> w;

        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
                cin >> g[i][j];

        tx = ty = h * w;
        for (int i = 1; i <= tx; i++)
            edges[i].clear();

        int v = 0;
        for (int i = 1; i <= h; i++)
            for (int j = 1; j <= w; j++)
                if (g[i][j] == '*')
                {
                    v++;
                    if ((i + j) % 2 == 0)
                    {
                        if (i < h && g[i + 1][j] == '*')
                            edges[(i - 1) * w + j].push_back(i * w + j);
                        if (i > 1 && g[i - 1][j] == '*')
                            edges[(i - 1) * w + j].push_back((i - 2) * w + j);
                        if (j < w && g[i][j + 1] == '*')
                            edges[(i - 1) * w + j].push_back((i - 1) * w + j + 1);
                        if (j > 1 && g[i][j - 1] == '*')
                            edges[(i - 1) * w + j].push_back((i - 1) * w + j - 1);
                    }
                }

        cout << (v - hungarian()) << '\n';
    }
    
    return 0;
}
