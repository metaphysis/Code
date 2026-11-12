[UVa 155 All Squares](https://blog.csdn.net/metaphysis/article/details/158571352)

## 题目描述

在一个 $2049 \times 2049$ 的网格上（坐标范围从 $(0,0)$ 到 $(2048,2048)$），我们需要根据给定的规则绘制一系列嵌套的正方形，并计算一个给定点被多少个正方形所包围（包括边界）。

正方形的定义规则如下：
- 最大的正方形大小为 $k$（即边长为 $2k+1$），中心位于网格中心 $(1024,1024)$。
- 允许的正方形大小范围：$1 \leq k \leq 512$。
- 对于大小 $k > 1$ 的正方形，需要在它的四个角上分别放置一个大小为 $\lfloor k/2 \rfloor$ 的正方形。
- 如果一个点位于正方形的边界上，也算作被该正方形包围。

给定 $k$ 值和点的坐标 $(x,y)$，需要计算有多少个正方形包含该点。

## 题目分析与解题思路

### 问题本质理解

这是一个递归生成图形并统计点包含关系的问题。从最大的中心正方形开始，按照规则不断在四个角上生成更小的正方形，直到正方形大小变为 $1$ 为止。整个过程形成了一种**四叉树**的结构。

### 关键点分析

1. **坐标系的设定**：
   - 左上角为 $(0,0)$，右下角为 $(2048,2048)$。
   - 中心点坐标固定为 $(1024,1024)$。

2. **正方形的表示**：
   - 大小为 $k$ 的正方形，边长实际为 $2k+1$。
   - 给定中心点 $(cx,cy)$ 和大小 $k$，正方形的范围是：
     - 左边界：$cx - k$
     - 右边界：$cx + k$
     - 上边界：$cy - k$
     - 下边界：$cy + k$

3. **包含关系的判断**：
   - 点 $(x,y)$ 被正方形包含的条件是：
     $$cx - k \leq x \leq cx + k \quad \text{且} \quad cy - k \leq y \leq cy + k$$
   - 注意边界上的点也算被包含，因此使用 $\leq$ 而非 $<$。

4. **递归生成规则**：
   - 对于大小 $k > 1$ 的正方形，在四个角上生成大小为 $\lfloor k/2 \rfloor$ 的正方形。
   - 四个角的位置分别是：
     - 左上角：$(cx - k, cy - k)$
     - 右上角：$(cx + k, cy - k)$
     - 右下角：$(cx + k, cy + k)$
     - 左下角：$(cx - k, cy + k)$
   - 注意：这里使用的是当前正方形的**边界坐标**作为新正方形的中心点。

### 算法设计

这是一个典型的**深度优先搜索**问题：
1. 从最大的中心正方形开始，判断当前正方形是否包含目标点。
2. 如果包含，计数器加 $1$。
3. 如果当前正方形大小 $k > 1$，则递归处理四个角上的子正方形。
4. 递归结束条件：正方形大小变为 $1$（此时 $k=1$，无法再生成更小的正方形）。

### 复杂度分析

- 每个正方形会生成 $4$ 个子正方形，形成一棵四叉树。
- 树的高度为 $\log_2 k$，总节点数约为 $4^{\log_2 k} = k^2$。
- 对于最大 $k=512$，节点数约为 $512^2 = 262144$，完全可行。
- 每个节点只进行常数次判断操作，因此总时间复杂度为 $O(k^2)$。

### 实现细节

- 使用全局变量记录目标点坐标和计数器。
- 递归函数参数：当前正方形的大小 $k$ 和中心点坐标 $(cx,cy)$。
- 注意 $k$ 的更新：$k = k / 2$（整数除法）。

## 代码实现

```cpp
// All Squares
// UVa ID: 155
// Verdict: Accepted
// Submission Date: 2016-02-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// 题目描述似乎有问题。

#include <bits/stdc++.h>

using namespace std;

int x, y;
int counter;

bool pointInSquare(int centerx, int centery, int size) {
    return (centerx - size <= x) && (x <= centerx + size) 
        && (centery - size <= y) && (y <= centery + size);
}

void generateSquare(int k, int centerx, int centery) {
    int side = k;
    if (pointInSquare(centerx, centery, side)) counter++;

    if (k > 1) {
        k /= 2;
        generateSquare(k, centerx - side, centery - side);
        generateSquare(k, centerx + side, centery - side);
        generateSquare(k, centerx + side, centery + side);
        generateSquare(k, centerx - side, centery + side);
    }
}

int main() {
    int k;
    while (cin >> k >> x >> y, k || x || y) {
        counter = 0;
        generateSquare(k, 1024, 1024);
        cout << setw(3) << right << counter << endl;
    }
	return 0;
}
```

## 示例验证

输入：
```
500 113 941
0 0 0
```

输出：
```
  5
```

输出格式要求右对齐，宽度为 $3$，因此 $5$ 显示为 `  5`。

## 总结

本题通过递归方式构建嵌套正方形，并在构建过程中统计点被包含的次数。理解正方形的定义和递归生成规则是关键。代码实现简洁高效，利用全局变量和递归函数很好地解决了问题。

需要注意的地方：
- 边界上的点也算被包含，判断条件要用 $\leq$。
- 递归时使用当前正方形的边界坐标作为子正方形的中心点。
- 输出格式要求右对齐宽度 $3$，需要使用 $\texttt{setw(3)}$ 控制格式。
