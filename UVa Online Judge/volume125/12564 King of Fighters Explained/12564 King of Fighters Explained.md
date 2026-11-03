
> **摘要**：本题以格斗游戏《拳皇》的判定模型为背景，将每个角色的攻击区域与弱点区域抽象为若干矩形的并集。核心任务是判断一方的攻击区域与另一方的弱点区域是否存在**正面积**交集，从而确定双方是否被击中。由于每个区域最多包含 5 个矩形，只需枚举至多 25 对矩形，用严格不等式判定二维重叠即可，时间复杂度为 $O(1)$ 量级。本文给出完整的题意分析、几何判定推导、算法步骤与 C++ 实现。

## 题目描述

$\texttt{King of Fighters}$（$\texttt{KOF}$）的格斗判定模型可抽象为：每个角色在每一帧具有攻击区域（由若干矩形并集构成）和弱点区域（由若干矩形并集构成）。若一方的攻击区域与另一方的弱点区域存在**正面积**交集，则后者受到攻击。双方可能同时被击中。

给定两个角色的攻击区域与弱点区域（矩形坐标均为整数，且 $0 \le x_1 < x_2 \le 100$，$0 \le y_1 < y_2 \le 100$），判断命中情况。

## 输入格式

第一行包含测试用例数 $T$（$T \le 100$）。  
每个测试用例包含两个部分，格式相同，分别描述第一个角色和第二个角色。  
每部分的第一行包含两个整数 $a$ 和 $w$（$0 \le a, w \le 5$），分别表示攻击区域和弱点区域中矩形的个数。  
随后 $a$ 行，每行四个非负整数 $x_1, y_1, x_2, y_2$，表示该矩形包含所有满足 $x_1 \le x \le x_2$ 且 $y_1 \le y \le y_2$ 的点。  
接下来 $w$ 行以相同格式描述弱点区域。

## 输出格式

对于每个测试用例，输出一行 `Case X: result`，其中 $X$ 为用例编号（从 $1$ 开始），`result` 为以下之一：

- `First`：仅第一个角色被击中；
- `Second`：仅第二个角色被击中；
- `Both`：双方均被击中；
- `Neither`：双方均未被击中。

## 样例

输入

```
3
1 1
2 2
5 3
0 0 2 4
0 1 4 0
6 4 3 1
1 2 2 4
1 0 2 4
1 2 5 4
0 1 4 4
3 5 4 0
5 5 0 2
2 4 1 0
2 3 0 2
1 4 2 3
5 4 2 1
4 3 0 0
5 4 0 1
1 3 0 0
5 1 0 2
4 3 2 1
3 3 1 4
5 5 0 3
3 5 0 0
4 5 1 1
4 5
```

输出

```
Case 1: Second
Case 2: Both
Case 3: Neither
```

## 题目分析

题中明确给出两个角色的攻击区域和弱点区域，且每个区域均由若干矩形（可能相交）的并集表示。由于两个区域均为闭矩形集，判断两个区域是否有交集，只需检查是否存在一对矩形（一个来自攻击区域，一个来自弱点区域），它们的交集面积大于 $0$。

两个矩形 $R_1 = [x_{1,1}, x_{1,2}] \times [y_{1,1}, y_{1,2}]$ 与 $R_2 = [x_{2,1}, x_{2,2}] \times [y_{2,1}, y_{2,2}]$ 有正面积交集，当且仅当它们在 $x$ 方向和 $y$ 方向上的区间均有正长度重叠，即

$$
x_{1,1} < x_{2,2} \quad \text{且} \quad x_{2,1} < x_{1,2} \quad \text{且} \quad y_{1,1} < y_{2,2} \quad \text{且} \quad y_{2,1} < y_{1,2}.
$$

此条件严格保证交集为二维区域（面积大于 $0$）。若仅边界接触（例如 $x_{1,2} = x_{2,1}$），则交集面积为零，不构成命中，因此必须使用严格不等式。

命中判定分为两个方向：

- 若第二个角色的**攻击区域**与第一个角色的**弱点区域**有重叠，则第一个角色被击中。
- 若第一个角色的**攻击区域**与第二个角色的**弱点区域**有重叠，则第二个角色被击中。

