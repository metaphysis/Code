// Come and Go
// UVa ID: 11838
// Verdict: Accepted
// Submission Date: 2017-10-17
// UVa Run Time: 0.040s
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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 2010;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
stack<int> s; vector<list<int>> edges(MAXV);
int N, M;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 1; u <= N; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn)); memset(scc, 0, sizeof(scc));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; s.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        ++cscc;
        while (true)
        {
            int v = s.top(); s.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> N >> M, N > 0)
    {
        initialize();

        int from, to, p;
        for (int i = 0; i < M; i++)
        {
            cin >> from >> to >> p;
            edges[from].push_back(to);
            if (p == 2)
            edges[to].push_back(from);
        }

        for (int u = 1; u <= N; u++)
            if (!dfn[u])
                tarjan(u);

        cout << (cscc == 1 ? 1 : 0) << '\n';
    }
    
    return 0;
}
