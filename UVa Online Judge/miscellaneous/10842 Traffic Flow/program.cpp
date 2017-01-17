// Traffic Flow
// UVa ID: 10842
// Verdict: Accepted
// Submission Date: 2017-01-17
// UVa Run Time: 0.060s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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

const int MAXV = 110, MAXE = 10010;

struct edge {
    int from, to, weight, enabled;

    bool operator<(const edge& x) const {
        return weight > x.weight;
    }
};

edge edges[MAXE];
int parent[MAXV], ranks[MAXV], number_of_vertices, number_of_edges;

void make_set()
{
    for (int i = 0; i <= number_of_vertices; i++) parent[i] = i, ranks[i] = 0;
}

int find_set(int x)
{
    return (parent[x] == x ? x : parent[x] = find_set(parent[x]));
}

bool union_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

int kruskal()
{
    int min_weight = 0;

    make_set();
    sort(edges, edges + number_of_edges);

    for (int i = 0; i < number_of_edges; i++)
        if (union_set(edges[i].from, edges[i].to))
            min_weight = edges[i].weight;
    
    return min_weight;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, from, to, weight;
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cout << "Case #" << c << ": ";
        
        cin >> number_of_vertices >> number_of_edges;
        for (int i = 0; i < number_of_edges; i++)
        {
            cin >> from >> to >> weight;
            edges[i] = (edge){from, to, weight, 1};
        }
        
        cout << kruskal() << '\n';
    }
    
    return 0;
}
