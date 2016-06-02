#include <iostream>
#include <vector>

using namespace std;

const int MAX_INT = 100000;

struct edge
{
    int index, weight;
};

vector< vector < edge > > edges;
vector< int > parent, distances;
vector< bool > visited;

void dijkstra(int start)
{
    parent.clear();
    visited.clear();
    distances.clear();

    for (int i = 0; i < edges.size(); i++)
    {
        parent.push_back(-1);
        visited.push_back(false);
        distances.push_back(MAX_INT);
    }

    distances[start] = 0;
    while (visited[start] == false)
    {
        visited[start] = true;
        for (int i = 0; i < edges[start].size(); i++)
        {
            edge current = edges[start][i];
            if (visited[current.index] == false &&
                distances[start] + current.weight < distances[current.index])
            {
                distances[current.index] = distances[start] + current.weight;
                parent[current.index] = start;
            }
        }

        int minDistance = MAX_INT;
        for (int i = 0; i < edges.size(); i++)
            if (visited[i] == false && minDistance > distances[i])
            {
                minDistance = distances[i];
                start = i;
            }
    }
}

int main(int argc, char *argv[])
{
    dijkstra(0);
    
    return 0;
}
