// Intervals
// UVa ID: 1723
// Verdict: Accepted
// Submission Date: 2018-10-27
// UVa Run Time: 0.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f, MAXN = 50002;

struct edge
{
    int u, v, w;
} edges[MAXN];

int n, dist[MAXN], mi, mx;

void bellmanFord()
{
    memset(dist, 0, sizeof(dist));

    bool updated = true;
    
    while (updated)
    {
        updated = false;
        
        for (int i = 0; i < n; i++)
        {
            int t = dist[edges[i].u] + edges[i].w;
            if (dist[edges[i].v] > t)
            {
                dist[edges[i].v] = t;
                updated = true;
            }
        }
        
        for (int i = mi; i <= mx; i++)
        {
            int t = dist[i - 1] + 1;
            if (dist[i] > t)
            {
                dist[i] = t;
                updated = true;
            }
        }
        
        for (int i = mx; i >= mi; i--)
            if (dist[i - 1] > dist[i])
            {
                dist[i - 1] = dist[i];
                updated = true;
            }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int cs = 0; cs < cases; cs++)
    {
        cin >> n;
        mx = 0, mi = INF;
        int u, v, w;
        for (int i = 0; i < n; i++)
        {
            cin >> u >> v >> w;
            u++, v++;
            assert(u > 0);
            edges[i].u = v, edges[i].v = u - 1, edges[i].w = -w;
            mi = min(mi, u), mx = max(mx, v);
        }
        bellmanFord();
        if (cs) cout << '\n';
        cout << (dist[mx] - dist[mi - 1]) << '\n';
    }

    return 0;
}
