// Connect the Campus
// UVa ID: 10397
// Verdict: Accepted
// Submission Date: 2017-01-13
// UVa Run Time: 0.030s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

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
#include <vector>

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
point buildings[MAXV];

void makeSet()
{
    for (int i = 0; i <= N; i++)
    {
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

double kruskal()
{
    double length = 0.0;

    makeSet();
    
    int x, y;
    cin >> M;
    for (int i = 1; i <= M; i++)
    {
        cin >> x >> y;
        unionSet(x, y);
    }
    
    sort(edges, edges + E);
    for (int i = 0; i < E; i++)
    {
        x = findSet(edges[i].from), y = findSet(edges[i].to);
        
        if (x != y)
        {
            unionSet(x, y);
            length += sqrt(edges[i].weight);
        }
    }

    return length;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> N)
    {
        for (int i = 1; i <= N; i++)
            cin >> buildings[i].x >> buildings[i].y;
        
        E = 0;
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
            {
                int x = buildings[i].x - buildings[j].x;
                int y = buildings[i].y - buildings[j].y;
                edges[E++] = (edge){i, j, x * x + y * y};
            }

        cout << fixed << setprecision(2) << kruskal() << '\n';
    }
    
    return 0;
}
