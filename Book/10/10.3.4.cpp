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

const int MAXV = 110, MAXE = 10010, INF = 0x7fffffff;

struct edge {
    int from, to, cost, disabled;
    bool operator<(const edge& x) const { return cost < x.cost; }
};

edge edges[MAXE];
int parent[MAXV], ranks[MAXV], n, m;

void makeSet()
{
    for (int i = 0; i <= n; i++) parent[i] = i, ranks[i] = 0;
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
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
    int minWeightSum = 0, intree[MAXV], idx = 0;

    makeSet();
    sort(edges, edges + m);

    int merged = 0;
    for (int i = 0; i < m; i++)
        if (unionSet(edges[i].from, edges[i].to)) {
            minWeightSum += edges[i].cost;
            intree[idx++] = i;
            merged++;
        }

    if (merged != (n - 1)) {
        cout << "No MST exist!\n";
        return;
    }
    else cout << minWeightSum;

    int secondaryWeightSum = INF;
    for (int i = 0; i < idx; i++) {
        int currentWeightSum = 0;
        edges[intree[i]].disabled = 1;

        makeSet();

        int addedVertices = 0;
        for (int j = 0; j < m; j++)
            if (!edges[j].disabled && unionSet(edges[j].from, edges[j].to)) {
                currentWeightSum += edges[j].cost;
                addedVertices++;
            }

        edges[intree[i]].disabled = 0;
        if (addedVertices == (n - 1))
            secondaryWeightSum = min(secondaryWeightSum, currentWeightSum);
    }

    if (secondaryWeightSum != INF) cout << ' ' << secondaryWeightSum;
    cout << '\n';
}

int main(int argc, char *argv[])
{
    return 0;
}
