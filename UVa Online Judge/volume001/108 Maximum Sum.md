
> **摘要**：本文讲解经典的最大子矩形和问题。给定一个 $N \times N$（$N \leq 100$）的整数矩阵，要求找出元素和最大的子矩形。文章从一维最大子段和出发，介绍通过二维前缀和（优势矩阵）实现 $O(1)$ 子矩形求和、再枚举所有子矩形求最大值的 $O(N^4)$ 解法，并给出完整的代码实现、复杂度分析与边界处理要点。

## 题目描述

给定一个 $N \times N$ 的二维整数数组（包含正数和负数），要求找出一个子矩形（连续的子数组，大小至少为 $1 \times 1$），使得该子矩形内所有元素的和最大。输出这个最大的和。

**输入格式：**

- 第一行是一个正整数 $N$（$N \leq 100$），表示二维数组的大小。
- 接下来 $N^2$ 个整数，以**行主序**（先第一行从左到右，再第二行，依此类推）给出数组元素，整数之间以空格或换行分隔。每个整数的取值范围为 $[-127, 127]$。

**输出格式：**

- 一个整数，表示最大子矩形的和。

**示例输入：**

```text
4
0 -2 -7 0
9 2 -6 2
-4 1 -4 1
-1 8 0 -2
```

**示例输出：**

```text
15
```

## 题目分析

这是一个经典的**最大子矩形和**问题，是**最大子段和**（一维）问题的二维推广。在一维情况下，我们可以用 $\texttt{Kadane}$ 算法在 $O(n)$ 时间内求解。但在二维中，如果直接枚举所有可能的子矩形，时间复杂度将高达 $O(N^4)$（$N$ 最大为 $100$，可能勉强可接受，但通常需要优化）。

本题的关键在于**降维**：我们可以通过预处理得到一个**二维前缀和**数组，从而在 $O(1)$ 时间内计算任意子矩形的和。具体步骤如下：

1. **构建二维前缀和数组 `dominance[i][j]`**：
   - `dominance[i][j]` 表示原数组从 $(0,0)$ 到 $(i,j)$ 所围成的矩形区域的所有元素之和。
   - 递推公式（需注意边界）：
     $$
     dominance[i][j] = grid[i][j] + dominance[i-1][j] + dominance[i][j-1] - dominance[i-1][j-1]
     $$

2. **枚举所有子矩形**：
   - 用四重循环枚举子矩形的左上角 $(i,j)$ 和右下角 $(k,l)$。
   - 利用前缀和快速计算该子矩形的和：
     $$
     sum = dominance[k][l] - dominance[i-1][l] - dominance[k][j-1] + dominance[i-1][j-1]
     $$
   - 更新最大和。

这样，总时间复杂度为 $O(N^4)$，但在 $N \leq 100$ 的情况下可以接受（$100^4 = 10^8$ 次运算，在合理优化和现代计算机上通常能在规定时间内完成）。

## 解题思路

1. **读入数据**：读入 $N$ 和 $N \times N$ 的矩阵。
2. **构建二维前缀和矩阵**：
   - 使用 `dominance` 数组存储前缀和，注意处理边界条件。
3. **枚举所有可能的子矩形**：
   - 左上角 $(i,j)$，右下角 $(k,l)$。
   - 利用前缀和公式计算子矩形和，并记录最大值。
4. **输出最大值**。

## 代码实现

```cpp
// Maximum Sum
// UVa ID: 108
// Verdict: Accepted
// Submission Date: 2011-11-23
// UVa Run Time: 0.112s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 110
int grid[MAXN][MAXN], dominance[MAXN][MAXN], n;

int main () {
	while (cin >> n) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> grid[i][j];

		// 行优先建立优势矩阵。
		memset(dominance, 0, sizeof(dominance));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				dominance[i][j] += grid[i][j];
				if (i > 0) dominance[i][j] += dominance[i - 1][j];				
				if (j > 0) dominance[i][j] += dominance[i][j - 1];
				if (i > 0 && j > 0) dominance[i][j] -= dominance[i - 1][j - 1];
			}

		// 利用正交范围查询找最大和。
		int maxSum = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				for (int k = i; k < n; k++)
					for (int l = j; l < n; l++) {
						int tmpSum = dominance[k][l];
						if (i > 0) tmpSum -= dominance[i - 1][l];
						if (j > 0) tmpSum -= dominance[k][j - 1];
						if (i > 0 && j > 0) tmpSum += dominance[i - 1][j - 1];
						maxSum = max(maxSum, tmpSum);
					}

		cout << maxSum << endl;
	}
	return 0;
}
```

## 复杂度分析

- **时间复杂度**：$O(N^4)$，其中 $N$ 为矩阵边长。由于 $N \leq 100$，最坏情况下 $10^8$ 次操作，在优化良好的情况下可以接受。
- **空间复杂度**：$O(N^2)$，用于存储原矩阵和前缀和矩阵。

## 总结

本题是一个典型的二维前缀和应用问题，通过预处理将子矩形和的查询降至 $O(1)$，再通过枚举所有子矩形得到最大和。虽然时间复杂度较高，但在题目给定的数据范围内是可行的。在实际编程中，应注意前缀和的计算公式和边界处理，避免出现数组越界或计算错误。
