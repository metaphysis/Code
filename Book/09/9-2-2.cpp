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
    int from, to, weight;
    
    bool operator<(const edge& x) const
    {
        if (from == x.from) {
            if (to == x.to) return weight < x.weight;
            else return to < x.to;
        }
        else
            return from < x.from;
    }
};

edge edges[MAXE];
int first[MAXV];

int main(int argc, char *argv[])
{
    int numberOfVertices, numberOfEdges;

    cin >> numberOfVertices >> numberOfEdges;
    for (int i = 0; i < numberOfEdges; i++)
        cin >> edges[i].from >> edges[i].to >> edges[i].weight;

    sort(edges, edges + numberOfEdges);

    memset(first, -1, sizeof(first));

    first[edges[0].from] = 0;
    for (int i = 1; i < numberOfEdges; i++)
        if (edges[i - 1].from != edges[i].from)
            first[edges[i].from] = i;

    for (int i = 1; i <= numberOfVertices; i++)
        for (int j = first[i]; edges[j].from == i; j++)
            cout << edges[j].from << ' ' << edges[j].to << ' ' << edges[j].weight << '\n';

    return 0;
}
