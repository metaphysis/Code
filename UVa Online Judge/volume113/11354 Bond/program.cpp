// Bond
// UVa ID: 11354
// Verdict: Accepted
// Submission Date: 2017-01-24
// UVa Run Time: 2.410s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 50010, MAXE = 100010;

struct edge
{
    int id, u, v, weight, enabled, next;

    bool operator<(const edge& x) const
    {
        return weight < x.weight;
    }
};

edge input[MAXE], query[MAXV], tree[MAXV], path[MAXV];
int idx, first_input[MAXV], first_query[MAXV], first_tree[MAXV];
int number_of_vertices, number_of_edges, number_of_queries;
int parent[MAXV], ranks[MAXV], ancestor[MAXV], visited[MAXV];
int risk[MAXV];

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
    idx = 0;
    fill(first_tree, first_tree + number_of_vertices, -1);

    make_set();
    sort(input, input + number_of_edges);

    for (int i = 0; i < number_of_edges; i++)
        if (union_set(input[i].u, input[i].v))
        {
            edge e = input[i];
            tree[idx] = (edge){idx, e.u, e.v, e.weight, 0, first_tree[e.u]};
            first_tree[e.u] = idx++;

            tree[idx] = (edge){idx, e.v, e.u, e.weight, 0, first_tree[e.v]};
            first_tree[e.v] = idx++;
        }
}

void dfs(int u)
{
    visited[u] = 1;

    for (int i = first_tree[u]; i != -1; i = tree[i].next)
    {
        int v = tree[i].v;
        if (!visited[v])
        {
            tree[i].enabled = 1;

            path[v].u = u;
            path[v].weight = tree[i].weight;

            dfs(v);
        }
    }
}

void lca(int u)
{
    ancestor[find_set(u)] = u;

    for (int i = first_tree[u]; i != -1; i = tree[i].next)
        if (tree[i].enabled) 
        {
            int v = tree[i].v;

            lca(v);

            union_set(u, v);
            ancestor[find_set(u)] = u;
        }

    visited[u] = 1;

    for (int i = first_query[u]; i != -1; i = query[i].next)
    {
        int v = query[i].v;

        if (visited[v])
        {
            int forebear = ancestor[find_set(v)];

            int risk1 = -1, from = u;
            while (from != forebear)
            {
                risk1 = max(risk1, path[from].weight);
                from = path[from].u;
            }

            int risk2 = -1, to = v;
            while (to != forebear)
            {
                risk2 = max(risk2, path[to].weight);
                to = path[to].u;
            }

            risk[query[i].id] = max(risk1, risk2);
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases = 0, u, v, weight;

    while (cin >> number_of_vertices)
    {
        idx = 0;
        fill(first_input, first_input + number_of_vertices, -1);

        cin >> number_of_edges;
        for (int i = 0; i < number_of_edges; i++)
        {
            cin >> u >> v >> weight;
            u--, v--;

            input[idx] = (edge){idx, u, v, weight, 0, first_input[u]};
            first_input[u] = idx++;

            input[idx] = (edge){idx, v, u, weight, 0, first_input[v]};
            first_input[v] = idx++;
        }
        number_of_edges = idx;

        kruskal();

        fill(visited, visited + number_of_vertices, 0);
        dfs(0);

        idx = 0;
        fill(first_query, first_query + number_of_vertices, -1);

        cin >> number_of_queries;
        for (int i = 0; i < number_of_queries; i++)
        {
            cin >> u >> v;
            u--, v--;

            query[idx] = (edge){i, u, v, 0, 0, first_query[u]};
            first_query[u] = idx++;
            
            query[idx] = (edge){i, v, u, 0, 0, first_query[v]};
            first_query[v] = idx++;
        }

        fill(visited, visited + number_of_vertices, 0);
        make_set();
        lca(0);

        if (cases++ > 0) cout << '\n';
        for (int i = 0; i < number_of_queries; i++) cout << risk[i] << '\n';
    }

    return 0;
}
