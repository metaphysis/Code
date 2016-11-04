// Crimewave
// UVa ID: 563
// Verdict: TLE
// Submission Date: 2016-10-17
// UVa Run Time: 3.000s
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

const int MAXV = 5100, INF = 100000;
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

int problem, streets, avenues, banks;

void addArc(int u, int v, int capacity)
{
    arcs[u][v].capacity = capacity, arcs[u][v].flow = 0;
}

void buildGraph()
{
    // 上下左右四个顶点的坐标偏移量。
    int offset[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

    // 初始化有向弧计数器，源点和汇点编号，顶点在链表中的最后序号。
    source = 0, sink = 2 * streets * avenues + 1;

    // 初始化有向弧。
    for (int i = source; i <= sink; i++)
        for (int j = source; j <= sink; j++)
            arcs[i][j].capacity = arcs[i][j].flow = INF;
            
    // 在源点和银行之间建立有向弧。
    for (int b = 1, x, y; b <= banks; b++)
    {
        cin >> x >> y;
        addArc(source, (x - 1) * avenues + y, 1);
    }

    // 在交叉路口之间和交叉路口与汇点间建立有向弧。
    int base = streets * avenues;
    for (int s = 1; s <= streets; s++)
        for (int a = 1; a <= avenues; a++)
        {
            int index = (s - 1) * avenues + a;
 
            // 将交叉路口拆分为前点和后点并建立有向弧。
            addArc(index, base + index, 1);

            // 如果交叉路口不位于城镇的边界上，则每个交叉路口的后点向上下左右四个
            // 交叉路口的前点建立有向弧，否则在交叉路口的后点和汇点间建立有向弧。
            if (s > 1 && s < streets && a > 1 && a < avenues)
            {
                for (int f = 0; f < 4; f++)
                {
                    int ss = s + offset[f][0], aa = a + offset[f][1];
                    if (ss >= 1 && ss <= streets && aa >= 1 && aa <= avenues)
                        addArc(base + index, (ss - 1) * avenues + aa, 1);
                }
            }
            else
                addArc(base + index, sink, 1);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    cin >> problem;
    for (int p = 1; p <= problem; p++)
    {
        cin >> streets >> avenues >> banks;
        buildGraph();
        int maxFlow = fordFulkerson();
        cout << (maxFlow == banks ? "possible" : "not possible") << '\n';
    }

	return 0;
}
