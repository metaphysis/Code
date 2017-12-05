// Weights and Measures （重量和力量）
// PC/UVa IDs: 111007/10154, Popularity: C, Success rate: average Level: 3
// Verdict: Programming Challenges - Solved, UVa - Accepted
// Submission Date: 2011-10-12
// UVa Run Time: 0.080s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// I know, up on top you are seeing great sights,
// But down at the bottom, we, too, should have rights.
// We turtles can't stand it. Our shells will all crack!
// Besides, we need food. We are starving!" groaned Mack.
//
// 			Yertle the Turtle, Dr.Seuss
//
// [Problem Description]
// A turtle named Mack, to avoid being cracked, has enlisted your advice as to
// the order in which turtles should be stacked to form Yertle the Turtle’s throne.
// Each of the 5,607 turtles ordered by Yertle has a different weight and strength.
// Your task is to build the largest stack of turtles possible.
//
// [Input]
// Standard input consists of several lines, each containing a pair of integers
// separated by one or more space characters, specifying the weight and strength
// of a turtle. The weight of the turtle is in grams. The strength, also in grams,
// is the turtle’s overall carrying capacity, including its own weight. That is,
// a turtle weighing 300 g with a strength of 1,000 g can carry 700 g of turtles
// on its back. There are at most 5,607 turtles.
//
// [Output]
// Your output is a single integer indicating the maximum number of turtles that
// can be stacked without exceeding the strength of any one.
//
// [Sample Input]
// 300 1000
// 1000 1200
// 200 600
// 100 101
//
// [Sample Output]
// 3
//
// [解题方法]
// 开始以为是很简单的 DP 题，把乌龟按可承重重量增序排列，若可承重重量相同，则体重轻的排上面，然后
// DP 求能得到的最大高度。程序在 Programming Challenges 倒是通过了，但是在 UVa 上是 WA。阅
// 读了 UVa BBS 上的帖子，才发现之所以在 PC 上通过是因为其测试数据太弱（汗...）。
//
// 先分析一下按可承重重量增序排列，若可承重重量相同，体重轻的排上面的方法为什么不可行。可
// 承重重量除了给出这只乌龟还能承重的重量外，不能给出更多信息了，如两只乌龟，重量和力量如下：
//
// （1）10 50
// （2）100 120
//
// 如果按照上述的排序方法乌龟（1）应该排在下方，（2）排在上方，能形成的乌龟塔最高为 1，但是实际上
// 若（2）在下，（1）在上，是能形成高度为 2 的乌龟塔的。所以按这种排序方法是不能达到乌龟顺序的最
// 优子结构的，所以也就不能保证一定获得最优解。
//
// 若按重量增序，重量相同按力量增序的顺序排列乌龟，也会得到错误的答案，因为没有考虑到乌龟的可承重
// 重量，反例如下：
//
// （1）10 1000
// （2）20 1000
// （3）30 40
//
// 排好序后乌龟塔的最高高度为 2，实际上应该是 3，只需将（3）放在最上面即可。
//
// 若按力量增序排列，力量相同按体重增序排列，从第一只乌龟开始处理，设当前新增加的乌龟为 i，从 1 到
// i - 1 搜索总重量小于乌龟 i 的可承重重量，且高度能增加的乌龟 j，更新乌龟 i 的总承重重量和能堆
// 叠的最大高度，使用这种方法，对于一般的测试数据，都能得到正确的答案，但是对于如下测试数据，却不能
// 得到正确的答案（之前我就是使用这种方法）：
//
// （1）101 101
// （2）100 201
// （3）99 300
// （4）98 301
// （5）5 302
//
// 前述算法能得到的最大高度是 3，实际上将（2），（3），（4），（5）堆叠起来可以得到高度为 4 的乌
// 龟塔，为什么算法失效了？因为在第二步处理乌龟（2）的时候，因为乌龟（1）能放在乌龟（2）上，故乌龟
// （2）拥有了最大高度 2，从而在处理后续乌龟时，（2）不能作为单独乌龟放置在其他乌龟上，只能是和
// （1）做为一个整体来放置，所以需要记录能达到高度 K 的乌龟塔时，乌龟的最小总重量，这样在构建乌龟
// 塔时，总是选择当前能堆叠最高且总重量最小的乌龟，才有可能构建更高的乌龟塔。
//
// 那么是否可以按力量来进行排序？答案是肯定的，假设有两只乌龟，重量和力量分别为 W1，S1，W2，S2，
// 且有 S1 <= S2，那么排序如下：
//
// W1 S1
// W2 S2
//
// 若力量为 S1 的乌龟能支撑起包括 W2 在内的乌龟重量，则有 S1 >= （W1 + W2），因为有 S2 >= S1
// 则力量为 S2 的乌龟总是同样能支撑起来，但是反过来就不一定了，即 S2 >= （W1 + W2），不一定有
// S1 >= （W1 + W2），故按力量来排序总是不会改变最优结构的。
//
// 综上所述，使用一个二维数组记录使用前 i 只乌龟形成高度为 h 的塔时的最小总重量，设为 minWeight
// [h][i]，有以下转移方程：
//
// minWeight[h][i] = min{minWeight[h][i - 1]，minWeight[h - 1][i - 1] + weight[i]}
//
// 其中第二个是有条件的，即 minWeight[h - 1][i - 1] + weight[i] <= strength[i]。同样的，
// 因为有较多的乌龟，若使用二维数组因数组很大而会引起段错误，可以使用一维滚动数组来代替优化空间使
// 用以避免出现因分配过多内存导致段错误。为什么可以用一维数组来优化，这是题目的转移方程决定的，在
// 最开始的时候，乌龟数目为 0，形成高度为 0 的乌龟塔时，最小总重量当然为 0，但是对于 1 至乌龟
// 总数的高度，是不可能堆叠成的，可设其最小总重量为一 MAXINT 值来标记。此时数组元素如下：
//
// minWeight[0][0] 0
// minWeight[1][0] MAXINT
// minWeight[2][0] MAXINT
//       ...        ...
// minWeight[N][0] MAXINT
//
// 假设需要计算乌龟数目为 1 时，形成的高度为 1 的乌龟塔最小总重量时，则根据转移方程，有：
//
// minWeight[1][1] = min{minWeight[1][0]，minWeight[0][0] + weight[1]}
//
// 当然第二个值是有条件的（这里假设满足条件），从数组的元素可以知道，minWeight[1][0] 已经存在于
// 数组中，minWeight[0][0] 也存在于数组中，最后计算得到的值 minWeight[1][1]，所存放的位置与
// minWeight[1][1] 行标号相同，只不过列标号增加 1，此后列为 0 的元素就不会被使用了，那么可以直
// 接省略掉列标号，变成一维数组：
//
// minWeight[0] minWeight[1] minWeight[2] ... minWeight[N]
//       0         MAXINT       MAXINT    ...    MAXINT
//
// 只不过在计算的时候，为了不覆盖前一次计算的值，每次都从最后一个元素开始使用转移方程往前计算即可。
// 前面的 UVa 10069 Distinct Subsequences 也可以使用的同样的方法来优化。

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 5610
#define MAXINT (1 << 20)

