// Bigger Square Please... （拼接正方形）
// PC/UVa IDs: 110808/10270, Popularity: C, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-09-25
// UVa Run Time: 0.032s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// Tony 有很多张正方形纸片。这些纸片的边长为 1 到 N - 1 不等，且每种纸片都有无数张。但是他并不
// 满足。他想要一张更大的 ---- 边长为 N 的纸片。
//
// 可以把已有纸片拼接成他想要的大正方形。例如，一个边长为 7 的正方形可以通过如下 9 个更小的正方形
// 拼接而成（使用字母来填充相应的正方形，A 表示边长为 1 的正方形纸片，B 表示边长为 2 的正方形纸
// 片，依此类推）：
//
//                B B B B C C C 
//                B B B B C C C 
//                A B B A C C C 
//                A B B D D D D 
//                C C C D D D D 
//                C C C D D D D 
//                C C C D D D D
//
// 在拼接出的正方形中间不能有空隙，不能有纸片超出正方形，且纸片不能相互重叠。并且，Tony 想要用尽
// 可能少的纸片来拼出这个大的正方形。你能帮助他吗？
//
// [输入]
// 输入第一行有一个单独的整数 T，表示测试数据的组数。每组数据为一个单独的整数 N（2 <= N <= 50）。
//
// [输出]
// 对于每组数据，输出一行，包含一个整数 K，表示最少需要的纸片数。接下来 K 行，每行三个整数 x，y，
// l，表示纸片左上角的坐标 （1 <= x，y <= N） 以及纸片的边长。
//
// [样例输入]
// 3
// 4
// 3
// 7
//
// [样例输出]
// 4
// 1 1 2
// 1 3 2
// 3 1 2
// 3 3 2
// 6
// 1 1 2
// 1 3 1
// 2 3 1
// 3 1 1
// 3 2 1
// 3 3 1
// 9
// 1 1 2
// 1 3 2
// 3 1 1
// 4 1 1
// 3 2 2
// 5 1 3
// 4 4 4
// 1 5 3
// 3 4 1
//
// [解题方法]
// 该题是 UVa 上的所有题目中 10% 较难的题目中的一题。如果是实时产生拼接方案，而不是预先生成拼接
// 方案再提交，说明水平确实比较高。题目要求用边长为 1 - （N - 1） 的任意张纸片拼接成一个边长为
// N 的正方形纸片，纸片间互相不能重叠，且不能超出边长为 N 的正方形范围，求使用纸片数最少的拼接方
// 案，以左上角为坐标起点 （1，1），按坐标、纸张边长的顺序输出每张纸片的坐标、边长值。
//
// 根据题意，设需要拼接的正方形边长为 N，很明显，拼接方案是一系列平方数的和。问题转化为如何将 N 表
// 示为平方数之和，且要求平方数的个数最小，这个问题可以通过回溯来解决。但是得到了一个将 N 拆分为平
// 方数之和的方案，并不表示就能将这些大小的纸片拼接成一个边长为 N 的纸片，例如，对于 N = 5，可以
// 拆分为 9 与 16 的和，9 和 16 都是平方数，但是实际上无法将一张边长为 3 和一张边长为 4 的纸片
// 拼接为一张边长为 5 的纸片，所以在生成一个平方数和方案后，需要实际尝试放置，若能放置，则表明此方
// 案可行，予以记录，将所有可行的方案记录后，挑选其中纸片数最小的方案即为所求。这样的话，将 N 拆分
// 为平方数之和是一步回溯，将拆分方案尝试放置又是一步回溯，需要通过两步回溯来解决本问题。
//
// 考虑到需要两步回溯，如果不予以充分剪枝，则计算时间将不可忍受，在 UVa BBS 上关于这个题目的讨论
// 即反映了这种情况。在将 N 拆分为平方数和的一步，若能生成一个拆分方案，尽管不是最优的，但是它的总
// 个数较小，且能实际放置，则将此方案的总个数作为剪枝阈值将可避免较多无效的搜索，将 N 拆分为平方数
// 后且能实际放置的一个非最优方案可以这样构造：左上角放置一个边长为 （N - 2） 的纸片，然后在右侧和
// 下方放置边长为 2 的纸片，剩余的空间放置边长为 1 的纸片，这样总的纸片需要数量为： 1 + [N / 2]
// + [（N - 2） / 2] + 4，其中符号 [] 表示取整，这样总的纸片放置数在 N 附近，可以做为一个较好
// 的剪枝阈值。通过回溯发现了总个数更少的方案后，则开始尝试实际放置，可以通过设立一个网格数组，当
// 填充边长为 A 的纸片时，在网格中查找是否有起始坐标为 （x，y） 且边长为 A 的空白区域，若无此种
// 空白区域，则表明该方案无法实际放置，若能找到，则找到所有这样的起始位置，逐一回溯进行尝试，尝试
// 某位置后，则将该区域标记为已填充，若后继填充不成功返回时则撤销标记。对于已经产生但不能实际拼接
// 的拆分方案需要予以记录，在后继生成的方案中，若有方案与记录的方案相同，则不必再次浪费时间搜索。
//
// 通过网络搜索该问题的相关信息可以知道，当 N MOD 2 = 0 或者 N MOD 6 = 3 时，有特殊的解法。
// 对于 N MOD 2 = 0，即 N 为偶数时，最少纸片数的拼接方法为：用 4 张边长为 N / 2 的纸片拼接得
// 到边长为 N 的正方形。当 N MOD 6 = 3 时，放置方法与 N = 3 的方案类似，只不过将相应的纸片边长
// 增加同样的数量。同时平方数如 25 的拼接方案和 5 的拼接方案类似，49 的拼接方案和 7 的拼接方案
// 类似，则在 2 - 50 之间的数，只需要求出质数的拼接方法即可。网络上已经有 2 - 50 之间的质数的
// 拼接方案和最少需要纸片数，利用这些信息，可以显著减少计算时间，甚至直接生成拼接方案后再提交。
//
// 参考网页：
// http://www2.stetson.edu/~efriedma/mathmagic/1298.html
// http://mathpuzzle.com/perkinsbestquilts.txt
// http://mathworld.wolfram.com/MrsPerkinssQuilt.html

