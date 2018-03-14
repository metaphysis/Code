// Slash Maze （斜线迷宫）
// PC/UVa IDs: 110904/705, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-09-28
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 通过用斜线（/）和反斜线（\）来填充一个矩形，你可以得到一个小迷宫，例如：
//
// （由于 gedit 不能插入图片，请参考 UVa 上原题的图片，原题链接：http://uva.onlinejudge.o
// rg/index.php?option=com_onlinejudge&Itemid=8&category=37&page=show_problem&pr
// oblem=646。）
//
// 正如你所看到的，迷宫中的通路从不分叉，因此整个迷宫中只有（1）环状通路以及（2）从一个地方进入并
// 从另外一个地方出去的通路。我们只对环感兴趣。在上述例子中有两个环。
//
// 你的任务是要写一个程序来计算最长的环的长度。环的长度被定义为组成这个环的小正方形（在图中用灰色
// 线条标记）的数量。在上述例子中，长环的长度为 16，短环的长度为 4。
//
// [输入]
// 输入包含若干组数据。每组数据的第一行两个整数 w 和 h（1 <= w，h <= 75），分别代表迷宫的宽度
// 和高度。接下来的 h 行，每行有 w 个字符，描述整个迷宫。这些字符都是“/”或“\”。
//
// 当 w = h = 0 时输入结束。这一行不必处理。
//
// [输出]
// 对于每个迷宫，先输出一行“Maze #n:”，其中 n 为迷宫序号。然后输出一行“k Cycles; the longest
// has length l.“，其中 k 为迷宫中环的数量，l 是最长环的长度。如果这个迷宫中没有环，输出”There
// are no cycles.“
//
// 在每组数据的输出后打印一个空行。
//
// [样例输入]
// 6 4
// \//\\/
// \///\/
// //\\/\
// \/\///
// 3 3
// ///
// \//
// \\\
// 0 0
//
// [样例输出]
// Maze #1:
// 2 Cycles; the longest has length 16.
//
// Maze #2:
// There are no cycles.
//
// [解题方法]
// 若是正常的迷宫，横平竖直的自然是比较好解决的，但是该题是用斜线表示的迷宫，初看不是很好处理，实
// 际上将斜线和反斜线构成的迷宫所隐含的图显式的构建出来，转换成直线型的迷宫，然后使用图遍历的算法
// 或者 Flood fill 算法或 Union-Find 算法计算最大环长度。
//
// 观察题目所给的图可以知道，斜线和反斜线占据了两个小正方形的边，那么可以将斜线占据的边使用 1 来
// 表示，反斜线占据的边用 2 来表示，未占据的边使用 0 来表示，那么题目所给的图转换成如下的矩阵：
//
// 200101202001
// 021010020210
// 200101012001
// 021010100210
// 010120200120
// 101002021002
// 200120010101
// 021002101010
//
// 问题转化为在此矩阵中寻找从值为 0 的位置出发能够回到出发位置的最长路径。先从矩阵的最外边寻找为
// 0 的位置，使用 Flood fill 算法将与该 0 位置连通的位置全部置为 3，表示这些点已经处理掉，因为
// 这些位置是不可能构成环的，这个是很明显的（不明白的话再想一下...）。将矩阵周边的 0 位置全部处
// 理掉后，矩阵变成：
//
// 233131232331
// 321310023213
// 233101012331
// 321010100213
// 310120200123
// 101002021332
// 200120013131
// 321332131313
//
// 经过处理后，所有不能够成环的 0 位置都已经处理掉了，此时从矩阵中任意选择一个 0 位置，使用
// Flood fill 算法遍历与该 0 位置能连通的所有位置，并将其置为 3，记录这个过程中找到 0 的次数，
// 即为该环的长度。
//
// 唯一需要注意的是在遍历时方向的选择问题，由于已经将正反斜线予以标记，只需朝位置为 0 的方向走即可，
// 在走的过程需要依据当前相邻的正反斜线决定可行的方向。
//
// Flood fill 算法介绍：
// http://en.wikipedia.org/wiki/Flood_fill。
//
// Union-Find 算法介绍：
// http://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf。

#include <bits/stdc++.h>

using namespace std;

#define MAXV 150

