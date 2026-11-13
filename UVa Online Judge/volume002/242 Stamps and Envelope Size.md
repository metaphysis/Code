[UVa 242 Stamps and Envelope Size](https://blog.csdn.net/metaphysis/article/details/161246240)

## 题目分析
### 题目背景

邮局希望用有限的邮票面额和有限的最大贴邮票数量，尽可能连续地覆盖邮资。具体来说：

- 一个信封最多可以贴 $S$ 张邮票。
- 有若干组邮票面额集合（每组面额已从小到大排序）。
- 对于每组面额，需要找出在不超过 $S$ 张邮票的条件下，**从 $1$ 开始连续能覆盖的最大邮资**。
- 从所有面额集合中，选出能使该连续覆盖值最大的集合。若有多个，则按以下规则依次比较：
  1. 集合中面额种类数更少的更优；
  2. 种类数相同时，最大面额更小的更优；
  3. 最大面额也相同时，比较次大面额，以此类推。

### 输入格式

- 多组数据，每组数据：
  - 第一行：$S$（信封最多能贴的邮票张数）。
  - 第二行：$N$（面额集合的数量）。
  - 接下来 $N$ 行：每行第一个整数 $D$ 表示该集合的面额个数，随后 $D$ 个整数表示具体面额（递增）。
- 输入以 $S = 0$ 结束。

### 输出格式

对于每组数据，输出：

```
max coverage = <值> : <面额列表>
```

其中面额之间空格隔开，宽度为 $3$（右对齐）。

---

## 解题思路

### 核心问题

对于一组给定的邮票面额（比如 $1, 4, 12, 21$）和最大允许邮票数 $S$，如何快速求出它能连续覆盖的最大邮资？

### 动态规划判定法

我们可以用 **$\texttt{DP}$ 模拟邮票的加法组合**：

- 定义 `value[j][k]` 表示**使用恰好 $j$ 张邮票能否凑出邮资 $k$**。
- 初始状态：`value[0][0] = true`（$0$ 张邮票，$0$ 邮资）。
- 转移方程：
  $$
  \text{value}[j][k] = \text{true} \quad \text{if} \quad \exists m \in \text{denominations}, \ \text{value}[j-1][k - m] = \text{true}
  $$
  且 $k - m \ge 0$。

- 实现时，由于 $S \le 10$，面额 $\le 100$，$k$ 的范围最多到 $S \times 100 = 1000$，因此二维数组大小 `[11][1001]` 完全可行。

### 优化空间与思路

题目代码中用一个 `appeared` 数组记录**是否能在不超过 $S$ 张邮票的情况下凑出某个邮资**：

- 每当 `value[j][k]` 为真时，就标记 `appeared[k] = 1`。
- 最后从 $1$ 开始扫描 `appeared`，第一个缺失的位置 `index` 就表示**无法连续覆盖到该值**，因此最大连续覆盖值为 `index - 1`。

### 多组比较

对于每组面额集合，我们计算它的最大连续覆盖值 `maxCover`，然后与当前最优比较：

1. 如果 `maxCover > bestCover`，则更新最优集合。
2. 如果 `maxCover == bestCover`，则比较面额个数：个数少的更优。
3. 如果个数也相等，则从大到小依次比较面额值，找到第一个不同的位置，选择面额更小的。

### 输入结束条件

当 $S = 0$ 时，输入结束。

---

## 算法复杂度

- 每组面额集合的 DP 复杂度：$O(S \times \text{最大邮资} \times D)$，其中最大邮资 $\le 1000$，$S \le 10$，$D \le S$，因此非常快。
- 总体复杂度可以轻松处理题目中的 $N \le 10$。

---

## 代码实现

```cpp
// Stamps and Envelope Size
// UVa ID: 242
// Verdict: Accepted
// Submission Date: 2016-05-15
// UVa Run Time: 0.040s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// value[j][k]: 使用恰好 j 张邮票能否凑出邮资 k
int value[11][1001], denomination[11], appeared[1010];
int best[11], bestD;  // best 存储当前最优面额集合，bestD 为面额个数

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int S;
    while (cin >> S, S)  // 输入 S，若 S == 0 则结束
    {
        int N;
        cin >> N;
        
        int maxValue = 0;      // 当前最大连续覆盖值
        bestD = 11;            // 初始化为较大值，便于比较
        
        for (int i = 1; i <= N; i++)
        {
            int D;
            cin >> D;
            
            // 读入当前集合的面额
            for (int j = 0; j < D; j++)
                cin >> denomination[j];
            
            // 初始化 DP 数组和 appeared 数组
            memset(value, 0, sizeof(value));
            memset(appeared, 0, sizeof(appeared));
            
            // 边界：0 张邮票凑出 0 邮资
            value[0][0] = 1;
            
            // DP 过程：枚举邮票张数，枚举已有邮资，枚举面额
            for (int j = 1; j <= S; j++)               // 邮票张数
                for (int k = 0; k < 1001; k++)         // 当前邮资
                    if (value[j - 1][k])               // 若上一步可凑出 k
                        for (int m = 0; m < D; m++)   // 尝试加一张面额
                        {
                            int nextValue = k + denomination[m];
                            if (nextValue <= 1000)
                            {
                                value[j][nextValue] = 1;
                                appeared[nextValue] = 1;
                            }
                        }
            
            // 找到第一个不能连续覆盖的邮资
            int index;
            for (index = 1; index < 1010; index++)
                if (appeared[index] == 0)
                    break;
            index--;  // 最大连续覆盖值
            
            // 根据规则选择最优集合
            if (index > maxValue)  // 覆盖值更大
            {
                maxValue = index;
                bestD = D;
                for (int i = 0; i < D; i++)
                    best[i] = denomination[i];
            }
            else if (index == maxValue && D < bestD)  // 覆盖值相同，但面额种类更少
            {
                bestD = D;
                for (int j = 0; j < D; j++)
                    best[j] = denomination[j];
            }
            else if (index == maxValue && D == bestD)  // 覆盖值和种类数相同，按面额从大到小比较
            {
                for (int j = D - 1; j >= 0; j--)
                {
                    if (denomination[j] > best[j])
                        break;
                    if (denomination[j] == best[j])
                        continue;
                    // 当前集合更优
                    for (int k = 0; k < D; k++)
                        best[k] = denomination[k];
                    break;
                }
            }
        }
        
        // 输出结果，宽度控制与样例一致
        cout << "max coverage =" << setw(4) << right << maxValue << " :";
        for (int i = 0; i < bestD; i++)
            cout << setw(3) << right << best[i];
        cout << endl;
    }
    
    return 0;
}
```

---

## 总结

本题的核心是**用动态规划判断邮票面额组合的连续覆盖能力**，然后根据题目给定的三个比较规则选出最优解。代码中使用二维 $\texttt{DP}$ 记录每种邮票张数下的可达邮资，并通过 `appeared` 数组简化后续扫描。虽然题目数据较小，但思路清晰，非常适合作为 $\texttt{DP}$ 入门到进阶的练习。
