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

const int MAXV = 1010;

struct edge
{
    int from, to, weight;

    bool operator<(const edge& x) const {
        return weight < x.weight;
    }
};

edge edges[MAXV * MAXV];
int parent[MAXV], ranks[MAXV];
int number_of_vertices, number_of_edges;

void make_set()
{
    for (int i = 0; i < number_of_vertices; i++) {
        parent[i] = i; ranks[i] = 0;
    }
}

int find_set(int x)
{
    return (parent[x] == x ? x : parent[x] = find_set(parent[x]));
}

void union_set(int x, int y)
{
    x = find_set(x), y = find_set(y);
    if (x != y) {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
    }
}

int kruskal()
{
    int min_weight_sum = 0;

    make_set();
    sort(edges, edges + number_of_edges);

    for (int i = 0; i < number_of_edges; i++) {
        int x = find_set(edges[i].from), y = find_set(edges[i].to);
        if (x != y) {
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
