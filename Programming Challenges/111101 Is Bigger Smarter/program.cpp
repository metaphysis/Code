// Is Bigger Smarter? （越大越聪明？）
// PC/UVa IDs: 111101/10131, Popularity: B, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-10-10
// UVa Run Time: 0.032s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 一些人认为，大象的体型越大，脑子越聪明。为了反驳这一错误观点，你想要分析一组大象的数据，找出尽量
// 多的大象组成一个体重严格递增但 IQ 严格递减的序列。
//
// [输入]
// 输入包含若干大象的数据，每行一头大象，直到输入结束。每头大象的数据包括两个整数：第一个是以千克为
// 单位的体重，第二个是以整百为单位的 IQ 指数。两个整数均在 1 到 10000之间。输入最多包含 1000 头
// 大象。两头大象可能有相同的体重，或者相同的 IQ，甚至体重和 IQ 都相同。
//
// [输出]
// 输出第一行应当包括一个整数 n，为找到的大象序列的长度。接下来的 n 行，每行包含一个正整数，表示一
// 头大象。用 W[i] 和 S[i] 表示输入数据中第 i 行的两个数，则若找到的这一序列为 a[1]，a[2]，
// ... ，a[n]，则必须有：
//
// W [a[1]] < W [a[2]] < ... < W [a[n]] 和 S[a[1]] > S[a[2]] > ... > S[a[n]]i
//
// 这里的 n 应当是最大可能值。所有不等关系均为严格不相等：体重严格递增，而 IQ 严格递减。
// 如果存在多组解，你的程序只需输出任何一个解。
//
// [样例输入]
// 6008 1300
// 6000 2100
// 500 2000
// 1000 4000
// 1100 3000
// 6000 2000
// 8000 1400
// 6000 1200
// 2000 1900
//
// [样例输出]
// 4
// 4
// 5
// 9
// 7
//
// [解题方法]
// 求解之前先将大象按体重增序排列，若两头大象体重相同，则按 IQ 降序排列，排序以后，问题转化为求 IQ
// 的一个最长递减子序列 （Longest Decreasing Subsequence，LDS），在计算时，有附加条件，即体
// 重应该是递增的，那么可以使用一个数组 length[] 记录第 i 头大象能得到的 LDS 长度，当处理第
// i + 1 头大象的数据时，从前 i 头大象中找体重小于第 i + 1 头大象但是 IQ 大于第 i + 1 头大象
// 的 LDS 最长的大象序号，更新第 i + 1 大象的 LDS 长度，并记录第 i + 1 头大象是接在那头大象后
// 得到的 LDS，这可以通过设立一个 parnet[] 数组来记录。

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXN 1000

class elephant
{
public:
	int index;
	int weight;
	int iq;

	bool operator<(const elephant &other) const
	{
		if (weight != other.weight)
			return weight < other.weight;
		return iq > other.iq;
	}
};

elephant elephants[MAXN];
int length[MAXN];	// 记录大象所能得到的 LDS 长度。
int parent[MAXN];	// 记录选择。

// 使用递归以便逆序输出答案。
void backtrack(int index)
{
	if (parent[index] != -1)
		backtrack(parent[index]);
	cout << (elephants[index].index + 1) << endl;
}

int main(int ac, char *av[])
{
	int index = 0, weight, iq;

	while (cin >> weight >> iq)
		elephants[index++] = (elephant){index, weight, iq};

	// 按体重升序排列，找 IQ 的最长递减序列，也
	// 可以按 IQ 降序排列，找体重的最长递增序列。
	sort(elephants, elephants + index);

	// 初始 LDS 长度均设为 1。
	for (int i = 0; i < index; i++)
	{
		length[i] = 1;
		parent[i] = -1;
	}

	// DP 求 LDS 长度。
	int maxLength = 0, maxIndex = 0;
	for (int i = 0; i < index; i++)
	{
		int iq = elephants[i].iq;
		int weight = elephants[i].weight;

		for (int j = 0; j < i; j++)
		{
			if (elephants[j].weight < weight && elephants[j].iq > iq)
				if (length[i] <= length[j])
				{
					length[i] = length[j] + 1;
					parent[i] = j;
				}
		}

		if (maxLength < length[i])
		{
			maxLength = length[i];
			maxIndex = i;
		}
	}

	// 利用递归反向输出结果。
	cout << maxLength << endl;
	backtrack(maxIndex);

	return 0;
}