双方可能同时满足这两个条件。

## 解题思路

由于每个区域最多包含 $5$ 个矩形，区域间判定只需枚举矩形对，最多 $5 \times 5 = 25$ 对，计算量极小。因此直接暴力枚举即可。

算法步骤：

1. 定义矩形结构体，包含 $x_1, y_1, x_2, y_2$。
2. 实现辅助函数 $\texttt{isOverlap}(a, b)$，利用上述严格不等式判定两个矩形是否有正面积交集。
3. 对于每个测试用例：
   - 分别读入角色 $1$ 的攻击矩形列表 $\textit{att}_1$ 和弱点矩形列表 $\textit{weak}_1$。
   - 分别读入角色 $2$ 的攻击矩形列表 $\textit{att}_2$ 和弱点矩形列表 $\textit{weak}_2$。
   - 判定 $\textit{hitFirst} = \texttt{hasHit}(\textit{att}_2, \textit{weak}_1)$，即角色 $2$ 攻击是否命中角色 $1$。
   - 判定 $\textit{hitSecond} = \texttt{hasHit}(\textit{att}_1, \textit{weak}_2)$，即角色 $1$ 攻击是否命中角色 $2$。
   - 根据 $\textit{hitFirst}$ 和 $\textit{hitSecond}$ 输出对应结果。

其中 $\texttt{hasHit}(A, W)$ 遍历 $A$ 中的所有攻击矩形和 $W$ 中的所有弱点矩形，若存在一对满足 $\texttt{isOverlap}$ 则返回 $\texttt{true}$，否则返回 $\texttt{false}$。

此方法直接反映题意，无需任何优化或复杂数据结构。

## 复杂度分析

- 每个测试用例中，每个方向的矩形对数量最多 $a \times w \le 25$，判定常数时间。
- 总时间复杂度 $O(T \cdot 25)$，即 $O(1)$ 量级。
- 空间复杂度 $O(1)$。

## 代码实现

```cpp
// King of Fighters Explained
// UVa ID: 12564
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int x1, y1, x2, y2;
};

bool isOverlap(const Rect& a, const Rect& b) {
    return a.x1 < b.x2 && b.x1 < a.x2 && a.y1 < b.y2 && b.y1 < a.y2;
}

bool hasHit(const vector<Rect>& att, const vector<Rect>& weak) {
    for (const Rect& a : att)
        for (const Rect& w : weak)
            if (isOverlap(a, w)) return true;
    return false;
}

int main() {
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int a1, w1;
        cin >> a1 >> w1;
        vector<Rect> att1(a1), weak1(w1);
        for (int i = 0; i < a1; ++i) cin >> att1[i].x1 >> att1[i].y1 >> att1[i].x2 >> att1[i].y2;
        for (int i = 0; i < w1; ++i) cin >> weak1[i].x1 >> weak1[i].y1 >> weak1[i].x2 >> weak1[i].y2;

        int a2, w2;
        cin >> a2 >> w2;
        vector<Rect> att2(a2), weak2(w2);
        for (int i = 0; i < a2; ++i) cin >> att2[i].x1 >> att2[i].y1 >> att2[i].x2 >> att2[i].y2;
        for (int i = 0; i < w2; ++i) cin >> weak2[i].x1 >> weak2[i].y1 >> weak2[i].x2 >> weak2[i].y2;

        bool hitFirst  = hasHit(att2, weak1);
        bool hitSecond = hasHit(att1, weak2);

        string result;
        if (hitFirst && hitSecond) result = "Both";
        else if (hitFirst)         result = "First";
        else if (hitSecond)        result = "Second";
        else                       result = "Neither";

        cout << "Case " << caseNo << ": " << result << '\n';
    }
    return 0;
}
```

## 总结

本题核心在于准确理解“区域交集”的几何意义：必须存在正面积重叠，而非仅接触。由于矩形数量极少，枚举所有矩形对即可高效解决问题。该思路体现了将复杂规则转化为基础几何判定的通用方法，同时严格使用不等式避免了边界情况的误判。
