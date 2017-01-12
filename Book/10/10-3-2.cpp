#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

struct edge
{
    int from, to, weight;
    
    bool operator<(const edge& x) const
    {
        return weight < x.weight;
    }
};

vector<edge> edges;
vector<int> parent, ranks;

void make_set()
{
    parent.resize(edges.size()); ranks.resize(edges.size());
    
    for (int i = 0; i < edges.size(); i++)
    {
        parent[i] = i; ranks[i] = 0;
    }
}

int find_set(int x)
{
    return (parent[x] == x ? x : parent[x] = find_set(parent[x]));
}

void union_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);
    
    if (x != y)
    {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else
        {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
    }
}

int kruskal()
{
    int min_weight_sum = 0;
    
    make_set();
    sort(edges.begin(), edges.end());
    
    for (int i = 0; i < edges.size(); i++)
    {
        int x = find_set(edges[i].from), y = find_set(edges[i].to);
        
        if (x != y)
        {
            union_set(x, y);
            min_weight_sum += edges[i].weight;
        }
    }
    
    return min_weight_sum;
}

int main(int argc, char *argv[])
{
    cout << kruskal() << endl;
 
    return 0;   
}
