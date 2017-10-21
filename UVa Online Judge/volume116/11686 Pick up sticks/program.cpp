// Pick up sticks
// UVa ID: 11686
// Verdict: Accepted
// Submission Date: 2017-10-22
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

const int MAXV = 1000010;
int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc, n, m;
vector<list<int>> edges(MAXV);
stack<int> ts, cc;

void initialize()
{
    dfstime = 0, cscc = 0;
    while (!cc.empty()) cc.pop();
    for (int u = 1; u <= n; u++) edges[u].clear();
    memset(dfn, 0, (n + 1) * sizeof(int));
    memset(scc, 0, (n + 1) * sizeof(int));
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++dfstime; cc.push(u);
    for (auto v : edges[u])
    {
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (!scc[v]) low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        cscc++;
        while (true)
        {
            int v = cc.top(); cc.pop();
            scc[v] = cscc;
            if (u == v) break;
        }
    }
    ts.push(u);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    while (cin >> n >> m, n > 0)
    {
        initialize();
            
        int from, to;
        for (int i = 1; i <= m; i++)
        {
            cin >> from >> to;
            edges[from].push_back(to);
        }
        
        while (!ts.empty()) ts.pop();
        for (int u = 1; u <= n; u++)
            if (!dfn[u])
                tarjan(u);

        if (cscc != n) cout << "IMPOSSIBLE\n";
        else
        {
            while (!ts.empty())
            {
                cout << ts.top() << '\n';
                ts.pop();
            }
        }
    }
    
    return 0;
}
