// Arctic Network
// UVa ID: 10369
// Verdict: Accepted
// Submission Date: 2017-01-13
// UVa Run Time: 0.010s
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

const int MAXV = 550;

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
int parent[MAXV], ranks[MAXV], S, P, E;
point outposts[MAXV];

void make_set()
{
    for (int i = 0; i <= P; i++)
    {
        parent[i] = i; ranks[i] = 0;
    }
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

int kruskal()
{
    make_set();

    sort(edges, edges + E);

    for (int i = 0; i < E; i++)
    {
        int x = find_set(edges[i].from), y = find_set(edges[i].to);
        
        if (x != y)
        {
            union_set(x, y);
            P--;
        }
        
        if (P == S) return edges[i].weight;
    }
    
    return 0;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> S >> P;
        for (int i = 1; i <= P; i++)
            cin >> outposts[i].x >> outposts[i].y;
        
        E = 0;
        for (int i = 1; i <= P; i++)
            for (int j = i + 1; j <= P; j++)
            {
                int x = outposts[i].x - outposts[j].x;
                int y = outposts[i].y - outposts[j].y;
                edges[E++] = (edge){i, j, x * x + y * y};
            }

        int D = kruskal();
        cout << fixed << setprecision(2) << sqrt(D) << '\n';
    }
    
    return 0;
}
