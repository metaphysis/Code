// Ants Colony
// UVa ID: 12238
// Verdict: Accepted
// Submission Date: 2017-02-27
// UVa Run Time: 0.290s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100010, MAXE = 200010;

struct edge
{
    int id, u, v, weight, next;
};

edge input[MAXE], query[MAXE];
int idx, head_input[MAXV], head_query[MAXV];
int number_of_vertices, number_of_queries;
int parent[MAXV], ranks[MAXV], ancestor[MAXV], visited[MAXV];
int father[MAXV], colored[MAXV], lca[MAXV];
long long int dist[MAXV];

void make_set()
{
    iota(parent, parent + MAXV, 0);
    memset(ranks, 0, sizeof(ranks));
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
        if (ranks[x] > ranks[y]) parent[y] = x;
        else
        {
            parent[x] = y;
            if (ranks[x] == ranks[y]) ranks[y]++;
        }
        return true;
    }
    return false;
}

void dfs(int u)
{
    ancestor[find_set(u)] = u;
    visited[u] = 1;

    for (int i = head_input[u]; i != -1; i = input[i].next)
        if (!visited[input[i].v])
        {
            father[input[i].v] = u;
            dist[input[i].v] = dist[u] + input[i].weight;

            dfs(input[i].v);

            union_set(u, input[i].v);
            ancestor[find_set(u)] = u;
        }

    colored[u] = 1;

    for (int i = head_query[u]; i != -1; i = query[i].next)
        if (colored[query[i].v])
            lca[query[i].id] = ancestor[find_set(query[i].v)];
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

        idx = 0;
        memset(head_query, -1, sizeof(head_query));

        cin >> number_of_queries;
        for (int i = 0; i < number_of_queries; i++)
        {
            cin >> u >> v;

            query[idx] = (edge){i, u, v, 0, head_query[u]};
            head_query[u] = idx++;
            
            query[idx] = (edge){i, v, u, 0, head_query[v]};
            head_query[v] = idx++;
        }

        memset(visited, 0, sizeof(visited));
        memset(colored, 0, sizeof(colored));
        memset(father, -1, sizeof(father));
        memset(dist, 0, sizeof(dist));
        make_set();
        
        dfs(0);

        for (int i = 0; i < number_of_queries; i++)
        {
            int aa = lca[i], uu = query[2 * i].u, vv = query[2 * i].v;
            if (i > 0) cout << ' ';
            cout << (dist[uu] + dist[vv] - 2 * dist[aa]);
        }
        cout << '\n';
    }

    return 0;
}