#include <bits/stdc++.h>

using namespace std;

#ifndef DEBUG_MODE
// #define DEBUG_MODE	// 测试用，若在线提交，需要将该语句注释掉。
#endif

#define NMAX 20		// 拆分时，纸片最多需要的张数。
#define NPRIME 11	// 10 - 50 之间的质数个数。
#define SMAX 1024	// 最多保存的未成功拼接的拆分方案数。
#define PMAX 2500	// 网格中坐标最大个数。
#define NCELL 50	// 网格边长。

struct square		// 表示拼接的纸片信息。
{
	int x, y;	// 纸片在网格中的坐标。
	int size;	// 纸片的边长。
};

square squares[NMAX];	// 记录当前的拼接方案。
square best[NMAX];	// 记录搜索得到的最好实际拼接方案。

struct point	// 表示网格中的一个点。
{
	int x;		// 点的横坐标。
	int y;		// 点的纵坐标。
};

// 2 - 50 之间的奇数拼接时所需要的最少纸片数。
int tip[24] = { 6, 8, 9, 6, 11, 11, 6, 12, 13, 6, 13, 8, 6, 14, 15, 6, 8, 15, 6,
	15, 16, 6, 17, 9
};

// 10 - 50 之间的质数的最佳拆分方案。数组第一个数表示质数，第二个数表示所需纸片数，其后的数字为
// 纸片大小，按纸片从大到小排列。
int trick[NPRIME][NMAX] = {
	{11, 11, 6, 5, 5, 4, 2, 2, 2, 2, 1, 1, 1},				// 11
	{13, 11, 7, 6, 6, 4, 3, 3, 2, 2, 2, 1, 1},				// 13
	{17, 12, 9, 8, 8, 5, 4, 4, 3, 2, 2, 2, 1, 1},				// 17
	{19, 13, 10, 9, 9, 5, 5, 5, 3, 2, 2, 2, 1, 1, 1},			// 19
	{23, 13, 12, 11, 11, 7, 5, 5, 4, 3, 3, 2, 2, 1, 1},			// 23
	{29, 14, 17, 12, 12, 9, 8, 8, 4, 4, 3, 2, 2, 2, 1, 1},			// 29
	{31, 15, 16, 15, 15, 8, 8, 8, 4, 4, 4, 2, 2, 2, 1, 1, 1},		// 31
	{37, 15, 19, 18, 18, 11, 8, 8, 6, 5, 5, 3, 3, 2, 1, 1, 1},		// 37
	{41, 15, 23, 18, 18, 12, 11, 11, 7, 5, 4, 3, 3, 2, 2, 1, 1},		// 41
	{43, 16, 22, 21, 21, 11, 11, 11, 6, 5, 5, 3, 3, 3, 2, 1, 1, 1},		// 43
	{47, 17, 25, 22, 22, 13, 12, 9, 8, 8, 5, 5, 4, 3, 3, 2, 2, 1, 1},	// 47
};

