// RACING
// UVa ID: 1234
// Verdict: Accepted
// Submission Date: 2018-02-12
// UVa Run Time: 0.060s
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

const int MAXV = 10010, MAXE = 100010, INF = 0x7fffffff;

struct edge {
    int from, to, cost;
    bool operator<(const edge& x) const { return cost > x.cost; }
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
    int maxWeight = 0, totalWeight = 0;

    makeSet();
    sort(edges, edges + m);

    for (int i = 0; i < m; i++)
    {
        totalWeight += edges[i].cost;
        if (unionSet(edges[i].from, edges[i].to))
            maxWeight += edges[i].cost;
    }

    cout << totalWeight - maxWeight << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int c = 1; c <= cases; c++)
    {
        cin >> n >> m;
        for (int i = 0; i < m; i++)
        {
            cin >> edges[i].from >> edges[i].to >> edges[i].cost;
        }
        kruskal();
    }

    return 0;
}
