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
    int id, u, v, next;
};

edge input[MAXE], query[MAXV];
int idx, first_input[MAXV], first_query[MAXV];
int number_of_vertices, number_of_edges, number_of_queries;
int parent[MAXV], ranks[MAXV], ancestor[MAXV], visited[MAXV];
int colored[MAXV], answer[MAXV];

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

void lca(int u)
{
    ancestor[find_set(u)] = u;
    visited[u] = 1;

    for (int i = first_input[u]; i != -1; i = input[i].next)
        if (!visited[input[i].v])
        {
            lca(input[i].v);
            union_set(u, input[i].v);
            ancestor[find_set(u)] = u;
        }

    colored[u] = 1;

    for (int i = first_query[u]; i != -1; i = query[i].next)
        if (colored[query[i].v])
            answer[query[i].id] = ancestor[find_set(query[i].v)];
}

int main(int argc, char *argv[])
{
    int u, v, weight;

    while (cin >> number_of_vertices)
    {
        idx = 0;
        fill(first_input, first_input + number_of_vertices, -1);

        cin >> number_of_edges;
        for (int i = 0; i < number_of_edges; i++)
        {
            cin >> u >> v;
            u--, v--;

            input[idx] = (edge){idx, u, v, first_input[u]};
            first_input[u] = idx++;

            input[idx] = (edge){idx, v, u, first_input[v]};
            first_input[v] = idx++;
        }

        idx = 0;
        fill(first_query, first_query + number_of_vertices, -1);

        cin >> number_of_queries;
        for (int i = 0; i < number_of_queries; i++)
        {
            cin >> u >> v;
            u--, v--;

            query[idx] = (edge){i, u, v, first_query[u]};
            first_query[u] = idx++;
            
            query[idx] = (edge){i, v, u, first_query[v]};
            first_query[v] = idx++;
        }

        fill(visited, visited + number_of_vertices, 0);
        fill(colored, colored + number_of_vertices, 0);
        make_set();
        
        lca(0);

        for (int i = 0; i < number_of_queries; i++)
            cout << (answer[i] + 1) << '\n';
    }

    return 0;
}
