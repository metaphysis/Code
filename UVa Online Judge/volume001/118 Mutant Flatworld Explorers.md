[UVa 118 Mutant Flatworld Explorers](https://blog.csdn.net/metaphysis/article/details/156644197)

## 题目分析

本题是一个模拟类题目，要求模拟机器人在一个矩形网格世界中的移动过程。世界的大小由右上角坐标 $(w, h)$ 给出，左下角固定为 $(0, 0)$。每个机器人有初始位置 $(x, y)$ 和朝向（`N`, `S`, `E`, `W` 分别代表北、南、东、西）。机器人按顺序接受指令，指令由三种动作组成：

- **`L`**：向左转 $90$ 度，位置不变。
- **`R`**：向右转 $90$ 度，位置不变。
- **`F`**：向前移动一格，方向不变。

机器人如果移动到网格边界之外，则视为“坠落”，并在坠落前的最后一个位置留下“气味”。之后若其他机器人试图从同一位置坠落到同一方向，则会忽略该移动指令，以避免再次坠落。

输入首先给出世界大小，之后每组数据包括机器人的初始位置和指令字符串。输出每个机器人的最终位置和朝向，若坠落则附加输出 `LOST`。

**关键点**：
- 网格坐标范围为 $0 \leq x \leq w$, $0 \leq y \leq h$。
- 最大坐标为 $50$，指令长度小于 $100$。
- 机器人按输入顺序独立处理，但“气味”信息是全局保存的。

## 解题思路

我们可以用一个二维数组 `grid` 记录每个格子是否“危险”（即是否有机器人从这里坠落过）。初始时所有格子都是安全的。

对于每个机器人，我们依次处理其指令：
- 如果是转向指令（`L` 或 `R`），则更新当前朝向。
- 如果是前进指令（`F`），则根据当前朝向更新坐标。
- 更新坐标后检查是否越界：
    - 如果越界，则检查上一步所在格子是否标记为“危险”：
        - 如果是，则忽略该移动，恢复上一步状态。
        - 如果不是，则输出上一步位置和朝向，并加上 `LOST`，同时将上一步所在格子标记为“危险”，结束该机器人的处理。
- 如果所有指令执行完毕仍未坠落，则输出最终位置和朝向。

**方向转换**：
我们可以用字符串表示方向（如 `N`, `S`, `E`, `W`），并通过条件判断实现转向逻辑。也可以使用数字编码（如 $0, 1, 2, 3$）配合方向向量数组来简化代码。

**注意**：题目中给出的世界大小 `width` 和 `height` 分别对应 $w$ 和 $h$，而数组索引从 $0$ 开始，所以判断越界时要注意边界条件。

## 代码实现

```cpp
// Mutant Flatworld Explorers
// UVa ID: 118
// Verdict: Accepted
// Submission Date: 2011-11-26
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
const int DANGEROUS = 0;
const int SAFE = 1;

struct status {
	int x, y;
	string direction;
};

int grid[MAXN][MAXN], width, height;

bool move(status & s, string instructions) {
	status last;
	for (int i = 0; i < instructions.length(); i++) 	{
		// 稍显华丽的  if else。
		last = s;
		if (s.direction == "N" && instructions[i] == 'L')
			s.direction = "W";
		else if (s.direction == "N" && instructions[i] == 'R')
			s.direction = "E";
		else if (s.direction == "N" && instructions[i] == 'F')
			s.y += 1;
		else if (s.direction == "S" && instructions[i] == 'L')
			s.direction = "E";
		else if (s.direction == "S" && instructions[i] == 'R')
			s.direction = "W";
		else if (s.direction == "S" && instructions[i] == 'F')
			s.y -= 1;
		else if (s.direction == "W" && instructions[i] == 'L')
			s.direction = "S";
		else if (s.direction == "W" && instructions[i] == 'R')
			s.direction = "N";
		else if (s.direction == "W" && instructions[i] == 'F')
			s.x -= 1;
		else if (s.direction == "E" && instructions[i] == 'L')
			s.direction = "N";
		else if (s.direction == "E" && instructions[i] == 'R')
			s.direction = "S";
		else if (s.direction == "E" && instructions[i] == 'F')
			s.x += 1;

		if (s.x > width || s.x < 0 || s.y > height || s.y < 0) {
			if (grid[last.y][last.x] == DANGEROUS)
				s = last;
			else	{
				cout << last.x << " " << last.y << " " << last.
					direction;
				cout << " LOST" << endl;
				grid[last.y][last.x] = DANGEROUS;
				return true;
			}
		}
	}
	cout << s.x << " " << s.y << " " << s.direction << endl;
	return false;
}

int main(int argc, char const *argv[]) {
	status robot;
	string line;
	cin >> width >> height;
	for (int i = 0; i <= height; i++)
		for (int j = 0; j <= width; j++)
			grid[i][j] = SAFE;
	while (cin >> robot.x >> robot.y >> robot.direction) {
		cin >> line;
		move(robot, line);
	}
	return 0;
}
```

## 总结

本题主要考察模拟和边界处理能力。实现时需要注意：
- 正确处理越界判断和“气味”标记。
- 机器人之间独立处理，但“气味”是全局共享的。
- 输出格式要严格符合题目要求。

通过本题可以加深对状态模拟和条件判断的理解，适合作为模拟类题目的入门练习。
