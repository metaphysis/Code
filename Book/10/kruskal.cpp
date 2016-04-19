#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct edge
{
    int start, end, weight;
};

vector < edge > edges;
vector < int > parent, ranks;

bool cmp(edge x, edge y)
{
    return x.weight < y.weight;
}

void makeSet()
{
    parent.resize(edges.size());
    ranks.resize(edges.size());
    
    for (int i = 0; i < edges.size(); i++)
    {
        parent[i] = i;
        ranks[i] = 0;
    }
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

void unionSet(int x, int y)
{
    x = findSet(x);
    y = findSet(y);
    
    if (x != y)
    {
        if (ranks[x] > ranks[y])
            parent[y] = x;
        else
        {
            parent[x] = y;
            if (ranks[x] == ranks[y])
                ranks[y]++;
        }
    }
}

void kruskal()
{
    makeSet();
    sort(edges.begin(), edges.end(), cmp);
    
    for (int i = 0; i < edges.size(); i++)
        unionSet(edges[i].start, edges[i].end);
}

int main(int argc, char *argv[])
{
    kruskal();
}
