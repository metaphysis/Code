[UVa 114 Simulation Wizardry](https://blog.csdn.net/metaphysis/article/details/156642183)

## 题目描述

本题要求模拟一个简化的弹珠游戏机。游戏在一个 $m \times n$ 的网格上进行，坐标范围为 $1 \leq x \leq m$，$1 \leq y \leq n$。网格边缘是墙壁，内部可能放置若干“缓冲器”（$\texttt{bumper}$）。每个缓冲器占据一个网格点，具有两个属性：**价值**（$\texttt{value}$）和**代价**（$\texttt{cost}$）。

弹珠从某个初始位置、初始方向（上、下、左、右）和初始寿命（$\texttt{lifetime}$）开始运动。每经过一个时间单位，弹珠向当前方向移动一格，同时寿命减少 $1$。如果弹珠在移动过程中遇到墙壁或缓冲器，则会发生反弹：弹珠立即向右（顺时针）旋转 $90^\circ$，且不占据障碍物的位置（即位置不变，只改变方向）。如果撞击的是缓冲器，则在寿命仍为正时获得该缓冲器的价值，同时寿命减去该缓冲器的代价（代价可为负，表示增加寿命）；如果撞击的是墙壁，则只减少寿命（减去墙壁的固定代价），不获得分数。

当寿命 $\leq 0$ 时，弹珠消失，游戏继续处理下一个弹珠。要求输出每个弹珠获得的分数，以及所有弹珠的总分。

---

## 输入格式

- 第一行：两个整数 $m$ 和 $n$（$2 < m, n < 51$）。
- 第二行：撞击墙壁的代价（整数）。
- 第三行：缓冲器数量 $p$（$p \geq 0$）。
- 接下来 $p$ 行：每行四个整数，分别为缓冲器的 $x$ 坐标、$y$ 坐标、价值、代价。
- 之后每行描述一个弹珠：四个整数，分别为初始 $x$、初始 $y$、方向（`0`: 右，`1`: 上，`2`: 左，`3`: 下）、初始寿命（正数）。

---

## 输出格式

- 对于每个弹珠，输出一行其获得的分数。
- 最后一行输出所有弹珠的总分。

---

## 题目分析与解题思路

### 关键点解析

1. **网格表示**：  
   由于坐标范围较小（最大 $50 \times 50$），可以使用二维数组存储每个格子的类型（空、缓冲器、墙壁）以及缓冲器的属性（价值、代价）。

2. **弹珠运动与碰撞检测**：  
   每个时间单位：
   - 根据当前方向计算下一步位置。
   - 如果下一步位置是墙壁或缓冲器，则触发反弹：
     - 方向顺时针旋转 $90^\circ$。
     - 如果撞击缓冲器且当前寿命 $> 0$，则增加价值，减少寿命（减去代价）。
     - 如果撞击墙壁，只减少寿命（减去墙壁代价）。
   - 如果下一步位置为空，则移动到该位置。
   - 寿命减少 $1$。

3. **寿命处理**：  
   - 每次移动前先减少 $1$ 寿命。
   - 如果撞击障碍物，再减去相应代价。
   - 寿命 $\leq 0$ 时弹珠消失，不再进行后续移动。

4. **方向表示**：  
   使用整数 $0, 1, 2, 3$ 分别表示右、上、左、下，便于通过取模运算实现顺时针旋转。

---

### 算法步骤

1. 读入 $m, n$，初始化网格，将边缘设为墙壁。
2. 读入墙壁代价和缓冲器数量，记录每个缓冲器的位置和属性。
3. 对于每个弹珠：
   - 初始化位置、方向、寿命、分数。
   - 当寿命 $> 0$ 时循环：
     - 寿命减 $1$。
     - 计算下一步坐标。
     - 根据下一步位置类型处理反弹、加分、减寿命或移动。
   - 累加分数并输出。
4. 输出总分数。

---

### 复杂度分析

- 网格大小：$O(mn)$，内存很小。
- 每个弹珠最多移动寿命步，寿命可能较大，但网格小，碰撞频繁，实际循环次数有限。
- 整体复杂度：$O(\text{弹珠数} \times \text{平均寿命})$，在题目限制下可接受。

---

## 代码实现

```cpp
// Simulation Wizardry
// UVa ID: 114
// Verdict: Accepted
// Submission Date: 2011-12-02
// UVa Run Time: 0.084s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;
const int GRID = 0, OBSTACLE = 1, WALL = 3;
const int RIGHT = 0, UP = 1, LEFT = 2, DOWN = 3;

struct obstacle
{
	int value, cost;
};

struct ball
{
	int x, y, direction, lifetime, points;
};

ball pinball;
obstacle bumpers[MAXN][MAXN];
int grid[MAXN][MAXN], gridWidth, gridHeight, costHitWall;
int offset[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

void play(void)
{
	int newX, newY;
	while (pinball.lifetime > 0)
	{
		pinball.lifetime--;
		newX = pinball.x + offset[pinball.direction][0];
		newY = pinball.y + offset[pinball.direction][1];

		if (grid[newY][newX] == WALL)
		{
			if (newY == gridHeight && pinball.direction == UP ||
				newY == 1 && pinball.direction == DOWN ||
				newX == gridWidth && pinball.direction == RIGHT ||
				newX == 1 && pinball.direction == LEFT)
			{
				pinball.direction--;
				if (pinball.direction < 0)
					pinball.direction += 4;
				pinball.lifetime -= costHitWall;	
			}			
		}
		else if (grid[newY][newX] == OBSTACLE)
		{
			pinball.direction--;
			if (pinball.direction < 0)
				pinball.direction += 4;
			if (pinball.lifetime > 0)
			{
				pinball.points += bumpers[newY][newX].value;
				pinball.lifetime -= bumpers[newY][newX].cost;
			}
		}
		else
		{
			pinball.x = newX;
			pinball.y = newY;
		}
	}
}

int main (int argc, char *argv[])
{
	int totalPoints = 0, numberBumpers, tmpX, tmpY;

	cin >> gridWidth >> gridHeight;
	cin >> costHitWall;
	for (int i = 1; i <= gridHeight; i++)
		for (int j = 1; j <= gridWidth; j++)
			if (i == 1 || j == 1 || i == gridHeight || j == gridWidth)
				grid[i][j] = WALL;
			else
				grid[i][j] = GRID;

	cin >> numberBumpers;
	for (int i = 1; i <= numberBumpers; i++)
	{
		cin >> tmpX >> tmpY;
		grid[tmpY][tmpX] = OBSTACLE;
		cin >> bumpers[tmpY][tmpX].value;
		cin >> bumpers[tmpY][tmpX].cost;
	}

	while (cin >> pinball.x)
	{
		cin >> pinball.y >> pinball.direction >> pinball.lifetime;
		pinball.points = 0;
		
		play();
	
		totalPoints += pinball.points;
		cout << pinball.points << endl;
	}

	cout << totalPoints << endl;

	return 0;
}
```

---

## 总结

本题是一个中等难度的模拟题，主要考察对状态转换和边界条件的处理。解题关键在于正确理解题目中关于移动、碰撞、反弹和寿命消耗的规则，并用清晰的逻辑实现每一步的更新。代码中使用二维数组存储网格状态，通过方向数组简化移动计算，通过取模运算实现方向的旋转，这些都是处理此类网格模拟问题的常用技巧。
