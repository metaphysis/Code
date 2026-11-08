
> **摘要**：本文讨论玻璃瓶回收的装箱问题——将三个桶中的棕色、绿色、透明三种瓶子重新分配，使每个桶只装一种颜色且移动瓶子数最少。由于颜色与桶的对应关系仅有 $3! = 6$ 种排列，算法通过枚举全部方案、以「总瓶数减去无需移动的瓶数」计算移动量，并在移动数相同时取字典序最小的方案，时间复杂度与空间复杂度均为 $O(1)$。文中给出完整 $\texttt{C++}$ 实现与复杂度分析。

## 题目描述

本题是一个关于玻璃瓶回收的装箱问题。我们有三个垃圾桶，每个桶内装有三种颜色的玻璃瓶：棕色（$\texttt{Brown}$）、绿色（$\texttt{Green}$）和透明（$\texttt{Clear}$）。为了便于回收，需要将瓶子重新分配，使得每个桶只包含一种颜色的瓶子。目标是通过移动最少数量的瓶子来实现这一要求。

输入包含多行数据，每行有9个整数，分别表示三个桶中棕色、绿色和透明瓶子的数量。例如，输入行：

```text
10 15 20 30 12 8 15 8 31
```

表示：
- 桶 $1$：$10$ 个棕色、$15$ 个绿色、$20$ 个透明
- 桶 $2$：$30$ 个棕色、$12$ 个绿色、$8$ 个透明
- 桶 $3$：$15$ 个棕色、$8$ 个绿色、$31$ 个透明

输出应包含一个由三个大写字母组成的字符串（`B`、`G`、`C`），表示每个桶最终分配的颜色，以及所需移动的最小瓶子数量。如果有多个方案移动数量相同，则输出字典序最小的字符串。

## 解题思路

### 问题分析

我们需要将三个桶中的瓶子重新分配，使得每个桶只包含一种颜色，且移动的瓶子数量最少。由于只有三种颜色和三个桶，可能的分配方案是有限的。具体来说，颜色的排列共有 $3! = 6$ 种可能。

### 关键点

1. **颜色排列**：六种可能的颜色分配顺序为：`BCG`、`BGC`、`CBG`、`CGB`、`GBC`、`GCB`。
2. **移动计算**：对于每种颜色分配，计算需要移动的瓶子数量。总移动数等于总瓶子数减去不需要移动的瓶子数（即每个桶中与分配颜色相同的瓶子数）。
3. **字典序处理**：由于六种排列已经按字典序排列，我们只需按顺序检查，并选择移动数最小的第一个方案即可。

### 算法步骤

1. 读取输入数据，存储每个桶中各种颜色的瓶子数量，并计算总瓶子数。
2. 枚举六种颜色分配方案，对每种方案计算需要移动的瓶子数量。
3. 选择移动数最小的方案，如果有多个方案移动数相同，选择字典序最小的。
4. 输出结果。

### 复杂度分析

- 时间复杂度：$O(1)$，因为只有六种排列需要检查。
- 空间复杂度：$O(1)$，只需固定大小的数组存储数据。

## 代码实现

```cpp
// Ecological Bin Packing
// Verdict: Accepted
// Submission Date: 2011-10-16
// UVa Run Time: 0.164s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
 
#include <bits/stdc++.h>
 
using namespace std;
 
#define MAXN 3
#define MAXTYPES 6
 
int bottles[MAXN][MAXN], total;
string sequences[MAXTYPES] = { "132", "123", "312", "321", "213", "231" };
string bins[MAXTYPES] = { "BCG", "BGC", "CBG", "CGB", "GBC", "GCB" };
 
int move(string sequence) {
	int movements = total;
	for (int i = 0; i < sequence.length(); i++)
		for (int j = 0; j < MAXN; j++)
			if (j == i)
				movements -= bottles[j][sequence[i] - '1'];
	return movements;
}
 
int main(int ac, char *av[]) {
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
 		total = 0;
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++) {
				iss >> bottles[i][j];
				total += bottles[i][j];
			}
 		int minimum = total, marker;
		for (int i = 0; i < MAXTYPES; i++) {
			int movements = move(sequences[i]);
			if (minimum > movements) {
				minimum = movements;
				marker = i;
			}
		}
 		cout << bins[marker] << " " << minimum << endl;
	}
 	return 0;
}
```

## 总结

本题通过枚举所有可能的颜色分配方案，并计算每种方案下的移动数量，有效地解决了玻璃瓶回收的装箱问题。由于颜色排列有限，算法效率较高，能够在短时间内处理大量输入数据。
