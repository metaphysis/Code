// Wormholes
// UVa ID: 558
// Verdict: Accepted
// Submission Date: 2017-10-24
// UVa Run Time: 0.030s
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

const int MAXV = 1100, MAXE = 100010, INF = 0x3fffffff;

struct edge { int from, to, weight, next; } edges[MAXE];

int n, m, head[MAXV];
int dist[MAXV], parent[MAXV], visited[MAXV], counter[MAXV];

bool spfa(int source)
{
    for (int i = 0; i < n; i++)
        dist[i] = INF, parent[i] = -1, visited[i] = 0, counter[i] = 0;
    dist[source] = 0, visited[source]++;
    
    queue<int> q; q.push(source);
    while (!q.empty())
    {
        int u = q.front(); q.pop();
 
        if (counter[u] > n) return true;
        
        for (int i = head[u]; ~i; i = edges[i].next)
        {
            int v = edges[i].to, w = edges[i].weight;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w, parent[v] = u;
                if (!visited[v]) q.push(v), visited[v]++, counter[v]++;
            }
        }
        
        visited[u]--;
    }

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, x, y, t;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        
        memset(head, -1, sizeof(head));
        for (int i = 0; i < m; i++)
        {
            cin >> x >> y >> t;
            edges[i] = edge{x, y, t, head[x]};
            head[x] = i;
        }

        cout << (spfa(0) ? "possible\n" : "not possible\n");
    }
    
	return 0;
}
