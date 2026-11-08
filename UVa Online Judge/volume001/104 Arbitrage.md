
> **摘要**：本文讲解 UVa 104「套汇（Arbitrage）」问题，将货币兑换抽象为有向图，把套汇转化为寻找长度不超过 $n$、边权乘积大于 $1.01$ 的最短环。文章给出基于动态规划的状态定义 $dp[i][j][k]$、状态转移方程、终止条件与路径回溯方法，分析 $O(n^4)$ 的复杂度，并附上完整 C++ 实现代码。

## 题目描述
套汇是指利用不同货币之间的汇率差异，通过一系列货币兑换操作，最终换回起始货币并获得利润的交易策略。例如，若 $1$ 美元可兑换 $0.7$ 英镑，$1$ 英镑可兑换 $9.5$ 法郎，$1$ 法郎可兑换 $0.16$ 美元，则从 $1$ 美元出发，经过上述兑换后可获得 $1 \times 0.7 \times 9.5 \times 0.16 = 1.064$ 美元，利润为 $6.4\%$。

题目要求：给定一个 $n \times n$ 的汇率表，其中 `profit[i][j]` 表示 $1$ 单位的货币 $i$ 可兑换多少单位的货币 $j$。判断是否存在一个长度不超过 $n$ 的兑换序列（允许从任意货币开始），使得从该货币出发，经过一系列兑换后回到该货币，且最终金额超过初始金额的 $1\%$（即利润大于 $0.01$）。若存在，输出一个最短的这样的序列（如果存在多个最短序列，输出任意一个）；否则输出 `no arbitrage sequence exists`。

## 输入格式
输入包含多个汇率表。每个表以整数 $n$ 开始，表示汇率表的维度（$2 \leq n \leq 20$）。接下来 $n$ 行，每行包含 $n-1$ 个实数，表示汇率表（对角元素为 $1.0$ 但未显式给出）。

## 输出格式
对于每个表，若存在满足条件的套汇序列，则输出该序列（序列以起始货币编号开始，以该编号结束）；否则输出 `no arbitrage sequence exists`。

## 样例输入

```text
3
1.2 .89
.88 5.1
1.1 0.15
4
3.1  0.0023  0.35
0.21  0.00353  8.13
200   180.559  10.339
2.11  0.089  0.06111
2
2.0
0.45
```
## 样例输出
```text
1 2 1
1 2 4 1
no arbitrage sequence exists
```

---

## 题目分析与解题思路

### 问题本质
本题可以转化为图论问题：将每种货币视为图中的一个顶点，从货币 $i$ 到货币 $j$ 的兑换汇率视为一条有向边的权值。我们需要找到一个 **长度不超过 $n$ 的环**，使得环上各边权值的乘积大于 $1.01$。

若存在这样的环，则可以通过在该环上不断循环兑换获得利润。题目要求输出 **最短** 的满足条件的环（即边数最少）。

### 动态规划建模
定义状态：
- $dp[i][j][k]$ 表示从货币 $i$ 出发，经过 **恰好 $k$ 步** 到达货币 $j$ 所能获得的最大利润。
- $path[i][j][k]$ 记录在状态 $dp[i][j][k]$ 下，从 $i$ 到 $j$ 的路径中第 $k-1$ 步经过的中间货币（用于回溯路径）。

#### 状态转移方程
对于 $k \geq 2$，我们可以枚举中间货币 $m$：
$$
dp[i][j][k] = \max_{1 \leq m \leq n} \{ dp[i][m][k-1] \times dp[m][j][1] \}
$$
其中 $dp[m][j][1]$ 即为直接从 $m$ 兑换到 $j$ 的汇率（即输入给出的值）。

**初始化**：
- $dp[i][i][1] = 1.0$（表示从 $i$ 到 $i$ 经过 $1$ 步的利润为 $1$，即不兑换）。
- 对于 $i \neq j$，$dp[i][j][1]$ 直接读入输入汇率。

#### 终止条件
当 $dp[i][i][k] > 1.01$ 时，说明存在一个从 $i$ 出发回到 $i$ 的长度为 $k$ 的环，且利润超过 $1\%$。由于我们按 $k$ 从小到大递推，因此第一次找到满足条件的环即为最短环。

#### 路径回溯
在状态转移时，同时记录 $path[i][j][k] = m$，表示在 $dp[i][j][k]$ 的最优解中，最后一步是从 $m$ 到 $j$。通过递归回溯即可得到完整路径。

### 算法复杂度
- 状态数：$O(n^3)$（$i, j, k$ 各 $n$ 种）。
- 转移枚举中间点 $m$：$O(n)$。
- 总复杂度：$O(n^4)$，对于 $n \leq 20$ 完全可行。


## 代码实现

```cpp
// Arbitrage
// UVa ID: 104
// Verdict: Accepted
// Submission Date: 2011-12-22
// UVa Run Time: 0.068s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 20

double profit[MAXN + 1][MAXN + 1][MAXN + 1];
int memo[MAXN + 1][MAXN + 1][MAXN + 1];
int n;

void output(int start, int end, int step) {
	if (step >= 2) {
		output(start, memo[start][end][step], step - 1);
		cout << " " << memo[start][end][step];
	}
}

int main() {
	while (cin >> n) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					profit[i][j][k] = 0.0;

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i == j) {
					profit[i][j][1] = 1;
					memo[i][j][1] = i;
				} else {
					cin >> profit[i][j][1];
					memo[i][j][1] = i;
				}

		int start, steps;
		bool arbitrage = false;

		for (int step = 2; step <= n; step++)
			for (int k = 1; k <= n; k++)
				for (int i = 1; i <= n; i++)
					for (int j = 1; j <= n; j++) {
						double temp = profit[i][k][step - 1] * profit[k][j][1];
						if (temp > profit[i][j][step]) {
							profit[i][j][step] = temp;
							memo[i][j][step] = k;

							if (i == j && profit[i][j][step] > 1.01) {
								arbitrage = true;
								start = i;
								steps = step;
								goto out;
							}
						}
					}

        out:
		if (arbitrage) {
			cout << start;
			output(start, start, steps);
			cout << " " << start << endl;		
		} else cout << "no arbitrage sequence exists" << endl;
	}
	return 0;
}
```
## 总结
本题是一道典型的 **动态规划求最短环** 问题，通过定义 $dp[i][j][k]$ 表示 $i$ 到 $j$ 经过 $k$ 步的最大利润，并利用类似 $\texttt{Floyd-Warshall}$ 的递推方式，可以在 $O(n^4)$ 时间内求解。注意：
- 利润是 **乘积** 而非加和。
- 需要记录路径以便输出。
- 判断利润是否超过 $1.01$ 而非 $1.0$。
