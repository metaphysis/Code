[UVa 321 The New Villa](https://blog.csdn.net/metaphysis/article/details/161510151)

## 题目描述

布莱克先生最近在乡下买了一栋别墅。只有一件事让他烦恼：虽然大多数房间都有电灯开关，但这些开关控制的灯往往在其他房间。他的房产经纪人认为这是一个特色，但布莱克先生开始相信，电工在连接开关和插座时有点心不在焉。

一天晚上，布莱克先生很晚才回家。站在走廊里时，他注意到所有其他房间的灯都关着。不幸的是，布莱克先生害怕黑暗，所以他从不敢进入没有开灯的房间，也永远不会关掉所在房间的灯。

经过一番思考，布莱克先生能够利用这种错误接线的电灯开关来为自己服务。他设法到达了卧室，并关掉了除卧室灯之外的所有灯。

要求：编写一个程序，给定别墅的描述，确定如何从走廊（房间 $1$）到达卧室（房间 $r$），初始时只有走廊的灯亮着。你永远不能进入黑暗的房间，并且在最后一步之后，除卧室灯外所有灯都必须关掉。如果有多个路径，选择步数最少的路径，其中“从一个房间移动到另一个房间”、“打开一盏灯”和“关掉一盏灯”各计为一步。

### 输入格式

输入文件包含多个别墅描述。每个别墅以一行包含三个整数 $r$、$d$ 和 $s$ 开始：
- $r$：房间数量（$\leq 10$）
- $d$：门/房间之间的连接数量
- $s$：别墅中的电灯开关数量

房间编号从 $1$ 到 $r$：房间 $1$ 是走廊，房间 $r$ 是卧室。

接下来 $d$ 行，每行两个整数 $i$ 和 $j$，表示房间 $i$ 和房间 $j$ 之间有门相连。

接下来 $s$ 行，每行两个整数 $k$ 和 $l$，表示房间 $k$ 中有一个开关控制房间 $l$ 的灯。

每个别墅描述后有一个空行。输入文件以 $r = d = s = 0$ 的别墅结束，该行不处理。

### 输出格式

对于每个别墅，首先输出一行测试用例编号（$\texttt{Villa \#1}$、$\texttt{Villa \#2}$ 等）。

如果存在解决方案，输出最短的操作步骤序列，格式如下所示。如果存在多个最短序列，输出任意一个。

如果不存在解决方案，输出一行 `The problem cannot be solved.`

每个测试用例后输出一个空行。

### 样例输入

```
3 3 4
1 2
1 3
3 2
1 2
1 3
2 1
3 2
2 2
1 1
1 2
0 0 0
```

### 样例输出

```
Villa #1
The problem can be solved in 6 steps:
- Switch on light in room 2.
- Switch on light in room 3.
- Move to room 2.
- Switch off light in room 1.
- Move to room 3.
- Switch off light in room 2.

Villa #2
The problem cannot be solved.
```

---

## 题目分析

### 问题的本质

这是一个**状态空间搜索**问题。状态包括：
- 当前所在的房间
- 每个房间的灯是亮还是灭

初始状态：房间 $1$（走廊），只有房间 $1$ 的灯亮，其他房间灯灭。

目标状态：房间 $r$（卧室），只有房间 $r$ 的灯亮，其他房间灯灭。

允许的操作：
1. **移动**：从当前房间移动到相邻房间（有门连接），前提是目标房间的灯是亮的
2. **开关灯**：在当前房间操作开关，改变其他房间的灯的状态，但不能关掉当前房间的灯

### 状态空间大小

房间数量 $r \leq 10$，每个房间的灯有 $2$ 种状态。因此总状态数为：
$$
r \times 2^r \leq 10 \times 1024 = 10240
$$

这是一个非常小的状态空间，可以使用广度优先搜索（$\texttt{BFS}$）找到最短路径。

### 状态编码

为了方便表示和存储，可以将状态编码为一个整数：
- 高 $4$ 位（或更多）存储当前房间编号
- 低 $10$ 位存储灯的亮灭状态（用位掩码表示）

例如：
- 房间编号：$1 \sim 10$，需要 $4$ 位（实际 $10$ 位足够）
- 灯状态：$2^{10} = 1024$ 种，需要 $10$ 位

编码公式：`status = (room << 10) | light_mask`

其中 `light_mask` 是一个 $10$ 位的整数，第 $i$ 位表示房间 $i+1$ 的灯是否亮。

---

## 解题思路

### 步骤一：读取输入并构建图

- 读取房间数 $r$、门数 $d$、开关数 $s$
- 用邻接矩阵 `connected[i][j]` 表示房间 $i$ 和 $j$ 之间是否有门
- 用邻接矩阵 `switchs[i][j]` 表示房间 $i$ 是否有控制房间 $j$ 的开关

### 步骤二：构建显式状态图

由于状态空间有限，可以预先构建所有可能的状态之间的转移边：

1. 从初始状态 `(1, 1)` 开始（房间 $1$，只有灯 $1$ 亮）
2. 对于每个状态，考虑所有可能的操作：
   - 移动：对于每个与当前房间相邻的房间，如果该房间的灯是亮的，则可以移动到该房间
   - 开关灯：对于当前房间的每个开关，可以打开或关闭对应房间的灯（不能关掉当前房间的灯）

3. 将新状态加入队列，继续构建，直到所有可达状态都被处理

### 步骤三：广度优先搜索

在构建好的状态图上，从初始状态到目标状态运行 $\texttt{BFS}$，记录每个状态的前驱（父节点）以便重建路径。

### 步骤四：重建路径并输出

从目标状态逆向回溯父节点，得到从初始状态到目标状态的完整状态序列。然后，将相邻状态之间的变化转换为可读的操作描述：
- 如果房间编号变化 → 移动操作
- 如果房间编号不变，灯状态变化 → 开关灯操作（比较两个状态的灯掩码，找出变化的位）

---

## 算法复杂度分析

### 时间复杂度

- 构建状态图：最多 $10240$ 个状态，每个状态最多检查 $r \times (r + d)$ 种操作
- $\texttt{BFS}$：$O(\text{状态数} + \text{边数})$
- 总复杂度：$O(r \times 2^r \times r^2)$，$r \leq 10$ 时完全可行

### 空间复杂度

- 状态图存储：$O(r \times 2^r)$
- 队列和父节点数组：$O(r \times 2^r)$

---

## 正确性证明

**引理 1**：状态编码 `(room << 10) | light_mask` 是单射的，即不同状态对应不同整数。

证明：房间编号和灯掩码独立，编码唯一确定状态。$\square$

**引理 2**：构建的状态图包含了所有合法状态之间的合法转移。

证明：对于每个状态，枚举所有可能的移动和开关操作，并将结果状态加入图中。由于状态空间有限，这个过程会终止并覆盖所有可达状态。$\square$

**引理 3**：$\texttt{BFS}$ 在无权图上找到最短路径。

证明：每条边的权重相同（一步操作），因此 $\texttt{BFS}$ 按层扩展，首次到达目标状态的路径即为最短路径。$\square$

---

## 参考代码

```cpp
// The New Villa
// UVa ID: 321
// Verdict: Accepted
// Submission Date: 2016-09-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 最大顶点数目：房间数 <= 10，灯状态 2^10 = 1024，总状态数 <= 10 * 1024 = 10240
const int MAX_V = 102050;

// 将所在房间和灯的亮灭状态转换为一个唯一的整数进行表示。
// 将房间编号左移 10 位，再加上表示所有灯亮灭的状态整数即可唯一标识某个时刻人所在房间及灯的状态。
const int SHIFTS = 10, SHIFTS_MASK = 1023;

// r: 房间数量，d: 门数量，s: 开关数量，cases: 测试用例计数器
int r, d, s, from, to, cases = 0;

// vertex: 顶点数组，visited: 标记顶点是否已被访问，parent: 记录各顶点的父节点
int vertex[MAX_V], visited[MAX_V], parent[MAX_V];

// connected: 记录门的连接（邻接矩阵），switchs: 记录开关信息
int connected[16][16], switchs[16][16];

// 以邻接表方式表示图（状态转移图）
map<int, set<int>> edges;

// 表示当前所在房间及灯亮灭状态
struct state
{
    int room;           // 当前房间编号
    bitset<10> light;   // 灯的亮灭状态，第 i 位表示房间 i+1 的灯
};

// 构建显式有向图（状态转移图）
void buildGraph()
{
    // 重置门及开关数据
    memset(connected, 0, sizeof(connected));
    memset(switchs, 0, sizeof(switchs));

    // 读入门数据
    for (int i = 1; i <= d; i++)
    {
        cin >> from >> to;
        connected[from][to] = connected[to][from] = 1;
    }

    // 读入开关数据
    for (int i = 1; i <= s; i++)
    {
        cin >> from >> to;
        switchs[from][to] = 1;
    }

    // 重置相关变量
    edges.clear();
    memset(visited, 0, sizeof(visited));

    // 从初始状态开始构建显式图
    queue<state> unvisited;
    unvisited.push((state){1, 1});  // 初始状态：房间1，只有灯1亮
    visited[1 << SHIFTS | 1] = 1;   // 标记初始状态已访问

    // 队列非空继续构建
    while (!unvisited.empty())
    {
        state current = unvisited.front();
        unvisited.pop();
        int room = current.room;
        bitset<10> light = current.light;
        int status = (room << SHIFTS) | light.to_ulong();
       
        // 尝试所有可能的下一状态
        for (int next_room = 1; next_room <= r; next_room++)
        {
            // 1. 移动：进入相邻且灯亮的房间
            if (light.test(next_room - 1) && connected[room][next_room])
            {
                int next_status = (next_room << SHIFTS) | light.to_ulong();
                edges[status].insert(next_status);
                if (!visited[next_status])
                {
                    visited[next_status] = 1;
                    unvisited.push((state){next_room, light});
                }
            }

            // 2. 开关灯：打开或关闭其他房间的灯（不能关闭所在房间的灯）
            if (next_room != room && switchs[room][next_room])
            {
                bitset<10> next_light(light);
                next_light.flip(next_room - 1);  // 切换灯的状态

                int next_status = (room << SHIFTS) | next_light.to_ulong();
                edges[status].insert(next_status);
                if (!visited[next_status])
                {
                    visited[next_status] = 1;
                    unvisited.push((state){room, next_light});
                }
            }
        }
    }
}

// 广度优先遍历，寻找从初始状态到目标状态的最短路径
void bfs()
{
    // 设置起始状态和终止状态对应的顶点
    from = (1 << SHIFTS) | 1;                     // 房间1，只有灯1亮
    to = (r << SHIFTS) | (1 << (r - 1));          // 房间r，只有灯r亮
    
    // 初始化父域和访问标记
    memset(parent, 0, sizeof(parent));
    memset(visited, 0, sizeof(visited));

    // 压入初始状态，开始遍历
    queue<int> unvisited;
    unvisited.push(from);
    visited[from] = 1;
    parent[from] = from;  // 根节点的父节点设为自身
    
    // 队列非空继续遍历
    while (!unvisited.empty())
    {
        int current = unvisited.front();
        unvisited.pop();

        // 当遍历遇到终止状态时退出
        if (current == to) break;

        // 遍历与当前状态相连接的其他状态
        for (auto edge : edges[current])
            if (!visited[edge])
            {
                visited[edge] = true;
                parent[edge] = current;
                unvisited.push(edge);
            }
    }
}

// 输出结果
void print()
{
    cout << "Villa #" << ++cases << '\n';

    // 如果终止状态的父域为空，则不存在解决方案
    if (parent[to] == 0)
    {
        cout << "The problem cannot be solved.\n\n";
        return;
    }
    
    // 构建从起始状态到达终止状态的最短路径，逆向查找父域
    vector<int> walk;
    int current = to;
    while (current != from)
    {
        walk.insert(walk.begin(), current);
        current = parent[current];
    }
    walk.insert(walk.begin(), from);

    // 输出最少操作步骤
    cout << "The problem can be solved in " << (walk.size() - 1) << " steps:\n";

    // 将路径转换为操作步骤描述
    for (int i = 1; i < walk.size(); i++)
    {
        int last_room = walk[i - 1] >> SHIFTS;              // 上一状态的房间
        int last_light = walk[i - 1] & SHIFTS_MASK;         // 上一状态的灯掩码
        int room = walk[i] >> SHIFTS;                       // 当前状态的房间
        int light = walk[i] & SHIFTS_MASK;                  // 当前状态的灯掩码

        // 判断操作类型
        if (last_room == room)  // 房间未变，是开关灯操作
        {
            if (light < last_light)
                cout << "- Switch off light in room ";
            else
                cout << "- Switch on light in room ";

            // 找出灯状态发生变化的房间
            int status = last_light ^ light;  // 异或得到变化的位
            int rooms = 0;
            while (status > 0)
            {
                status >>= 1;
                rooms++;
            }
            cout << rooms << ".\n";
        }
        else  // 房间变化，是移动操作
        {
            cout << "- Move to room " << room << ".\n";
        }
    }

    cout << '\n';
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false);

    while (cin >> r >> d >> s)
    {
        if (r == 0) break;
        buildGraph();   // 构建状态转移图
        bfs();          // 广度优先搜索
        print();        // 输出结果
    }

    return 0;
}
```
