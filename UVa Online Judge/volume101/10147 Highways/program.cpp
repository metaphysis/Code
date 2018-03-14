// Highways
// UVa ID: 10147
// Verdict: Accepted
// Submission Date: 2017-01-13
// UVa Run Time: 0.130s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 760;

struct point
{
    int x, y;
};

struct edge
{
    int from, to, weight;
    
    bool operator<(const edge& x) const
    {
        return weight < x.weight;
    }
};

edge edges[MAXV * MAXV];
int parent[MAXV], ranks[MAXV], N, M, E;
point towns[MAXV];

void make_set()
{
    for (int i = 0; i <= N; i++) parent[i] = i, ranks[i] = 0;
}

int find_set(int x)
{
    return (parent[x] == x ? x : parent[x] = find_set(parent[x]));
}

void union_set(int x, int y)
{
    x = find_set(x), y = find_set(y);

    if (x != y)
    {
        if (ranks[x] > ranks[y]) parent[y] = x;
        else
        {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
    }
}

void kruskal()
{
    int highways = 0;

    make_set();
    
    int x, y;
    cin >> M;
    for (int i = 1; i <= M; i++)
    {
        cin >> x >> y;
        union_set(x, y);
    }
    
    sort(edges, edges + E);
    for (int i = 0; i < E; i++)
    {
        x = find_set(edges[i].from), y = find_set(edges[i].to);
        
        if (x != y)
        {
            union_set(x, y);
            cout << edges[i].from << ' ' << edges[i].to << '\n';
            highways++;
        }
    }

    if (!highways) cout << "No new highways need\n";
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cin >> N;
        for (int i = 1; i <= N; i++)
            cin >> towns[i].x >> towns[i].y;
        
        E = 0;
        for (int i = 1; i <= N; i++)
            for (int j = i; j <= N; j++)
            {
                int x = towns[i].x - towns[j].x;
                int y = towns[i].y - towns[j].y;
                edges[E++] = (edge){i, j, x * x + y * y};
            }

        kruskal();
    }
    
    return 0;
}
