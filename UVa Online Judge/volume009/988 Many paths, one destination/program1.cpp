// Many paths, one destination
// UVa ID: 988
// Verdict: Accepted
// Submission Date: 2017-03-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> edges;
vector<int> visited, ways;

int dfs(int i)
{
    visited[i] = 1;

    if (edges[i].size() == 0)
        ways[i] = 1;
    else
    {
        for (int j = 0; j < edges[i].size(); j++)
        {
            if (!visited[edges[i][j]])
                dfs(edges[i][j]);
            ways[i] += ways[edges[i][j]];
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n, m, choice, cases = 0;
    while (cin >> n)
    {
        edges.clear();
        edges.assign(n, vector<int>());
        
        for (int i = 0; i < n; i++)
        {
            cin >> m;
            for (int j = 0; j < m; j++)
            {
                cin >> choice;
                edges[i].push_back(choice);
            }
        }

        visited.clear(); ways.clear();
        visited.assign(n, 0); ways.assign(n, 0);

        dfs(0);
        
        if (cases++ > 0) cout << '\n';
        cout << ways[0] << '\n';
    }
    
    return 0;
}
