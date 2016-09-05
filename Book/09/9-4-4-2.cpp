#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int MAX_V = 1000;
int dfstime = 0, dfn[MAX_V], low[MAX_V], inscc[MAX_V], cscc = 0;
vector<vector<int>> edges;
stack<int> s;

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!inscc[v]) low[u] = min(low[u], dfn[v]);
    }

    if (low[u] == dfn[u])
        while (true)
        {
            ++cscc;
            int v = s.top(); s.pop();
            inscc[v] = cscc;
            if (u == v) break;
        }
}

int main(int argc, char *argv[])
{
    tarjan(1);

    return 0;
}
