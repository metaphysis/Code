// Factors and Multiples
// UVa ID: 11159
// Verdict: Accepted
// Submission Date: 2017-09-26
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

const int MAXV = 110;

int g[MAXV][MAXV], visited[MAXV], cx[MAXV], cy[MAXV];
int tx, ty;

int dfs(int u)
{
    for (int v = 0; v < ty; v++)
        if (g[u][v] && !visited[v])
        {
            visited[v] = 1;
            if (cy[v] == -1 || dfs(cy[v]))
            {
                cx[u] = v;
                cy[v] = u;
                return 1;
            }
        }

    return 0;
}

// 匈牙利算法求最大匹配数。
int hungarian()
{
    memset(cx, -1, sizeof(cx)); memset(cy, -1, sizeof(cy));
    
    int matches = 0;
    for (int i = 0; i < tx; i++)
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

    int n[110], m[110];
    
    int cases;
    cin >> cases;
    
    for (int c = 1; c <= cases; c++)
    {
        cin >> tx;
        for (int i = 0; i < tx; i++) cin >> n[i];
        cin >> ty;
        for (int j = 0; j < ty; j++) cin >> m[j];
        
        memset(g, 0, sizeof(g));
        for (int i = 0; i < tx; i++)
            for (int j = 0; j < ty; j++)
                if (m[j] == 0 || (n[i] != 0 && (m[j] % n[i]) == 0))
                    g[i][j] = 1;
        
        cout << "Case " << c << ": " << hungarian() << '\n';
    }
    
    return 0;
}
