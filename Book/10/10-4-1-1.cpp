#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int MAX_DIST = 10000000;

struct edge
{
    int idx, weight;
};

vector<vector<edge>> edges;
vector<int> parent, dist, visited;

void mooreDijkstra(int u)
{
    parent.clear(), visited.clear(), dist.clear();
    for (int i = 0; i < edges.size(); i++)
        parent.push_back(-1), visited.push_back(0), dist.push_back(MAX_DIST);

    dist[u] = 0;
    while (!visited[u])
    {
        visited[u] = 1;
        for (edge v : edges[u])
            if (!visited[v.idx] && dist[v.idx] > dist[u] + v.weight)
                dist[v.idx] = dist[u] + v.weight, parent[v.idx] = u;

        int minDist = MAX_DIST;
        for (int i = 0; i < edges.size(); i++)
            if (!visited[i] && minDist > dist[i])
                minDist = dist[i], u = i;
    }
}

int main(int argc, char *argv[])
{
    mooreDijkstra(0);
    
    return 0;
}
