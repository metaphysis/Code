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
int idx, head_input[MAXV], head_query[MAXV];
int number_of_vertices, number_of_queries;
int ancestor[MAXV][MAXD], depth[MAXV], visited[MAXV];

void dfs(int u)
{
    visited[u] = 1;

    for (int i = head_input[u]; i != -1; i = input[i].next)
        if (!visited[input[i].v])
        {
            ancestor[input[i].v][0] = u;
            depth[input[i].v] = depth[u] + 1;

            dfs(input[i].v);
        }
}

void initialize()
{
    for (int d = 0; (1 << d) <= number_of_vertices; d++)
        for (int u = 0; u < number_of_vertices; u++)
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
        int maxd = log2(number_of_vertices);
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
    while (cin >> number_of_vertices, number_of_vertices)
    {
        idx = 0;
        memset(head_input, -1, sizeof(head_input));

        for (int from = 1; from <= number_of_vertices - 1; from++)
        {
            cin >> v >> weight;

            input[idx] = (edge){idx, from, v, weight, head_input[from]};
            head_input[from] = idx++;

            input[idx] = (edge){idx, v, from, weight, head_input[v]};
            head_input[v] = idx++;
        }

        memset(ancestor, -1, sizeof(ancestor));
        memset(visited, 0, sizeof(visited));
        memset(depth, 0, sizeof(depth));
        memset(dist, 0, sizeof(dist));

        dfs(0);
        initialize();

        cin >> number_of_queries;
        for (int i = 0; i < number_of_queries; i++)
        {
            cin >> u >> v;
            cout << lca(u, v) << '\n';
            
        }
    }

    return 0;
}
