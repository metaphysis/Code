// Edit Step Ladders （递变阶梯）
// PC/UVa IDs: 110905/10029, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-09-30
// UVa Run Time: 2.108s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// 递变（edit step）是指通过增加、减少或改变单词 x 中的一个字母，使它变成字典中的另一个单词 y。
// 比如将 dig 变为 dog，将 dog 变成 do 都是递变。递变阶梯（edit step ladder）是一个按字典
// 序排列的单词序列 w1，w2，... ，wn，满足对于从 1 到 n - 1 的所有 i，单词 wi 到 w（i+1）
// 都是一次递变。
//
// 给出一部字典，你要计算其中最长的递变阶梯。
//
// [输入]
// 输入文件是一部字典：每行都是一个由小写字母构成的单词。所有单词按照字典序排列。所有的单词长度都
// 不超过 16，且字典中最多有 25 000 个单词。
//
// [输出]
// 输出一个整数，代表最长的递变阶梯包含的单词数量。
//
// [样例输入]
// cat
// dig
// dog
// fig
// fin
// fine
// fog
// log
// wine
//
// [样例输出]
// 5
//
// [解题方法]
// 由于输出需要字典序，若对其进行图建模，则得到一个有向无环图，问题就是在这个有向无环图中找最长路径。
// 这个问题也可以归结为求最长递增序列（Longest Increasing Subsequence，LIS）的问题。
//
// 由题意可知，需要求一个递增的单词序列，由于给定的输入是排好序的，故只需考虑当前单词和已读入单词
// 之间的关系，设当前读入的单词为 W，其长度为 L，则 W 只可能与长度为 L - 1，L，L + 1 的单词构
// 成递变关系（当 L = 1 时，只能与 L，L + 1 的单词构成递变）。且由于输出字典序的要求，只考虑字典
// 序小于 W 的且长度满足要求的单词 Y。故可以从单词 W 出发，构造一个递变 X，满足长度要求，并查找
// X 是否在已读入的单词中，若存在则取出其最大递变长度加 1，与 W 的当前递变长度比较，若大于，则可以
// 替换，否则继续构造下一个递变单词，重复此过程，并记录之中找到的最大递变长度。以上是利用简单动态
// 规划思想求 LIS 的算法，时间复杂度为 O（n^2）。
//
// 附：看排名列表里面有很多人的运行时间是 0s，估计是不断尝试出来的，因为只有一个输入文件，只要有
// 一个可以通过的程序，则可以通过二分法不断提交尝试出这个最后结果来，我也试了一下，UVa 上的测试数
// 据字典的最大递变长度为 45。

#include <iostream>
#include <string>
#include <map>

using namespace std;

#define MAXN 25000
#define MAXLENGTH 16
#define INIT_LENGTH 1

map<string, int> dict[MAXLENGTH + 1];	// 不同长度单词分开，提高搜索速度。
int steps[MAXN];	// 存储对应单词最大递变长度。

int exist(int index, string &temp, int step)
{
	map<string, int>::iterator it;
	it = dict[index].find(temp);
	if (it != dict[index].end())
		if ((steps[(*it).second] + 1) > step)
			step = steps[(*it).second] + 1;
	return step;
}

int main(int ac, char *av[])
{
	string line, temp;
	int current = 0;
	int maximum = 0;

	// 初始化全部单词的递变长度为 1。
	for (int c = 0; c < MAXN; c++)
		steps[c] = INIT_LENGTH;

	while (cin >> line)
	{
		int index = line.length() - 1;
		int step = 1;

		// 构建长度为 L - 1，L，L + 1，字典序小于当前单词，与当前单词构成递变关系的
		// 单词，查找并比较最长递增序列长度。若当前单词长度为 1 ，则只需构造长度为 1
		// 的递变单词。
		if (index > 0)
		{
			for (int i = 0; i <= index; i++)
			{
				temp = line;
				if (i == index || temp[i] >= temp[i + 1])
				{
					temp.erase(temp.begin() + i);
					step = exist(index - 1, temp, step);
				}

				temp = line;
				while (temp[i] > 'a')
				{
					temp[i]--;
					step = exist(index, temp, step);
				}

				temp = line;
				temp.insert(temp.begin() + i, line[i]);
				while (temp[i] > 'a')
				{
					temp[i]--;
					step = exist(index + 1, temp, step);
				}
			}
		}
		else
		{
			temp = line;
			while (temp[0] > 'a')
			{
				temp[0]--;
				step = exist(index, temp, step);
			}
		}

		// 获取最大值。
		if (step > maximum)
			maximum = step;

		// 保存当前结果。
		steps[current] = step;
		dict[index].insert(make_pair<string, int>(line, current));
		current++;
	}

	cout << maximum << endl;

	return 0;
}
