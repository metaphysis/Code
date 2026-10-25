## 题目描述

一场重要的足球比赛即将在 $\texttt{A}$ 队和 $\texttt{B}$ 队之间展开。$\texttt{B}$ 队赢得开球权，一名球员位于中场位置 $(0,0)$。$\texttt{A}$ 队的防守半场是一个边长为 $2s$ 的正方形区域，中场线与 $X$ 轴重合。该区域被划分为每边 $2s$ 个方格的网格，球门位于 $Y = 2s$ 直线上，占据 $Y$ 轴两侧各 $g$ 个方格的宽度。

$\texttt{A}$ 队有 $n$ 名防守球员，位于网格交点处。每名球员可以拦截进入其周围 $p$ 个方格范围内的球（即覆盖一个以球员为中心、边长为 $2p$ 的方形区域）。中场位置 $(0,0)$ 不会被任何 $\texttt{A}$ 队球员覆盖。

$\texttt{B}$ 队教练希望放置至多 $n$ 名额外的球员（不包括开球者）在网格交点处，通过一系列直线传球（只能平行于 $X$ 或 $Y$ 轴）将球从中场位置移动到 $\texttt{A}$ 队球门，且球经过的每个格点都不能被 $\texttt{A}$ 队球员覆盖。要求使用最少的球员数（即传球次数最少），若有多个方案则选择总移动距离最短的方案。

## 输入格式

输入包含多组测试用例，每组一行，格式如下：

- 四个整数 $s$、$g$、$p$、$n$，其中 $0 < s < 10$，$0 < g < s$，$0 < p < s$，$0 \le n < 100$。
- 随后跟有 $n$ 对整数 $(x, y)$，表示 $\texttt{A}$ 队球员的坐标（$x$ 范围 $[-s, s]$，$y$ 范围 $[0, 2s]$）。

输入以单独的一行 `0` 结束。

## 输出格式

对于每组测试用例，输出一行标识场景序号，格式为 `Scenario X.`。  
若无法进球，输出 `Situation Impossible`；  
否则输出 `Goal with k kicks: (x1,y1)(x2,y2)...(xk+1,yk+1)`，其中 $(x_i, y_i)$（$i \le k$）表示第 $i$ 次踢球时球所在的格点（即第 $i$ 名球员的位置），$(x_{k+1}, y_{k+1})$ 是球最终到达的球门线上的点，满足 $y_{k+1} = 2s$ 且 $|x_{k+1}| \le g$。

两组输出之间用一个空行隔开。

## 样例

输入
```
4 2 1 2 -2 8 1 8
7 2 3 3 0 7 6 10 0 9
9 3 3 1 -5 9
0
```

输出
```
Scenario 1.
Situation Impossible

Scenario 2.
Goal with 3 kicks: (0,0)(-4,0)(-4,14)(-2,14)

Scenario 3.
Goal with 1 kicks: (0,0)(0,18)
```

## 题目分析

本题的核心是在给定的网格中寻找一条从起点 $(0,0)$ 到球门线的最短路径，其中路径由若干条水平或垂直的直线段组成（每次传球），且路径上所有格点均不能被 $\texttt{A}$ 队防守球员覆盖。约束条件是路径的段数（即踢球次数）不能超过 $n+1$（因为可以放置至多 $n$ 名额外球员，起点开球者不算在内）。在段数最少的前提下，要求总曼哈顿距离最短。

由于 $s < 10$，网格大小不超过 $20 \times 20$，状态空间非常小，因此可以采用带优先级的搜索算法，以段数为主关键字、总距离为次关键字进行广度优先搜索（$\texttt{BFS}$）变种。

## 解题思路

### 模型转化

将整个球场的坐标整体向右平移 $s$ 个单位，使得所有格点的 $x$ 坐标落在区间 $[0, 2s]$ 内。这样做的好处是可以使用二维数组直接索引每个格点，无需偏移常量。平移后的起点变为 $(s, 0)$，球门线变为 $y = 2s$，且球门范围为 $|x - s| \le g$。

### 覆盖判定

$\texttt{A}$ 队球员 $(a, b)$ 覆盖所有满足 $|x - a| \le p$ 且 $|y - b| \le p$ 的格点。因此，任意格点 $(x, y)$ 是否被覆盖，只需遍历所有球员检查切比雪夫距离是否不超过 $p$ 即可。由于 $n \le 100$，且网格很小，该检查常数极低。

### 状态表示与搜索

定义状态为 $(x, y, \textit{kick}, \textit{dist})$，其中 $(x, y)$ 是当前球所在的格点，$\textit{kick}$ 是已经执行的踢球次数（即已经经过的直线段数），$\textit{dist}$ 是累计的曼哈顿移动距离。

优先级比较规则：首先比较 $\textit{kick}$，较小的优先；若相同则比较 $\textit{dist}$，较小的优先。使用优先队列（小根堆）实现 $\texttt{Dijkstra}$ 风格的搜索。

起点状态为 $(s, 0, 0, 0)$，因为尚未执行任何踢球。

### 状态扩展

从当前格点出发，尝试沿四个方向（上、下、左、右）直线前进。每次尝试向前走一步到达新的格点，若该格点不合法（越界）或被覆盖，则停止该方向的继续前进。否则，记录走过的步数 $\textit{step}$，生成新状态：新格点 $(nx, ny)$，新踢球次数 $\textit{nk} = \textit{kick} + 1$，新总距离 $\textit{nd} = \textit{dist} + \textit{step}$。

