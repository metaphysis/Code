// Tug of War （拔河）
// PC/UVa IDs: 110805/10032, Popularity: B, Success rate: low Level: 2
// Verdict: UVa Online Judge - Wrong answer, Programming-Challenges - Solved
// Submission Date: 2011-08-09
// Programming-Challenges Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 直接枚举子集不可行，因为给定的子集数目太大。解题思路如下：确定所有子集所能得到的不同的总重量，
// 子集的不同总重量个数要比子集数目少得多。为了获得所有可能的总重量，可以先将重量按从小到大的顺序
// 排列，设第一队人员总数为 i，第二队人员总数为 j，所有人员的总体重为 G，总人数为 N，根据题意，
// 两队人员相差不能超过一个人，故 i 和 j 可根据总人数 N 来确定，若 N 为偶数，则 i = j = 
// [N / 2]，若 N 为奇数，则 i = [N / 2]，j = [N / 2] + 1，符号 [] 表示取整。由于已经将体
// 重值按从小到大的顺序排列，则可以知道前 i 个人的体重和是所能得到的最小体重值，后 j 个人的体重
// 和是能得到的最大体重值。则某队的体重值只可能在此范围内变化，为了得到差值最小的两队体重分布，可
// 以比较前 i 个人与后 j 个人的体重差值，取最先得到最小差值的两个人，交换他们的体重，判断是否达
// 到总体重的一半，若达到可返回，若仍小于总体重的一半，将交换后的两队人员体重值按从小到大的顺序排
// 序，继续寻找体重差值最小的两个人，交换体重，直到前一队人员总体重达到或大于总体重的一半，获取体
// 重和相差较小的一组值。这样可以保证取到所有可能的体重值，在小于 G / 2 和大于 G / 2 的时候需要
// 判断哪个差值更小。
//
// 但是对于以下数据，该算法失效：
//
// 1
//
// 5
// 1
// 4
// 10
// 10
// 20
//
// 为什么失效了？因为对于差为 0 的数据也进行了交换。
//
// 有意思的是，别人使用动态规划算法得到的解法虽然在 Programming Challenges 和 UVa 获得 AC，
// 但是某些测试数据却无法通过，我使用这个算法，通过了 UVa 论坛上的所有数据，而且一些连 AC 程序都
// 错误的数据也通过了。可见 PC 和 UVa 上的测试数据并不是很强。使用动态规划解题的程序示例可参考
// http://tausiq.wordpress.com/2011/03/07/uva-10032-tug-of-war/（目前已经无法访问），评论里
// 有不能通过的测试数据。
//
// 在 UVa 上的另外一个问题（题号 562）和此题非常类似，是分硬币的问题，不过和本题不同，分成两部
// 分的硬币没有数目最多相差 1 枚的限制。更一般的这类问题称为平衡划分问题，可以使用动态规划解决，可
// 参考： http://people.csail.mit.edu/bdean/6.046/dp/ 。
//
// 本题解法在Progrmming Challenges上通过，在UVa Online Judge上为WA。

#include <bits/stdc++.h>

using namespace std;

#define MAX_DIFF 450	// 两个人体重差值最大可能值。

int tug_of_war(vector <int> &weight, int sum)
{
	// 若只有 1 人，显然一队体重为 0，另一队体重即为唯一参加野餐的人的体重。
	if (weight.size() == 1)
		return 0;

	// 将体重值按增序排列，以便获得总体重值的一个递增序列。
	sort(weight.begin(), weight.end());

	int lower, upper;

	lower = weight.size() / 2 - 1;
	upper = lower + 1;

	// 查找并替换最先找到的两队中体重值相差最小的两个队员，当前一队的体重总重量小于后一队
	// 时，继续该过程，直到前一队体重值等于或大于总体重的一半。
	int origin_lower, origin_upper;
	while (true)
	{
		int memo_lower, memo_upper;
		int diff_weight = MAX_DIFF;

		// 寻找最先出现的体重差值最小的两个队员。
		bool changed = false;
		for (int m = 0; m <= lower; m++)
		{
			for (int n = upper; n < weight.size(); n++)
			{
				int tmp = weight.at(n) - weight.at(m);
				// 保证交换后大于原队伍的体重和。
				if (tmp > 0 && tmp < diff_weight)
				{
					memo_lower = m;
					memo_upper = n;
					diff_weight = weight.at(n) - weight.at(m);
					changed = true;
				}
			}
		}

		// 若找到，交换最先出现的差值最小的两个队员。
		if (changed == true)
		{
			origin_lower = weight.at(memo_lower);
			origin_upper = weight.at(memo_upper);

			int tmp = weight.at(memo_lower);
			weight.at(memo_lower) = weight.at(memo_upper);
			weight.at(memo_upper) = tmp;
		}

		// 计算前一队的体重和。
		int team_weight = 0;
		for (int i = 0; i <= lower; i++)
			team_weight += weight.at(i);

		// 未找到差值大于 0 的两个队员，或者前一队体重和等于总体重的一半，返回当前
		// 前一队的体重和即为题目所求。
		if (changed == false || team_weight == (sum / 2))
			return team_weight;

		// 前一队体重和小于总体重的一半，将两队人员体重各自按增序排列后继续替换。
		if (team_weight < (sum / 2))
		{
			sort(weight.begin(), weight.begin() + lower);
			sort(weight.begin() + upper, weight.end());
			continue;
		}

		// 前一队人员体重和大于总体重的一半，比较前一次替换和当前两队人员体重差值，取
		// 差值较小的一组。
		int team_a = 0, team_b = 0;
		for (int i = 0; i <= lower; i++)
			team_a += weight.at(i);
		team_b = team_a + origin_lower - origin_upper;

		if (abs(2 * team_a - sum) < abs(2 * team_b - sum))
			return (sum - team_a);
		else
			return team_b;
	}
}

int main(int ac, char *av[])
{
	int cases;		// 测试数据组数。
	vector <int> weight;	// 记录体重值。

	cin >> cases;
	while (cases--)
	{
		int n;		// 参加野餐总人数。
		int tmp;	// tmp 为单个人的体重
		int sum = 0;	// sum 为总的体重。

		weight.clear();

		cin >> n;
		while (n--)
		{
			cin >> tmp;
			sum += tmp;
			weight.push_back(tmp);
		}

		// 获取满足题意的体重较小的一队总体重值。
		int smaller = tug_of_war(weight, sum);
		cout << smaller << " " << (sum - smaller) << endl;

		if (cases)
			cout << endl;
	}

	return 0;
}
