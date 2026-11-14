[UVa 302 John's Trip](https://blog.csdn.net/metaphysis/article/details/161441829)

## 题目描述

小约翰买了一辆新车，决定开车去镇上拜访他的朋友们。每条街道上恰好有一位他的朋友。他希望行程尽可能短，很快意识到最好的方式是**每条街道恰好经过一次**，并且最终回到起点（他父母的家）。

镇上的街道用 $1$ 到 $n$（$n < 1995$）的整数编号，路口用 $1$ 到 $m$（$m \leq 44$）的整数独立编号。每条街道恰好连接两个路口（可以是同一个路口），不同街道的编号不同。

约翰希望找到一条**经过每条街道恰好一次并回到起点**的回路。如果存在多条这样的回路，他选择**街道编号序列字典序最小**的那一条。约翰住在**第一组输入中编号较小的那个路口**。

假设所有街道都是双向的，且整个镇子的街道是连通的。街道非常窄，一旦进入就不能掉头。

### 输入格式

输入文件由多个数据块组成。每个数据块描述一个城镇。每行包含三个整数 $x, y, z$，表示街道 $z$ 连接路口 $x$ 和 $y$（$x > 0, y > 0$）。数据块以一行 `0 0` 结束。输入文件末尾由一个空块（`0 0`）表示结束。

### 输出格式

输出文件由与输入数据块对应的 $2$ 行块组成。每个输出块的第一行包含描述约翰回路的街道编号序列（编号之间用空格分隔），如果回路不存在，则输出 `Round trip does not exist.`。每个输出块的第二行为空行。

### 样例输入

```
1 2 1
2 3 2
3 1 6
1 2 5
2 3 3
3 1 4
0 0
1 2 1
2 3 2
1 3 3
2 4 4
0 0
0 0
```

### 样例输出

```
1 2 3 5 4 6

Round trip does not exist.

```

---

## 题目分析

### 问题的本质

这是一个经典的**欧拉回路**（$\texttt{Eulerian Circuit}$）问题。给定一个无向图，要求找到一条经过每条边**恰好一次**且回到起点的回路。如果存在多条回路，选择**字典序最小**的边序列。

关键要点：
- 图是**无向图**
- 每条边有唯一的整数编号
- 需要输出**街道编号序列**（不是路口编号）
- 起点为第一组输入中编号较小的路口
- 字典序最小指的是**边编号序列**的字典序最小

### 欧拉回路的存在条件

对于无向图，存在欧拉回路当且仅当：
1. **所有顶点的度数均为偶数**
2. 图是连通的（本题输入保证连通）

如果存在奇度数顶点，则不存在欧拉回路。

### 字典序最小的要求

在寻找欧拉回路时，如果从某个顶点出发有多个未访问的边，选择**编号最小**的边进行遍历，最终得到的边序列就是字典序最小的。这是因为：
- 欧拉回路的构造过程中，每次选择的边决定了后续序列的字典序
- 贪心地选择当前可用的最小边，可以得到全局字典序最小的回路

---

## 解题思路

### 步骤一：图的存储

由于需要按街道编号排序和查找，使用邻接表存储图：
- 每个顶点对应一个**多重集合**（$\texttt{multiset}$）存储邻接边
- 多重集合中的元素按街道编号自动排序
- 使用 `map<int, multiset<edge>>` 存储整个图

`edge` 结构体包含：
- `to`：邻接顶点编号
- `street`：街道编号

重载 `<` 运算符，使 `multiset` 按 `street` 升序排列。

### 步骤二：判断欧拉回路的存在性

遍历所有顶点，检查每个顶点的度数（即邻接边集合的大小）是否为偶数。如果存在奇度数顶点，直接输出 `Round trip does not exist.`。

### 步骤三：寻找欧拉回路（$\texttt{Hierholzer}$ 算法）

使用递归版本的 $\texttt{Hierholzer}$ 算法：

```cpp
void euler(int vertex)
{
    for (auto e : adjacentEdges[vertex])
        if (!traveled[e.street])
        {
            traveled[e.street] = true;
            euler(e.to);
            trip.insert(trip.begin(), e.street);
        }
}
```

算法流程：
1. 从起点出发
2. 对于当前顶点的每条邻接边，如果该边未被访问过，则：
   - 标记边为已访问
   - 递归访问边的另一端顶点
   - 将该边插入到结果序列的**开头**
3. 由于递归返回时插入边，最终得到的是逆序的欧拉回路
4. 递归结束后，`trip` 中存储的就是正确的边序列

### 步骤四：字典序最小

由于 `multiset` 按 `street` 升序存储邻接边，在遍历时自然按从小到大的顺序尝试。这保证了：
- 优先尝试编号较小的边
- 得到的边序列是字典序最小的

### 步骤五：输出格式

- 如果存在欧拉回路，输出边序列（空格分隔），然后输出一个空行
- 如果不存在，输出 `Round trip does not exist.`，然后输出一个空行

---

## 算法复杂度分析

### 时间复杂度

- 每个数据块：$O(E \log d + E)$，其中 $E$ 为边数，$d$ 为顶点的平均度数
- $\log d$ 来自 `multiset` 的插入和遍历
- $E < 1995$，$d \leq 44$，完全可行

### 空间复杂度

- 邻接表存储：$O(E)$
- 访问标记数组：$O(E)$
- 结果序列：$O(E)$
- 总空间复杂度 $O(E)$

---

## 正确性证明

**引理 1**（欧拉回路存在性）：无向连通图存在欧拉回路当且仅当所有顶点的度数均为偶数。

证明：经典图论结论。$\square$

**引理 2**（$\texttt{Hierholzer}$ 算法的正确性）：从任意顶点开始，每次走一条未走过的边，当无法继续时，将当前路径插入回路中，最终得到欧拉回路。

证明：算法保证每条边恰好被访问一次，且由于所有顶点度数均为偶数，算法最终回到起点。$\square$

**引理 3**（字典序最小性）：如果每次从当前顶点选择可用的最小边，最终得到的边序列是字典序最小的。

证明：设 $e_1, e_2, \dots, e_E$ 为最终序列。假设存在另一序列 $f_1, f_2, \dots, f_E$ 字典序更小，则存在最小的 $k$ 使得 $e_k > f_k$。但在构造第 $k$ 步时，$f_k$ 是可用的且比 $e_k$ 小，算法应选择 $f_k$，矛盾。$\square$

---

## 参考代码

```cpp
// John's Trip
// UVa ID: 302
// Verdict: Accepted
// Submission Date: 2016-07-02
// UVa Run Time: 0.020s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int to, street;
    // 按街道编号排序，用于 multiset 自动排序
    bool operator<(const edge & another) const
    {
        return street < another.street;
    }
};

int x, y, z, start;
map<int, multiset<edge>> adjacentEdges;  // 邻接表，按街道编号自动排序
vector<bool> traveled(2000);             // 标记边是否已访问
vector<int> trip;                        // 存储欧拉回路的边序列

// Hierholzer 算法递归实现
// 参数 vertex: 当前访问的顶点
void euler(int vertex)
{
    // 遍历当前顶点的所有邻接边（按街道编号升序）
    for (auto e : adjacentEdges[vertex])
        if (!traveled[e.street])         // 如果边未被访问
        {
            traveled[e.street] = true;   // 标记为已访问
            euler(e.to);                 // 递归访问另一端顶点
            trip.insert(trip.begin(), e.street);  // 将边插入到序列开头
        }
}

// 寻找并输出欧拉回路
void findEulerCircuit()
{
    // 检查所有顶点的度数是否为偶数
    for (auto element : adjacentEdges)
        if (element.second.size() % 2 == 1)  // 存在奇度数顶点
        {
            cout << "Round trip does not exist." << endl << endl;
            return;
        }

    // 重置访问标记和结果序列
    fill(traveled.begin(), traveled.end(), false);
    trip.clear();

    // 从起点开始寻找欧拉回路
    euler(start);

    // 输出边序列
    for (int i = 0; i < trip.size(); i++)
        if (i > 0)
            cout << " " << trip[i];
        else
            cout << trip[i];
    cout << endl << endl;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int dataItems = 0;
    while (cin >> x >> y)
    {
        // 遇到 0 0 表示一个数据块的结束
        if (x == 0 && y == 0)
        {
            // 如果还没有读取任何边，则整个输入结束
            if (dataItems == 0)
                break;

            // 处理当前数据块
            findEulerCircuit();

            // 清空数据结构，准备处理下一个数据块
            adjacentEdges.clear();
            dataItems = 0;
            continue;
        }

        // 读取街道编号
        cin >> z;
        
        // 添加双向边
        adjacentEdges[x].insert((edge){y, z});
        adjacentEdges[y].insert((edge){x, z});

        // 记录起点：第一组输入中编号较小的路口
        if (++dataItems == 1)
            start = min(x, y);
    }

    return 0;
}
```

---

## 总结

本题的核心在于：
1. **识别问题类型**：欧拉回路
2. **存在性判断**：所有顶点度数均为偶数
3. **字典序最小**：使用 `multiset` 按街道编号排序
4. **算法实现**：$\texttt{Hierholzer}$ 算法的递归版本

### 关键点回顾

| 知识点 | 说明 |
|--------|------|
| 欧拉回路存在条件 | 无向连通图所有顶点度数均为偶数 |
| 字典序最小 | 每次选择编号最小的可用边 |
| 数据结构 | `map<int, multiset<edge>>` |
| 算法 | $\texttt{Hierholzer}$ 算法 |
| 起点确定 | 第一组输入中编号较小的路口 |
| 输出格式 | 每个数据块输出两行（包含空行） |

### 常见陷阱

1. **输出空行**：每个数据块输出后必须有一个空行（包括最后一个）
2. **起点选择**：起点不是固定为 $1$，而是第一组输入中较小的路口
3. **多重边**：两个路口之间可能有多条不同编号的街道，需要使用 `multiset`
4. **递归深度**：边数最多 $1994$，递归深度安全

这种“欧拉回路 + 字典序最小”的解题模式，在图论问题中具有典型性和实用性。
