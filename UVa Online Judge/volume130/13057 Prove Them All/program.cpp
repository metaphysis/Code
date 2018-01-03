// Prove Them All
// UVa ID: 13057
// Verdict: Accepted
// Submission Date: 2018-01-03
// UVa Run Time: 0.030s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <cstring>
#include <iostream>
#include <list>
#include <stack>
#include <vector>

using namespace std;

// 最大顶点数目。
const int MAXV = 10010;

int dfn[MAXV], low[MAXV], scc[MAXV], dfstime, cscc;
int cases, n, m, from, to;
int id[MAXV] = {0};
stack<int> s; vector<list<int>> edges(MAXV);

// 初始化。
void initialize()
{
    dfstime = 0, cscc = 0;
    while (!s.empty()) s.pop();
    for (int u = 1; u <= n; u++) edges[u].clear();
    memset(dfn, 0, sizeof(dfn)); memset(scc, 0, sizeof(scc));
}

// Tarjan算法求强联通分量。
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

inline int nextChar()
{
    const int LENGTH = 1048576;
    static char buffer[LENGTH], *p = buffer, *end = buffer;
    if (p == end) {
        if ((end = buffer + fread(buffer, 1, LENGTH, stdin)) == buffer) return EOF;
        p = buffer;
    }
    return *p++;
}

inline bool nextInt(int &x)
{
    static char negative = 0, c = nextChar();
    negative = 0, x = 0;
    while ((c < '0' || c > '9') && c != '-') { if (c == EOF) return false; c = nextChar(); }
    if (c == '-') { negative = 1; c = nextChar(); }
    do x = (x << 3) + (x << 1) + c - '0'; while ((c = nextChar()) >= '0');
    if (negative) x = -x;
    return true;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    //cin >> cases;
    nextInt(cases);
    for (int c = 1; c <= cases; c++)
    {
        // 初始化。
        initialize();

        // 以邻接表方式读入图数据。
        //cin >> n >> m;
        nextInt(n), nextInt(m);
        for (int e = 1; e <= m; e++)
        {
            //cin >> from >> to;
            nextInt(from), nextInt(to);
            edges[from].push_back(to);
        }

        // Tarjan算法求强连通分量。
        for (int u = 1; u <= n; u++) if (!dfn[u]) tarjan(u);

        cout << "Case " << c << ": ";

        // 如果已经是强连通的则只需证明一个即可。
        if (cscc == 1) cout << "1\n";
        else
        {
            // 将同一强连通分量中的顶点视为一个顶点，计数其出度及入度。
            memset(id, 0, sizeof(id));
            for (int u = 1; u <= n; u++)
                for (auto v : edges[u])
                {
                    if (scc[u] == scc[v]) continue;
                    id[scc[v]] = 1;
                }

            // 计数缩点操作后新图中出度或入度为0的顶点数的较大值即为所求。
            int tid = 0;
            for (int u = 1; u <= cscc; u++)
                if (!id[u]) tid++;
            cout << tid << '\n';
        }
    }

	return 0;
}
