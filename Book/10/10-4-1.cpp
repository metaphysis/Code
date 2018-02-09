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

        int minDist = INF;
        for (int i = 0; i < n; i++)
            if (!visited[i] && minDist > dist[i])
                minDist = dist[i], u = i;
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
        edge v = q.top(); q.pop();
        for (auto e : edges[v.to])
            if (dist[e.to] > dist[v.to] + e.weight)
            {
                dist[e.to] = dist[v.to] + e.weight;
                parent[e.to] = v.to;
                q.push(edge(e.to, dist[e.to]));
            }
    }
}

int main(int argc, char *argv[])
{
    mooreDijkstra(0);
    mooreDijkstra1(0);

    return 0;
}
