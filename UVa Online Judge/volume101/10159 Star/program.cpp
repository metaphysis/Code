// Star （六角星）
// PC/UVa IDs: 111203/10159, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.056s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXLINES 12		// 行数。
#define MAXCELLS 48		// 小格总个数。
#define MAXINT 10
#define EMPTY (-1)
#define MAXTYPES (1 << 12)

int maxValue[MAXLINES];		// 每行的最大值。
int cells[MAXCELLS];		// 小格内数字值。

// 每个小格属于那些行，行使用题目所给的 A - I 表示。从 0 开始，按从上到下，从左至右的顺序编号。
string belongs[MAXCELLS] = {
	"EL", 	// 0
	"EK", "EL", "FL",	// 1 - 3
	"AI", "AI", "AJ", "AEJ", "AEK", "AFK", "AFL", "AGL", "AG", "AH", "AH",	// 4 - 14
	"BI", "BEI", "BEJ", "BFJ", "BFK", "BGK", "BGL", "BHL", "BH",	// 15 - 23
	"CE", "CEI", "CFI", "CFJ", "CGJ", "CGK", "CHK", "CHL", "CL",	// 24 - 32
	"DE", "DE", "DF", "DFI", "DGI", "DGJ", "DHJ", "DHK", "DK", "DL", "DL",	// 33 - 43
	"GI", "HI", "HJ",	// 44 - 46
	"HI"	// 47
};

// 非 EMPTY 元素值表示组成该行的小格编号，从 0 开始，按从上到下，从左至右的顺序编号。
int lines[MAXLINES][MAXLINES - 1] = {
	{ 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 },
	{ 15, 16, 17, 18, 19, 20, 21, 22, 23, EMPTY, EMPTY },
	{ 24, 25, 26, 27, 28, 29, 30, 31, 32, EMPTY, EMPTY },
	{ 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43 },
	{ 0, 1, 2, 7, 8, 16, 17, 24, 25, 33, 34 },
	{ 3, 9, 10, 18, 19, 26, 27, 35, 36, EMPTY, EMPTY },
	{ 11, 12, 20, 21, 28, 29, 37, 38, 44, EMPTY, EMPTY },
	{ 13, 14, 22, 23, 30, 31, 39, 40, 45, 46, 47 },
	{ 4, 5, 15, 16, 25, 26, 36, 37, 44, 45, 47 },
	{ 6, 7, 17, 18, 27, 28, 38, 39, 46, EMPTY, EMPTY },
	{ 1, 8, 9, 19, 20, 29, 30, 40, 41, EMPTY, EMPTY },
	{ 0, 2, 3, 10, 11, 21, 22, 31, 32, 42, 43 }
};

// 动态规划求最小可能值，思想可参考本博客的 UVa Problem 10149 Yahtzee 题解，这里使用了 tmp
// 数组，在原 sum 数组计算的结果先填写在 tmp 数组上，以免持续在 sum 数组上操作引起混乱，同时
// 注意最小可能值方案一定是将最大可能值方案中某些小格置 0 而得来的（为什么这样，可以思考一下！）。
int dynamic_programming()
{
	int sum[MAXTYPES], tmp[MAXTYPES];
	
	// 初始化。
	memset(sum, EMPTY, sizeof(sum));
	
	// 当无任何行匹配时，和最小值为 0.
	sum[0] = 0;

	for (int i = 0; i < MAXLINES; i++)
	{
		// 在副本上操作。
		memcpy(tmp, sum, sizeof(sum));
		for (int j = 0; j < MAXTYPES; j++)
			if (sum[j] > EMPTY)
			{
				for (int k = 0; k < MAXLINES - 1; k++)
				{
					// 空小格，该行已处理完毕。
					if (lines[i][k] == EMPTY)
						break;

					// 只需处理值为该行最大值的小格。
					if (cells[lines[i][k]] == maxValue[i])
					{
						int t = j;
						// cell 表示该小格属于哪些行。
						string cell = belongs[lines[i][k]];
						for (int c = 0; c < cell.length(); c++)
							// 注意条件！只有当小格的值满足了某行的最大值要求，才计
							// 入 t。t 的意义是该小格值满足了哪些行的最大值要求。
							// 使用匹配的行的序号作为移位值来生成一个唯一表示该行的
							// 整数。
							if (cells[lines[i][k]] == maxValue[cell[c] - 'A'])
								t = t | (1 << (cell[c] - 'A'));

						// 更新和的最小值。
						if (tmp[t] > EMPTY)
							tmp[t] = min(tmp[t], sum[j] + maxValue[i]);
						else
							tmp[t] = sum[j] + maxValue[i];
					}
				}
			}

		// 获得副本上的结果。
		memcpy(sum, tmp, sizeof(tmp));
	}

	return sum[MAXTYPES - 1];
}

int main(int ac, char *av[])
{
	string line;

	while (getline(cin, line))
	{
		// 读入每行的最大值限制。
		istringstream iss(line);
		for (int i = 0; i < MAXLINES; i++)
			iss >> maxValue[i];

		// 根据限制，获得每个方格的最大值。
		memset(cells, 0, sizeof(cells));
		for (int i = 0; i < MAXCELLS; i++)
		{
			int value = MAXINT;
			for (int j = 0; j < belongs[i].length(); j++)
				value = min(value,
					maxValue[belongs[i][j] - 'A']);

			cells[i] = value;
		}

		// 检查方格的值是否满足最大值要求。
		bool noSolution = false;
		for (int i = 0; i < MAXLINES; i++)
		{
			int tmp = 0;
			for (int j = 0; j < MAXLINES - 1; j++)
			{
				if (lines[i][j] == EMPTY)
					break;
				tmp = max(tmp, cells[lines[i][j]]);
			}
			
			if (tmp != maxValue[i])
			{
				noSolution = true;
				break;
			}
		}
		
		// 输出。
		if (noSolution)
			cout << "NO SOLUTION" << endl;
		else
		{
			// 数字和最大可能值。
			int maxSum = 0;
			for (int i = 0; i < MAXCELLS; i++)
				maxSum += cells[i];

			// 数字和最小可能值。最小可能值的含义是取尽可能少的数字，使得满足所有
			// 最大值的要求。由于前面的最大可能值方案中已经包含了最小可能值的方案，
			// 需要将一些小格置为 0 来获得最小可能值，如果小格置 0 的数目越多，
			// 当然最后和更小，那么就要求一个小格的数字尽可能满足多行的最大值要求，
			// 这样可以减少非零数字的使用，可以使用动态规划找最小值。
			int minSum = dynamic_programming();

			cout << minSum << " " << maxSum << endl;
		}
	}

	return 0;
}
