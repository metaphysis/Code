
> **摘要**：本文讲解 $\texttt{UVa 101「The Blocks Problem」}$ 的模拟解法。题目要求模拟机器人手臂在 $n$ 个方块上执行 `move`/`pile` 与 `onto`/`over` 组合而成的四种移动命令，并忽略无效指令。文章从题意分析入手，采用二维数组 `state[MAXN][MAXN]` 维护各位置的方块堆栈，配合 `returning` 归位、`findIndex` 定位等关键操作实现四种移动，最终给出时间复杂度 $O(mn)$、空间复杂度 $O(n^2)$ 的完整 $\texttt{C++}$ 代码。

## 题目分析

本题要求模拟一个机器人手臂在方块世界中的操作。初始时有 $n$ 个方块（编号从 $0$ 到 $n-1$），每个方块最初位于对应的位置 $i$ 上。机器人手臂可以执行以下五种命令：

1. `move a onto b`：将方块 $a$ 移动到方块 $b$ 上，在移动之前先将 $a$ 和 $b$ 上面的所有方块归位。
2. `move a over b`：将方块 $a$ 移动到包含 $b$ 的堆栈顶部，在移动之前先将 $a$ 上面的所有方块归位。
3. `pile a onto b`：将 $a$ 及其上面的整个堆栈移动到 $b$ 上，在移动之前先将 $b$ 上面的所有方块归位。
4. `pile a over b`：将 $a$ 及其上面的整个堆栈移动到包含 $b$ 的堆栈顶部。
5. `quit`：终止操作。

**注意**：
- 如果 $a = b$ 或 $a$ 和 $b$ 在同一个堆栈中，则命令无效，应忽略。
- 所有无效命令不影响当前方块配置。

## 解题思路

### 数据结构选择
我们使用一个二维数组 `state[MAXN][MAXN]` 来存储每个位置上的方块堆栈，其中 `state[i]` 表示位置 $i$ 上的方块堆栈，`blocks[i]` 表示位置 $i$ 上的方块数量。

### 关键操作
1. **归位操作（$\texttt{returning}$）**：将指定方块上面的所有方块放回其初始位置。
2. **查找方块位置（$\texttt{findIndex}$）**：找到指定方块所在的位置和高度。
3. **四种移动操作**：
   - `moveOver` 和 `moveOnto` 用于处理单个方块的移动。
   - `pileOver` 和 `pileOnto` 用于处理整个堆栈的移动。

### 算法步骤
1. **初始化**：将每个方块放在对应的位置上。
2. **处理命令**：
   - 读取命令，如果是 `quit` 则终止。
   - 检查命令是否有效（$a \neq b$ 且不在同一堆栈）。
   - 根据命令类型调用相应的移动函数。
3. **输出结果**：遍历每个位置，输出其上的方块堆栈。

### 复杂度分析
- 时间复杂度：每个命令最多需要 $O(n)$ 时间，总共有 $m$ 个命令，因此总时间复杂度为 $O(mn)$。
- 空间复杂度：$O(n^2)$，用于存储方块堆栈。

## 代码实现

```cpp
// The Blocks Problem
// Verdict: Accepted
// Submission Date: 2011-10-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 模拟题，注意题意的操作中将方块返回原位置是指将方块 i 放到第 i 组方块最上方。
 
#include <bits/stdc++.h>

using namespace std;

#define MAXN 25

int blocks[MAXN];
int state[MAXN][MAXN];
int nBlocks;

void returning(int x, pair<int, int> xIndex) {
	for (int i = xIndex.second + 1; i < blocks[xIndex.first]; i++) {
		int tmp = state[xIndex.first][i];
		state[tmp][blocks[tmp]++] = tmp;
	}
	blocks[xIndex.first] = xIndex.second + 1;
}

void moveOver(int a, int b, pair<int, int> aIndex, pair<int, int> bIndex) {
	returning(a, aIndex);
	state[bIndex.first][blocks[bIndex.first]++] = a;
	blocks[aIndex.first] = aIndex.second;
}

void moveOnto(int a, int b, pair<int, int> aIndex, pair<int, int> bIndex) {
	returning(b, bIndex);
	moveOver(a, b, aIndex, bIndex);
}

void pileOver(int a, int b, pair<int, int> aIndex, pair<int, int> bIndex) {
	int current = aIndex.second;
	while (current < blocks[aIndex.first])
		state[bIndex.first][blocks[bIndex.first]++] = state[aIndex.first][current++];
	blocks[aIndex.first] = aIndex.second;
}

void pileOnto(int a, int b, pair<int, int> aIndex, pair<int, int> bIndex) {
	returning(b, bIndex);
	pileOver(a, b, aIndex, bIndex);
}

pair<int, int> findIndex(int x) {
	for (int i = 0; i < nBlocks; i++)
		for (int j = 0; j < blocks[i]; j++)
			if (state[i][j] == x)
				return make_pair(i, j);
}

void print(void) {
	for (int i = 0; i < nBlocks; i++) {
		cout << i << ":";
		for (int j = 0; j < blocks[i]; j++) cout << " " << state[i][j];
		cout << endl;
	}
}

int main() {
	int a, b, aIndex, bIndex;
	string command, action;
	cin >> nBlocks;
	for (int i = 0; i < nBlocks; i++) {
		blocks[i] = 0;
		state[i][blocks[i]++] = i;
	}
	while (cin >> command, strcmp(command.data(), "quit")) {
		cin >> a >> action >> b;
		if (a == b)	continue;
		pair<int, int> aIndex = findIndex(a);
		pair<int, int> bIndex = findIndex(b);
		if (aIndex.first == bIndex.first) continue;
		if (strcmp(command.data(), "move") == 0) {
			if (strcmp(action.data(), "onto") == 0)	moveOnto(a, b, aIndex, bIndex);
			else moveOver(a, b, aIndex, bIndex);
		}
		else if (strcmp(action.data(), "onto") == 0) pileOnto(a, b, aIndex, bIndex);
		else pileOver(a, b, aIndex, bIndex);
	}
	print();
	return 0;
}
```

## 总结

本题是一个典型的模拟题，关键在于理解四种操作的具体含义，并正确实现归位和移动操作。代码中使用了二维数组来存储方块堆栈，通过维护每个位置的方块数量来管理堆栈。注意处理无效命令的情况，确保程序的鲁棒性。
