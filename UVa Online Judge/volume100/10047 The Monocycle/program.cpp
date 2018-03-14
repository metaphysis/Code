// The Monocycle（独轮车）
// PC/UVa IDs: 111202/10047, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.076s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题可以归结为图的遍历，动态规划问题。题目所要求的是到达终点 T 时，轮子绿色部分中心着地时的最短
// 时间，如果能通过遍历到达终点 T，则肯定存在一个最短时间，否则说明起点 S 和终点 T 之间无通路，目
// 标不可达。若遍历能到达终点 T，不一定刚好是绿色部分中心着地，即走的步数刚好是 5 的倍数，那么就
// 需要从这些路径中选一条达到终点 T 时，中心着地部分为绿色且时间最短的一条，这个可以通过动态规划
// 来解决。使用 minTime[i][j][c][d] 表示在位置（i，j）颜色为 c，方向为 d 时的最小到达时间，
// 在遍历中更新该时间，大于等于该时间的同等状态不再继续扩展进行遍历，最后取终点 T，中心着地颜色为
// 绿色时的到达时间最小值，若最小值还是预设的 MAXINT，则表示目标不可达。

#include <bits/stdc++.h>

using namespace std;

#define MAXN 25			// 地面大小最大值。
#define MAXCOLORS 5		// 颜色数目。
#define MAXD 4			// 方向数目。
#define MAXINT (1 << 20)	// 预设的最大时间。为该值则表示不可达。

// 面朝方向：北。
#define NORTH 0
#define SOUTH 1
#define WEST 2
#define EAST 3

// 中心着地部分颜色。
#define GREEN 0
#define BLACK 1
#define RED 2
#define BLUE 3
#define WHITE 4

// 独轮车手状态。
struct state
{
	int x, y;	// 所处位置。
	int time;	// 已用时间。
	int direction;	// 面朝方向。
	int color;	// 中心着地部分颜色。
};

// 到达位置（i，j）时，中心着地部分颜色为 c，方向为 d 时的最小时间。
int minTime[MAXN][MAXN][MAXCOLORS][MAXD];
// 表示地面的字符数组。
char matrix[MAXN][MAXN];
// 测试例数，表示地面矩阵的行数，列数。
int cases = 1, line, row;
// 从当前方向 i 到转到方向 j 所需时间，如 delay[NORTH][SOUTH] 表示从朝北方向转到朝南方向，所
// 需时间为 2 秒，因为要在原地转两次 90 度。
int delay[MAXD][MAXD] = {
	{ 0, 2, 1, 1 }, { 2, 0, 1, 1 }, { 1, 1, 0, 2 }, { 1, 1, 2, 0 } };
int offset[MAXD][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
// 表示起点和终点的位置。
pair < int, int > sIndex, tIndex;

void dynamic_programming(void)
{
	// 置初始值。
	for (int i = 0; i < line; i++)
		for (int j = 0; j < row; j++)
			for (int c = GREEN; c <= WHITE; c++)
				for (int d = NORTH; d <= EAST; d++)
					minTime[i][j][c][d] = MAXINT;
	
	// 压入初始状态。
	queue < state > states;
	states.push((state){sIndex.first, sIndex.second, 0, NORTH, GREEN});
	
	// 宽度优先遍历。
	while (!states.empty())
	{
		state s = states.front();
		states.pop();

		// 比较状态，更新相同状态到达时间的最小值。
		if (s.time >= minTime[s.x][s.y][s.color][s.direction])
			continue;
		else
			minTime[s.x][s.y][s.color][s.direction] = s.time;

		// 原地转方向。
		for (int d = NORTH; d <= EAST; d++)
		{
			if (d == s.direction)
				continue;

			states.push((state){s.x, s.y, s.time +
					delay[s.direction][d], d, s.color});
		}

		// 若前后左右无障碍且在地面范围内，则前进。
		for (int d = NORTH; d <= EAST; d++)
		{
			int x = s.x + offset[d][0];
			int y = s.y + offset[d][1];
			
			if (x < 0 || x >= line || y < 0 || y >= row)
				continue;
			if (matrix[x][y] == '#')
				continue;

			states.push((state){x, y, s.time + delay[s.direction][d] + 1, 
						d, (s.color + 1) % MAXCOLORS});
		}
	}

	// 取到达终点 T 时的最小到达时间。
	int minimum = MAXINT;
	for (int i = NORTH; i <= EAST; i++)
		 minimum = min(minimum, minTime[tIndex.first][tIndex.second][GREEN][i]);

	// 输出空行。
	if (cases >= 2)
		cout << endl;

	// 输出结果。
	cout << "Case #" << cases++ << endl;
	if (minimum < MAXINT)
		cout << "minimum time = " << minimum << " sec" << endl;
	else
		cout << "destination not reachable" << endl;
}

int main(int ac, char *av[])
{
	while (cin >> line >> row, line || row)
	{
		for (int i = 0; i < line; i++)
			for (int j = 0; j < row; j++)
			{
				cin >> matrix[i][j];
				if (matrix[i][j] == 'S')
					sIndex = make_pair(i, j);
				if (matrix[i][j] == 'T')
					tIndex = make_pair(i, j);
			}

		dynamic_programming();
	}

	return 0;
}