#define EMPTY 0
#define SLASH 1
#define BACKSLASH 2
#define VISITED 3

#define LEFT_UP 0
#define UP 1
#define RIGHT_UP 2
#define LEFT 3
#define RIGHT 4
#define LEFT_BOTTOM 5
#define DOWN 6
#define RIGHT_BOTTOM 7

struct mazes
{
	int status[MAXV][MAXV];
	int width, height;
};

int length;
int offset[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0},
	{1, 1} };

// 检查坐标是否在矩阵内。
inline bool in_range(int line, int row, int width, int height)
{
	return ((0 <= line && line < height) && (0 <= row && row < width));
}

// 使用 Flood fill 算法将与位置（line，row）相连通的位置其值置为 VISITED。Flood fill 算法
// 实际上是深度优先搜索的思想。
void flood_fill(mazes * maze, int line, int row)
{
	length++;
	maze->status[line][row] = VISITED;

	for (int d = LEFT_UP; d <= RIGHT_BOTTOM; d++)
	{
		int tline = line + offset[d][0];
		int trow = row + offset[d][1];

		if (in_range(tline, trow, maze->width, maze->height))
			if (maze->status[tline][trow] == EMPTY)
			{
				// 左，右，上，下的 0 位置总是可以直接走的。
				if (tline == line || trow == row)
					flood_fill(maze, tline, trow);
				// 对角线上的 0 位置才需要判断。
				else
				{
					// 左上角的 0 位置可行的条件是其左侧不为斜线。
					if (d == LEFT_UP)
						if (maze->status[line][row - 1] != SLASH)
							flood_fill(maze, tline, trow);
					// 右下角的 0 位置可行的条件是其右侧不为斜线。
					if (d == RIGHT_BOTTOM)
						if (maze->status[line][row + 1] != SLASH)
							flood_fill(maze, tline, trow);
					// 左下角的 0 位置可行的条件是其左侧不为反斜线。
					if (d == LEFT_BOTTOM)
						if (maze->status[line][row - 1] != BACKSLASH)
							flood_fill(maze, tline, trow);
					// 右上角的 0 位置可行的条件是其右侧不为反斜线。
					if (d == RIGHT_UP)
						if (maze->status[line][row + 1] != BACKSLASH)
							flood_fill(maze, tline, trow);
				}
			}
	}
}

int main(int ac, char *av[])
{
	mazes maze;
	int width, height, cases = 1;
	char slash;
	bool is_backslash;

	while (cin >> width >> height, width && height)
	{
		// 注意在读入数据时是将给定迷宫长和宽各扩大两倍来表示。
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				cin >> slash;
				
				is_backslash = (slash == '\\');
				maze.status[i * 2][j * 2] = is_backslash ? BACKSLASH : EMPTY;
				maze.status[i * 2][j * 2 + 1] = is_backslash ? EMPTY : SLASH;
				maze.status[i * 2 + 1][j * 2] = is_backslash ? EMPTY : SLASH;
				maze.status[i * 2 + 1][j * 2 + 1] = is_backslash ? BACKSLASH : EMPTY;				
			}

		maze.width = 2 * width;
		maze.height = 2 * height;

		// 处理矩阵周边的 0。
		for (int i = 0; i < maze.height; i++)
			for (int j = 0; j < maze.width; j++)
				if (maze.status[i][j] == EMPTY)
					if (i == 0 || j == 0 || i == (maze.height - 1)
						|| j == (maze.width - 1))
						flood_fill(&maze, i, j);

		// 获取最大环长度。
		int maximum = 0, cycles = 0;
		for (int i = 0; i < maze.height; i++)
			for (int j = 0; j < maze.width; j++)
				if (maze.status[i][j] == EMPTY)
				{
					cycles++;
					
					length = 0;
					flood_fill(&maze, i, j);

					if (maximum < length)
						maximum = length;
				}

		// 输出结果，注意每组数据后需要输出空行。
		cout << "Maze #" << cases++ << ":" << endl;
		if (maximum > 0)
		{
			cout << cycles;
			cout << " Cycles; the longest has length ";
			cout << maximum << ".";
		}
		else
			cout << "There are no cycles.";
		cout << endl << endl;
	}

	return 0;
}
