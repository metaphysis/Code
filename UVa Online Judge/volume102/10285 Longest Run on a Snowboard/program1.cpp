// Longest Run on a Snowboard
// UVa ID: 10285
// Verdict: Accepted
// Submission Date: 2018-02-14
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 10010;

struct edge
{
    int v, w;
    edge (int v = 0, int w = 0): v(v), w(w) {}
};

list<edge> edges[MAXV];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    string name;
    int R, C, height[110][110], visited[MAXV], dist[MAXV];
    int offset[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> name >> R >> C;

        edges[0].clear();
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
            {
                cin >> height[i][j];
                edges[(i - 1) * C + j].clear();
                edges[0].push_back(edge((i - 1) * C + j, -1));
            }
        for (int i = 1; i <= R; i++)
            for (int j = 1; j <= C; j++)
                for (int k = 0; k < 4; k++)
                {
                    int nexti = i + offset[k][0], nextj = j + offset[k][1];
                    if (nexti < 1 || nexti > R || nextj < 1 || nextj > C) continue;
                    if (height[nexti][nextj] <= height[i][j]) continue;
                    edges[(i - 1) * C + j].push_back(edge((nexti - 1) * C + nextj, -1));
                }

        int longest = 0;

        memset(dist, 0, sizeof(dist));
        queue<edge> q;
        q.push(edge(0, 0));
        dist[0] = 0;

        while (!q.empty())
        {
            edge e1 = q.front(); q.pop();
            visited[e1.v] = 0;
            for (auto e2 : edges[e1.v])
            {
                if (dist[e2.v] > dist[e1.v] + e2.w)
                {
                    dist[e2.v] = dist[e1.v] + e2.w;
                    longest = min(longest, dist[e2.v]);
                    if (!visited[e2.v])
                    {
                        visited[e2.v] = 1;
                        q.push(edge(e2.v, dist[e2.v]));
                    }
                }
            }
        }

        cout << name << ": " << -longest << '\n';
    }

    return 0;
}
