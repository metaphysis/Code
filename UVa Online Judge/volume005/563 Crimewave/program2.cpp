// Crimewave
// UVa ID: 563
// Verdict: Time limit exceeded
// Submission Date: 2017-09-21
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

const int MAXV = 5100, INF = 0x7fffffff;
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

class FordFulkerson
{
private:
    int vertices, source, sink;

public:
    FordFulkerson(int v, int s, int t)
    {
        vertices = v;
        source = s, sink = t;
        for (int i = source; i <= sink; i++)
            for (int j = source; j <= sink; j++)
                arcs[i][j].capacity = arcs[i][j].flow = INF;
    }

    int maxFlow()
    {
        // 反复进行标号过程直到不存在改进路。
        while (true)
        {
            // 初始化变量。
            memset(flags, 0xff, vertices * sizeof(flag));

            // 首先标记源点为已标号未检查顶点。
            queue<int> unchecked; unchecked.push(source);
            flags[source] = flag{UNCHECKED, -1, INF};

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
                        if (arcs[u][v].capacity < INF && arcs[u][v].flow < arcs[u][v].capacity)
                        {
                            flags[v].status = UNCHECKED, flags[v].parent = u;
                            flags[v].alpha = min(flags[u].alpha, arcs[u][v].capacity - arcs[u][v].flow);
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
                if (arcs[u][v].flow < INF)
                    arcs[u][v].flow += offset;
                else
                    arcs[v][u].flow -= offset;

                // 调整到汇点，退出。
                if (u == source) break;
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
    
    void addArc(int u, int v, int capacity)
    {
        arcs[u][v].capacity = capacity, arcs[u][v].flow = 0;
    }
};

int problem, streets, avenues, banks;

void createGraph(FordFulkerson &ff)
{
    // 上下左右四个顶点的坐标偏移量。
    int offset[4][2] = { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

    // 在源点和银行之间建立有向弧。
    for (int b = 1, x, y; b <= banks; b++)
    {
        cin >> x >> y;
        ff.addArc(0, (x - 1) * avenues + y, 1);
    }

    // 在交叉路口之间和交叉路口与汇点间建立有向弧。
    int base = streets * avenues;
    for (int s = 1; s <= streets; s++)
        for (int a = 1; a <= avenues; a++)
        {
            int index = (s - 1) * avenues + a;

            // 将交叉路口拆分为前点和后点并建立有向弧。
            ff.addArc(index, base + index, 1);

            // 如果交叉路口不位于城镇的边界上，则每个交叉路口的后点向上下左右四个
            // 交叉路口的前点建立有向弧，否则在交叉路口的后点和汇点间建立有向弧。
            if (s > 1 && s < streets && a > 1 && a < avenues)
            {
                for (int f = 0; f < 4; f++)
                {
                    int ss = s + offset[f][0], aa = a + offset[f][1];
                    if (ss >= 1 && ss <= streets && aa >= 1 && aa <= avenues)
                        ff.addArc(base + index, (ss - 1) * avenues + aa, 1);
                }
            }
            else
                ff.addArc(base + index, 2 * streets * avenues + 1, 1);
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    cin >> problem;
    for (int p = 1; p <= problem; p++)
    {
        cin >> streets >> avenues >> banks;
        FordFulkerson ff(MAXV, 0, 2 * streets * avenues + 1);
        createGraph(ff);
        cout << (ff.maxFlow() == banks ? "possible" : "not possible") << '\n';
    }

    return 0;
}
