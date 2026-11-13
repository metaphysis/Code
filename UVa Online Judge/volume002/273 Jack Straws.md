[UVa 273 Jack Straws](https://blog.csdn.net/metaphysis/article/details/161333199)

## 题目分析

本题的题目背景源自一种名为 “$\texttt{Jack Straws}$” 的游戏，玩家需要从桌上一堆杂乱摆放的塑料或木质 “稻草” 中逐根取出，而不扰动其他稻草。本题不关心游戏过程，只关心一个问题：给定若干根稻草（视为二维平面上的线段），以及多组询问 $(a, b)$，判断稻草 $a$ 和稻草 $b$ 是否 “连通”。

“连通” 的定义包含两个层面：

1. **直接连通**：两根稻草在平面上有公共点（即线段相交），此时称它们直接相连。
2. **间接连通**：如果稻草 $a$ 与稻草 $c$ 直接相连，且稻草 $c$ 与稻草 $b$ 直接相连，则 $a$ 与 $b$ 间接连通。连通关系具有传递性。

此外，一根稻草与自身视为连通。

输入格式较为特殊：有多组测试数据，每组数据以 $n$ 开头（$1 < n < 13$），随后 $n$ 行每行给出四个正整数 $x_1, y_1, x_2, y_2$，表示一根稻草的两个端点坐标。接着是多行询问，每行包含两个正整数 $a, b$，以 `0 0` 作为询问结束标志。输出时，每组测试数据之间需要用空行分隔。

## 解题思路

本题的核心可以分解为三个步骤：

1. **判断任意两根稻草是否直接相连**（线段相交判断）。
2. **根据直接相连关系，计算所有稻草之间的连通性**（传递闭包）。
3. **对每个询问，$O(1)$ 时间输出连通性结果**。

### 第一步：线段相交判断

两根稻草在平面上均为线段，我们需要判断它们是否相交。线段相交的情况包括：

- 规范相交：两条线段在内部（非端点）相交。
- 非规范相交：相交于端点，或一条线段端点在另一条线段上。

由于题目保证没有零长度稻草，我们不需要处理退化为点的情况。

判断线段相交的常用方法是 **跨立实验** 结合 **矩形快速排斥**。设线段 $AB$ 和 $CD$，则：

1. **快速排斥**：两个线段的外接矩形必须有重叠，否则不可能相交。这一步可以提前过滤掉明显不相交的情况。在实现中，快速排斥通常被包含在点是否在矩形内的判断中。
2. **跨立实验**：对于线段 $AB$ 和 $CD$，要求点 $C$ 和点 $D$ 位于直线 $AB$ 的两侧，且点 $A$ 和点 $B$ 位于直线 $CD$ 的两侧。用叉积判断方向：

   - $d_1 = \overrightarrow{AB} \times \overrightarrow{AC}$
   - $d_2 = \overrightarrow{AB} \times \overrightarrow{AD}$
   - $d_3 = \overrightarrow{CD} \times \overrightarrow{CA}$
   - $d_4 = \overrightarrow{CD} \times \overrightarrow{CB}$

   如果 $d_1 \cdot d_2 < 0$ 且 $d_3 \cdot d_4 < 0$，则规范相交。
   
3. **端点相交处理**：如果某个叉积为零，说明对应点在另一条线段所在直线上，此时还需用 **点是否在线段上** 判断（即点在矩形范围内）。这是处理非规范相交的关键。

**为什么选择这种方案？**  
$n < 13$ 非常小，即使对所有稻草对进行 $O(n^2)$ 的相交检测也毫无压力。线段相交判断逻辑清晰，且能正确处理端点接触的情况，满足题目 “触碰即连通” 的要求。

### 第二步：传递闭包计算

得到直接相连关系后，我们需要求出连通关系的传递闭包。由于 $n \le 12$，可以用 **$\texttt{Floyd-Warshall}$ 算法** 的变种：

- 将连通性视作 $n \times n$ 的布尔矩阵 `connected[i][j]`。
- 初始化：若线段 $i$ 与线段 $j$ 直接相交（包括 $i=j$），则 `connected[i][j] = true`。
- 三重循环：`for k in [0, n-1]`，`for i in [0, n-1]`，`for j in [0, n-1]`，若 `connected[i][k] && connected[k][j]` 成立，则 `connected[i][j] = true`。

时间复杂度为 $O(n^3)$，$n \le 12$ 时完全可接受。

**为什么不直接 $\texttt{DFS}$ 或 $\texttt{BFS}$？**  
虽然 $n$ 很小，但询问次数未知。预处理出所有对之间的连通性后，每个询问只需 $O(1)$ 输出，效率更高。

### 第三步：处理询问与输出格式

输入询问时，连续读取 $a, b$ 直到遇到 `0 0`。输出时注意：
- 每组测试数据之间有一个空行。
- 第一个测试数据前不输出空行。

## 代码实现

```cpp
// Jack Straws
// UVa ID: 273
// Verdict: Accepted
// Submission Date: 2016-05-15
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 点结构体
struct point
{
    int x, y;
};

// 线段结构体
struct segment
{
    point start, end;
};

// 判断点 p 是否在线段 ab 的包围盒内
bool pointInBox(point p, point a, point b)
{
    return ((p.x >= min(a.x, b.x)) && (p.x <= max(a.x, b.x))
        && (p.y >= min(a.y, b.y)) && (p.y <= max(a.y, b.y)));
}

// 计算叉积：(b - a) × (c - a)
double direction(point a, point b, point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// 判断两条线段是否相交（包括端点接触）
bool segmentsIntersect(segment a, segment b)
{
    double d1, d2, d3, d4;
    
    d1 = direction(a.start, a.end, b.start);
    d2 = direction(a.start, a.end, b.end);
    d3 = direction(b.start, b.end, a.start);
    d4 = direction(b.start, b.end, a.end);
    
    // 规范相交：互相跨立
    if ((d1 * d2 < 0) && (d3 * d4 < 0)) return true;
    // 非规范相交：端点重合或端点在另一线段上
    if (d1 == 0 && pointInBox(b.start, a.start, a.end)) return true;
    if (d2 == 0 && pointInBox(b.end, a.start, a.end)) return true;
    if (d3 == 0 && pointInBox(a.start, b.start, b.end)) return true;
    if (d4 == 0 && pointInBox(a.end, b.start, b.end)) return true;
        
    return false;
}

int main(int argc, char *argv[])
{
    bool first = true;  // 控制输出空行
    int cases;
    cin >> cases;
    
    while (cases--)
    {
        int n, x1, y1, x2, y2;
        cin >> n;
        
        // 存储所有稻草
        vector < segment > segments;
        for (int i = 1; i <= n; i++)
        {
            cin >> x1 >> y1 >> x2 >> y2;
            segments.push_back((segment){(point){x1, y1}, (point){x2, y2}});
        }
        
        // 初始化连通矩阵
        bool connected[13][13];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                connected[i][j] = false;
        
        // 根据线段相交关系填充直接连通性
        for (int i = 0; i < segments.size(); i++)
            for (int j = 0; j < segments.size(); j++)
                if (segmentsIntersect(segments[i], segments[j]))
                    connected[i][j] = true;

        // Floyd-Warshall 求传递闭包
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (connected[i][k] && connected[k][j])
                        connected[i][j] = true;
        
        // 控制两组数据之间的空行
        if (first)
            first = false;
        else
            cout << endl;
            
        // 处理询问
        int a, b;
        while (cin >> a >> b, a && b)
            cout << (connected[a - 1][b - 1] ? "CONNECTED" : "NOT CONNECTED") << endl;
    }
    
	return 0;
}
```

## 总结

本题是一道典型的计算几何与图论结合的题目。核心难点在于正确判断两条线段是否相交（特别是端点接触的情况）。由于数据规模极小，我们可以直接使用 $O(n^3)$ 的 $\texttt{Floyd-Warshall}$ 算法计算传递闭包，从而高效地回答所有连通性询问。解题时注意输出格式，特别是多组数据之间的空行处理。
