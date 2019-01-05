// Is There A Second Way Left
// UVa ID: 10462
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.010s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110, MAXE = 12100, INF = 0x7f7f7f7f;

struct edge {
    int u, v, weight, enabled;
    bool operator<(const edge &e) const { return weight < e.weight; }
} edges[MAXE];

int parent[MAXV], ranks[MAXV], n, m;

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

void kruskal()
{
    int fbSumOfWeight = 0, intree[MAXV], cntOfIntree = 0;

    makeSet();
    sort(edges, edges + m);

    int cntOfMerged = 0;
    for (int i = 0; i < m; i++)
        if (unionSet(edges[i].u, edges[i].v)) {
            cntOfMerged++;
            intree[cntOfIntree++] = i;
            fbSumOfWeight += edges[i].weight;
        }
    
    if (cntOfMerged != (n - 1))
    {
        cout << "No way\n";
        return;
    }

    int sbSumOfWeight = INF, sum;
    for (int i = 0; i < cntOfIntree; i++) {
        edges[intree[i]].enabled = 0;
        makeSet();
        sum = 0, cntOfMerged = 0;
        for (int j = 0; j < m; j++)
            if (edges[j].enabled && unionSet(edges[j].u, edges[j].v)) {
                cntOfMerged++;
                sum += edges[j].weight;
            }

        edges[intree[i]].enabled = 1;
        if (cntOfMerged == (n - 1)) sbSumOfWeight = min(sbSumOfWeight, sum);
    }

    if (sbSumOfWeight == INF) cout << "No second way\n";
    else cout << sbSumOfWeight << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases;
    cin >> cases;

    for (int cs = 1; cs <= cases; cs++)
    {
        cout << "Case #" << cs << " : ";
        cin >> n >> m;
        for (int i = 0, u, v, w; i < m; i++)
        {
            cin >> u >> v >> w;
            u--, v--;
            edges[i] = edge{u, v, w, 1};
        }
        kruskal();
    }

    return 0;
}
