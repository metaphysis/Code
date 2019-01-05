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
    int idx;
    int from, to, weight;
    int in_tree, in_path;
    int next;
};

bool cmp1(const edge& x, const edge& y)
{
    return x.weight < y.weight;
}

bool cmp2(const edge& x, const edge& y)
{
    return x.idx < y.idx;
}

edge edges_of_input[MAXE], edges_of_query[MAXE], edges_of_path[MAXV];
int first_of_input[MAXV], first_of_query[MAXV];
int number_of_vertices, number_of_edges, number_of_queries;
int parent[MAXV], ranks[MAXV], ancestor[MAXV], visited[MAXV];
int max_edge[MAXV];

void make_set()
{
    for (int i = 0; i < number_of_vertices; i++) parent[i] = i, ranks[i] = 0;
}

int find_set(int x)
{
    return (x == parent[x] ? x : parent[x] = find_set(parent[x]));
}

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
    stable_sort(edges_of_input, edges_of_input + number_of_edges, cmp1);
    
    for (int i = 0; i < number_of_edges; i += 2)
        if (union_set(edges_of_input[i].from, edges_of_input[i].to))
        {
            edges_of_input[i].in_tree = 1;
            edges_of_input[i + 1].in_tree = 1;
        }
        
    sort(edges_of_input, edges_of_input + number_of_edges, cmp2);
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

void lca(int u)
{
    ancestor[find_set(u)] = u;

    for (int i = first_of_input[u]; i != -1; i = edges_of_input[i].next)
        if (edges_of_input[i].in_path)
        {
            int v = edges_of_input[i].to;

            lca(v);

            union_set(u, v);
            ancestor[find_set(u)] = u;
        }

    visited[u] = 1;

    for (int i = first_of_query[u]; i != -1; i = edges_of_query[i].next)
    {
        int v = edges_of_query[i].to;

        if (visited[v])
        {
            int forebear = ancestor[find_set(v)];

            int max_edge1 = -1, uu = u;
            while (uu != forebear)
            {
                max_edge1 = max(max_edge1, edges_of_path[uu].weight);
                uu = edges_of_path[uu].from;
            }

            int max_edge2 = -1, vv = v;
            while (vv != forebear)
            {
                max_edge2 = max(max_edge2, edges_of_path[vv].weight);
                vv = edges_of_path[vv].from;
            }

            max_edge[edges_of_query[i].idx] = max(max_edge1, max_edge2);
        }
    }
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

        fill(visited, visited + number_of_vertices, 0);
        dfs(0);
        
        cin >> number_of_queries;

        idx = 0;
        for (int i = 0; i < number_of_queries; i++)
        {
            cin >> from >> to;
            from--, to--;

            edges_of_query[idx] = (edge){i, from, to, weight, 0, 0, first_of_query[from]};
            first_of_query[from] = idx++;
            
            edges_of_query[idx] = (edge){i, to, from, weight, 0, 0, first_of_query[to]};
            first_of_query[to] = idx++;
        }

        fill(visited, visited + number_of_vertices, 0);
        make_set();
        lca(0);

        if (cases++ > 0)
            cout << '\n';
        for (int i = 0; i < number_of_queries; i++)
            cout << max_edge[i] << '\n';
    }

    return 0;
}
