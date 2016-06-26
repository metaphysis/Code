// Network
// UVa IDs: 315
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.190s
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

vector<set<int>> edges, removed;
vector<bool> visited;

// 深度优先遍历。
void dfs(int vertex)
{
    for (auto next : removed[vertex])
        if (visited[next] == false)
        {
            visited[next] = true;
            dfs(next);
        }
}

// 获取连通图中割点的个数。顶点序号从1开始。
int checkArticulationPoints()
{
    // 当图的顶点数为1时，割点数为0。
    int n = edges.size() - 1;
    
    if (n == 1)
        return 0;
    
    visited.resize(edges.size());
        
    // 逐个定点判读是否为割点。
    int counter = 0;
    for (int i = 1; i <= n; i++)
    {
        // 复制当前邻接表。
        removed.clear();
        for (auto edge : edges)
            removed.push_back(edge);
        
        // 获取移除当前顶点以及相连接的边。        
        for (int j = 1; j <= n; j++)
            removed[j].erase(i);
        removed[i].clear();
        
        // 使用深度优先遍历来遍历图。从任意一个剩余的顶点开始遍历。
        fill(visited.begin(), visited.end(), false);
        int start = (i - 1 > 0 ? i - 1 : i + 1);
        visited[start] = true;
        dfs(start);
        
        // 检查图是否仍是连通图。
        for (int j = 1; j <= n; j++)
            if (visited[j] == false && j != i)
            {
                counter++;
                break;
            }
    }
    
    return counter;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        int n = stoi(line);
        if (n == 0) break;
        
        edges.clear();
        edges.resize(n + 1, set<int>());
            
        while (getline(cin, line), line != "0")
        {
            istringstream iss(line);
            int start, next;
            iss >> start;
            while (iss >> next)
                edges[start].insert(next), edges[next].insert(start);
        }
        
        cout << checkArticulationPoints() << endl;
    }
    
	return 0;
}
