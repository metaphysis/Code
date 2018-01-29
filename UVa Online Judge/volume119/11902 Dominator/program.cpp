// Dominator
// UVa ID: 11902
// Verdict: Accepted
// Submission Date: 2016-09-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

const int MAXV = 110;

int cases, n, edges[MAXV][MAXV], dominate[MAXV][MAXV];
int visited[MAXV], reachable[MAXV];

int dfs1(int u)
{
    reachable[u] = 1;
    for (int v = 0; v < n; v++)
        if (!reachable[v] && edges[u][v])
            dfs1(v);
}

int dfs2(int u, int ignore)
{
    visited[u] = 1;
    for (int v = 0; v < n; v++)
        if (v != ignore && !visited[v] && edges[u][v])
            dfs2(v, ignore);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> edges[i][j];

        memset(dominate, 0, sizeof(dominate));
        memset(reachable, 0, sizeof(reachable));

        dfs1(0);

        for (int i = 0; i < n; i++)
            dominate[0][i] = reachable[i];

        for (int i = 1; i < n; i++)
        {
            memset(visited, 0, sizeof(visited));
            dfs2(0, i);
            for (int j = 0; j < n; j++)
            {
                if (j == i)
                    dominate[i][j] = reachable[j];
                else if (reachable[j] && !visited[j])
                    dominate[i][j] = 1;
            }
        }

        int t = 2 * n - 1;
        cout << "Case " << c << ":\n";
        for (int i = 0; i < n; i++)
        {
            cout << '+';
            for (int j = 1; j <= t; j++)
                cout << '-';
            cout << "+\n";
            for (int j = 0; j < n; j++)
                cout << '|' << (dominate[i][j] ? 'Y' : 'N');
            cout << "|\n";
        }
        cout << '+';
        for (int j = 1; j <= t; j++)
            cout << '-';
        cout << "+\n";
    }
    
	return 0;
}
