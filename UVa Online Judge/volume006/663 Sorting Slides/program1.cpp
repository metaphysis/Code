// Sorting Slides
// UVa ID: 663
// Verdict: Accepted
// Submission Date: 2016-11-05
// UVa Run Time: 0.010s
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

const int MAXV = 60, INF = 0x3f3f3f3f;
const int UNLABELED = -1, UNCHECKED = 0, CHECKED = 1;

struct arc
{
    int capacity, flow;
};

struct flag
{
    int status, parent, alpha;
};

arc arcs[MAXV][MAXV];
flag flags[MAXV];
int source, sink;

// 使用标号法求容量网络的最大流。
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

struct point
{
    int x, y;
};

struct rectangle
{
    int xmin, xmax, ymin, ymax;
};

point points[MAXV];
rectangle rectangles[MAXV];

// 判断点是否在矩形内。
bool pointInBox(point p, rectangle r)
{
    return p.x > r.xmin && p.x < r.xmax && p.y > r.ymin && p.y < r.ymax;
}

int main(int argc, char *argv[])
{
    int heap, cases = 0;
    while (cin >> heap, heap > 0)
    {
        // 读入矩形和点的位置数据。
        for (int i = 1; i <= heap; i++)
        {
            cin >> rectangles[i].xmin >> rectangles[i].xmax;
            cin >> rectangles[i].ymin >> rectangles[i].ymax;
        }
        
        for (int i = 1; i <= heap; i++)
            cin >> points[i].x >> points[i].y;

        // 初始化容量网络。
        for (int i = 0; i <= 2 * heap + 1; i++)
            for (int j = 0; j <= 2 * heap + 1; j++)
                arcs[i][j].capacity = arcs[i][j].flow = INF;

        // 在源点和数字间建立有向边，在矩形和汇点间建立有向边。
        source = 0, sink = 2 * heap + 1;
        for (int i = 1; i <= heap; i++)
            arcs[source][i].capacity = 1, arcs[source][i].flow = 0;
        for (int i = heap + 1; i <= 2 * heap; i++)
            arcs[i][sink].capacity = 1, arcs[i][sink].flow = 0;

        // 根据数字是否在某个矩形内，建立有向边。
        for (int i = 1; i <= heap; i++)
            for (int j = 1; j <= heap; j++)
                if (pointInBox(points[i], rectangles[j]))
                    arcs[i][j + heap].capacity = 1, arcs[i][j + heap].flow = 0;

        // 使用标号法求最大流从而得到最大匹配数。
        int maxMatch = fordFulkerson();
        
        // 将任意一条有向边移除，再次求最大匹配数，检查最大匹配数是否减少，以此
        // 判定有向边是否唯一可确定。
        cout << "Heap " << ++cases << '\n';
        bool outputed = false;

        // 因为需要按照幻灯片编号升序输出，故移除有向边的顺序要相应改变。
        for (int i = 1; i <= heap; i++)
            for (int j = 1; j <= heap; j++)
                if (arcs[j][i + heap].capacity == 1)
                {
                    // 将容量网络恢复到初始状态。
                    for (int ii = 0; ii < MAXV; ii++)
                        for (int jj = 0; jj < MAXV; jj++)
                            if (arcs[ii][jj].capacity == 1)
                                arcs[ii][jj].flow = 0;

                    // 移除有向边。
                    arcs[j][i + heap].capacity = arcs[j][i + heap].flow = INF;
                    
                    // 再次求最大匹配数。
                    int nextMatch = fordFulkerson();
                    
                    // 比较最大匹配数是否减小，减小表明移除的有向边为唯一可确定
                    // 的关联边。
                    if (nextMatch < maxMatch)
                    {
                        if (outputed) cout << ' ';
                        else outputed = true;
                        cout << '(' << (char)('A' + i - 1) << ',' << j << ')';
                    }

                    // 恢复有向边。
                    arcs[j][i + heap].capacity = 1, arcs[j][i + heap].flow = 0;
                }

        if (!outputed) cout << "none";

        cout << "\n\n";
    }
    
	return 0;
}
