// Inspector's Dilemma
// UVa ID: 12118
// Verdict: Accepted
// Submission Date: 2017-08-23
// UVa Run Time: 0.030s
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

int edges[1010][1010], tops[1010];
int V, E, T, visited[1010], appeared[1010];

int dfs(int u)
{
    visited[u] = 1;
    int oddDegreeVertices = (tops[u] & 1 ? 1 : 0);
    for (int i = 0; i < tops[u]; i++)
    {
        int v = edges[u][i];
        if (!visited[v])
            oddDegreeVertices += dfs(v);
    }
    return oddDegreeVertices;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;
    while (cin >> V >> E >> T)
    {
        if (V == 0) break;

        memset(tops, 0, sizeof(tops));
        memset(visited, 0, sizeof(visited));
        memset(appeared, 0, sizeof(appeared));
        
        int a, b;
        for (int i = 1; i <= E; i++)
        {
            cin >> a >> b;
            edges[a][tops[a]++] = b;
            edges[b][tops[b]++] = a;
            appeared[a] = appeared[b] = 1;
        }
        
        int additional = 0, components = 0;
        for (int i = 1; i <= V; i++)
            if (appeared[i] && !visited[i])
            {
                components++;
                int oddDegreeVertices = dfs(i);
                additional += max(oddDegreeVertices - 2, 0) / 2;
            }

        cout << "Case " << ++cases << ": ";
        cout << T * (max(components - 1, 0) + E + additional) << '\n';
    }

    return 0;
}
