// Gopher II
// UVa ID: 10080
// Verdict: Accepted
// Submission Date: 2016-11-09
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 210, INF = 100000;
const double EPSILON = 1E-6;
const int UNLABELED = -1, UNCHECKED = 0, CHECKED = 1;

struct point
{
    double x, y;
};

struct arc
{
    int capacity, flow;
};

struct flag
{
    int status, parent, alpha;
};

point gophers[MAXV], holes[MAXV];
arc arcs[MAXV][MAXV];
flag flags[MAXV];
int source, sink, n, m, s, v;

bool escaped(point gopher, point hole)
{
    return pow(gopher.x - hole.x, 2) + pow(gopher.y - hole.y, 2) < pow(s * v, 2) - EPSILON;
}

int fordFulkerson()
{
    // 反复进行标号过程直到不存在改进路。
	while (true)
	{
	    // 初始化变量。
        memset(flags, -1, sizeof(flags));

        // 首先标记源点为已标号未检查顶点。
	    queue<int> unchecked;
	    unchecked.push(source);
	    flags[source].status = UNCHECKED;
	    flags[source].parent = -1;
	    flags[source].alpha = INF;

        // 当汇点尚未被标记且队列非空时继续。
	    while (flags[sink].status == UNLABELED && !unchecked.empty())
	    {
	        // 取出位于队列首的顶点u。
		    int u = unchecked.front(); unchecked.pop();
		    
		    // 检查与顶点u正向或反向连接的其他顶点v。
		    for (int v = source; v <= sink; v++)
		    {
		        // 如果顶点v尚未被标号则予以标号。
		        if (flags[v].status == UNLABELED)
		        {
		            if (arcs[u][v].capacity < INF &&
		                arcs[u][v].flow < arcs[u][v].capacity)
		            {
		                flags[v].status = UNCHECKED, flags[v].parent = u;
		                flags[v].alpha = min(flags[u].alpha,
		                    arcs[u][v].capacity - arcs[u][v].flow);
		                unchecked.push(v);
		            }
		            else if (arcs[v][u].capacity < INF && arcs[v][u].flow > 0)
		            {
		                flags[v].status = UNCHECKED, flags[v].parent = -u;
		                flags[v].alpha = min(flags[u].alpha, arcs[v][u].flow);
		                unchecked.push(v);
		            }
		        }
		    }
		    
		    // 顶点u已经标号且已经检查完毕。
		    flags[u].status = CHECKED;
	    }
        
	    // 当标号过程未能到达汇点或者汇点的调整量为0，表明已经不存在改进路。
	    if (flags[sink].status == UNLABELED || flags[sink].alpha == 0)
	        break;

        // 汇点有标号，根据汇点的改进量沿着改进路对容量网络进行调整。
        int v = sink, u = abs(flags[v].parent), offset = flags[v].alpha;
        while (true)
        {
            if (arcs[u][v].flow < INF) arcs[u][v].flow += offset;
            else arcs[v][u].flow -= offset;
            
            if (u == source)
                break;
            v = u, u = abs(flags[u].parent);
        }
	}

    // 统计从源点流出的总流量。
    int maxFlow = 0;
    for (int u = source; u <= sink; u++)
        if (arcs[source][u].flow < INF)
            maxFlow += arcs[source][u].flow;
        
	return maxFlow;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    while (cin >> n)
    {
        cin >> m >> s >> v;
        
        for (int i = 1; i <= n; i++)
            cin >> gophers[i].x >> gophers[i].y;
        for (int i = 1; i <= m; i++)
            cin >> holes[i].x >> holes[i].y;
            
        source = 0, sink = n + m + 1;
        for (int i = source; i <= sink; i++)
            for (int j = source; j <= sink; j++)
                arcs[i][j].capacity = arcs[i][j].flow = INF;

        for (int i = 1; i <= n; i++)
            arcs[source][i].capacity = 1, arcs[source][i].flow = 0;
        for (int i = n + 1; i < sink; i++)
            arcs[i][sink].capacity = 1, arcs[i][sink].flow = 0;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (escaped(gophers[i], holes[j]))
                    arcs[i][j + n].capacity = 1, arcs[i][j + n].flow = 0;

        cout << (n - fordFulkerson()) << '\n';
    }
    
	return 0;
}
