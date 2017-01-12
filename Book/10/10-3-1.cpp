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
#include <vector>

using namespace std;

const int MAX_DIST = 1000000, MAXV = 1010;

struct edge
{
    int idx, weight;
    
    bool operator<(const edge& x) const
    {
        return weight > x.weight;
    }
};

vector<edge> edges[MAXV];
int parent[MAXV], dist_to_tree[MAXV], intree[MAXV];

int prim(int u)
{
    int min_weight_sum = 0;

    for (int i = 0; i < MAXV; i++)
    {
        parent[i] = -1; intree[i] = 0; dist_to_tree[i] = MAX_DIST;
    }

    dist_to_tree[u] = 0;
    while (!intree[u])
    {
        intree[u] = 1;
        min_weight_sum += dist_to_tree[u];

        for (int i = 0; i < edges[u].size(); i++)
        {
            edge v = edges[u][i];
            if (!intree[v.idx] && dist_to_tree[v.idx] > v.weight)
            {
                dist_to_tree[v.idx] = v.weight;
                parent[v.idx] = u;
            }
        }

        int min_dist_to_tree = MAX_DIST;
        for (int i = 0; i < MAXV; i++)
        {
            if (!intree[i] && min_dist_to_tree > dist_to_tree[i])
            {
                min_dist_to_tree = dist_to_tree[i];
                u = i;
            }
        }
    }

    return min_weight_sum;
}

int prim1(int u)
{
    int min_weight_sum = 0;

    for (int i = 0; i < MAXV; i++)
    {
        parent[i] = -1; intree[i] = 0; dist_to_tree[i] = MAX_DIST;
    }

    priority_queue<edge> unvisited;
    unvisited.push((edge){u, 0});

    while (!unvisited.empty())
    {
        edge v = unvisited.top(); unvisited.pop();

        if (intree[v.idx]) continue;
        intree[v.idx] = 1;
        min_weight_sum += v.weight;

        for (int i = 0; i < edges[v.idx].size(); i++)
        {
            edge e = edges[v.idx][i];
            if (!intree[e.idx] && dist_to_tree[e.idx] > e.weight)
            {
                dist_to_tree[e.idx] = e.weight;
                parent[e.idx] = v.idx;
            }
        }
    }

    return min_weight_sum;
}

int main(int argc, char *argv[])
{
    prim(0);
    prim1(0);

    return 0;
}
