// Picnic Planning
// UVa ID: 1537
// Verdict: Accepted
// Submission Date: 2019-02-21
// UVa Run Time: 0.800s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 30, MAXE = 1010, INF = 0x7f7f7f7f;

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

int kruskal(int mask)
{
    int sumOfWeight = 0, cntOfMerged = 0;

    makeSet();

    for (int i = 0; i < m; i++)
    {
        if (edges[i].u == 0 && (mask & (1 << edges[i].v)) == 0) continue;
        if (unionSet(edges[i].u, edges[i].v)) {
            cntOfMerged++;
            sumOfWeight += edges[i].weight;
        }
    }
    if (cntOfMerged != n - 1) sumOfWeight = INF;
    return sumOfWeight;
}


int main(int argc, char *argv[])
{
    int cases, mask;
    map<string, int> names;
    string name1, name2;

    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> m;
        names.clear();
        mask = 0, n = 0;
        names["Park"] = n++;
        for (int i = 0, dist; i < m; i++)
        {
            cin >> name1 >> name2 >> dist;
            if (name2 == "Park") swap(name1, name2);
            if (names.find(name1) == names.end()) names[name1] = n++;
            if (names.find(name2) == names.end()) names[name2] = n++;
            edges[i] = edge(names[name1], names[name2], dist);
            if (name1 == "Park") mask |= (1 << (names[name2]));
        }
        sort(edges, edges + m);

        int s;
        cin >> s;

        int r = INF;
        for (int i = 0; i <= mask; i++)
        {
            if ((i & mask) != i) continue;
            if (__builtin_popcount(i) > s) continue;
            r = min(r, kruskal(i));
        }

        if (cs > 1) cout << '\n';
        cout << "Total miles driven: " << r << '\n';
    }

    return 0;
}
