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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 1010, MAXE = 1000010;

struct edge {
    int from, to, weight, next;
};

edge edges[MAXE];
int first[MAXV];

int main(int argc, char *argv[])
{
    int number_of_vertices, number_of_edges;
    int u, v, w, idx = 0;
    
    memset(first, -1, sizeof(first));
    
    cin >> number_of_vertices >> number_of_edges;
    for (int i = 0; i < number_of_edges; i++)
    {
        cin >> u >> v >> w;
        
        edges[idx] = (edge){u, v, w, first[u]};
        first[u] = idx++;
        
        edges[idx] = (edge){v, u, w, first[v]};
        first[v] = idx++;
    }

    for (int i = 1; i <= number_of_vertices; i++)
        for (int j = first[i]; j != -1; j = edges[j].next)
            cout << edges[j].from << ' ' << edges[j].to << ' ' << edges[j].weight << '\n';

    return 0;
}
