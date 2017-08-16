// Network
// UVa ID: 315
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.190s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <cstring>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

// 顶点数目。
const int MAX_V = 110;

// 使用邻接表来表示图。
vector<set<int>> edges;

// dfn保存各顶点的深度优先数，如果顶点的dfn值为0，表明该顶点尚未被访问。
// ic记录各顶点是否为割顶，为1表示为割顶，为0表示不是割顶。
// dfstime为时间戳。
int dfn[MAX_V], ic[MAX_V], dfstime = 0;

// Tarjan算法。调用时从任意一个顶点开始，parent设置为-1，表示起点为根结点。
int dfs(int u, int parent)
{
    int lowu = dfn[u] = ++dfstime, lowv, children = 0;
    
    // 对未访问的非根结点进行深度优先遍历并比较low值以判断是否为割顶。
    for (auto v : edges[u])
    {
        if (!dfn[v])
        {
            ++children, lowu = min(lowu, lowv = dfs(v, u));
            if (lowv >= dfn[u]) ic[u] = 1;
        }
        else 
        {
            if (dfn[v] < dfn[u] && v != parent)
                lowu = min(lowu, dfn[v]);
        }
    }

    // 如果为树的根结点且子孙结点数目少于两个，不是割顶。
    if (parent < 0 && children == 1) ic[u] = 0;

    // 将顶点u的最小深度优先数保存在数组中以便后续使用。
    return dfn[u] = lowu;
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
        
        dfstime = 0;
        memset(ic, 0, sizeof(ic));
        memset(dfn, 0, sizeof(dfn));
        
        dfs(1, -1);
        
        int count  = 0;
        for (int i = 1; i <= n; i++)
            if (ic[i])
                count++;

        cout << count << '\n';
    }
    
	return 0;
}
