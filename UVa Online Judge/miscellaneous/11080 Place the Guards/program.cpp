// Place the Guards
// UVa ID: 11080
// Verdict: Accepted
// Submission Date: 2017-09-27
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

vector<int> edges[210], visited(210, 0);

int colors[3];

bool dfs(int u, int color)
{
    visited[u] = color, colors[color]++;
    for (auto v : edges[u])
        if ((!visited[v] && !dfs(v, 3 - color)) || visited[v] == color)
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int T, v, e, f, t;
    
    cin >> T;
    for (int c = 1; c <= T; c++)
    {
        cin >> v >> e;
        for (int i = 0; i < v; i++) edges[i].clear();
        for (int i = 0; i < e; i++)
        {
            cin >> f >> t;
            edges[f].push_back(t);
            edges[t].push_back(f);
        }
        
        int guards = 0;

        fill(visited.begin(), visited.end(), 0);

        for (int u = 0; u < v; u++)
            if (!visited[u])
            {
                colors[1] = colors[2] = 0;

                if (dfs(u, 1))
                {
                    if (colors[1] == 0 || colors[2] == 0)
                        guards += max(colors[1], colors[2]);
                    else
                        guards += min(colors[1], colors[2]);
                }
                else
                {
                    guards = -1;
                    break;
                }
            }

        cout << guards << '\n';
    }
    
	return 0;
}