int n;				// 要拼接的正方形边长。
int smallest;			// 当前实际最佳拼接方案的纸片数。
int ncount[NCELL];		// 记录拼接方案中重复纸片的张数。
int cell[NCELL][NCELL];		// 尝试拼接时使用的网格。
int backup[NCELL][NCELL];	// 记录实际最佳方案网格状态。
int ncache[NMAX];		// 记录的未成功拼接的拆分方案个数。
int cache[NMAX][SMAX][NMAX];	// 记录未能成功拼接的拆分方案。

bool found;			// 当前是否发现了非最优拆分方案的实际拼接方案。
bool finished;			// 提前结束回溯的标志。

// 在网格 cell 中查找边长为 size 的空白区域的左上角坐标。
int find(int size, point points[PMAX])
{
	// 初始时，找到的坐标个数为 0。
	int npoints = 0;

	for (int y = 0; y <= (n - size); y++)
		for (int x = 0; x <= (n - size); x++)
			// 找到了空白点。
			if (cell[y][x] == 0)
			{
				// 查看此点是否存在边长为 size 的正方形空白区域。
				bool empty = true;
				for (int i = y; i < (y + size); i++)
				{
					for (int j = x; j < (x + size); j++)
						if (cell[i][j] != 0)
						{
							empty = false;
							break;
						}

					if (!empty)
						break;
				}

				// 存在边长为 size 的空白区域，记录起点坐标。
				if (empty)
				{
					points[npoints].x = x;
					points[npoints].y = y;

					npoints++;
				}
			}

	return npoints;
}

// 输出拼接方案。
void print(square s[NMAX], int nsquares)
{

#ifdef DEBUG_MODE
	cout << "A FILL SOLUTION FOR SQUARE WITH SIZE: " << n << endl;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < n; y++)
			cout << (char) ('A' + backup[x][y] - 1) << " ";
		cout << endl;
	}
#endif

	cout << nsquares << endl;
	for (int i = 0; i < nsquares; i++)
		cout << s[i].x << " " << s[i].y << " " << s[i].size << endl;
}

// 尝试按照拆分方案 blocks 拼接边长为 n 的正方形。
void fill(int blocks[], int ncurrent, int goal, bool display_when_find)
{
	// 所有纸片均已匹配，表明该拆分方案可行，输出。
	if (ncurrent == goal)
	{
		memcpy(backup, cell, sizeof(cell));

		// 是否显示结果。
		if (display_when_find)
			print(squares, ncurrent);
		else
			memcpy(best, squares, sizeof(squares));

		finished = true;
	}
	else
	{
		int npoints;	// 记录找到的坐标个数。
		point points[PMAX];	// 记录起始坐标。

		// 未找到则返回。
		if ((npoints = find(blocks[ncurrent], points)) == 0)
			return;

		// 逐一尝试找到的位置。
		for (int i = 0; i < npoints; i++)
		{
			int x = points[i].x;
			int y = points[i].y;
			int s = blocks[ncurrent];

			// 启发式规则：第一张纸片总是放置在左上角。
			if (ncurrent == 0 && (y != 0 || x != 0))
				continue;

			// 启发式规则：第二张纸片总是放置在右上角。
			if (ncurrent == 1 && (y != 0 || x != blocks[0]))
				continue;

			// 启发式规则：第三张纸片总是放置在左下角。
			if (ncurrent == 2 && (y != blocks[0] || x != 0))
				continue;

			// 启发式规则：第四张纸片总是靠近右侧边放置。
			if (ncurrent == 3 && x != (n - blocks[ncurrent]))
				continue;

			// 启发式规则：第五张纸片总是靠近右侧边或下边放置。
			if (ncurrent == 4 && (x != (n - blocks[ncurrent]) &&
					y != (n - blocks[ncurrent])))
				continue;

			// 记录当前的拼接方法。注意坐标起点的不同，输出要求从起点 （1，1） 
			// 开始输出。
			squares[ncurrent].x = (x + 1);
			squares[ncurrent].y = (y + 1);
			squares[ncurrent].size = s;

			// 标记网格中的相应区域为填充状态。
			for (int gy = y; gy < (y + s); gy++)
				for (int gx = x; gx < (x + s); gx++)
					cell[gy][gx] = s;

			// 继续向前匹配下一张纸片。
			fill(blocks, ncurrent + 1, goal, display_when_find);

			// 是否结束回溯。
			if (finished)
				return;

			// 未结束回溯，表明当前拼接方案不可行，撤销对网格的更改。
			for (int gy = y; gy < (y + s); gy++)
				for (int gx = x; gx < (x + s); gx++)
					cell[gy][gx] = 0;
		}
	}
}

