[UVa 388 Galactic Import](https://blog.csdn.net/metaphysis/article/details/161673665)

## 题目描述

随着新型 $\texttt{Thrust Zoom}$ 超空间驱动器的引入，$\texttt{Hyper Commodities}$（一家新泽西州的进出口企业集团）开始与宇宙中最遥远的星系进行贸易。$\texttt{Hyper Commodities}$ 希望从 $\texttt{Plural Z}$ 星系的某些星系进口商品。

已知事实：
- 每个星系包含 $1$ 到 $26$ 颗行星
- 每颗行星用一个字母 $A \sim Z$ 标识
- 每颗行星专门生产和出口一种商品，同一星系内不同行星出口不同商品
- 某些行星之间有超空间航线相连，可以自由贸易
- 如果两颗行星通过中间行星间接相连，每经过一个中间行星，中间行星会收取 $5\%$ 的运输费（即货物只留下 $95\%$）
- 每个星系至少有一颗行星愿意开设通往地球的 $\texttt{Thrust Zoom}$ 航线
- 每颗行星的出口商品有一个相对价值（小于 $10$ 的正实数）

问题：考虑运输费用后，哪颗行星的出口价值最高？

### 输入格式

每个星系描述以整数 $N$ 开头（行星数量）。接下来 $N$ 行，每行包含：
1. 行星的字母标识
2. 空格
3. 出口的相对价值（格式 `d.dd`）
4. 空格
5. 一个字符串，包含字母和/或 `*`：字母表示到该行星的航线，`*` 表示愿意开通到地球的 $\texttt{Thrust Zoom}$ 航线

### 输出格式

对于每个星系，输出一行：`Import from X`，其中 $X$ 是价值最高的行星字母。

### 样例输入

```
1
F 0.81 *
5
E 0.01 *A
D 0.01 A*
C 0.01 *A
A 1.00 EDCB
B 0.01 A*
10
S 2.23 Q*
A 9.76 C
K 5.88 MI
E 7.54 GC
M 5.01 OK
G 7.43 IE
I 6.09 KG
C 8.42 EA
O 4.55 QM
Q 3.21 SO
```

### 样例输出

```
Import from F
Import from A
Import from A
```

---

## 题目分析

### 问题的本质

这是一个**带权最短路径**问题。地球可以视为一个特殊节点，与愿意开通 $\texttt{Thrust Zoom}$ 航线的行星直接相连。从地球到某行星的路径上，每经过一个中间行星，货物价值损失 $5\%$。需要找出经过损失后价值最高的行星。

### 数学模型

- 将地球视为节点 $26$（或 $0$，但代码中使用 $26$）
- 每颗行星为一个节点（$0 \sim 25$）
- 航线是无向边
- 从地球到行星 $i$ 的路径长度为 $dist[i]$（经过的边数）
- 地球直接连接的行星 $dist = 1$
- 最终价值 = 原始价值 $\times 0.95^{dist-1}$（因为第一个节点是地球，不需要收费？需要仔细分析）

注意：运输费由中间行星收取。如果地球直接与行星 $K$ 相连，则没有中间行星，货物价值不变。如果经过 $d$ 段航线，则有 $d-1$ 个中间行星，每个收取 $5\%$，因此最终价值 = 原始价值 $\times 0.95^{d-1}$。

### 算法

使用 $\texttt{Dijkstra}$ 或 $\texttt{BFS}$ 计算从地球到所有行星的最短路径（边权均为 $1$），然后计算每个行星的最终价值，取最大值。

---

## 参考代码

```cpp
// Galactic Import
// UVa ID: 388
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

struct edge
{
    int to, weight;
    bool operator<(const edge &another) const
    {
        return weight > another.weight;
    }
};

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n;
    while (cin >> n)
    {
        vector<vector<int>> edges(30);  // 邻接表，26 表示地球
        vector<double> value(30);       // 行星原始价值
        
        char planet;
        string line;

        for (int i = 1; i <= n; i++)
        {
            cin >> planet;
            cin >> value[planet - 'A'];
            cin >> line;
            
            // 添加边
            for (char letter : line)
                if (letter == '*')
                {
                    edges[planet - 'A'].push_back(26);
                    edges[26].push_back(planet - 'A');
                }
                else
                {
                    edges[planet - 'A'].push_back(letter - 'A');
                    edges[letter - 'A'].push_back(planet - 'A');
                }
        }
        
        // Dijkstra 求最短路径（边权为 1）
        vector<int> distances(30, 100000);
        distances[26] = 0;
        priority_queue<edge> unvisited;
        unvisited.push((edge){26, 0});
        
        while (!unvisited.empty())
        {
            edge v = unvisited.top();
            unvisited.pop();

            for (auto e : edges[v.to])
                if (distances[v.to] + 1 < distances[e])
                {
                    distances[e] = distances[v.to] + 1;
                    unvisited.push((edge){e, distances[e]});
                }
        }
        
        // 计算最终价值并找出最大值
        double maxValue = -1.0;
        int import_from = -1;
        for (int i = 0; i <= 25; i++)
            if (distances[i] < 100000)
            {
                // 经过 distances[i] 段航线，有 distances[i]-1 个中间行星
                double finalValue = value[i] * pow(0.95, distances[i] - 1);
                if (finalValue > maxValue)
                {
                    maxValue = finalValue;
                    import_from = i;
                }
            }
            
        cout << "Import from " << (char)('A' + import_from) << endl;
    }
    
    return 0;
}
```
