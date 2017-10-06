// SAM I AM
// UVa ID: 11419
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

const int MAXV = 1010;

vector<int> edges[MAXV];
int visited[MAXV], cx[MAXV], cy[MAXV], tx;

int dfs(int u)
{
    for (auto v : edges[u])
        if (!visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
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
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    for (int i = 1; i <= tx; i++)
        if (cx[i] == -1)
        {
            memset(visited, 0, sizeof(visited));
            matches += dfs(i);
        }
    return matches;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int r, c, n, x, y;
    while (cin >> r >> c >> n, r > 0)
    {
        tx = r;

        for (int i = 1; i <= r; i++)
            edges[i].clear();

        for (int i = 1; i <= n; i++)
        {
            cin >> x >> y;
            edges[x].push_back(y);
        }
        
        cout << hungarian();
        vector<int> rs, cs;
        for (int i = 1; i <= r; i++)
            if (cx[i] != -1)
            {
                if (edges[i].size() > edges[cx[i]].size())
                    rs.push_back(i);
                else
                    cs.push_back(cx[i]);
            }

        sort(rs.begin(), rs.end());
        sort(cs.begin(), cs.end());

        for (auto u : rs) cout << " r" << u;
        for (auto v : cs) cout << " c" << v;

        cout << '\n';
    }

    return 0;
}