class turtle
{
public:
	int weight;
	int strength;

	bool operator<(const turtle &other) const
	{
		// 力量大的的在下方。
		if (strength != other.strength)
			return strength < other.strength;

		// 若力量相同，则重的乌龟在下方。
		return weight < other.weight;
	};
};

int main(int ac, char *av[])
{
	turtle turtles[MAXN];
	int minWeight[MAXN];
	int nTurtles = 1, weight, strength;
	
	while (cin >> weight >> strength)
	{
		if (weight > strength)
			continue;

		turtles[nTurtles++] = (turtle){weight, strength};
	}

	// 按承重和自身重量排序。
	sort(turtles + 1, turtles + nTurtles);
	nTurtles--;

	// 赋初值，若为 MAXINT 则不可能形成高度为 h 的乌龟塔。
	minWeight[0] = 0;
	for (int h = 1; h <= nTurtles; h++)
		minWeight[h] = MAXINT;

	// DP 找最大高度。
	int answer = 1;
	for (int i = 1; i <= nTurtles; i++)
		for (int h = nTurtles; h >= 1; h--)
		{
			if (minWeight[h - 1] + turtles[i].weight <= turtles[i].strength)
			minWeight[h] = min(minWeight[h], minWeight[h - 1] + turtles[i].weight);

			if (minWeight[h] < MAXINT)
				answer = max(answer, h);
		}

	cout << answer << endl;

	return 0;
}
