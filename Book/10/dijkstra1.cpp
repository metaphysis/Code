#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

const long long int MAX_DISTANCE = numeric_limits<int>::max();
const int N = 1000;

struct edge
{
    int to;
    long long int weight;
    
    bool operator<(edge another) const
    {
        return weight > another.weight;
    }
};

vector<vector<edge>> edges(N + 1);
vector<long long int> distances(N + 1);
vector<int> parent(N + 1);

void dijkstra(int start)
{
    fill(parent.begin(), parent.end(), 0);
    fill(distances.begin(), distances.end(), MAX_DISTANCE);

    distances[start] = 0;
    
    priority_queue<edge> unvisited;
    unvisited.push((edge){start, distances[start]});

    while (!unvisited.empty())
    {
        edge v = unvisited.top();
        unvisited.pop();
        
        for (auto e : edges[v.to])
            if (distances[v.to] + e.weight < distances[e.to])
            {
                distances[e.to] = distances[v.to] + e.weight;
                parent[e.to] = v.to;
                unvisited.push((edge){e.to, distances[e.to]});
            }
    }
}

int main(int argc, char *argv[])
{
    dijkstra(0);
    
    return 0;
}
