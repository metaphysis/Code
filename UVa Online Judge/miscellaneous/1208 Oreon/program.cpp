// Oreon
// UVa ID: 1208
// Verdict: Accepted
// Submission Date: 2017-01-12
// UVa Run Time: 0.000s
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

const int MAX_DIST = 1000000, MAXV = 26;

struct tunnel
{
    int from, to, weight;
    
    bool operator<(const tunnel& x) const
    {
        if (weight != x.weight) return weight < x.weight;
        else {
            if (from != x.from )
                return from < x.from;
            else
                return to < x.to;
        }
    }
};

int edges[MAXV][MAXV], n;
int parent[MAXV], dist_to_tree[MAXV], intree[MAXV];
vector<tunnel> tunnels;

void prim(int u)
{
    for (int i = 0; i < n; i++)
    {
        parent[i] = -1; intree[i] = 0; dist_to_tree[i] = MAX_DIST;
    }

    dist_to_tree[u] = 0;
    while (!intree[u])
    {
        intree[u] = 1;

        if (parent[u] != -1)
        {
            int from = parent[u], to = u;
            if (from > to) swap(from, to);
            tunnels.push_back((tunnel){from, to, dist_to_tree[u]});
        }
        
        for (int v = 0; v < n; v++)
        {
            if (!intree[v] && edges[u][v])
            {
                if (dist_to_tree[v] > edges[u][v])
                {
                    dist_to_tree[v] = edges[u][v];
                    parent[v] = u;
                }
                else
                {
                    if (dist_to_tree[v] == edges[u][v] && parent[v] > u)
                        parent[v] = u;
                }
            }
        }

        int min_dist_to_tree = MAX_DIST;
        for (int i = 0; i < n; i++)
        {
            if (!intree[i])
            {
                if (min_dist_to_tree > dist_to_tree[i])
                {
                    min_dist_to_tree = dist_to_tree[i];
                    u = i;
                }
                else
                {
                    if (min_dist_to_tree == dist_to_tree[i] && parent[i] < parent[u])
                       u = i;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        
        char comma;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (j > 0) cin >> comma;
                cin >> edges[i][j];
            }
        
        tunnels.clear();

        prim(0);

        sort(tunnels.begin(), tunnels.end());
        
        cout << "Case " << c << ":\n";
        for (auto t : tunnels)
        {
            cout << (char)('A' + t.from) << '-' << (char)('A' + t.to);
            cout << ' ' << t.weight << '\n';
        }
    }
    
    return 0;
}
