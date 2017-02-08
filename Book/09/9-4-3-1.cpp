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

const int MAXV = 10000;

vector<int> edges[MAXV];
int parent[MAXV], visited[MAXV];

int lca(int u, int v)
{
    set<int> ancestors;

    int uu = u;
    while (uu != -1) {
        ancestors.insert(uu);
        uu = parent[uu];
    }

    int vv = v;
    while (vv != -1) {
        if (ancestors.find(vv) != ancestors.end()) return vv;
        vv = parent[vv];
    }

    return -1;
}

void dfs(int u)
{
    visited[u] = 1;
    
    for (auto v : edges[u])
        if (!visited[v])
        {
            parent[v] = u;
            dfs(v);
        }
}

int main(int argc, char *argv[])
{
    int n, m, u, v;

    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            edges[i].clear();
            cin >> m;
            for (int j = 0, k = 0; j < m; j++)
            {
                cin >> k;
                k--;
                edges[i].push_back(k);
            }
        }

        fill(parent, parent + n, -1);
        fill(visited, visited + n, 0);
        dfs(0);

        cin >> n;
        for (int i = 0; i < n; i++)
        {
            cin >> u >> v;
            u--, v--;
            cout << "LCA of " << u << " and " << v << " is ";
            cout << lca(u, v) << '\n';
        }
    }
}
