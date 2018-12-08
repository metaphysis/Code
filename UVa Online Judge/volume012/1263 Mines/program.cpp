// Mines
// UVa ID: 1263
// Verdict: Accepted
// Submission Date: 2018-12-08
// UVa Run Time: 0.430s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cases, N, xi[2048], yi[2048], di[2048], visited[2048];
stack<int> s;
list<int> edges[2048];

void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
    s.push(u);
}

void rdfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> xi[i] >> yi[i] >> di[i];
        for (int i = 0; i < N; i++) edges[i].clear();
    
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
            {
                if (2 * xi[j] >= 2 * xi[i] - di[i] && 2 * xi[j] <= 2 * xi[i] + di[i] &&
                    2 * yi[j] >= 2 * yi[i] - di[i] && 2 * yi[j] <= 2 * yi[i] + di[i])
                    edges[i].push_back(j);
                if (2 * xi[i] >= 2 * xi[j] - di[j] && 2 * xi[i] <= 2 * xi[j] + di[j] &&
                    2 * yi[i] >= 2 * yi[j] - di[j] && 2 * yi[i] <= 2 * yi[j] + di[j])
                    edges[j].push_back(i);
            }

        memset(visited, 0, sizeof(visited));
        for (int i = 0; i < N; i++)
            if (!visited[i])
                dfs(i);

        int cnt = 0;
        memset(visited, 0, sizeof(visited));
        while (!s.empty())
        {
            int u = s.top();
            if (!visited[u])
            {
                rdfs(u);
                cnt++;
            }
            s.pop();
        }
        cout << cnt << '\n';
    }

    return 0;
}
