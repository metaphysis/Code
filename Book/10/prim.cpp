#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct edge
{
    int index, weight;
};

vector< vector < edge > > edges;
vector< int > parent, distances;
vector< bool > intree;

void prim(int start)
{
    parent.clear();
    intree.clear();
    distances.clear();

    for (int i = 0; i < edges.size(); i++)
    {
        parent.push_back(-1);
        intree.push_back(false);
        distances.push_back(numeric_limits< int >::max());
    }

    distances[start] = 0;
    while (intree[start] == false)
    {
        intree[start] = true;
        for (int i = 0; i < edges[start].size(); i++)
        {
            edge current = edges[start][i];
            if (intree[current.index] == false &&
                current.weight < distances[current.index])
            {
                    distances[current.index] = current.weight;
                    parent[current.index] = start;
            }
        }

        start = 0;
        int minDistance = numeric_limits< int >::max();
        for (int i = 0; i < edges.size(); i++)
            if (intree[i] == false && minDistance > distances[i])
            {
                minDistance = distances[i];
                start = i;
            }
    }
}

int main(int argc, char *argv[])
{
    prim(0);
    
    return 0;
}
