// All Roads Lead Where?
// UVa ID: 10009
// Verdict: Accepted
// Submission Date: 2018-02-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, m, n, edges[32][32], parent[32];
    string city1, city2;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        memset(edges, 0, sizeof(edges));

        cin >> m >> n;
        for (int i = 0; i < m; i++)
        {
            cin >> city1 >> city2;
            edges[city1.front() - 'A'][city2.front() - 'A'] = 1;
            edges[city2.front() - 'A'][city1.front() - 'A'] = 1;
        }

        if (c > 1) cout << '\n';

        for (int i = 0; i < n; i++)
        {
            cin >> city1 >> city2;

            int s = city1.front() - 'A';
            int t = city2.front() - 'A';

            memset(parent, -1, sizeof(parent));
    
            queue<int> q;
            q.push(s);
            parent[s] = s;

            while (!q.empty())
            {
                int u = q.front(); q.pop();
                for (int v = 0; v < 26; v++)
                    if (edges[u][v] && parent[v] < 0)
                    {
                        q.push(v);
                        parent[v] = u;
                    }
            }
            
            vector<char> path;
            while (parent[t] != t)
            {
                path.push_back(char('A' + t));
                t = parent[t];
            }
            path.push_back(char('A' + s));
            reverse(path.begin(), path.end());
            for (auto p : path) cout << p;
            cout << '\n';
        }
    }

    return 0;
}
