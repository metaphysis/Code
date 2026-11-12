[UVa 157 Route Finding](https://blog.csdn.net/metaphysis/article/details/158611182)

## 题目分析

这是一道经典的图论最短路径问题，但具有特殊的应用场景——城市公共交通系统的路线规划。题目中描述了三种类型的路线：直线往返路线、环形路线和连接线路，但本质上都可以抽象为图结构进行处理。

### 问题特点

1. **站点标识**：每条线路用大写字母 $\texttt{A}$ 到 $\texttt{Z}$ 标识，每个站点用小写字母 $\texttt{a}$ 到 $\texttt{z}$ 标识，因此每个站点可以用线路字母加站点字母的组合唯一标识，如 $\texttt{Ab}$ 表示线路 $\texttt{A}$ 上的 $\texttt{b}$ 站。

2. **换乘站处理**：换乘站具有多个标识，例如一个站点可能同时是 $\texttt{Ab}$、$\texttt{Bc}$ 和 $\texttt{Cd}$，这意味着同一个物理位置对应多个不同的编码。

3. **时间代价**：在同一线路上相邻站点间移动需要 $1$ 单位时间，在线路之间换乘需要 $3$ 单位时间。

4. **输入格式特殊**：输入中使用 $\texttt{=}$ 号表示站点的其他线路标识，可能会连续出现多个 $\texttt{=}$ 号连接多个不同线路的同一站点。

### 核心挑战

题目的难点在于如何正确解析输入并构建图结构，特别是处理换乘站点的连接关系。由于换乘站具有多个标识，我们需要确保这些标识之间能够相互连通，且换乘代价为 $3$ 单位时间。

## 解题思路

### 1. 图模型构建

将每个站点标识（如 $\texttt{Ab}$）视为图中的一个节点。如果两个节点在同一线路上相邻，则它们之间有一条权值为 $1$ 的边。如果两个节点代表同一个物理位置（换乘站），则它们之间有一条权值为 $3$ 的边。

### 2. 输入解析策略

题目输入格式比较特殊，需要仔细处理：

```
4
A:fgmpnxzabjd=Dbf
D:b=Adac=Ccf
B:acd=Azefg=Cbh
C:bac
```

对于每一行，先去掉所有 $\texttt{=}$ 号，然后将路线展开为节点序列。例如 $\texttt{A:fgmpnxzabjd=Dbf}$ 去掉 $\texttt{=}$ 后得到 $\texttt{A:fgmpnxzabjdDbf}$，然后提取节点：$\texttt{Af, Ag, Am, Ap, An, Ax, Az, Aa, Ab, Aj, Ad, Db, Df}$。注意 $\texttt{Db}$ 和 $\texttt{Df}$ 是因为 $\texttt{=Dbf}$ 表示的换乘站而产生的不同线路上的节点。

### 3. 换乘关系处理

关键是要识别哪些节点代表同一个物理位置。从输入中可以看到，换乘关系是通过 $\texttt{=}$ 号直接相连的节点，例如 $\texttt{=Dbf}$ 表示当前线路上的某个站点同时也是线路 $\texttt{D}$ 上的 $\texttt{b}$ 站和 $\texttt{f}$ 站。

对于 $\texttt{=}$ 后面的字符串 $\texttt{Dbf}$，它表示：
- 第一个字符 $\texttt{D}$ 是线路标识
- 后面的字符 $\texttt{b}$ 和 $\texttt{f}$ 是该线路上的站点标识
- 因此生成节点 $\texttt{Db}$ 和 $\texttt{Df}$

这些节点与 $\texttt{=}$ 前面的节点代表同一个物理位置，需要在它们之间建立权值为 $3$ 的边（换乘边）。

### 4. 最短路径算法

由于图中节点数量有限（最多 $26 \times 26 = 676$ 个），可以使用 `Dijkstra` 算法求解单源最短路径。对于每组查询，运行一次 `Dijkstra` 算法，记录前驱节点，最后回溯路径。

### 5. 路径输出格式

输出要求按照特定格式显示路径：在同一线路上连续行走时只输出站点字母，换乘时输出 $\texttt{=}$ 加上完整的新站点标识。例如 $\texttt{Agfdjba}$ 表示：
- $\texttt{Ag}$（起点）
- 在同一线路上依次经过 $\texttt{f, d, j, b, a}$ 站

而 $\texttt{Abaz=Bdefgh}$ 表示从 $\texttt{Ab}$ 出发，经过 $\texttt{a, z}$，然后换乘到线路 $\texttt{B}$ 的 $\texttt{d}$ 站，再继续行走。

## 代码实现细节

### 数据结构设计

使用 $\texttt{map<string, string> graph}$ 存储图的邻接表，键为节点标识，值为所有邻接节点拼接成的字符串（每两个字符表示一个节点）。

### 输入处理流程

1. 读取路线数量 $\texttt{routes}$
2. 循环读取每条路线描述
3. 对每行去掉所有 $\texttt{=}$ 号
4. 解析出所有节点标识
5. 构建同线路相邻节点之间的连接（权值 $1$）
6. 识别换乘关系，构建换乘节点之间的连接（权值 $3$）

### `Dijkstra` 算法实现

```cpp
void dijkstra(void)
{
    // 初始化
    for (auto it = graph.begin(); it != graph.end(); it++)
    {
        visited[it->first] = false;
        times[it->first] = MAXINT;
        parent[it->first].clear();
    }
    
    times[start] = 0;
    string station = start;
    
    while (visited[station] == false)
    {
        visited[station] = true;
        // 遍历邻接节点
        for (int i = 0; i < graph[station].length(); i += 2)
        {
            string next = graph[station].substr(i, 2);
            int weight = station[0] == next[0] ? 1 : 3;
            if (times[next] > times[station] + weight)
            {
                times[next] = times[station] + weight;
                parent[next] = station;
            }
        }
        
        // 选择未访问节点中时间最小的
        int maxTime = MAXINT;
        station = start;
        for (auto it = graph.begin(); it != graph.end(); it++)
            if (visited[it->first] == false && maxTime > times[it->first])
            {
                maxTime = times[it->first];
                station = it->first;
            }
    }
}
```

### 路径回溯

使用递归方式回溯路径，同时记录当前所在线路，以便在输出时决定是否添加 $\texttt{=}$ 号：

```cpp
char routeCode;
void findPath(string first, string last)
{
    if (first == last)
    {
        routeCode = first[0];
        path += first;
    }
    else
    {
        findPath(first, parent[last]);
        if (routeCode == last[0])
            path += last[1];  // 同一线路，只加站点字母
        else
        {
            path += "=";
            path += last;      // 换乘，加完整标识
            routeCode = last[0];
        }
    }
}
```

### 换乘关系补全

在初步构建图之后，还需要进行一步处理：确保所有换乘关系都被正确建立。因为可能存在这样的情况：$\texttt{Ab}$ 连接到 $\texttt{Bc}$（换乘），$\texttt{Bc}$ 连接到 $\texttt{Cd}$（换乘），那么 $\texttt{Ab}$ 和 $\texttt{Cd}$ 也应该直接相连（间接换乘）。这一步骤通过多次迭代直到不再新增连接来完成。

## 算法复杂度分析

- **时间复杂度**：假设有 $N$ 个节点，$M$ 条边。Dijkstra 算法使用简单实现（非堆优化）的时间复杂度为 $O(N^2)$。由于 $N \leq 676$，$N^2 \approx 4.5 \times 10^5$，对于每组查询来说是可以接受的。
- **空间复杂度**：$O(N + M)$，用于存储邻接表和辅助数组。

## 总结

本题的核心是正确解析输入格式并构建图模型，难点在于处理换乘站的多种标识以及换乘关系的传递性。一旦图构建完成，使用标准的最短路径算法即可求解。代码实现需要注意字符串处理的细节，以及路径输出格式的特殊要求。

## 完整代码

```cpp
// Route Finding
// UVa ID: 157
// Verdict: Accepted
// Submission Date: 2016-02-05
// UVa Run times: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXINT = numeric_limits<int>::max();

map<string, string> graph;
map<string, string> parent;
map<string, bool> visited;
map<string, int> times;
string start, to, path;

void dijkstra(void)
{
    for (map<string, string>::iterator it = graph.begin(); it != graph.end(); it++)
    {
        visited[it->first] = false;
        times[it->first] = MAXINT;
        parent[it->first].clear();
    }
    
    times[start] = 0;
    string station = start;
    
    while (visited[station] == false)
    {
        visited[station] = true;
        for (int i = 0; i < graph[station].length(); i += 2)
        {
            string next = graph[station].substr(i, 2);
            int weight = station[0] == next[0] ? 1 : 3;
            if (times[next] > (times[station] + weight))
            {
                times[next] = times[station] + weight;
                parent[next] = station;
            }
        }
        
        int maxTime = MAXINT;
        station = start;
        for (map<string, string>::iterator it = graph.begin(); it != graph.end(); it++)
            if (visited[it->first] == false && maxTime > times[it->first])
            {
                maxTime = times[it->first];
                station = it->first;
            }
    }
}

char routeCode;
void findPath(string first, string last)
{
    if (first == last)
    {
        routeCode = first[0];
        path += first;
    }
    else
    {
        findPath(first, parent[last]);
        if (routeCode == last[0])
            path += last[1];
        else
        {
            path += "=";
            path += last;
            routeCode = last[0];
        }
    }
}

string trim(string line)
{
    for (int i = line.length() - 1; i >= 0; i--)
        if (line[i] == ' ' || line[i] == '\t')
            line.erase(line.begin() + i);
    return line;
}

int main(int argc, char *argv[])
{
    string line;
    int routes;
    
    getline(cin, line);
    istringstream iss(line);
    iss >> routes;

    // 构建交通连接图
    while (routes--)
    {
        getline(cin, line);
        
        line = trim(line);
        
        for (int i = line.length() - 1; i >= 0; i--)
            if (line[i] == '=')
                line.erase(line.begin() + i);
        
        string route;
        int index = 2;
        while (index < line.length())
        {
            if (islower(line[index]))
            {
                route += line[0];
                route += line[index++];
            }
            else
            {
                route += line[index++];
                route += line[index++];
            }
        }
        
        index = 0;        
        while (index < route.length() - 2)
        {
            vector < string > station;
            station.push_back(route.substr(index, 2));
            
            while (index < route.length() - 2)
            {
                index += 2;
                string next = route.substr(index, 2);
                station.push_back(next);
                
                if (next[0] == station[0][0])
                    break;
            }
            
            graph[station[0]] += station[station.size() - 1];
            graph[station[station.size() - 1]] += station[0];
            
            for (int i = 0; i <= (int)station.size() - 3; i++)
                for (int j = i + 1; j <= (int)station.size() - 2; j++)
                {
                    graph[station[i]] += station[j];
                    graph[station[j]] += station[i];
                }
        }
    }
    
    // 查找是否有未添加的换乘点
    while (true)
    {
        int totalChanges = 0;
        vector<string> stations;
        for (map<string, string>::iterator it = graph.begin(); it != graph.end(); it++)
            stations.push_back(it->first);

        for (int i = 0; i < stations.size(); i++)
        {
            string station = stations[i];
            string next = graph[station];
            for (int j = 0; j < next.length(); j += 2)
            {
                string near = next.substr(j, 2);
                if (near[0] == station[0])
                    continue;
                    
                string nearNext = graph[near];
                for (int k = 0; k < nearNext.length(); k += 2)
                {
                    string some = nearNext.substr(k, 2);
                    if (near[0] != some[0] && some != station)
                    {
                        if (graph[station].find(some) == next.npos)
                        {
                            graph[station] += some;
                            totalChanges++;
                        }
                    }
                }
            }
        }
        
        if (totalChanges == 0)
            break;
    }
                
    while (getline(cin, line), line[0] != '#')
    {
        line = trim(line);
        
        start = line.substr(0, 2);
        to = line.substr(2, 2);
        
        dijkstra();
        
        cout << setw(3) << right << times[to] << ": ";
        
        path.clear();
        findPath(start, to);
        cout << path << endl;
    }
    
	return 0;
}
```
