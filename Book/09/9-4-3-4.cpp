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

const int MAXV = 100010, MAXD = 20, MAXE = 200010;

struct edge
{
    int id, u, v, weight, next;
};

edge input[MAXE], query[MAXE];
int idx, headInput[MAXV], headQuery[MAXV];
int numberOfVertices, numberOfQueries;
int ancestor[MAXV][MAXD], depth[MAXV], visited[MAXV];

void dfs(int u)
{
    visited[u] = 1;

    for (int i = headInput[u]; i != -1; i = input[i].next)
        if (!visited[input[i].v])
        {
            ancestor[input[i].v][0] = u;
            depth[input[i].v] = depth[u] + 1;

            dfs(input[i].v);
        }
}

void initialize()
{
    for (int d = 0; (1 << d) <= numberOfVertices; d++)
        for (int u = 0; u < numberOfVertices; u++)
            if (ancestor[u][d - 1] != -1)
                ancestor[u][d] = ancestor[ancestor[u][d - 1]][d - 1];
}

int lca(int u, int v)
{
    if (depth[u] < depth[v]) swap(u, v);

    int diff = depth[u] - depth[v];

    for (int d = 0; (1 << d) <= diff; d++)
        if ((1 << d) & diff)
            u = ancestor[u][d];

    if (u != v)
    {
        int maxd = log2(numberOfVertices);
        for (int d = maxd; d >= 0; d--)
            if (ancestor[u][d] != -1 && ancestor[u][d] != ancestor[v][d])
                u = ancestor[u][d], v = ancestor[v][d];
        u = ancestor[u][0];
    }

    return u;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int u, v, weight;
    while (cin >> numberOfVertices, numberOfVertices)
    {
        idx = 0;
        memset(headInput, -1, sizeof(headInput));

        for (int from = 1; from <= numberOfVertices - 1; from++)
        {
            cin >> v >> weight;

            input[idx] = (edge){idx, from, v, weight, headInput[from]};
            headInput[from] = idx++;

            input[idx] = (edge){idx, v, from, weight, headInput[v]};
            headInput[v] = idx++;
        }

        memset(ancestor, -1, sizeof(ancestor));
        memset(visited, 0, sizeof(visited));
        memset(depth, 0, sizeof(depth));
        memset(dist, 0, sizeof(dist));

        dfs(0);
        initialize();

        cin >> numberOfQueries;
        for (int i = 0; i < numberOfQueries; i++)
        {
            cin >> u >> v;
            cout << lca(u, v) << '\n';
            
        }
    }

    return 0;
}
