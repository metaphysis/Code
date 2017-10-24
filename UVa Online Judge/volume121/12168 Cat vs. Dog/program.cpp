// Cat vs. Dog
// UVa ID: 12168
// Verdict: Accepted
// Submission Date: 2017-10-24
// UVa Run Time: 0.020s
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

const int MAXV = 510;

list<int> edges[MAXV];
int visited[MAXV], cx[MAXV], cy[MAXV], tx;

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

    int cases = 0, c, d, v;
    int vote[MAXV][2];
        
    cin >> cases;
    for (int k = 1; k <= cases; k++)
    {
        cin >> c >> d >> v;
        
        char pet;
        int number;
        for (int i = 1; i <= v; i++)
        {
            cin >> pet >> number;
            if (pet == 'D') number += c;
            vote[i][0] = number;
            
            cin >> pet >> number;
            if (pet == 'D') number += c;
            vote[i][1] = number;
        }
        
        tx = v;
        for (int i = 1; i <= tx; i++)
            edges[i].clear();
        
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
            {
                if (i == j) continue;
                if (vote[i][0] == vote[j][1] || vote[i][1] == vote[j][0])
                    edges[i].push_back(j);
            }

        cout << (v - hungarian() / 2) << '\n';
    }

    return 0;
}
