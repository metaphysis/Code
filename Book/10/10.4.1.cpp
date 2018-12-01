#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, INF = 0x3fffffff;

struct edge
{
    int to, weight;
    edge (int to = 0, int weight = 0): to(to), weight(weight) {}
    bool operator<(const edge &e) const { return weight > e.weight; }
};

list<edge> edges[MAXV];
int dist[MAXV], parent[MAXV], visited[MAXV];
int n, m;

void mooreDijkstra(int u)
{
    for (int i = 0; i < n; i++) dist[i] = INF, parent[i] = -1, visited[i] = 0;
    dist[u] = 0;

    while (!visited[u])
    {
        visited[u] = 1;
        for (auto e : edges[u])
            if (!visited[e.to] && dist[e.to] > dist[u] + e.weight)
                dist[e.to] = dist[u] + e.weight, parent[e.to] = u;

        int least = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && least > dist[i])
                least = dist[i], u = i;
    }
}

void mooreDijkstra1(int u)
{
    for (int i = 0; i < n; i++) dist[i] = INF, parent[i] = -1;
    dist[u] = 0;
    
    priority_queue<edge> q;
    q.push(edge(u, dist[u]));

    while (!q.empty())
    {
        edge ue = q.top(); q.pop();
        if (dist[ue.to] < ue.weight) continue;
        for (auto ve : edges[ue.to])
            if (dist[ve.to] > dist[ue.to] + ve.weight)
            {
                dist[ve.to] = dist[ue.to] + ve.weight;
                parent[ve.to] = ue.to;
                q.push(edge(ve.to, dist[ve.to]));
            }
    }
}

int main(int argc, char *argv[])
{
    mooreDijkstra(0);
    mooreDijkstra1(0);

    return 0;
}
