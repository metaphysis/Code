#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1010, INF = 0x3f3f3f3f;

struct edge
{
    int v, weight;
    edge (int v = 0, int weight = 0): v(v), weight(weight) {}
};

list<edge> edges[MAXV];
int n;
int dist[MAXV], parent[MAXV], visited[MAXV];

void mooreDijkstra(int s)
{
    for (int i = 0; i < n; i++)
        dist[i] = INF, parent[i] = -1, visited[i] = 0;
    dist[s] = 0;
    int u = s;
    while (!visited[u])
    {
        visited[u] = 1;
        for (auto e : edges[u])
            if (!visited[e.v] && dist[e.v] > dist[u] + e.weight)
                dist[e.v] = dist[u] + e.weight, parent[e.v] = u;

        int least = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && least > dist[i])
                least = dist[i], u = i;
    }
}

int main(int argc, char *argv[])
{
    mooreDijkstra(0);

    return 0;
}
