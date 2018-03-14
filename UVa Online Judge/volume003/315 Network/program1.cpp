// Network
// UVa ID: 315
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.190s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 使用邻接表方式表示图。每个顶点的出边使用一个集合来表示。
vector<set<int>> edges;

// 标记顶点是否已访问的向量。
vector<bool> visited;

// 深度优先遍历。v为移除的顶点，在遍历过程中需要跳过。
void dfs(int u, int v)
{
    for (auto w : edges[u])
        if (w != v && !visited[w])
        {
            visited[w] = true;
            dfs(w, v);
        }
}

// 获取无向连通图中割顶的个数。
int getCutVertices()
{
    // 设置图的顶点数目。顶点序号从1开始。
    int n = edges.size() - 1;
    
    // 当图的顶点数为1时，割顶数为0。
    if (n == 1) return 0;
    
    // 设置访问标记向量的大小。
    visited.resize(edges.size());

    // 逐个顶点判断是否为割顶。
    int count = 0;
    for (int v = 1; v <= n; v++)
    {
        // 使用深度优先遍历来遍历图。
        fill(visited.begin(), visited.end(), false);
        
        // 顶点数为1的特殊情况已经处理，此处从任意一个剩余的顶点开始遍历。
        int u = (v - 1 > 0 ? v - 1 : v + 1);
        
        // 设置移除的顶点和起始顶点为已访问状态，后续检查连通时不考虑这两个顶点。
        visited[v] = visited[u] = true;

        // 深度优先遍历。
        dfs(u, v);

        // 检查图是否连通，如果不再连通，则该顶点是割顶。
        for (int j = 1; j <= n; j++)
            if (!visited[j])
            {
                count++;
                break;
            }
    }
    
    // 返回割顶的数目。
    return count;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
 
    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        if (n == 0) break;

        edges.assign(n + 1, set<int>());
        
        istringstream iss;
        while (getline(cin, line), line != "0")
        {
            iss.clear(); iss.str(line);

            int start, next;
            iss >> start;
            while (iss >> next)
                edges[start].insert(next), edges[next].insert(start);
        }
        
        cout << getCutVertices() << '\n';
    }
    
	return 0;
}
