[UVa 278 Chess](https://blog.csdn.net/metaphysis/article/details/161333940)

## 题目分析

本题是一个棋盘上的组合优化问题。给定 $m \times n$ 的棋盘（$4 \leq m, n \leq 10$），要求在棋盘上放置尽可能多的同一类棋子（车、马、后、王），使得任意两个棋子之间无法互相攻击。

题目输入包含多个测试用例，每个用例由一个棋子类型字符和两个整数 $m, n$ 组成。棋子类型的含义为：
- `r`：车（$\texttt{Rook}$）
- `k`：马（$\texttt{Knight}$）
- `Q`：后（$\texttt{Queen}$）
- `K`：王（$\texttt{King}$）

输出为对应棋盘上能放置的最大棋子数量。

## 解题思路

对于四种不同的棋子，我们需要分别推导出最大放置数量的公式。由于棋盘尺寸较小（最大 $10 \times 10$），理论上可以用回溯法或暴力搜索求解，但本题存在简洁的数学解，可以 $O(1)$ 计算。

### 1. 车（$\texttt{Rook}$）

车的攻击方式是水平方向和垂直方向任意格。因此，在 $m \times n$ 的棋盘上，任何两车不能在同一行或同一列。

这等价于在 $m$ 行 $n$ 列中选择若干行和列，每行每列最多放一个车。最大放置数即为 $\min(m, n)$。因为我们可以将车放在一个 $\min(m, n) \times \min(m, n)$ 的子棋盘的对角线上。

**公式**：$ans = \min(m, n)$

### 2. 后（$\texttt{Queen}$）

后的攻击方式结合了车和象的攻击范围（水平、垂直、对角线）。由于后的攻击能力最强，放置后的约束也最严格。实际上，在一个 $m \times n$ 的棋盘上放置互不攻击的后，最大数量等于 $\min(m, n)$。

这是因为后继承了车的行列限制：任意两后不能在同一行或同一列，所以最多只能放 $\min(m, n)$ 个后。而且这个上界是可以达到的（例如放在主对角线上，当 $m = n$ 时是经典八皇后问题的解；当 $m \neq n$ 时，也可以构造出 $\min(m, n)$ 个后的放置方案）。

**公式**：$ans = \min(m, n)$

> 注意：本题中车和后的公式相同，但原因不同——车只受行列约束，后除了行列还受对角线约束，但行列约束已经限制了上界。

### 3. 王（$\texttt{King}$）

王的攻击范围是周围 $8$ 个相邻格（上、下、左、右、四个对角）。要使两王互不攻击，任意两个王之间的曼哈顿距离至少为 $2$ 且切比雪夫距离至少为 $2$。这等价于将棋盘划分成若干个 $2 \times 2$ 的小方块，每个小方块内最多放一个王。

更精确的放置策略是：将王放在所有 $(i, j)$ 满足 $i$ 和 $j$ 都是奇数的格子（假设行列编号从 $1$ 开始）。这样每个王的周围 $8$ 格都是偶数坐标，不会被其他王占据。

- 行方向：可以放置的行的数量为 $\lceil m/2 \rceil$，即 $(m + 1) / 2$（整数除法）
- 列方向：可以放置的列的数量为 $\lceil n/2 \rceil$，即 $(n + 1) / 2$

因此总数为两者乘积。

**公式**：$ans = \left\lceil \frac{m}{2} \right\rceil \times \left\lceil \frac{n}{2} \right\rceil = \frac{m+1}{2} \times \frac{n+1}{2}$（整数除法）

### 4. 马（$\texttt{Knight}$）

马走“日”字形（$2 \times 1$ 或 $1 \times 2$ 的 L 形）。马的攻击范围相对较小，因此可以放置较多的数量。

对于马的放置问题，有一个经典的结论：在一个足够大的棋盘上，可以放置大约一半的格子（交替放置）。具体来说，马的颜色攻击特性是：马总是从黑格跳到白格（或反之）。因此，将棋盘按国际象棋棋盘染色后，马只能攻击异色格。这意味着如果只放置所有同色格子上的马，它们之间一定互不攻击——因为同色格子之间的马步距离总是奇数步？实际上需要更仔细的分析。

标准解法是：棋盘按 $(i + j) \bmod 2$ 染色后，马步会改变颜色。但在同一颜色内放置马，是否一定安全？不一定，因为同色格子之间也可能存在马步距离？实际上两个同色格子的曼哈顿距离是偶数，而马步的曼哈顿距离是 $3$（奇数），所以马步一定连接异色格子。**因此，在同一颜色（例如所有白格）上放置马，任意两个马之间不可能有马步攻击**。所以最大放置数至少是 $\lceil mn/2 \rceil$。

但需要注意边界情况：当棋盘较小时，这个上界是否能达到？对于 $m, n \geq 4$ 的棋盘（题目保证），可以达到 $\lceil mn/2 \rceil$。实际上还有一种更精细的放置策略：当一行长度为偶数时，每行可以放 $m/2$ 个马（交错放置）；当一行长度为奇数时，需要交替减少一个。

代码中的实现采用了两种方向的计算并取最大值，这是因为马的放置模式可以按行交替，也可以按列交替，取较大者。具体分析如下：

- 按行放置：每行放 $\lceil m/2 \rceil$ 个马，但相邻行需要错开。如果 $m$ 是奇数，奇数行放 $\lceil m/2 \rceil$，偶数行放 $\lfloor m/2 \rfloor$。
- 按列放置：同理，每列放 $\lceil n/2 \rceil$ 个马。

对于 $m, n \geq 4$，两种策略的结果可能不同，取最大值即为最优解。实际上对于马来说，标准答案是 $\left\lceil \frac{mn}{2} \right\rceil$，但需要处理 $m = 1$ 或 $n = 1$ 的边界情况。由于题目限定 $m, n \geq 4$，所以 $\left\lceil \frac{mn}{2} \right\rceil$ 总是可达。

代码中的实现是等价但更复杂的形式，本质上是计算两种棋盘方向的“跳棋盘”放置的最大值。

## 算法复杂度

每个测试用例只需要 $O(1)$ 时间计算，总时间复杂度 $O(T)$，其中 $T$ 为测试用例数量。空间复杂度 $O(1)$。

## 代码实现

```cpp
// Chess
// UVa ID: 278
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int getCount(char piece, int m, int n) {
    // Rook（车）：行列约束，最多 min(m, n)
    if (piece == 'r') return min(m, n);
    // Knight（马）：按棋盘染色放置，相当于约一半格子
    // 分别按行方向和列方向计算，取较大值
    if (piece == 'k') {
        int maxCounter = 0, counter = 0, countPerLine = (m + 1) / 2;
        // 策略一：按行放置，奇数行放 countPerLine 个，偶数行放 countPerLine-1 个
        if (m % 2 == 1)         {
            for (int i = 1; i <= n; i++)
                counter += ((i % 2 == 1) ? countPerLine : (countPerLine - 1));
        } else {
            // m 为偶数时每行可以放 countPerLine 个
            for (int i = 1; i <= n; i++)
                counter += countPerLine;
        }
        maxCounter = max(maxCounter, counter);
        // 策略二：按列放置，类似地计算
        counter = 0;
        countPerLine = (n + 1) / 2;
        if (n % 2 == 1) {
            for (int i = 1; i <= m; i++)
                counter += ((i % 2 == 1) ? countPerLine : (countPerLine - 1));
        } else {
            for (int i = 1; i <= m; i++)
                counter += countPerLine;
        }
        maxCounter = max(maxCounter, counter);
        return maxCounter;
    }
    // Queen（后）：行列约束，最多 min(m, n)
    if (piece == 'Q') return min(m, n);
    // King（王）：放在所有 (奇数行, 奇数列) 的格子
    if (piece == 'K') return ((m + 1) / 2) * ((n + 1) / 2);
}

int main() {
    cin.tie(0); cin.sync_with_stdio(false);
    int cases, m, n;
    char piece;
    cin >> cases;
    while (cases--) {
        cin >> piece >> m >> n;
        cout << getCount(piece, m, n) << endl;
    }
    return 0;
}
```

## 总结

本题的关键在于识别每种棋子的攻击模式，并转化为数学模型：
- 车和后受限于行列，答案为 $\min(m, n)$。
- 王受限于 $2 \times 2$ 区域的独立性，答案为 $\lceil m/2 \rceil \times \lceil n/2 \rceil$。
- 马可以利用棋盘染色性质，答案为 $\lceil mn/2 \rceil$（在 $m, n \geq 4$ 时成立）。

上述解法充分利用了组合数学的构造思想，避免了复杂的搜索算法，体现了算法竞赛中“分析问题本质”的重要性。
