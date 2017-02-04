// Bond
// UVa ID: 11354
// Verdict: Accepted
// Submission Date: 2017-01-24
// UVa Run Time: 2.410s
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

const int MAXV = 50010, MAXE = 100010;

struct edge
{
    int idx;
    int from, to, weight;
    int in_tree, in_path;
    int next;

    bool operator<(const edge & x) const
    {
        return weight < x.weight;
    }
};

edge edges_of_input[MAXE], edges_of_query[MAXE], edges_of_path[MAXV], edges_of_used[MAXE];
int first_of_input[MAXV], first_of_query[MAXV];
int number_of_vertices, number_of_edges, number_of_queries;
int parent[MAXV], ranks[MAXV], ancestor[MAXV], visited[MAXV];
int max_edge[MAXV];

void make_set()
{
    for (int i = 0; i < number_of_vertices; i++) parent[i] = i, ranks[i] = 0;
}

// 带路径压缩的查找，使用递归实现。
int find_set(int x)
{
    return (x == parent[x] ? x : parent[x] = find_set(parent[x]));
}

//  集合的按秩合并。
bool union_set(int x, int y)
{
    x = find_set(x), y = find_set(y);

    if (x != y)
    {
        if (ranks[x] > ranks[y])
            parent[y] = x;
        else
        {
            parent[x] = y;
            if (ranks[x] == ranks[y])
                ranks[y]++;
        }
        return true;
    }
    return false;
}

void kruskal()
{
    for (int i = 0; i < number_of_edges; i++)
        edges_of_used[i] = edges_of_input[i];
    
    sort(edges_of_used, edges_of_used + number_of_edges);
    
    for (int i = 0; i < number_of_edges; i++)
        if (union_set(edges_of_used[i].from, edges_of_used[i].to))
        {
            edges_of_input[edges_of_used[i].idx].in_tree = 1;

            if (edges_of_used[i].idx & 1 == 1)
                edges_of_input[edges_of_used[i].idx - 1].in_tree = 1;
            else
                edges_of_input[edges_of_used[i].idx + 1].in_tree = 1;
        }
}

void dfs(int u)
{
    visited[u] = 1;

    for (int i = first_of_input[u]; i != -1; i = edges_of_input[i].next)
        if (edges_of_input[i].in_tree)
        {
            int v = edges_of_input[i].to;
            if (!visited[v])
            {
                edges_of_input[i].in_path = 1;

                edges_of_path[v].from = u;
                edges_of_path[v].weight = edges_of_input[i].weight;

                dfs(v);
            }
        }
}

int lca1(int u, int v)
{
    map<int, int> ancestors;

    int uu = u, max_edge1 = 0;
    while (uu != -1) {
        ancestors[uu] = max_edge1;
        max_edge1 = max(max_edge1, edges_of_path[uu].weight);
        uu = edges_of_path[uu].from;
    }

    int vv = v, max_edge2 = 0;
    while (vv != -1) {
        if (ancestors.find(vv) != ancestors.end()) break;
        max_edge2 = max(max_edge2, edges_of_path[vv].weight);
        vv = edges_of_path[vv].from;
    }

    return max(ancestors[vv], max_edge2);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, idx, from, to, weight;

    while (cin >> number_of_vertices >> number_of_edges)
    {
        fill(first_of_input, first_of_input + number_of_vertices, -1);
        fill(first_of_query, first_of_query + number_of_vertices, -1);

        idx = 0;
        for (int i = 0; i < number_of_edges; i++)
        {
            cin >> from >> to >> weight;
            from--, to--;

            edges_of_input[idx] = (edge){idx, from, to, weight, 0, 0, first_of_input[from]};
            first_of_input[from] = idx++;

            edges_of_input[idx] = (edge){idx, to, from, weight, 0, 0, first_of_input[to]};
            first_of_input[to] = idx++;
        }
        number_of_edges = idx;

        make_set();
        kruskal();

        for (int i = 0; i < number_of_vertices; i++)
            edges_of_path[i].from = -1;

        fill(visited, visited + number_of_vertices, 0);
        dfs(0);
        
        if (cases++ > 0) cout << '\n';
        
        cin >> number_of_queries;
        for (int i = 0; i < number_of_queries; i++)
        {
            cin >> from >> to;
            from--, to--;

            cout << lca1(from, to) << '\n';
        }
    }

    return 0;
}
