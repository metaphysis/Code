// Lighting Away
// UVa ID: 11770
// Verdict: Accepted
// Submission Date: 2017-10-19
// UVa Run Time: 0.060s
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

const int MAXV = 10010;

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

    int cases = 0;

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        cin >> N >> M;
        
        initialize();

        int from, to;
        for (int i = 0; i < M; i++)
        {
            cin >> from >> to;
            edges[from].push_back(to);
        }

        for (int u = 1; u <= N; u++)
            if (!dfn[u])
                tarjan(u);

        // 如果已经是强连通的则不需继续计算。
        cout << "Case " << c << ": ";
        if (cscc == 1) cout << "1\n";
        else
        {
            // 将同一强连通分量中的顶点视为一个顶点，计数入度。
            int id[MAXV] = {0};
            for (int u = 1; u <= N; u++)
                for (auto v : edges[u])
                {
                    if (scc[u] == scc[v]) continue;
                    id[scc[v]] = 1;
                }

            // 计数缩点操作后新图中入度为0的顶点数即为所求。
            int tid = 0;
            for (int u = 1; u <= cscc; u++)
                if (!id[u]) tid++;
            cout << tid << '\n';
        }
    }
    
    return 0;
}
