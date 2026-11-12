[UVa 192 Synchronous Design](https://blog.csdn.net/metaphysis/article/details/160942014)

## 题目分析

在数字集成电路设计中，同步设计是保证芯片正确性的关键。一个电路要满足同步设计，需要满足两个条件：

1. **无异步节点构成的环**：如果电路中存在完全由异步节点（如 `AND`、`OR` 等逻辑门）组成的环，实际电路中可能产生振荡，导致行为不可预测。
2. **最大延迟不超过时钟周期**：任意两个同步节点（触发器）之间的路径延迟必须小于等于给定的时钟周期，否则信号无法在下一个时钟边沿前稳定。

题目给定电路的节点信息（类型和延迟）、连接关系以及时钟周期，要求判断电路是否满足同步设计，并输出相应的结果。

### 节点类型

| 类型 | 代码 | 说明 |
|------|------|------|
| 输入 | `i` | 外部输入，延迟为 $0$ |
| 输出 | `o` | 外部输出，延迟为 $0$ |
| 同步节点 | `s` | 触发器，延迟为 $0$ |
| 异步节点 | `a` | 逻辑门，有正延迟 |

## 解题思路

### 第一步：检测异步节点环

要检测一个**有向图**中是否存在由**异步节点**构成的环，可以使用**拓扑排序**。只考虑异步节点：

- 计算每个异步节点的入度（只统计来自异步节点的边）
- 重复删除入度为 $0$ 的异步节点及其出边
- 如果最后还有异步节点未被删除，说明存在异步节点环

### 第二步：计算最大路径延迟

如果没有异步环，则计算所有从“输入或同步节点”出发到“同步或输出节点”结束的路径的最大延迟和。

由于图已无环，可以使用 $\texttt{DFS}$ 回溯搜索：
- 从每个输入节点或同步节点开始
- 沿边遍历，累加节点延迟
- 遇到同步或输出节点时，更新最大延迟

### 第三步：比较与输出

- 若存在异步环 → `Circuit contains cycle.`
- 否则，若最大延迟 $>$ 时钟周期 → `Clock period exceeded.`
- 否则 → `Synchronous design. Maximum delay: <ss>.`

## 代码实现

```cpp
// Synchronous Design
// UVa ID: 192
// Verdict: Accepted
// Submission Date: 2016-03-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 节点类型常量
const int INPUT = 0, OUTPUT = 1, SYN = 2, ASYN = 3;
const string typeText = "iosa";

// 节点结构体
struct vertex {
    int index;      // 节点编号
    int delay;      // 节点延迟（异步节点有效）
    int type;       // 节点类型
};

vector<vertex> verties;         // 所有节点
vector<int> path;               // DFS 路径缓存
vector<vector<int>> edges;      // 邻接表
int maximumDelay;               // 最大路径延迟

// 拓扑排序检测是否存在异步节点构成的环
bool findCycle() {
    vector<int> connections;
    connections.resize(verties.size());
    fill(connections.begin(), connections.end(), 0);
    
    // 计算每个异步节点的入度（仅考虑异步节点之间的边）
    for (int i = 0; i < edges.size(); i++)
        for (int j = 0; j < edges[i].size(); j++)
            if (verties[edges[i][j]].type == ASYN)
                connections[edges[i][j]]++;
   
    vector<bool> removed;
    removed.resize(verties.size());
    fill(removed.begin(), removed.end(), false);
    
    bool nodeRemoved = true;
    int numberRemovedNodes = 0;
    
    // 反复删除入度为 0 的异步节点
    while (nodeRemoved) {
        nodeRemoved = false;
        for (int i = 0; i < removed.size(); i++)
            if (removed[i] == false && connections[i] == 0) {
                nodeRemoved = true;
                numberRemovedNodes++;
                removed[i] = true;
                // 删除该节点的所有出边，更新后继节点的入度
                for (int j = 0; j < edges[i].size(); j++)
                    if (verties[edges[i][j]].type == ASYN)
                        connections[edges[i][j]]--;
            }
    }
    // 若还有异步节点未删除，说明存在环
    return numberRemovedNodes != verties.size();
}

// DFS 回溯搜索所有路径，计算最大延迟
void forward(int v, int index) {
    path[index] = v;
    // 当前路径终点是同步节点或输出节点时，计算路径总延迟
    if (index >= 1 && verties[path[index]].type != ASYN) {
        int tempMax = 0;       
        for (int i = 0; i <= index; i++)
            tempMax += verties[path[i]].delay;
        maximumDelay = max(tempMax, maximumDelay);
    } else {
        // 否则继续 DFS
        for (int i = 0; i < edges[v].size(); i++)
            forward(edges[v][i], index + 1);        
    }
}

// 从所有输入节点和同步节点开始搜索最长路径
void findMaximumDelay() {
    path.resize(verties.size());
    maximumDelay = 0;
    for (int i = 0; i < verties.size(); i++)
        if (verties[i].type == INPUT || verties[i].type == SYN)
            forward(i, 0);
}

int main() {
    int clock, circuits, delay, nodes, start, end, typeIndex;
    string type;
    cin >> circuits;   // 读取电路数量
    while (circuits--) {
        cin >> clock >> nodes;   // 时钟周期和节点数
        verties.clear();
        edges.clear();
        edges.resize(nodes);
        // 读取每个节点信息
        for (int i = 0; i < nodes; i++) {
            cin >> type >> delay;
            typeIndex = (int)typeText.find(type);
            // 输入、输出、同步节点的延迟均为 0
            if (typeIndex == INPUT || typeIndex == OUTPUT || typeIndex == SYN) delay = 0;
            verties.push_back((vertex){i, delay, typeIndex});
        }
        
        // 读取连接关系
        int m;
        cin >> m;
        for (int i = 1; i <= m; i++) {
            cin >> start >> end;
            edges[start].push_back(end);
        }
          
        // 判断异步环
        if (findCycle()) cout << "Circuit contains cycle." << endl;
        else {
            // 计算最大路径延迟
            findMaximumDelay();
            if (maximumDelay > clock) cout << "Clock period exceeded." << endl;
            else cout << "Synchronous design. Maximum delay: " << maximumDelay << "." << endl;
        }
    }
    return 0;
}
```

## 总结

本题核心是图的环检测与路径搜索：

- **环检测**：使用拓扑排序，只关注异步节点，判断是否存在异步环。
- **最大延迟计算**：在无环图中，通过 $\texttt{DFS}$ 枚举所有从输入/同步节点出发的路径，累加延迟并更新最大值。

算法时间复杂度为 $O(N^2)$（最坏情况），对于题目给定的数据规模足够高效。
