// Longest Paths
// UVa ID: 10000
// Verdict: Accepted
// Submission Date: 2018-02-11
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

list<int> edges[MAXV];
int n, s, dist[MAXV], visited[MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int p, q, cases = 0;
    while (cin >> n, n > 0)
    {
        for (int i = 1; i <= n; i++)
            edges[i].clear();
        cin >> s;
        while (cin >> p >> q, q > 0)
            edges[p].push_back(q);

        memset(visited, 0, sizeof(visited));
        memset(dist, 0, sizeof(dist));

        queue<int> q;
        q.push(s);
        dist[s] = 0;

        while (!q.empty())
        {
            int u = q.front(); q.pop();
            for (auto v : edges[u])
            {
                if (dist[v] < dist[u] + 1)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        
        int maxDist = 0, idx = 0;
        for (int i = 1; i <= n; i++)
            if (dist[i] > maxDist)
            {
                maxDist = dist[i];
                idx = i;
            }
        cout << "Case " << ++cases << ": The longest path from ";
        cout << s << " has length " << maxDist << ", finishing at ";
        cout << idx << ".\n\n";
    }

    return 0;
}
