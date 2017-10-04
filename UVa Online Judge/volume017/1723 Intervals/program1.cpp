// Intervals
// UVa ID: 1723
// Verdict: TLE
// Submission Date: 2017-05-10
// UVa Run Time: 3.000s
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

const int INF = 1000000, MAXN = 50002;

struct edge
{
    int v, w;
};

vector<edge> edges[MAXN];
int n, dist[MAXN], visited[MAXN], counter[MAXN], mn, mx;

bool spfa()
{
    for (int i = 0; i <= mx; i++)
    {
        visited[i] = 0;
        counter[i] = 0;
        dist[i] = -INF;
    }
    
    queue<int> unvisited;

    // choose mn - 1 as source vertex.
    unvisited.push(mn - 1);
    dist[mn - 1] = 0;
    visited[mn - 1] = 1;
    
    while (!unvisited.empty())
    {
        int u = unvisited.front();
        unvisited.pop();
        
        if (counter[u] > mx) return true;
        
        for (auto e : edges[u])
        {
            int t = dist[u] + e.w;
            if (dist[e.v] < t)
            {
                dist[e.v] = t;
                if (!visited[e.v])
                {
                    unvisited.push(e.v);
                    counter[e.v]++;
                    visited[e.v] = 1;
                }
            }
        }
        
        visited[u] = 0;
    }
    
    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> n;

    mx = 0, mn = INF;
    for (int i = 0; i < MAXN; i++)
        edges[i].clear();

    int u, v, w;
    for (int i = 0; i < n; i++)
    {
        cin >> u >> v >> w;
        assert(u > 0);
        edges[u - 1].push_back(edge{v, w});
        mn = min(mn, u), mx = max(mx, v);
    }

    for (int i = mn; i <= mx; i++)
    {
        edges[i].push_back(edge{i - 1, -1});
        edges[i - 1].push_back(edge{i, 0});
    }

    cout << (spfa() ? -1 : dist[mx]) << '\n';
    
    return 0;
}
