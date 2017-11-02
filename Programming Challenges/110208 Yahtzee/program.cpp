// Yahtzee （Yahtzee 游戏）
// PC/UVa IDs: 110208/10149, Popularity: C, Success rate: average Level: 3
// 版权所有（C），邱秋，2011。metaphysis at yeah dot net
// Verdict: Accepted
// Submission Date: 2011-05-16
// UVa Run Time: 0.030s

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define NDICES	5		// 每组色子的数量。
#define NROUNDS	13		// 掷色子的轮数。
#define NCOMBINATIONS	8192	// 1 << 13，计分种类的不同组合方式种数。
#define NCATEGORIES	13	// 计分种类。
#define NUPPER	64		// 63（奖励分条件） + 1
#define NBOUNS	35		// 奖励分

// 为计算一个二进制数中 1 的位数定义的宏。
#define POW(c) (1<<(c))
#define MASK(c) (((unsigned long)-1) / (POW(POW(c)) + 1))
#define ROUND(n, c) (((n) & MASK(c)) + ((n) >> POW(c) & MASK(c)))

// 计算整数 n 表示为二进制数时位为 1 的个数。
int bits(int n)
{
    for (int i = 0; i < 5; i++) n = ROUND(n, i);
	return n;
}

// 根据不同计分方式计算一组色子的分值，对于后6种计分方式，需要先判断
// 是否符合该种计分方式的要求，符合则返回相应的分数，否则计 0 分。
int scoring(int dices[NDICES], int category)
{
	// 计一到计六。
	int ret = 0;
	if (category < 6)
	{
		for (int i = 0; i < NDICES; i++)
			if (dices[i] == (category + 1))
				ret += dices[i];
	}
	else
	{
		switch (category)
		{
			// 机会。
			case 6:
				for (int i = 0; i < NDICES; i++) ret += dices[i];
				break;
			// 三同。
			case 7:
				if (dices[0] == dices[2] || dices[1] == dices[3] || dices[2] == dices[4])
					for (int i = 0; i < NDICES; i++)
						ret += dices[i];
				break;
			// 四同。
			case 8:
				if (dices[0] == dices[3] || dices[1] == dices[4])
					for (int i = 0; i < NDICES; i++)
						ret += dices[i];
				break;
			// 五同。
			case 9:
				if (dices[0] == dices[4]) ret = 50;
				break;
			// 小顺。
			case 10:
				bool value[6];
				memset(value, 0, sizeof(value));
				for (int i = 0; i < 5; i++)	value[dices[i] - 1] = true;
				for (int i = 0; i < 3; i++)
					if (value[i] && value[i + 1] && value[i + 2] && value[i + 3])
						ret = 25;
				break;
			// 大顺。
			case 11:
				if (dices[1] == (dices[0] + 1) && dices[2] == (dices[1] + 1) &&
					dices[3] == (dices[2] + 1) && dices[4] == (dices[3] + 1))
					ret = 35;
				break;
			// 葫芦。
			case 12:
				if (dices[0] == dices[1] && dices[2] == dices[4] ||
					dices[0] == dices[2] &&	dices[3] == dices[4])
					ret = 40;
				break;
		}
	}

	return ret;
}
	
void dynamicProgramming(int yahtzee[NROUNDS][NDICES])
{
	int scores[NROUNDS][NROUNDS];	    // 保存各组色子按不同计分方式所得分。
	int sum[NCOMBINATIONS][NUPPER];	    // 保存每种策略的总分数。
	int memo[NCOMBINATIONS][NUPPER][2]; // memo[NCOMBINATIONS][NUPPER][0] 记录每种策略所使用的计分方式
	                                    // memo[NCOMBINATIONS][NUPPER][1] 记录前六项分数。

	// 计算第（i + 1）组色子使用第（j + 1）种计分方式时的得分。
	for (int i = 0; i < NROUNDS; i++)
		for (int j = 0; j < NCATEGORIES; j++)
			scores[i][j] = scoring(yahtzee[i], j);

	// 初始化总分数组为 -1，未选择策略时总分为 0。
	memset(sum, -1, sizeof(sum));
	sum[0][0] = 0;

	int bit, score, flag, all, added;
	// 遍历所有可能的计分组合方式，并计算每种组合方式下的最大分值，
	for (int m = 0; m < NCOMBINATIONS; m++)
	{
	    // 计算当 m 表示为二进制数时，位为 1 的个数，表示当前是为第（bit + 1）组色子选择计分方式。
	    bit = bits(m);
		for (int c = 0; c < NCATEGORIES; c++)
			// 必须保证第（c + 1）种计分方式尚未使用。
			if (!(m & (1 << c)))
			{
				// 设置当前使用策略的二进制标志。
				flag = m | (1 << c);

				// 取第（bit + 1）组色子的第（c + 1）种计分方式得分。
				score = scores[bit][c];

				// 如果所选计分方式为前六种方式之一，则加上该组色子此种计分方式得分。
				added = (c < 6) ? score : 0;	
				for (int u = 0; u < NUPPER; u++)
					if (~sum[m][u])
					{
					    // 按前六项等分之和对总分进行区分。
						all = ((u + added) < (NUPPER - 1) ? (u + added) : (NUPPER - 1));
						if (sum[flag][all] < (sum[m][u] + score))
						{
							memo[flag][all][0] = c;
							memo[flag][all][1] = u;
							sum[flag][all] = sum[m][u] + score;
						}
					}
			}
	}

	// 判断最大总分是否包含奖励分。
	int max = 0, bouns = 0, upper, total;

	// 无奖励分的最大总分值。
	for (int u = 0; u < NUPPER - 1; u++)
		if (sum[NCOMBINATIONS - 1][u] > max)
		{
			max = sum[NCOMBINATIONS - 1][u];
			upper = u;
		}

	// 有奖励分的最大总分值。
	total = max;
	if (sum[NCOMBINATIONS - 1][NUPPER - 1] > -1)
	{
		bouns = NBOUNS;
		total = sum[NCOMBINATIONS - 1][NUPPER - 1] + bouns;
	}

	// 比较两种总分值的大小。
	if (max < total)
	{
		max = total;
		upper = NUPPER - 1;
	}

	// 根据 memo 数组回溯得到解的过程。
	int last = NCOMBINATIONS - 1;
	int category[NROUNDS];
	for (int i = NROUNDS - 1; i >= 0; i--)
	{
		category[i] = memo[last][upper][0];
		upper = memo[last][upper][1];
		last ^= (1 << category[i]);
	}

	// 根据解输出结果。
	for (int i = 0; i < NCATEGORIES; i++)
		for (int j = 0; j < NROUNDS; j++)
			if (category[j] == i)
				cout << scores[j][i] << " ";

	cout << bouns << " " << max << '\n';
}

int main(int ac, char *av[])
{
	int yahtzee[NROUNDS][NDICES];
	string line;
	int count = 0;

	while (getline(cin, line))
	{
		istringstream iss(line);
		for (int i = 0; i < NDICES; i++)
			iss >> yahtzee[count % NROUNDS][i];

		sort(yahtzee[count % NROUNDS], yahtzee[count % NROUNDS] + NDICES);

		if (++count % NROUNDS == 0)
			dynamicProgramming(yahtzee);
	}

	return 0;
}
