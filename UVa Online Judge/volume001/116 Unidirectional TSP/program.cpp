// Unidirectional TSP
// UVa ID: 116
// Verdict: Accepted
// Submission Date: 2016-04-12
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>

using namespace std;

#define MAXLINE 11
#define MAXROW 101
#define MAXINT (1 << 30 - 1)

int main(int ac, char *av[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
	int line, row, tag, tmp;
	int successor[MAXLINE][MAXROW];
	long long matrix[MAXLINE][MAXROW];
	long long min;
	
	while (cin >> line >> row)
	{
		for (int i = 1; i <= line; i++)
			for (int j = 1; j <= row; j++)
				cin >> matrix[i][j];

		// 从右往左进行动态规划，即列优先处理，从倒数第二列开始，因为需要字典序最小
		// 的最小权和路径，如果从左往右处理，可以得到行号最小的权和方案，但是不一定
		// 是字典序最小的。
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

		// 找第一列权和最小的单元格。
		min = MAXINT;
		for (int i = 1; i <= line; i++)
			if (matrix[i][1] < min)
			{
				min = matrix[i][1];
				tag = i;
			}

		// 输出路径和最小权和。
		cout << tag;
		int next = 1;
		int tmp = tag;
		while (next < row)
		{
			cout << " " << successor[tmp][next];
			tmp = successor[tmp][next];
			next++;
		}

		cout << "\n";
		cout << matrix[tag][1] << "\n";
	}

	return 0;
}
