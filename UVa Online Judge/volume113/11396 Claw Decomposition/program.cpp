// Claw Decomposition
// UVa ID: 11396
// Verdict: Accepted
// Submission Date: 2017-09-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<int> edges[310], visited(310, 0);

bool dfs(int u, int color)
{
    visited[u] = color;
    for (auto v : edges[u])
        if ((!visited[v] && !dfs(v, 3 - color)) || visited[v] == color)
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int V, a, b;

    while (cin >> V, V > 0)
    {
        for (int i = 1; i <= V; i++)
            edges[i].clear();

        while (cin >> a >> b, a && b)
        {
            edges[a].push_back(b);
            edges[b].push_back(a);
        }

        bool clawed = true;

        fill(visited.begin(), visited.end(), 0);

        for (int u = 1; u <= V; u++)
            if (!visited[u] && !dfs(u, 1))
            {
                clawed = false;
                break;
            }

        cout << (clawed ? "YES" : "NO") << '\n';
    }
    
	return 0;
}
