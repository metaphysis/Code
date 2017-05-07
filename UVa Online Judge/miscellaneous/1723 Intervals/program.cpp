// Intervals
// UVa ID: 1723
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int INF = 1000000, MAXN = 50001;

struct edge
{
    int u, v, w;
};

edge edges[MAXN];
int n, dist[MAXN], mn, mx;

void bellmanFor()
{
    bool updated = true;
    
    while (updated)
    {
        updated = false;
        
        for (int i = 0; i < n; i++)
        {
            int t = dist[edges[i].u] + edges[i].w;
            if (dist[edges[i].v] > t)
                dist[edges[i].v] = t, updated = true;
        }
        
        for (int i = mn; i <= mx; i++)
        {
            int t = dist[i - 1] + 1;
            if (dist[i] > t)
                dist[i] = t, updated = true;
        }
        
        for (int i = mx; i >= mn; i--)
            if (dist[i - 1] > dist[i])
                dist[i - 1] = dist[i], updated = true;
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n)
    {
        memset(dist, 0, sizeof(dist));
        mx = 1, mn = INF;
        
        int u, v, w;
        for (int i = 0; i < n; i++)
        {
            cin >> u >> v >> w;
            edges[i].u = v, edges[i].v = u - 1, edges[i].w = -w;
            mn = min(mn, u), mx = max(mx, v);
        }
        
        bellmanFor();
        cout << (dist[mx] - dist[mn - 1]) << '\n';
    }
    
    return 0;
}
