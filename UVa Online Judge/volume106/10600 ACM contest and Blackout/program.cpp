// ACM contest and Blackout
// UVa ID: 10600
// Verdict: Accepted
// Submission Date: 2017-01-15
// UVa Run Time: 0.000s
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

const int MAXV = 110, MAXE = 10010, MAX_DIST = 1000000;

struct edge {
    int from, to, weight, disabled;

    bool operator<(const edge& x) const {
        return weight < x.weight;
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

void kruskal()
{
    int min_weight_sum = 0, intree[MAXV], idx = 0;

    make_set();
    sort(edges, edges + number_of_edges);

    for (int i = 0; i < number_of_edges; i++)
        if (union_set(edges[i].from, edges[i].to)) {
            min_weight_sum += edges[i].weight;
            intree[idx++] = i;
        }

    int secondary_weight_sum = MAX_DIST;
    for (int i = 0; i < idx; i++) {
        int current_weight_sum = 0;
        edges[intree[i]].disabled = 1;

        make_set();

        int added_vertices = 0;
        for (int j = 0; j < number_of_edges; j++)
            if (!edges[j].disabled && union_set(edges[j].from, edges[j].to)) {
                current_weight_sum += edges[j].weight;
                added_vertices++;
            }

        edges[intree[i]].disabled = 0;
        if (added_vertices == (number_of_vertices - 1))
            secondary_weight_sum = min(secondary_weight_sum, current_weight_sum);
    }

    cout << min_weight_sum << ' ';
    cout << secondary_weight_sum << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases, from, to, weight;

    cin >> cases;
    for (int c = 1; c <= cases; c++) {
    
        cin >> number_of_vertices >> number_of_edges;
        for (int i = 0; i < number_of_edges; i++)
        {
            cin >> from >> to >> weight;
            from--, to--;
            edges[i] = (edge){from, to, weight, 0};
        }

        kruskal();
    }

    return 0;
}
