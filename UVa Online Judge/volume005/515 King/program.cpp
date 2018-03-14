// King
// UVa ID: 515
// Verdict: Accepted
// Submission Date: 2017-04-28
// UVa Run Time: 0.040s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net
//
// System of difference constraints, Bellman-Ford algorithm.
//

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int u, v, weight;
};

edge edges[1024];
int nedges, dist[1024], n, m, si, ni, ki;
string oi;

void addEdge(int u, int v, int weight)
{
    edges[nedges].u = u, edges[nedges].v = v, edges[nedges].weight = weight;
    nedges++;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n, n > 0)
    {
        cin >> m;

        nedges = 0;
        for (int i = 1; i <= m; i++)
        {
            cin >> si >> ni >> oi >> ki;

            if (oi.front() == 'g')
                addEdge(si + ni + 1, si, -ki - 1);
            else
                addEdge(si, si + ni + 1, ki - 1);
        }

        n += 2;
        for (int i = 1; i < n; i++)
            addEdge(0, i, 0);

        dist[0] = 0;
        for (int i = 1; i < n; i++)
            dist[i] = (1 << 30);

        int iterations = 0, updated = 0;
        do
        {
            updated = 0;
            for (int i = 0; i < nedges; i++)
            {
                int weight = dist[edges[i].u] + edges[i].weight;
                if (dist[edges[i].v] > weight)
                    updated++, dist[edges[i].v] = weight;
            }
        }
        while (updated && iterations++ < n);

        cout << (updated ? "successful conspiracy\n" : "lamentable kingdom\n");
    }

    return 0;
}
