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

const int MAXV = 5010, MAXE = 10010;

struct edge
{
    int id, u, v, next;
};

edge input[MAXE], query[MAXE];
int idx, headInput[MAXV], headQuery[MAXV];
int numberOfVertices, numberOfQueries;
int parent[MAXV], ranks[MAXV], ancestor[MAXV], visited[MAXV];
int father[MAXV], colored[MAXV], lca[MAXV];

void makeSet()
{
    iota(parent, parent + MAXV, 0);
    memset(ranks, 0, sizeof(ranks));
}

// 带路径压缩的查找，使用递归实现。
int findSet(int x)
{
    return (x == parent[x] ? x : parent[x] = findSet(parent[x]));
}

//  集合的按秩合并。
bool unionSet(int x, int y)
{
    x = findSet(x), y = findSet(y);
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
    ancestor[findSet(u)] = u;
    visited[u] = 1;

    for (int i = headInput[u]; i != -1; i = input[i].next)
        if (!visited[input[i].v])
        {
            father[input[i].v] = u;

            dfs(input[i].v);
            unionSet(u, input[i].v);
            ancestor[findSet(u)] = u;
        }

    colored[u] = 1;

    for (int i = headQuery[u]; i != -1; i = query[i].next)
        if (colored[query[i].v])
            lca[query[i].id] = ancestor[findSet(query[i].v)];
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
    int u, v;
    while (cin >> numberOfVertices, numberOfVertices)
    {
        idx = 0;
        memset(headInput, -1, sizeof(headInput));

        for (int i = 0; i < numberOfVertices - 1; i++)
        {
            cin >> u >> v;

            input[idx] = (edge){idx, u, v, headInput[u]};
            headInput[u] = idx++;

            input[idx] = (edge){idx, v, u, headInput[v]};
            headInput[v] = idx++;
        }

        idx = 0;
        memset(headQuery, -1, sizeof(headQuery));

        cin >> numberOfQueries;
        for (int i = 0; i < numberOfQueries; i++)
        {
            cin >> u >> v;

            query[idx] = (edge){i, u, v, headQuery[u]};
            headQuery[u] = idx++;
            
            query[idx] = (edge){i, v, u, headQuery[v]};
            headQuery[v] = idx++;
        }

        memset(visited, 0, sizeof(visited));
        memset(colored, 0, sizeof(colored));
        memset(father, -1, sizeof(father));
        makeSet();
        
        dfs(1);
        
        for (int i = 0; i < numberOfQueries; i++)
            cout << lca[i] << '\n';
    }

    return 0;
}
