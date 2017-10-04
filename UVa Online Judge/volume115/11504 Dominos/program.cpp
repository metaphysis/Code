// Dominos
// UVa ID: 11504
// Verdict: Accepted
// Submission Date: 2016-09-12
// UVa Run Time: 0.096s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <cstring>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

// 最大顶点数目。
const int MAX_V = 100010;

int visited[MAX_V], cases, n, m, from, to;
stack<int> s;
vector<int> edges[MAX_V];

// 第一次深度优先遍历，推倒的骨牌总是排在此骨牌能够导致倒下的其他骨牌之后。
void dfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            dfs(v);
    s.push(u);
}

// 第二次深度优先遍历，从最后一次推倒的骨牌开始。
void rdfs(int u)
{
    visited[u] = 1;
    for (auto v : edges[u])
        if (!visited[v])
            rdfs(v);
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        // 初始化。
        while (!s.empty()) s.pop();
        for (int u = 1; u <= n; u++) edges[u].clear(), visited[u] = 0;

        // 以邻接表方式读入图数据。
        cin >> n >> m;
        for (int e = 1; e <= m; e++)
        {
            cin >> from >> to;
            edges[from].push_back(to);
        }

        for (int u = 1; u <= n; u++)
            if (!visited[u])
                dfs(u);

        int cc = 0;
        for (int u = 1; u <= n; u++) visited[u] = 0;
        while (!s.empty())
        {
            int u = s.top();
            if (!visited[u])
                rdfs(u), cc++;
            s.pop();
        }
        
        cout << cc << '\n';
    }

    return 0;
}
