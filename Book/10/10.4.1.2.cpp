#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, INF = 0x3f3f3f3f;

struct edge
{
    int v, weight;
    edge (int v = 0, int weight = 0): v(v), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];

int n;
int dist[MAXV], parent[MAXV];

void mooreDijkstra(int u)
{
    for (int i = 0; i < n; i++) dist[i] = INF, parent[i] = -1;
    dist[u] = 0;
    
    priority_queue<edge> q;
    q.push(edge(u, dist[u]));

    while (!q.empty())
    {
        edge e1 = q.top(); q.pop();
        if (dist[e1.v] < e1.weight) continue;
        for (auto e2 : edges[e1.v])
            if (dist[e2.v] > dist[e1.v] + e2.weight)
            {
                dist[e2.v] = dist[e1.v] + e2.weight;
                parent[e2.v] = e1.v;
                q.push(edge(e2.v, dist[e2.v]));
            }
    }
}

int main(int argc, char *argv[])
{
    mooreDijkstra(0);

    return 0;
}
