#include <bits/stdc++.h>

using namespace std;

const int MAXV = 5010, MAXE = 10010;

struct edge
{
    int id, u, v, next;
};

edge data[MAXE], query[MAXE];
int idx, headD[MAXV], headQ[MAXV];
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

    for (int i = headD[u]; i != -1; i = data[i].next)
        if (!visited[data[i].v])
        {
            father[data[i].v] = u;

            dfs(data[i].v);
            unionSet(u, data[i].v);
            ancestor[findSet(u)] = u;
        }

    colored[u] = 1;

    for (int i = headQ[u]; i != -1; i = query[i].next)
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
        memset(headD, -1, sizeof(headD));

        for (int i = 0; i < numberOfVertices - 1; i++)
        {
            cin >> u >> v;

            data[idx] = (edge){idx, u, v, headD[u]};
            headD[u] = idx++;

            data[idx] = (edge){idx, v, u, headD[v]};
            headD[v] = idx++;
        }

        idx = 0;
        memset(headQ, -1, sizeof(headQ));

        cin >> numberOfQueries;
        for (int i = 0; i < numberOfQueries; i++)
        {
            cin >> u >> v;

            query[idx] = (edge){i, u, v, headQ[u]};
            headQ[u] = idx++;
            
            query[idx] = (edge){i, v, u, headQ[v]};
            headQ[v] = idx++;
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