// 排序函数的顺序规则。
bool cmp(int x, int y)
{
	return x > y;
}

// 使用最少纸片数作为剪枝阈值搜索拆分方案。
void cut_by_tip(int area, int blocks[NMAX], int nblocks, int goal)
{
	// 当切分纸片数达到剪枝阈值，但仍有面积剩余，则结束回溯。
	if (area > 0 && nblocks == goal)
		return;

	// 当切分完毕，切分的总纸片数不为剪枝阈值，则结束回溯。
	if (area == 0 && nblocks != goal)
		return;

	// 切分完毕，且切分方案纸片张数为最少。
	if (area == 0)
	{
		int temp[NMAX];

		// 注意数组作为形式参数时，传递的是指针，故不能使用 sizeof(blocks) 来计算
		// 数组 blocks 的大小。
		memcpy(temp, blocks, NMAX * sizeof(int));

		// 将纸片大小按从大到小排序。
		sort(temp, temp + nblocks, cmp);

		// 若在未成功拼接的方案中未找到当前切分方案，则尝试拼接。
		bool exist = false;
		for (int i = 0; i < ncache[nblocks - 1]; i++)
		{
			bool equal = true;
			for (int j = 0; j < nblocks; j++)
				if (cache[nblocks - 1][i][j] != temp[j])
				{
					equal = false;
					break;
				}

			if (equal)
			{
				exist = true;
				break;
			}
		}

		// 不存在则尝试拼接。
		if (!exist)
		{
			// 重置网格。
			memset(cell, 0, sizeof(cell));

			// 尝试拼接。
			fill(temp, 0, nblocks, true);

			// 成功则返回。
			if (finished)
				return;

			// 拼接不成功，予以保存。
			memcpy(cache[nblocks - 1][ncache[nblocks - 1]++],
				temp, sizeof(temp));
		}

	}
	else
	{
		// 找到能切分出的最大边长的纸片。
		int up;
		for (int u = n - 1; u >= 1; u--)
			if (area >= (u * u))
			{
				up = u;
				break;
			}

		// 启发式规则：优先考虑大小在 up / 2 + 1 和  up 之间的纸片。
		for (int r = (up / 2 + 1); r <= up; r++)
		{
			// 启发式规则：第二张纸片的大小与第一张纸片的大小和为 n。
			if (nblocks == 1 && (r + blocks[0]) != n)
				continue;

			// 启发式规则：第三张纸片的大小应该与第二张纸片的大小相同。
			if (nblocks == 2 && r != blocks[1])
				continue;

			// 启发式规则：第四张纸片和第五张纸片的大小之和应该为第一张纸片的大小，
			// 即拼接所得到的正方形某一边纸片数不能超过 3 张。
			if (nblocks == 4 && (r + blocks[3]) != blocks[0])
				continue;

			// 记录当前切分。
			blocks[nblocks] = r;

			// 继续切分。
			cut_by_tip(area - (r * r), blocks, nblocks + 1, goal);

			// 根据 finished 标志决定是否提前退出。
			if (finished)
				return;
		}
	}
}

