// Sorting Slides
// UVa ID: 663
// Verdict: 
// Submission Date: 
// UVa Run Time: s
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

const int MAXV = 60, INF = 100000;
const int UNLABELED = -1, UNCHECKED = 0, CHECKED = 1;

struct point
{
    int x, y;
};

struct rectangle
{
    int xmin, xmax, ymin, ymax;
};

struct arc
{
    int capacity, flow;
};

struct flag
{
    int status, parent, alpha;
};

rectangle rectangles[MAXV];
point points[MAXV];
arc arcs[MAXV][MAXV], backup[MAXV][MAXV], edge[MAXV][MAXV];
flag flags[MAXV];
int source, sink;

bool pointInBox(point p, rectangle r)
{
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
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

    int heap, cases = 0;
    while (cin >> heap, heap > 0)
    { 
        cout << "Heap " << ++cases << '\n';
        
        for (int i = 1; i <= heap; i++)
        {
            cin >> rectangles[i].xmin >> rectangles[i].xmax;
            cin >> rectangles[i].ymin >> rectangles[i].ymax;
        }
        
        for (int i = 1; i <= heap; i++)
            cin >> points[i].x >> points[i].y;
        
        for (int i = 0; i <= 2 * heap + 1; i++)
            for (int j = 0; j <= 2 * heap + 1; j++)
                arcs[i][j].capacity = arcs[i][j].flow = INF;

        source = 0, sink = 2 * heap + 1;
        for (int i = 1; i <= heap; i++)
            arcs[source][i].capacity = 1, arcs[source][i].flow = 0;
        for (int i = heap + 1; i <= 2 * heap; i++)
            arcs[i][sink].capacity = 1, arcs[i][sink].flow = 0;

        for (int i = 1; i <= heap; i++)
            for (int j = 1; j <= heap; j++)
                if (pointInBox(points[i], rectangles[j]))
                    arcs[i][j + heap].capacity = 1, arcs[i][j + heap].flow = 0;

        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++)
            {
                backup[i][j].capacity = arcs[i][j].capacity;
                backup[i][j].flow = arcs[i][j].flow;
            }

        int maxMatch = fordFulkerson();

        for (int i = 0; i < 30; i++)
            for (int j = 0; j < 30; j++)
            {
                edge[i][j].capacity = arcs[i][j].capacity;
                edge[i][j].flow = arcs[i][j].flow;
            }
            
        bool outputed = false;
        for (int i = 1; i <= heap; i++)
            for (int j = 1; j <= heap; j++)
                if (edge[j][i + heap].capacity == 1)
                {
                    for (int ii = 0; ii < 30; ii++)
                        for (int jj = 0; jj < 30; jj++)
                        {
                            arcs[ii][jj].capacity = backup[ii][jj].capacity;
                            arcs[ii][jj].flow = backup[ii][jj].flow;
                        }
                    arcs[j][i + heap].capacity = arcs[j][i + heap].flow = INF;
                    
                    int nextMatch = fordFulkerson();
                    
                    if (nextMatch < maxMatch)
                    {
                        if (outputed)
                            cout << ' ';
                        else
                            outputed = true;
                        cout << '(' << (char)('A' + i - 1) << ',' << j << ')';
                        break;
                    }
                }
        if (!outputed)
            cout << "none";        
        cout << "\n\n";
    }
    
	return 0;
}
