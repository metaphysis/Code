#include <bits/stdc++.h>

using namespace std;

const int MAXV = 1000, WHITE = 0, GRAY = 1, BLACK = 2;
vector<list<int>> edges(MAXV);
int parent[MAXV], color[MAXV], dfn[MAXV], ft[MAXV];
int dfstime = 0;

// 深度优先遍历。
void dfs(int u)
{
    dfn[u] = ++dfstime, color[u] = GRAY;
    for (auto v : edges[u])
        if (!color[v])
        {
            parent[v] = u;
            dfs(v);
        }
    ft[u] = ++dfstime, color[u] = BLACK;
}

void findPath1(int u, int v)
{
    if (v != u)
    {
        findPath1(u, parent[v]);
        cout << ' ' << v;
    }
    else
        cout << u;
}

void findPath2(int u, int v)
{
    vector<int> path;
    while (v != u)
    {
        path.insert(path.begin(), v);
        // path.push_back(v);
        v = parent[v];
    }

    path.insert(path.begin(), u);
    // path.push_back(u);
    // reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
    {
        if (i > 0)
            cout << ' ';
        cout << path[i];
    }
    cout << '\n';
}

int main(int argc, char *argv[])
{
    int n;
    string line;
    istringstream iss;
        
    while (cin >> n)
    {
        cin.ignore(1024, '\n');
        
        for (int i = 1; i <= n; i++)
            edges[i].clear();

        for (int from = 1, to; from <= n; from++)
        {
            getline(cin, line);
            iss.clear(), iss.str(line);

            while (iss >> to)
            {
                edges[from].push_back(to);
                edges[to].push_back(from);
            }
        }

        // 初始化父域向量和标记顶点是否发现的向量。顶点序号从1开始。
        memset(parent, -1, sizeof(parent));
        memset(color, WHITE, sizeof(color));

        dfs(1);

        cout << "parent V(P):\n";
        for (int i = 1; i <= n; i++)
        {
            if (i > 1)
                cout << ' ';
            cout << i << '(' << parent[i] << ')';
        }
        cout << '\n';
        
        cout << "path from 1 to 9 by recursion:\n";    
        findPath1(1, 9);
        cout << '\n';

        cout << "path from 1 to 9 by backtrack:\n";
        findPath2(1, 9);
    }
    
    return 0;
}
