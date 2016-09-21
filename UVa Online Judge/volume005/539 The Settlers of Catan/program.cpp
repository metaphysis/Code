// The Settlers of Catan
// UVa ID: 593
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int MAX_V = 30;

int n, m, maxLength = 0, visited[MAX_V][MAX_V], connected[MAX_V][MAX_V];

void dfs(int u, int length)
{
    maxLength = max(maxLength, length);

    for (int v = 0; v < n; v++)
        if (connected[u][v] && !visited[u][v] && !visited[v][u])
        {
            visited[u][v] = visited[v][u] = 1;
            dfs(v, length + 1);
            visited[u][v] = visited[v][u] = 0;
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int from, to;

    while (cin >> n >> m, n > 0)
    {
        memset(connected, 0, sizeof(connected));
        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to;
            connected[from][to] = connected[to][from] = 1;
        }

        maxLength = 0;
        for (int i = 0; i < n; i++)
        {
            memset(visited, 0, sizeof(visited));
            dfs(i, 0);
        }

        cout << maxLength << '\n';
    }
    
	return 0;
}
