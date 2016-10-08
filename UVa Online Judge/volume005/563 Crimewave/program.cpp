// Crimewave
// UVa ID: 563
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

const int MAXV = 2610;

struct arc
{
	int capacity, flow, residual;
};

map<int, arc> arcs[MAXV];
int parents[MAXV], discovered[MAXV], occupied[MAXV];
int offset[4][2] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

void bfs(int source, int sink)
{
    memset(discovered, 0, sizeof(discovered));
	memset(parents, -1, sizeof(parents));

	queue<int> vertices;

	vertices.push(source);
	discovered[source] = 1;

	while (!vertices.empty())
	{
		int v = vertices.front();
		vertices.pop();
		for (auto a : arcs[v])
			// 沿着残留容量为正的弧进行图遍历，检查是否为饱和边。
			if (a.second.residual > 0)
				if (!discovered[a.first])
				{
					vertices.push(a.first);
					discovered[a.first] = 1;
					parents[a.first] = v;

					// 遍历到汇点后说明已经找到一条增广路，可以退出。
					if (a.first == sink)
						return;
				}
	}
}

void augmentPath(int source, int sink, int volume)
{
	if (source == sink) return;

	arcs[parents[sink]][sink].flow += volume;
	arcs[parents[sink]][sink].residual -= volume;

	arcs[sink][parents[sink]].residual += volume;

	augmentPath(source, parents[sink], volume);
}

int pathVolume(int source, int sink)
{
	if (parents[sink] == -1) return 0;

    int volume = arcs[parents[sink]][sink].residual;
	if (source == parents[sink])
		return volume;
	else
		return (min(pathVolume(source, parents[sink]), volume));
}

bool edmondsKarp(int streets, int avenues, int banks)
{
	int maxFlow = 0, volume, source = 1, sink = 2600;

	bfs(source, sink);
	volume = pathVolume(source, sink);
	while (volume > 0)
	{
		maxFlow += volume;
		augmentPath(source, sink, volume);
		bfs(source, sink);
		volume = pathVolume(source, sink);
	}

	return maxFlow == banks;
}

void buildGraph(int streets, int avenues)
{
    int edged[MAXV][4];
    memset(edged, 0, sizeof(edged));
    
    for (int s = 1; s <= streets; s++)
        for (int a = 1; a <= avenues; a++)
        {
            // 源点到每家银行所处交叉路口的弧。
            if (occupied[s * avenues + a])
            {
                arcs[1][s * avenues + a] = (arc){1, 0, 1};
                arcs[s * avenues + a][1] = (arc){1, 0, 0};
            }
                
            // 城镇边界上的交叉路口到汇点的弧。
            if (s == 1 || s == streets || a == 1 || a == avenues)
            {
                arcs[s * avenues + a][2600] = (arc){1, 0, 1};
                arcs[2600][s * avenues + a] = (arc){1, 0, 0};
            }
                
            // 在其余顶点间构建残留网络。
            for (int f = 0; f < 4; f++)
            {
                int ss = s + offset[f][0], aa = a + offset[f][1];
                if (ss >= 1 && ss <= streets && aa >= 1 && aa <= avenues)
                {
                    if (!occupied[ss * avenues + aa])
                        arcs[s * avenues + a][ss * avenues + aa] = (arc){1, 0, 1};
                    if (!occupied[s * avenues + a])
                        arcs[ss * avenues + aa][s * avenues + a] = (arc){1, 0, 0};
                }
            }
        }
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int problem, streets, avenues, banks, x, y;
    cin >> problem;
    
    for (int p = 1; p <= problem; p++)
    {
        cin >> streets >> avenues >> banks;
        
        memset(occupied, 0, sizeof(occupied));
        for (int b = 1; b <= banks; b++)
        {
            cin >> x >> y;
            occupied[x * avenues + y] = 1;
        }
        
        buildGraph(streets, avenues);
        bool possible = edmondsKarp(streets, avenues, banks);
        cout << (possible ? "possible" : "not possible") << '\n';
    }
    
	return 0;
}
