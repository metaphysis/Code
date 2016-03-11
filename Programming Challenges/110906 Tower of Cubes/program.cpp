// Tower of Cubes （立方体之塔）
// PC/UVa IDs: 110906/10051, Popularity: C, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-01
// UVa Run Time: 0.168s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 给你 N 个质量各异的彩色立方体。每个立方体都不是单色的 —— 事实上，它们的每一面都被涂上了不同的
// 颜色。你的工作是要用这些立方体建一座最高的塔，使得（1）每个立方体上面的那个立方体都比它轻，（2）
// 每个立方体（除了塔底的立方体）底面的颜色必须和它下面那个立方体的顶面颜色相同。
//
// [输入]
// 输入包含若干组数据。每组数据的第一行为一个整数 N（1 <= N <= 500），表示立方体的数量。接下来
// 的 N 行中，第 i 行描述了第 i 个立方体。该描述中的六个数分别表示这个立方体前、后、左、右、上、
// 下这几个面的颜色，颜色都用 1 ～ 100 之间的整数代表。假设输入立方体的质量是递增的，即第 1 个是
// 最轻的而第 N 个是最重的。
//
// 当 N = 0 是输入结束。
//
// [输出]
// 对于每组数据，按照样例格式现在单独的一行输出数据的序号，然后在下一行输出塔的最大高度。接下来按
// 从上到下的顺序描述塔的每一层。每行描述一个立方体：先给出它的输入序号，然后是空格和一个表示着色
// 方式的字符串（front，back，left，right，top 或者 bottom），分别表示该立方体在塔中的顶面
// 是输入中的那个面。如果有多种解，任意输出一种即可。
//
// 相邻两组数据的输出之间用一个空行隔开。
//
// [样例输入]
// 3
// 1 2 2 2 1 2
// 3 3 3 3 3 3
// 3 2 1 1 1 1
// 10
// 1 5 10 3 6 5
// 2 6 7 3 6 9
// 5 7 3 2 1 9
// 1 3 3 5 8 10
// 6 6 2 2 4 4
// 1 2 3 4 5 6
// 10 9 8 7 6 5
// 6 1 2 3 4 7
// 1 2 3 3 2 1
// 3 2 1 1 2 3
// 0
//
// [样例输出]
// Case #1
// 2
// 2 front
// 3 front
//
// Case #2
// 8
// 1 bottom
// 2 back
// 3 right
// 4 left
// 6 top
// 8 front
// 9 front
// 10 top
//
// [解题方法]
// 每个立方体的一面和它对应的一面构成了一条边，立方体之间又构成一些边，然后需要在这些立方体之间寻
// 找一条最长路径，这就是问题所求。将第一例测试数据转换一下可以看得更明白。
//
// 2 1 2 2 2 1
// | | | | | |  (立方体 1）
// 1 2 2 2 1 2
//
// 3 3 3 3 3 3
// | | | | | | （立方体 2）
// 3 3 3 3 3 3
//   |
// 2 3 1 1 1 1
// | | | | | | （立方体 3）
// 3 2 1 1 1 1
//
// 由上可知可将其建模成有向无环图，然后其最长路径即为所求。由于本题的特点，与 UVa 10029 类似，也
// 可以利用求 LIS（Longest Increasing Subsequence） 的算法予以解决，或者直接使用动态规划来
// 解决，这样可以更方便。为了简便，本题使用动态规划解决。由于立方体的颜色总数最多为 100 种，则可以
// 设立一个数组 tower，其中的元素 tower[i] 表示底面颜色为 i 的塔的最大高度。对于读入的相对应的
// 面对，如 front 和 back 组成一个面对，同理 left 和 right，top 和 bottom组成一个面对，若
// 面对能增加底面颜色为 i 的塔高度，则更新底面颜色为 i 的塔高度，同时记录构成该塔的顶面颜色以便
// 最后输出。

#include <iostream>
#include <cstring>

using namespace std;

#define MAXCOLORS 100
#define FACES 6
#define MAXN 500

int tower[MAXCOLORS + 1];	// 底面颜色为 i 所能构成的塔的最大高度。
int temp[MAXCOLORS + 1];	// 临时保存避免直接在 tower 数组上操作，避免破坏结果。
int path[MAXCOLORS + 1][MAXN + 1];	// 底面颜色为 i 构成的最大高度塔的各顶面颜色。
int backup[MAXCOLORS + 1][MAXN + 1];	// 临时操作，避免破坏数组 path 的结果。

int main(int ac, char *av[])
{
	int n, cases = 1, top, bottom;
	string faces[FACES] = { "front", "back", "left", "right", "top", "bottom" };

	while (cin >> n, n)
	{
		// 相邻两组输出用空格隔开。
		if (cases > 1)
			cout << endl;

		// 将各颜色能得到的最大塔高度即相应路径重置。
		memset(tower, 0, sizeof(tower));
		memset(path, 0, sizeof(path));

		// 最大塔高初始为 0。
		int highest = 0;
		
		// 记录能得到最大高度的底面颜色。
		int color = 0;
		
		// 处理时，一次读入两个面的颜色，作为顶面和底面的颜色。
		for (int i = 1; i <= n; i++)
		{
			// 在当前结果的副本上操作。
			memcpy(temp, tower, sizeof(tower));
			memcpy(backup, path, sizeof(path));
			for (int j = 1; j <= (FACES / 2); j++)
			{
				cin >> top >> bottom;
				// 若底面颜色为 bottom 的塔高度小于当前所找到的最大高度
				// 的塔，则替换，将路径复制到副本上。
				if ((tower[top] + 1) > temp[bottom])
				{
					memcpy(backup[bottom], path[top], sizeof(path[top]));
					backup[bottom][i] = 2 * j - 1;
					
					temp[bottom] = tower[top] + 1;
					if (temp[bottom] > highest)
					{
						highest = temp[bottom];
						color = bottom;
					}
				}
				
				// 若底面颜色为 top 的塔高度小于当前所找到的最大高度
				// 的塔，则替换，将路径复制到副本上。
				if ((tower[bottom] + 1) > temp[top])
				{
					memcpy(backup[top], path[bottom], sizeof(path[bottom]));
					backup[top][i] = 2 * j;
					
					temp[top] = tower[bottom] + 1;
					if (temp[top] > highest)
					{
						highest = temp[top];
						color = top;
					}
				}
			}
			// 将副本上的数据还原。
			memcpy(tower, temp, sizeof(temp));
			memcpy(path, backup, sizeof(backup));
		}

		// 输出结果。
		cout << "Case #" << cases++ << endl;
		cout << highest << endl;
		for (int i = 1; i <= n; i++)
			if (path[color][i])
				cout << i << " " << faces[path[color][i] - 1] << endl;
	}

	return 0;
}
