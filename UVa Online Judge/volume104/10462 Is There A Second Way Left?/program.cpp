// Is There A Second Way Left?
// UVa ID: 10462
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
            merged++;
            minWeightSum += edges[i].cost;
            intree[idx++] = i;
        }
    
    if (merged != (n - 1))
    {
        cout << "No way\n";
        return;
    }

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

    if (secondaryWeightSum != INF) cout << "No second way\n";
    else cout << secondaryWeightSum << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cout << "Case #" << c << " : ";
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> edges[i].from >> edges[i].to >> edges[i].cost;
        }
        kruskal();
    }

    return 0;
}
