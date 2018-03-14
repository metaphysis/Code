// The Mysterious X Network
// UVa ID: 1148
// Verdict: Accepted
// Submission Date: 2018-02-07
// UVa Run Time: 0.450s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100010;

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, n, nc, c1, c2, length[MAXV], visited[MAXV];
    list<int> edges[MAXV];

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        for (int i = 0; i < n; i++)
        {
            visited[i] = 0;
            edges[i].clear();
        }
        
        for (int i = 0; i < n; i++)
        {
            cin >> c1 >> nc;
            for (int j = 0; j < nc; j++)
            {
                cin >> c2;
                edges[c1].push_back(c2);
                edges[c2].push_back(c1);
            }
        }

        cin >> c1 >> c2;
        length[c1] = 0;
        queue<int> q;
        q.push(c1);
        visited[c1] = 1;
        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (auto v : edges[u])
                if (!visited[v])
                {
                    length[v] = length[u] + 1;
                    q.push(v);
                    visited[v] = 1;
                }
            if (u == c2) break;
        }
        if (c > 1) cout << '\n';
        cout << c1 << ' ' << c2 << ' ' << (length[c2] - 1) << '\n';
    }

    return 0;
}
