#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// 最大顶点数目。
const int MAX_V = 1000;

// 使用邻接表来表示图。
vector<vector<int>> edges(MAX_V);

// parent记录各顶点的父域，visited记录顶点是否已被访问，dfn记录顶点的时间戳。
vector<int> parent(MAX_V), visited(MAX_V), dfn(MAX_V);

// dfstime为全局变量，表示时间戳。
int dfstime = 0;

// 深度优先遍历。
void dfs(int u)
{
    // 记录顶点的发现时间并标记顶点为已发现。
    dfn[u] = ++dfstime, visited[u] = 1;

    // 处理与当前顶点相连接的其他顶点。
    for (auto v : edges[u])
        if (!visited[v])
        {
            parent[v] = u;
            dfs(v);
        }
}

// 使用递归输出路径。
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

// 使用回溯来输出路径。
void findPath2(int u, int v)
{
    // 声明一个vector，存储路径上顶点的编号。
    vector<int> path;

    // v为终止顶点的序号，u为起始顶点的序号。每次将顶点编号插入到路径的最前端。
    // 然后将当前顶点的编号设置为其父顶点的编号，继续该过程，直到找到起始顶点。
    while (v != u)
    {
        path.insert(path.begin(), v);

        // path.push_back(v);

        v = parent[v];
    }

    // 注意在退出while循环时，v和u相同，但起始顶点u的编号尚未加入，需要
    // 将起始顶点的编号添加进来，这样才能构成从起点到终点的一条完整路径。
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
        fill(parent.begin(), parent.end(), -1);
        fill(visited.begin(), visited.end(), 0);

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
