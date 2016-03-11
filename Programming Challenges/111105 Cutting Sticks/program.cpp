// Cutting Sticks （切割木棍）
// PC/UVa IDs: 111105/10003, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-10-14
// UVa Run Time: 0.548s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 是否可以使用贪心法来解决？
//
// 题目是具有最优子结构性质的。最优解是在某一个切割点进行切割，得到的两段棍子的切割费用之和最小值，
// 设切割后棍子分为 A，B 两段，而棍子 A，B 各自的最小费用，同样是在各自某一切割点进行切割后，切割
// 费用和的最小值。
//
// 但是本题的最优子结构能不能得出一个有效的贪心策略呢？
//
// 第一种策略：如样例输入给出的第一组数据，在接近中心的切割点进行切割总费用是最小的，但是对于第二
// 组数据就不是这样。
//
// 第二种策略，在这样的切割点进行切割：在此切割点切割后，左右两段棍子的长度尽量相等，这种策略对第
// 一组数据是适用的，但是对于第二组数据失效了。
//
// 第三种策略，观察第二组测试数据，第一次切割点选在 4，然后形成一个长度为 6，需要切割点为 1，3，4
// 的棍子，刚好在 3 处切割，形成两根长度为 3 的棍子，此方案切割费用最小，为 22，那么是否可以将此
// 策略一般化？答案，否定，如以下测试数据：
//
// 10
// 1 2 3 7
//
// 无法在第一次选择时做出决定，选 1 还是选 7 好。
//
// 综上述，对于贪心法来说，似乎本题无法使用有效的策略来为每一步决定一个最优选择。
//
// 使用动态规划如何？
//
// 对于第一次切割，在任何一个切割点进行，都会将棍子切割成两段 A 和 B，很明显，最小切割费用应该是
// 对棍子 A 和 B 继续进行切割的费用和的最小值，当然对棍子 A 和 B 也应该是一样的，这样似乎有递归
// 的味道。那么不妨设 minCost[i][j] 为对第 i 个切割点起始至第 j 个切割点结束这段棍子的最小切割
// 费用，为了解题方便，假设有 k 个切割点，并设初始时棍子左端为第 0 个切割点，棍子右端为第 k + 1
// 个切割点，切割点 i 距离棍子左端的距离为 places[i]，则有以下递推关系：
//
// minCost[i][j] = min{minCost[i][j], minCost[i][c] + minCost[c][j] + (places[j]
// - places[i])|i < c < j}
//
// 初始时，切割点 i 到 切割点 i + 1 的棍子切割费用为 0，因为两端都为切割点，无须再切割。在递归
// 求解时，可以使用表格式 DP 加快求解速度，因为本题的测试数据似乎很多。

#include <iostream>

using namespace std;

#define min(a, b) ((a) <= (b) ? (a) : (b))

#define MAXCUTS 55
#define MAXCOST (1 << 20)

int length, cuts;
int places[MAXCUTS] = { 0 };
int minCost[MAXCUTS][MAXCUTS];

// 递归 + 表格式 DP。
int cost(int start, int end)
{
	if (minCost[start][end] < MAXCOST)
		return minCost[start][end];
	
	for (int i = (start + 1); i <= (end - 1); i++)
	{
		int tmpCost = cost(start, i) + cost(i, end);
		tmpCost += (places[end] - places[start]);
		
		if (tmpCost < minCost[start][end])
			minCost[start][end] = tmpCost;
	}
	
	return minCost[start][end];
}

int main(int ac, char *av[])
{
	int money;

	while (cin >> length, length)
	{
		// 在棍子两端新增两个切割点 0 和 length。
		cin >> cuts;
		for (int i = 1; i <= cuts; i++)
			cin >> places[i];
		places[cuts + 1] = length;

		// 若切割次数大于 0 才计算。
		money = 0;
		if (cuts)
		{
			for (int i = 0; i < MAXCUTS; i++)
				for (int j = 0; j < MAXCUTS; j++)
					minCost[i][j] = MAXCOST;
			for (int i = 0; i <= cuts; i++)
				minCost[i][i + 1] = 0;

			cost(0, cuts + 1);
			money = minCost[0][cuts + 1];
		}

		cout << "The minimum cutting is " << money << ".\n";
	}

	return 0;
}
