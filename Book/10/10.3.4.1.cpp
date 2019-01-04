#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100, MAXE = 10010, INF = 0x7f7f7f7f;

struct edge {
    int u, v, weight, disabled;
    bool operator<(const edge& x) const { return weight < x.weight; }
} edges[MAXE];

int parent[MAXV], ranks[MAXV], nv, ne;

void makeSet()
{
    for (int i = 0; i < nv; i++) parent[i] = i, ranks[i] = 0;
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
    int fbSumOfWeight = 0, intree[MAXV], cntOfIntree = 0;

    makeSet();
    sort(edges, edges + ne);

    int cntOfMerged = 0;
    for (int i = 0; i < ne; i++)
        if (unionSet(edges[i].u, edges[i].v)) {
            cntOfMerged++;
            intree[cntOfIntree++] = i;
            fbSumOfWeight += edges[i].weight;
        }

    if (cntOfMerged != (nv - 1)) {
        cout << "No MST exist!\n";
        return;
    }
    else cout << fbSumOfWeight;

    int sbSumOfWeight = INF;
    for (int i = 0; i < cntOfIntree; i++) {
        int sumOfWeight = 0;
        edges[intree[i]].disabled = 1;

        makeSet();

        int addedVertices = 0;
        for (int j = 0; j < ne; j++)
            if (!edges[j].disabled && unionSet(edges[j].u, edges[j].v)) {
                sumOfWeight += edges[j].weight;
                addedVertices++;
            }

        edges[intree[i]].disabled = 0;
        if (addedVertices == (nv - 1))
            sbSumOfWeight = min(sbSumOfWeight, sumOfWeight);
    }

    if (sbSumOfWeight != INF) cout << ' ' << sbSumOfWeight;
    cout << '\n';
}

int main(int argc, char *argv[])
{

    kruskal();

    return 0;
}
