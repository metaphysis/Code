const int MAXV = 5100, MAXA = 31000;

struct arc
{
    int u, v, capacity, residual, next;
};

struct edmondsKarp
{
    arc arcs[MAXA];
    int source, sink, indexer, head[MAXV], path[MAXV], visited[MAXV];

    void initialize()
    {
        indexer = 0;
        memset(head, -1, sizeof(head));
    }
    
    int maxFlow()
    {
        int flow = 0;

	    while (true)
	    {
	        // 使用广度优先遍历寻找从源点到汇点的增广路。
            memset(visited, 0, sizeof(visited));
	        memset(path, -1, sizeof(path));

	        queue<int> unvisited;
	        unvisited.push(source);
	        visited[source] = 1;

	        while (!unvisited.empty())
	        {
		        int u = unvisited.front();
		        unvisited.pop();
		        
		        // 遍历以当前顶点为起点的有向弧，沿着残留容量为正的弧进行图遍历。
		        for (int x = head[u]; x != -1; x = arcs[x].next)
			        if (!visited[arcs[x].v] && arcs[x].residual > 0)
			        {
				        unvisited.push(arcs[x].v);
				        visited[arcs[x].v] = 1;

				        // 注意路径记录的是有向弧的编号。
				        path[arcs[x].v] = x;
			        }
	        }

	        // 遍历未能到达汇点，表明不存在增广路，当前可行流已经为最大流。
	        if (!visited[sink])
	            break;

            // 确定增广路的流量。
	        int minFlow = 1000000;
            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
                minFlow = min(minFlow, arcs[x].residual);

            // 更新可行流的流量及残留网络。
            flow += minFlow;

            for (int x = path[sink]; x != -1; x = path[arcs[x].u])
            {
                arcs[x].residual -= minFlow;
                arcs[x ^ 1].residual += minFlow;
            }
	    }

	    return flow;
    }

    void addArc(int u, int v, int capacity)
    {
        arcs[indexer] = (arc){u, v, capacity, capacity, head[u]};
        head[u] = indexer++;
        
        arcs[indexer] = (arc){v, u, capacity, 0, head[v]};
        head[v] = indexer++;
    }
};
