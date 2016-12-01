#include <algorithm>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

const int MAX_V = 1000;

// parent：记录顶点的父域；
// visited：标记顶点是否已经发现；
// dist：记录从起始顶点到各顶点的最短距离，即经过的最少边数量。
int parent[MAX_V], visited[MAX_V], dist[MAX_V];

// 以邻接表方式来表示图。
vector<int> edges[MAX_V];

// 广度优先遍历。
void bfs(int u)
{
    // 初始化。
    memset(parent, -1, sizeof(parent));
    memset(visited, 0, sizeof(visited));
    memset(dist, -1, sizeof(dist));

    // 存储未访问顶点的队列，将起始顶点放入队列中。
    queue<int> unvisited; unvisited.push(u);
    visited[u] = 1; dist[u] = 0;

    // 当队列不为空时继续处理。
    while (!unvisited.empty())
    {
        // 取出尚未访问的顶点
        int v = unvisited.front(); unvisited.pop();

        // 遍历与当前顶点相连接的其他顶点，如果其他顶点未发现，则将其加入到队列中，
        // 并将后继顶点的父顶点设置为当前顶点。
        for (auto next : edges[v])
            if (!visited[next])
            {
                unvisited.push(next);
                visited[next] = 1, parent[next] = v, dist[next] = dist[v] + 1;
            }
    }
}

int main(int argc, char *argv[])
{
    // 读入图数据，顶点从1开始编号。
    // number_of_vertices：图中顶点的数目；
    // number_of_edges：与某个顶点相连接的其他顶点数目；
    // next_v：与某个顶点相连接的其他顶点编号。
    int number_of_vertices, number_of_edges, next_v;

    while (cin >> number_of_vertices)
    {
        for (int v = 1; v <= number_of_vertices; v++)
        {
            edges[v].clear();

            cin >> number_of_edges;

            // 读入相连接的其他顶点，构建图。
            for (int i = 1; i <= number_of_edges; i++)
            {
                cin >> next_v;
                edges[v].push_back(next_v);
                edges[next_v].push_back(v);
            }
        }

        // 使用广度优先遍历从第1个顶点开始遍历图。
        bfs(1);

        // 输出各顶点的父顶点以及和起始顶点间的最短距离。
        cout << "vertex  parent  distance\n";
        for (int i = 1; i <= number_of_vertices; i++)
        {
            cout << setw(3) << right << i;
            cout << setw(8) << right << parent[i];
            cout << setw(9) << right << dist[i];
            cout << '\n';
        }
    }

    return 0;
}
