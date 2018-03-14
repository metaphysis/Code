// IP-TV
// UVa ID: 1174
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 2010;

struct edge
{
    int from, to, cost;
    edge (int from = 0, int to = 0, int cost = 0): from(from), to(to), cost(cost) {}
    bool operator<(const edge& x) const {
        return cost < x.cost;
    }
};

edge edges[50010];
int parent[MAXV], ranks[MAXV];
int numberOfVertices, numberOfEdges;
map<string, int> indexer;

void makeSet()
{
    for (int i = 0; i < numberOfVertices; i++) {
        parent[i] = i; ranks[i] = 0;
    }
}

int findSet(int x)
{
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

void unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
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
    int minWeightSum = 0;

    makeSet();
    sort(edges, edges + numberOfEdges);

    for (int i = 0; i < numberOfEdges; i++) {
        int x = findSet(edges[i].from), y = findSet(edges[i].to);
        if (x != y) {
            unionSet(x, y);
            minWeightSum += edges[i].cost;
        }
    }

    return minWeightSum;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    while (cases--)
    {
        cin >> numberOfVertices >> numberOfEdges;

        int cost, cnt = 0;
        string from, to;
        indexer.clear();

        for (int i = 0; i < numberOfEdges; i++)
        {
            cin >> from >> to >> cost;
            if (indexer.find(from) == indexer.end()) indexer[from] = cnt++;
            if (indexer.find(to) == indexer.end()) indexer[to] = cnt++;
            edges[i] = edge(indexer[from], indexer[to], cost);
        }
        cout << kruskal() << '\n';
        if (cases) cout << '\n';
    }

    return 0;
}
