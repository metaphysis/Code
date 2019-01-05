#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 12100;

struct edge {
    int u, v, weight;
    edge (int u = 0, int v = 0, int weight = 0): u(u), v(v), weight(weight) {}
    bool operator<(const edge &e) const { return weight < e.weight; }
} edges[MAXE];

int n, m;

int parent[MAXV], ranks[MAXV];

void makeSet()
{
    for (int i = 0; i < n; i++) parent[i] = i, ranks[i] = 0;
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

int kruskal()
{
    int sumOfWeight = 0, cntOfMerged = 0;

    makeSet();
    sort(edges, edges + m);

    for (int i = 0; i < m; i++)
        if (unionSet(edges[i].u, edges[i].v)) {
            cntOfMerged++;
            sumOfWeight += edges[i].weight;
        }
    return sumOfWeight;
}

int main(int argc, char *argv[])
{
    kruskal();
    
    return 0;
}