// 使用回溯法构建拆分方案。参数为尚未切分的面积数量。
void cut_by_hard_work(int area, int blocks[NMAX], int nblocks)
{
	// 当切分纸片数达到当前可行的最小纸片数，但仍有面积剩余，不需继续尝试。
	if (area >= 0 && nblocks > smallest)
		return;

	// 对于纸张数为 smallest 来说，已经找到了一个实际拼接方案，则对于同样的纸张数来说，其他
	// 拆分方案不必再去尝试。    
	if (area == 0 && nblocks == smallest && found)
		return;

	// 启发式规则：至少有两张边长为 1 的纸片。
	if (area == 0 && ncount[1] <= 1)
		return;

	// 切分完毕，且切分方案纸片张数较当前最优值 smallest 小。
	if (area == 0)
	{
		int temp[NMAX];

		// 注意数组作为形式参数时，传递的是指针，故不能使用 sizeof(blocks) 来计算
		// 数组 blocks 的大小。
		memcpy(temp, blocks, NMAX * sizeof(int));

		// 将纸片大小按从大到小排序。
		sort(temp, temp + nblocks, cmp);

		// 不检测当前方案是否与之前生成的未能成功拼接的方案重复，会增加搜索时间。
		// 但检测的话生成方案数很多，需要多量的内存。
		
		// 重置网格。
		memset(cell, 0, sizeof(cell));

		// 尝试拼接。
		finished = false;
		fill(temp, 0, nblocks, false);
		if (finished)
		{
			smallest = nblocks;
			found = true;
		}
	}
	else
	{
		// 找到能切分出的最大边长的纸片。
		int c, r, up, down, step;
		for (r = n - 2; r >= 1; r--)
			if (area >= (r * r))
				break;

		c = r;
		step = (nblocks == 0) ? 1 : (-1);
		r = (nblocks == 0) ? 1 : r;

		for (; c >= 1; c--, r += step)
		{
			// 启发式规则：第一张纸片的大小在 n / 2 + 1 和  n - 2 之间的纸片。
			if (nblocks == 0 && r < (n / 2 + 1))
				continue;

			// 启发式规则：第二张纸片的大小与第一张纸片的大小和为 n。
			if (nblocks == 1 && (r + blocks[0]) != n)
				continue;

			// 启发式规则：第三张纸片的大小应该与第二张纸片的大小相同。
			if (nblocks == 2 && r != blocks[1])
				continue;

			// 启发式规则：第四张纸片和第五张纸片的大小之和应该为第一张纸片的大小，
			// 即拼接所得到的正方形某一边纸片数不能超过 3 张。
			if (nblocks == 4 && (r + blocks[3]) != blocks[0])
				continue;

			// 启发式规则：相同大小的纸片数不超过 4 张。
			if ((ncount[r] + 1) > 4)
				continue;

			ncount[r]++;

			// 记录当前切分。
			blocks[nblocks] = r;

			// 继续切分。
			cut_by_hard_work(area - (r * r), blocks, nblocks + 1);

			ncount[r]--;
		}
	}
}

// 使用已经生成好的最少纸片数拆分方案来得到拼接方案。
void solve_it_by_trick()
{
	// 查找相应质数的的拆分方案。
	int blocks[NMAX];
	int nblocks;

	for (int r = 0; r < NPRIME; r++)
		if (trick[r][0] == n)
		{
			// 找到相应质数的数据，设置纸片总数及具体拆分方案。
			nblocks = trick[r][1];

			for (int c = 0; c < nblocks; c++)
				blocks[c] = trick[r][c + 2];

			break;
		}

	// 重置结束标志。
	finished = false;

	// 重置网格数组。
	memset(cell, 0, sizeof(cell));

	// 根据相应的最佳拆分方案拼接正方形。
	fill(blocks, 0, nblocks, true);
}

// 使用最少纸片数拆分方案的纸片张数作为剪枝阈值，搜索可行的拼接方案。
void solve_it_by_tip()
{
	int blocks[NMAX];

	finished = false;

	memset(ncache, 0, sizeof(ncache));

	// 若使用网络已经提供的拼接边长为 n 的正方形至少需要的纸张数，则可大
	// 大减少搜索时间，否则搜索时间很长。
	int goal = tip[n / 2 - 1];

	// 用回溯法将 n * n 拆分为不大于 smallest 个平方数之和。
	cut_by_tip(n * n, blocks, 0, goal);
}

