// Wormholes
// UVa ID: 558
// Verdict: Accepted
// Submission Date: 2017-05-10
// UVa Run Time: 0.020s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1100, INF = 0x3fffffff;

struct edge
{
    int from, to, weight;
    edge *next;
};

edge *edges[MAXV];
int n, dist[MAXV], parent[MAXV], visited[MAXV], counter[MAXV];

// source为起始顶点的序号。
bool spfa(int source)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF, parent[i] = -1;
        visited[i] = 0, counter[i] = 0;
    }

    dist[source] = 0, visited[source]++;
    
    queue<int> q; q.push(source);
    
    while (!q.empty())
    {
        int u = q.front(); q.pop();
 
        if (counter[u] > n) return true;
        
        edge *e = edges[u];
        while (e != NULL)
        {
            int v = e->to;
            if (dist[v] > dist[u] + e->weight)
            {
                dist[v] = dist[u] + e->weight; parent[v] = u;
                if (!visited[v])
                {
                    q.push(v); visited[v]++; counter[v]++;
                }
            }
            e = e->next;
        }
        
        visited[u]--;
    }

    return false;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, m, x, y, t;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            cin >> x >> y >> t;
            
            edge *e = new edge;
            e->to = y, e->weight = t, e->next = NULL;

            if (edges[x] == NULL)
                edges[x] = e;
            else
                e->next = edges[x], edges[x] = e;
        }

        cout << (spfa(0) ? "possible\n" : "not possible\n");
        
        for (int i = 0; i < n; i++)
        {
            edge *e = edges[i];
            while (e != NULL)
            {
                edges[i] = e->next; delete e; e = edges[i];
            }
        }
    }
    
	return 0;
}
