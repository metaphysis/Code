#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>

using namespace std;

// 记录顶点的父顶点
vector<int> parent;

// 标记顶点是否已经发现
vector<bool> discovered;

// 记录从起始顶点到各顶点的最短距离，即经过的最少边数量
vector<int> distances;

// 以邻接表方式来表示图
vector<vector<int>> edges;

// 宽度优先遍历
void bfs(int start)
{
    // 初始化
    parent.resize(edges.size());
    discovered.resize(edges.size());
    distances.resize(edges.size());
    
    fill(parent.begin(), parent.end(), -1);
    fill(discovered.begin(), discovered.end(), false);
    fill(distances.begin(), distances.end(), -1);
       
    // 存储未访问顶点的队列，将起始顶点放入队列中
    queue<int> unvisited;
    unvisited.push(start);
    discovered[start] = true;
    distances[start] = 0;
    
    // 当队列不为空时继续处理
    while (!unvisited.empty())
    {
        // 取出尚未访问的顶点
        int current = unvisited.front();
        unvisited.pop();
        
        // 遍历与当前顶点相连接的其他顶点，如果其他顶点未发现，则将其加入到队列中，
        // 并将后继顶点的父顶点设置为当前顶点
        for (int i = 0; i < edges[current].size(); i++)
        {
            int next = edges[current][i];
            if (!discovered[next])
            {
                unvisited.push(next);
                discovered[next] = true;
                parent[next] = current;
                distances[next] = distances[current] + 1;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    // 读入图数据
    int count_of_vertices, count_of_edges, next_vertex;
    
    cin >> count_of_vertices;
    edges.resize(count_of_vertices + 1);

    for (int vertex = 1; vertex <= count_of_vertices; vertex++)
    {
        cin >> count_of_edges;
        for (int i = 1; i <= count_of_edges; i++)
        {
            cin >> next_vertex;
            edges[vertex].push_back(next_vertex);
            edges[next_vertex].push_back(vertex);
        }
    }
    
    // 使用宽度优先遍历从第一个顶点开始遍历图
    bfs(1);
    
    // 输出各顶点的父顶点以及和起始顶点间的最短距离
    cout << "vertex  parent  distance" << endl;
    for (int i = 1; i <= count_of_vertices; i++)
    {
        cout << setw(6) << right << i;
        cout << setw(8) << right << parent[i];
        cout << setw(10) << right << distances[i];
        cout << endl;
    }

    return 0;
}