// 利用求最大公约数的辗转相除法得到较好的拼接剪枝阈值。
void gcd(int a, int b)
{
	if (a < b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	smallest += (a / b) * 2;

	if (a % b != 0)
		gcd(a % b, b);
}

// 完全靠实时回溯生成最少纸片数的拼接方案。
void solve_it_by_hard_work()
{
	int current[NMAX];

	memset(ncache, 0, sizeof(ncache));

	// 若使用网络已经提供的拼接边长为 n 的正方形至少需要的纸张数，则可大大减少搜索时间，否
	// 则搜索时间很长。若不使用，则在计算时需要动态调整 smallest 的值。当 n 逐渐增大时，可
	// 以选择较大的纸片来填充已减少剪枝阈值的值。
	smallest = 1 + n / 2 + (n - 2) / 2 + 4;

	// 当 n 值较大时，试图找到一个更好的剪枝阈值。可以这样寻找：先放一张边长为 s 的纸片在左
	// 上角，然后再放一张边长为 （n - s） 的纸片在右下角，之后在剩余空间先填充边长为 （n -
	// s） 的纸片，剩余的空间则尽可能填充大的正方形，余下的填充边长为 1 的正方形纸片，这样
	// 获得的剪枝阈值较好。实际上可以利用求最大公约数的辗转相除法来得到。
	int threshold = smallest;
	for (int s = (n / 2 + 1); s < (n - 2); s++)
	{
		smallest = 2;

		gcd(s, n - s);

		if (threshold > smallest)
			threshold = smallest;
	}

	smallest = threshold;

	// 用回溯法将 n * n 拆分为不大于 smallest 个平方数之和。
	cut_by_hard_work(n * n, current, 0);

	// 输出最佳方案。
	print(best, smallest);
}

// 输出在坐标 （x，y） 边长为 size 的纸片。
void building(int x, int y, int size)
{
	cout << x << " " << y << " " << size << endl;
}

int main(int ac, char *av[])
{

#ifdef DEBUG_MODE
	clock_t start = clock();
#endif

	int cases;		// 测试数据例数。

	cin >> cases;
	while (cases--)
	{
		cin >> n;

		// 若 n 为偶数，则直接输出拼接方案。
		if (n % 2 == 0)
		{
			int size = n / 2;

			cout << "4" << endl;

			building(1, 1, size);
			building(1, 1 + size, size);
			building(1 + size, 1, size);
			building(1 + size, 1 + size, size);
		}
		// 若 n 为形如 6 * m + 3 的数，则拼接方案与 n = 3 时相同，直接输出拼接方案。
		else if (n % 6 == 3)
		{
			int size = n / 3;

			cout << "6" << endl;

			building(1, 1, size * 2);
			building(1 + size * 2, 1, size);
			building(1 + size * 2, 1 + size, size);
			building(1 + size * 2, 1 + size * 2, size);
			building(1, 1 + size * 2, size);
			building(1 + size, 1 + size * 2, size);
		}
		// 对于 m 和 n，m 为质数且是能整除 n 的最小质数，则有 g（m） = g（n），且
		// 拼接方案类似。若 n 为奇数，且 5 是能整除 n 的最小质数，则 g（5） = g（n），
		// 包括 5 和 25。
		else if (n % 5 == 0)
		{
			int size = n / 5;

			cout << "8" << endl;

			building(1, 1, size * 3);
			building(1 + size * 3, 1, size * 2);
			building(1 + size * 3, 1 + size * 2, size * 2);
			building(1, 1 + size * 3, size * 2);
			building(1 + size * 2, 1 + size * 3, size);
			building(1 + size * 2, 1 + size * 4, size);
			building(1 + size * 3, 1 + size * 4, size);
			building(1 + size * 4, 1 + size * 4, size);
		}
		// 若 n 为奇数，且 7 是能整除 n 的最小质数，则 g（7） = g（n），包括 7 和 49。
		else if (n % 7 == 0)
		{
			int size = n / 7;

			cout << "9" << endl;

			building(1, 1, size * 4);
			building(1 + size * 4, 1, size * 3);
			building(1, 1 + size * 4, size * 3);
			building(1 + size * 3, 1 + size * 5, size * 2);
			building(1 + size * 5, 1 + size * 5, size * 2);
			building(1 + size * 5, 1 + size * 3, size * 2);
			building(1 + size * 4, 1 + size * 3, size);
			building(1 + size * 4, 1 + size * 4, size);
			building(1 + size * 3, 1 + size * 4, size);
		}
		// 对于其他情况，通过回溯找到满足题意的方案。
		else
		{
			// 使用已经生成好的拆分方案尝试拼接。使用此方法 UVa RT 为 0.032s。
			solve_it_by_trick();

			// 直接使用最少纸片数作为剪枝阈值，使用回溯方法获得拆分方案，使用此
			// 方法得到 10 - 50 之间的所有质数的拆分方案运行时间为 27s。
			// solve_it_by_tip();

			// 完全靠实时回溯获得拆分方案，然后尝试拼接，剪枝阈值使用非最优方案的
			// 纸片数。使用此方法在我的笔记本上 （Intel Core2 T5200 1.60GHz，
			// 2.0GiB 内存） 运行了半个多小时才得到 10 - 50 之间质数的拼接方案。
			// solve_it_by_hard_work();
		}
	}

#ifdef DEBUG_MODE
	cout << "TIME ELAPSED: " << (clock() - start) / CLOCKS_PER_SEC << " s." << endl;
#endif

	return 0;
}
