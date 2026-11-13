[UVa 280 Vertex](https://blog.csdn.net/metaphysis/article/details/161360318)

## 题目分析

本题要求我们处理多个有向图，对于每个给定的起点，输出从该起点出发无法到达的所有顶点。

### 输入格式解析

题目描述中的输入格式比较特殊，需要仔细理解：

1. 首先输入一个整数 $n$（$1 \leq n \leq 100$），表示图中顶点的数量。顶点编号为 $1$ 到 $n$。

2. 接下来是一组描述边的行，每行的格式为：
   - 第一个整数 $i$ 表示边的起点
   - 接下来若干个整数 $j, k, \ldots$ 表示终点
   - 每行以 $0$ 结尾
   - 例如 “$3\ 1\ 2\ 0$” 表示从顶点 $3$ 到顶点 $1$ 和顶点 $2$ 有边

3. 描述完所有边后，有一行单独的 “$0$” 表示该图的边输入结束。

4. 然后是一行查询列表：第一个整数表示接下来有多少个起点需要查询，后面跟着这些起点的编号。

5. 输入以另一个 “$0$” 表示所有图处理完毕。

### 可达性定义

题目给出了可达的递归定义：
- 如果存在边 $p \rightarrow r$，则 $r$ 从 $p$ 可达
- 如果存在某个顶点 $q$，使得 $q$ 从 $p$ 可达，且 $r$ 从 $q$ 可达，则 $r$ 从 $p$ 可达

这正是图论中**有向图的可达性**的标准定义，等价于从起点出发，沿着有向边可以到达的所有顶点。

### 输出格式

对于每个查询的起点，输出一行：
- 第一个数字是不可达顶点的数量
- 后面按编号升序列出所有不可达的顶点编号

## 解题思路

### 核心算法选择

本题的核心是**有向图的遍历**，用于找出从给定起点可以到达的所有顶点。由于 $n \leq 100$，图规模较小，既可以使用 $\texttt{DFS}$ 也可以使用 $\texttt{BFS}$。

### 算法流程

1. **读取图结构**：
   - 使用 `vector<vector<int>>` 存储邻接表
   - 注意顶点编号从 $1$ 开始，代码中转换为 $0$ 为底的索引方便处理

2. **对每个查询的起点执行 $\texttt{BFS}$**：
   - 初始化 `visited` 数组标记是否已访问（用于 $\texttt{BFS}$ 的队列控制）
   - 初始化 `accessible` 数组标记从起点是否可达
   - 将起点加入队列，标记为已访问

3. **$\texttt{BFS}$ 遍历过程**：
   - 从队列中取出当前顶点
   - 遍历它的所有邻接点（即所有出边指向的顶点）
   - 若邻接点未被访问过，将其加入队列并标记为已访问
   - **关键点**：无论邻接点是否曾入队，只要存在边，就将该邻接点标记为 `accessible` 为 `true`

4. **收集不可达顶点**：
   - 遍历 $1$ 到 $n$ 所有顶点
   - 若 `accessible[i] == false`，则该顶点从起点不可达
   - 按升序输出

### 为什么需要两个标记数组

代码中同时使用了 `visited` 和 `accessible` 两个布尔数组：

- **`visited`** ：用于 $\texttt{BFS}$ 算法的队列控制，防止同一个顶点被重复加入队列
- **`accessible`** ：真正记录“从起点是否可达”的信息。即使一个顶点已经在队列中（即 `visited` 为 `true`），如果通过另一条路径再次到达它，`accessible` 依然被设置为 `true`（虽然此时 `visited` 已经是 `true` 不会重新入队）

实际上，本题中由于只需要判断是否可达，可以简化：$\texttt{BFS}$ 完成后的 `visited` 数组就等价于可达性标记。但参考代码采用了两套标记，逻辑上更清晰，分别服务于“遍历控制”和“结果记录”。

### 时间复杂度分析

- 对于单个图，读取边的时间复杂度为 $O(E)$，其中 $E$ 是边的数量
- 对于每个查询起点，$\texttt{BFS}$ 的时间复杂度为 $O(V + E)$，其中 $V$ 是顶点数（$n$），$E$ 是边数
- 由于 $n \leq 100$，即使最坏情况也能高效运行
## 代码实现

```cpp
// Vertex
// UVa ID: 280
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.210s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int vertices;                           // 图的顶点数量
    vector < vector < int > > edges;        // 邻接表存储有向图
    vector < bool > visited, accessible;    // visited用于BFS队列控制，accessible记录可达性
    // 循环处理多个图，当输入0时结束
    while (cin >> vertices, vertices) {
        // 初始化邻接表，大小为vertices
        edges.clear();
        edges.resize(vertices);
        // 初始化标记数组
        visited.resize(vertices);
        accessible.resize(vertices);
        cin.ignore();                       // 忽略换行符
        // 读取边信息，每行以单独的"0"结束
        string line;
        while(getline(cin, line), line != "0") {
            istringstream iss(line);
            int start, index;
            iss >> start;                   // 边的起点
            // 读取所有终点，直到遇到0
            while (iss >> index, index)
                edges[start - 1].push_back(index - 1);  // 转换为0基索引存储
        }
        // 读取查询：第一个数字是查询数量，后面跟着这些起点的编号
        int numberOfVertices, vertex;
        cin >> numberOfVertices;
        // 对每个查询的起点分别进行BFS
        for (int i = 1; i <= numberOfVertices; i++) {
            cin >> vertex;
            // 重置标记数组
            fill(visited.begin(), visited.end(), false);
            fill(accessible.begin(), accessible.end(), false);
            queue<int> unvisited;       // BFS队列
            // 将起点加入队列并标记为已访问
            visited[vertex - 1] = true;
            unvisited.push(vertex - 1);
            // 广度优先搜索
            while (!unvisited.empty()) {
                int current = unvisited.front();
                unvisited.pop();
                // 遍历当前顶点的所有邻接点
                for (int j = 0; j < edges[current].size(); j++) {
                    int neighbor = edges[current][j];
                    // 如果邻接点未被访问过，将其加入队列
                    if (visited[neighbor] == false) {
                        visited[neighbor] = true;
                        unvisited.push(neighbor);
                    }
                    // 无论是否首次访问，都标记为可达
                    accessible[neighbor] = true;
                }
            }
            // 收集所有不可达的顶点
            int numberOfUnvisited = 0;
            string verticesText;
            for (int i = 0; i < accessible.size(); i++)
                if (accessible[i] == false) {
                    numberOfUnvisited++;
                    verticesText.append(" " + to_string(i + 1));  // 转回1基编号
                }
            // 输出结果：不可达数量 + 不可达顶点列表
            cout << numberOfUnvisited << verticesText << "\n";
        }
    }
    return 0;
}
```

## 总结

本题是图论中可达性问题的基本应用。关键在于：
1. 正确理解输入格式，尤其是边的表示方式
2. 选择适当的图遍历算法（$\texttt{BFS}$或 $\texttt{DFS}$）
3. 注意顶点编号从 $1$ 开始，在内部处理时转换为 $0$ 基索引更方便
4. 输出时需要将结果转换回 $1$ 基编号并按升序排列
