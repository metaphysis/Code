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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 10000;

vector<int> edges[MAXV];
int parent[MAXV], visited[MAXV];

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

int lca(int u, int v)
{
    unordered_set<int> ancestors;

    while (u != -1) {
        ancestors.insert(u);
        u = parent[u];
    }

    while (v != -1) {
        if (ancestors.find(v) != ancestors.end())
            return v;
        v = parent[v];
    }
}

int main(int argc, char *argv[])
{
    int n;

    while (cin >> n)
    {
        for (int u = 0; u < n; u++)
            edges[u].clear();

        for (int u = 0, m; u < n; u++)
        {
            cin >> m;
            for (int j = 0, v; j < m; j++)
            {
                cin >> v;
                v--;
                edges[u].push_back(v);
                edges[v].push_back(u);
            }
        }

        memset(parent, -1, sizeof(parent));
        memset(visited, 0, sizeof(visited));

        dfs(0);

        cin >> n;
        for (int i = 0, u, v; i < n; i++)
        {
            cin >> u >> v;
            cout << "LCA of " << u << " and " << v << " is ";
            cout << (lca(--u, --v) + 1) << '\n';
        }
    }
}
