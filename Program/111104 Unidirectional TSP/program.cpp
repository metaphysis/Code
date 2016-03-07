// Unidirectional TSP （单向旅行商问题）
// PC/UVa IDs: 111104/116, Popularity: A, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-12
// UVa Run Time: 0.252s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [题目 PDF 文件下载地址]
// http://uva.onlinejudge.org/external/1/116.pdf
//
// [解题方法]
// 每个格子只能接受来自其左方、左上方、左下方走过来的路线，那么只要选择其中权和最小的路线，则当前
// 经过此格的路线的权和就是最小的，状态转移方程：
//
// matrix[i][j] += min{matrix[i][j - 1]，matrix[i - 1][j - 1]，matrix[i + 1][j - 1]}
//
// 简单的 DP，不过题目的条件加了一个小小的意外情况，第一行和最后一行可以相连，不过这并没有增加什么
// 难度，只需单独处理第一行和最后一行即可。注意：题目要求输出权和最小且字典序最小的路径，如果从左
// 往右进行 DP，虽然当每一列权和最小时行号都是最小，但是不能保证输出的是字典序最小的路径，反例如下：
//
// 3 4 1 2 8 6
// 1 2 8 2 1 1
// 5 9 3 9 9 5
// 1 1 1 3 1 1
// 3 7 2 8 6 4
//
// 如果是从左往右选权和最小的路径，则直接走第四行是权和最小的，但是字典序最小的却是 2 - 2 - 1 -
// 1 - 2 - 2，所以需要从右往左进行 DP，这样保证每一次都是权和最小，同时选择行号最小的以保证字典
// 序。因为题目给定的数不一定是整数，虽然路径权和不会超过 30 个比特，但是列数最多有 100 列，故需
// 要考虑使用 long long 型整数。

#include <iostream>

using namespace std;

#define MAXLINE 11
#define MAXROW 101
#define MAXINT (1 << 30 - 1)

int main(int ac, char *av[])
{
	int line, row, tag, tmp;
	int successor[MAXLINE][MAXROW];
	long long matrix[MAXLINE][MAXROW];
	long long min;
	
	while (cin >> line >> row)
	{
		for (int i = 1; i <= line; i++)
			for (int j = 1; j <= row; j++)
				cin >> matrix[i][j];

		// 列优先处理，从倒数第二列开始处理，因为需要字典序最小的最小权和路径，如果从左
		// 往右处理，可以得到行号最小的权和方案，但是不一定是字典序最小的。
		for (int j = row - 1; j >= 1; j--)
		{
			for (int i = 1; i <= line; i++)
			{
				min = MAXINT;

				tmp = (i == 1 ? line : i - 1);
				if (min > matrix[tmp][j + 1])
				{
					min = matrix[tmp][j + 1];
					tag = tmp;
				}
				else if (min == matrix[tmp][j + 1] && tag > tmp)
					tag = tmp;

				if (min > matrix[i][j + 1])
				{
					min = matrix[i][j + 1];
					tag = i;
				}
				else if (min == matrix[i][j + 1] && tag > i)
					tag = i;

				tmp = (i == line ? 1 : i + 1);
				if (min > matrix[tmp][j + 1])
				{
					min = matrix[tmp][j + 1];
					tag = tmp;
				}
				else if (min == matrix[tmp][j + 1] && tag > tmp)
					tag = tmp;

				matrix[i][j] += min;
				successor[i][j] = tag;
			}
		}

		// 找权和最小的单元格。
		min = MAXINT;
		for (int i = 1; i <= line; i++)
			if (matrix[i][1] < min)
			{
				min = matrix[i][1];
				tag = i;
			}

		// 输出。
		cout << tag;
		int next = 1;
		int tmp = tag;
		while (next < row)
		{
			cout << " " << successor[tmp][next];
			tmp = successor[tmp][next];
			next++;
		}

		cout << endl;
		cout << matrix[tag][1] << endl;
	}

	return 0;
}
