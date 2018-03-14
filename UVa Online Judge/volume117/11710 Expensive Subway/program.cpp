// Expensive Subway
// UVa ID: 11710
// Verdict: Accepted
// Submission Date: 2018-02-05
// UVa Run Time: 0.220s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 410;

struct edge
{
    int from, to, cost;
    edge (int from = 0, int to = 0, int cost = 0): from(from), to(to), cost(cost) {}
    bool operator<(const edge& x) const {
        return cost < x.cost;
    }
};

edge edges[100010];
int parent[MAXV], ranks[MAXV];
int n, m;
map<string, int> indexer;

void makeSet()
{
    for (int i = 0; i < n; i++) {
        parent[i] = i; ranks[i] = 0;
    }
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

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m, n > 0)
    {
        indexer.clear();
        string name;
        for (int i = 0; i < n; i++)
        {
            cin >> name;
            indexer[name] = i;
        }
        
        string start, end;
        int cost;
        for (int i = 0; i < m; i++)
        {
            cin >> start >> end >> cost;
            edges[i] = edge(indexer[start], indexer[end], cost);
        }
        cin >> start;

        makeSet();
        sort(edges, edges + m);

        int merged = 0, total = 0;
        for (int i = 0; i < m; i++)
            if (unionSet(edges[i].from, edges[i].to))
            {
                merged++;
                total += edges[i].cost;
            }
        if (merged == n - 1) cout << total << '\n';
        else cout << "Impossible\n";
    }

    return 0;
}
