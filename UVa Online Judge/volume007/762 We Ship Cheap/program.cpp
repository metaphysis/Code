// We Ship Cheap
// UVa ID: 762
// Verdict: Accepted
// Submission Date: 2016-11-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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
#include <vector>

using namespace std;

const int MAX_V = 700;

int parent[MAX_V], visited[MAX_V], dist[MAX_V];
vector<int> edges[MAX_V];

int get_indexer(string &name)
{
    return (name.front() - 'A') * 26 + (name.back() - 'A');
}

string get_name(int indexer)
{
    string name;
    name += (char)(indexer / 26 + 'A');
    name += (char)(indexer % 26 + 'A');
    return name;
}

// 广度优先遍历。
void bfs(int u)
{
    memset(parent, -1, sizeof(parent));
    memset(visited, 0, sizeof(visited));
    memset(dist, -1, sizeof(dist));
    
    // 存储未访问顶点的队列，将起始顶点放入队列中。
    queue<int> unvisited; unvisited.push(u);
    visited[u] = true; dist[u] = 0;
    
    // 当队列不为空时继续处理。
    while (!unvisited.empty())
    {
        // 取出尚未访问的顶点
        int v = unvisited.front(); unvisited.pop();
        
        // 遍历与当前顶点相连接的其他顶点，如果其他顶点未发现，则将其加入到队列中，
        // 并将后继顶点的父顶点设置为当前顶点。
        for (auto next : edges[v])
            if (!visited[next])
            {
                unvisited.push(next);
                visited[next] = 1, parent[next] = v, dist[next] = dist[v] + 1;
            }
    }
}

// 使用递归输出路径。
void find_path(int u, int v)
{
    if (parent[v] != u)
    {
        find_path(u, parent[v]);
        cout << get_name(parent[v]) << ' ' << get_name(v) << '\n';
    }
    else
        cout << get_name(u) << ' ' << get_name(v) << '\n';;
}

int main(int argc, char *argv[])
{
    // 读入图数据。
    int n, cases = 0;
    
    while (cin >> n)
    {
        if (cases++ > 0) cout << '\n';

        int counter = 0;
        
        for (int i = 0; i < MAX_V; i++)
            edges[i].clear();
        
        string from, to;
        int start, end;
        for (int i = 1; i <= n; i++)
        {
            cin >> from >> to;

            start = get_indexer(from), end = get_indexer(to);
            edges[start].push_back(end);
            edges[end].push_back(start);
        }
        
        cin >> from >> to;
        
        if (from == to)
            cout << from << ' ' << to << '\n';
        else
        {
            // 使用广度优先遍历从第一个顶点开始遍历图。
            start = get_indexer(from), end = get_indexer(to);
            
            bfs(start);
    
            if (dist[end] != -1)
                find_path(start, end);
            else
                cout << "No route\n";
        }
    }
    
    return 0;
}