若 $\textit{nk} \le n + 1$（因为最多允许 $n+1$ 次踢球），并且该新状态比当前记录的最优状态（$\textit{bestKick}[nx][ny]$，$\textit{bestDist}[nx][ny]$）更优，则更新最优记录，记录前驱格点，并将新状态入队。

### 目标判定

当从优先队列中弹出某个状态时，若其 $y = 2s$ 且 $|x - s| \le g$，则说明球已到达球门线，且该状态是当前队列中最优的（因为优先级保证了先弹出段数最少、距离最短的状态），因此可以立即终止搜索。

### 回溯路径

从目标状态开始，沿着记录的 `parent` 数组回溯到起点，即可得到完整的格点序列，输出时需将 $x$ 坐标还原（减 $s$）。

### 复杂度分析

- 状态数：网格格点总数为 $(2s+1) \times (2s+1) \le 19 \times 19 = 361$。
- 每个状态扩展时沿四个方向，每个方向最多前进 $2s$ 步，因此总扩展次数约为 $O(4 \times 361 \times 2s) \approx O(s^2)$，其中 $s < 10$，常数极小。
- 优先队列操作 $O(\log V)$，总时间复杂度可视为 $O(1)$ 量级，空间复杂度 $O(1)$。

## 代码实现

```cpp
// Grid Soccer
// UVa ID: 747
// Verdict: Accepted
// Submission Date: 2026-07-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct state {
	int x, y, kick, dist;
	bool operator>(const state& o) const {
		if (kick != o.kick) return kick > o.kick;
		return dist > o.dist;
	}
};

int s, g, p, n;
vector<pair<int,int>> players;

int bestKick[32][32], bestDist[32][32];
pair<int,int> parent[32][32];

bool covered(int x, int y) {
	for (auto &pl : players) {
		int a = pl.first, b = pl.second;
		if (abs(x - a) <= p && abs(y - b) <= p)
			return true;
	}
	return false;
}

bool valid(int x, int y) {
	return x >= 0 && x <= 2 * s && y >= 0 && y <= 2 * s;
}

int main() {
	cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
	int scenario = 0;
	while (cin >> s, s) {
		cin >> g >> p >> n;
		players.clear();
		for (int i = 0; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			players.push_back({a + s, b});
		}
		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++) {
				bestKick[i][j] = bestDist[i][j] = INT_MAX;
				parent[i][j] = {0, 0};
			}
		priority_queue<state, vector<state>, greater<state>> pq;
		int sx = s, sy = 0;
		bestKick[sx][sy] = bestDist[sx][sy] = 0;
		pq.push({s, 0, 0, 0});
		bool found = false;
		state target;
		int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, 1, -1};
		while (!pq.empty()) {
			state now = pq.top();
			pq.pop();
			int cx = now.x, cy = now.y;
			int cKick = now.kick, cDist = now.dist;
			if (cKick != bestKick[cx][cy] || cDist != bestDist[cx][cy]) continue;
			if (cy == 2 * s && abs(cx - s) <= g) {
				found = true;
				target = now;
				break;
			}
			if (cKick == n + 1) continue;
			for (int d = 0; d < 4; ++d) {
				int nx = cx, ny = cy, step = 0;
				while (true) {
					nx += dx[d], ny += dy[d];
					if (!valid(nx, ny)) break;
					if (covered(nx, ny)) break;
					step++;
					int nk = cKick + 1, nd = cDist + step;
					if (nk > n + 1) break;
					if (nk < bestKick[nx][ny] || (nk == bestKick[nx][ny] && nd < bestDist[nx][ny])) {
						bestKick[nx][ny] = nk;
						bestDist[nx][ny] = nd;
						parent[nx][ny] = {cx, cy};
						pq.push({nx, ny, nk, nd});
					}
				}
			}
		}
		if (scenario) cout << "\n";
		cout << "Scenario " << ++scenario << ".\n";
		if (!found) cout << "Situation Impossible\n";
		else {
			vector<pair<int,int>> path;
			int cx = target.x, cy = target.y;
			while (!(cx == s && cy == 0)) {
				path.push_back({cx, cy});
				auto p = parent[cx][cy];
				cx = p.first, cy = p.second;
			}
			path.push_back({s, 0});
			reverse(path.begin(), path.end());
			cout << "Goal with " << target.kick << " kicks: ";
			for (size_t i = 0; i < path.size(); ++i) cout << "(" << path[i].first - s << "," << path[i].second << ")";
			cout << "\n";
		}
	}
	return 0;
}
```

## 总结

本题的关键在于将实际问题抽象为网格上的最优路径问题，并利用网格规模小的特点，采用优先队列进行带优先级的搜索。代码中的几个设计亮点值得注意：

- **坐标平移**：将 $x$ 坐标整体加 $s$，使得所有坐标非负，便于数组索引，简化边界判断。
- **段数优先的搜索**：通过自定义比较函数，保证优先队列总是先弹出踢球次数最少的状态，从而首次找到的目标即为最优解。
- **直线扩展**：每次传球可沿一个方向连续前进多格，但每个中间格点都作为候选状态入队，保证了不会遗漏可能的转向点。
- **精确的约束控制**：将踢球次数上限设为 $n+1$，完美贴合题目中“至多 $n$ 名额外球员”的定义，且代码实现简洁。

该解法充分利用了题目的小数据特性，以直观的搜索方式解决了实际问题，是一道适合练习图论建模和优先队列应用的典型题目。
