const int MAXV = 110, INF = 0x3f3f3f3f;
const int UNLABELED = -1, UNCHECKED = 0, CHECKED = 1;

struct arc { int capacity, flow; } arcs[MAXV][MAXV];
struct flag { int status, parent, alpha; } flags[MAXV];
int source, sink;

int fordFulkerson()
{
    // 反复进行标号过程直到不存在改进路。
	while (true)
	{
	    // 初始化变量。
        memset(flags, -1, sizeof(flags));

        // 首先标记源点为已标号未检查顶点。
	    queue<int> unchecked; unchecked.push(source);
	    flags[source] = flag{UNCHECKED, -1, INF};

        // 当汇点尚未被标记且队列非空时继续。
	    while (flags[sink].status == UNLABELED && !unchecked.empty())
	    {
	        // 取出位于队列首的顶点u。
		    int u = unchecked.front(); unchecked.pop();
		    
		    // 检查与顶点u正向或反向连接的其他顶点v。
		    for (int v = 1; v <= nodes; v++)
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
	    if (flags[sink].status == UNLABELED || flags[sink].alpha == 0) break;

        // 汇点有标号，根据汇点的改进量沿着改进路对容量网络进行调整。
        int v = sink, u = abs(flags[v].parent), offset = flags[v].alpha;
        while (true)
        {
            if (arcs[u][v].flow < INF) arcs[u][v].flow += offset;
            else arcs[v][u].flow -= offset;
            
            // 调整到汇点，退出。
            if (u == source) break;
            v = u, u = abs(flags[u].parent);
        }
	}

    // 统计从源点流出的总流量。
    int maxFlow = 0;
    for (int u = 1; u <= nodes; u++)
        if (arcs[source][u].flow < INF)
            maxFlow += arcs[source][u].flow;
	return maxFlow;
}
