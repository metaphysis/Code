#include <iostream>
#include <limits>
#include <vector>

using namespace std;

const int MAX_INT = numeric_limits<int>::max();

struct edge
{
    int idx, weight;
};

vector<vector<edge>> edges;
vector<int> parent, dist, visited;

void moore_dijkstra(int u)
{
    parent.clear();
    visited.clear();
    dist.clear();

    for (int i = 0; i < edges.size(); i++)
    {
        parent.push_back(-1);
        visited.push_back(0);
        dist.push_back(MAX_INT);
    }

    dist[u] = 0;
    while (!visited[u])
    {
        visited[u] = 1;
        for (int i = 0; i < edges[u].size(); i++)
        {
            edge v = edges[u][i];
            if (!visited[v.idx] && dist[v.idx] > dist[u] + v.weight)
            {
                dist[v.idx] = dist[u] + v.weight;
                parent[v.idx] = u;
            }
        }

        int min_dist = MAX_INT;
        for (int i = 0; i < edges.size(); i++)
            if (!visited[i] && min_dist > dist[i])
            {
                min_dist = dist[i];
                u = i;
            }
    }
}

int main(int argc, char *argv[])
{
    moore_dijkstra(0);
    
    return 0;
}
