// Intervals
// UVa ID: 1723
// Verdict: TLE
// Submission Date: 2017-05-10
// UVa Run Time: 3.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000, MAXN = 50002;

struct edge
{
    int u, v, w;
};

edge edges[MAXN];
int n, dist[MAXN], mn, mx;

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
        
        for (int i = mn; i <= mx; i++)
        {
            int t = dist[i - 1] + 1;
            if (dist[i] > t)
            {
                dist[i] = t;
                updated = true;
            }
        }
        
        for (int i = mx; i >= mn; i--)
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

    cin >> n;

    mx = 0, mn = INF;

    int u, v, w;
    for (int i = 0; i < n; i++)
    {
        cin >> u >> v >> w;
        assert(u > 0);
        edges[i].u = v, edges[i].v = u - 1, edges[i].w = -w;
        mn = min(mn, u), mx = max(mx, v);
    }

    bellmanFord();
 
    cout << (dist[mx] - dist[mn - 1]) << '\n';

    return 0;
}
