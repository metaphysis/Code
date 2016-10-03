// Hanoi Tower Troubles Again! （汉诺塔卷土重来！）
// PC/UVa IDs: 110908/10276, Popularity: B, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-10-02
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [问题描述]
// There are many interesting variations on the Tower of Hanoi problem. This version
// consists of N pegs and one ball containing each number from 1, 2, 3,..., . 
// Whenever the sum of the numbers on two balls is not a perfect square (i.e., 
// c2 for some integer c), they will repel each other with such force that they
// can never touch each other.
//
// The player must place balls on the pegs one by one, in order of increasing ball
// number (i.e., first ball 1, then ball 2, then ball 3...). The game ends where
// there is no non-repelling move.
//
// The goal is to place as many balls on the pegs as possible. The figure above
// gives a best possible result for 4 pegs. 
//
// [输入]
// The first line of the input contains a single integer T indicating the number
// of test cases ( 1 <= T <= 50). Each test case contains a single integer N
// ( 1 <= N <= 50) indicating the number of pegs available.
//
// [输出]
// For each test case, print a line containing an integer indicating the maximum
// number of balls that can be placed. Print ``-1'' if an infinite number of balls
// can be placed.
//
// [样例输入]
// 2
// 4
// 25
//
// [样例输出]
// 11
// 337
//
// [解题方法]
// 该题解法有多种，一种是直接模拟放置球的过程，使用贪婪策略，将 1 到 50 根柱子所能放
// 置的最大球数计算出，这是最直观的，第二种是找规律，能放置的球数从 1 根柱子开始是：
// 1，3，7，11，17，23，31，39，49，... ，相邻两个数之差为 2，4，4，6，6，8，8，10，
// 10，... ，看出了什么规律？第三种是使用 DAG （有向无环图） 来对约束建模，然后使用
// 图论方法解决。

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define MAXN 50

int main(int ac, char *av[])
{
	vector < vector < int > > number;
	vector < int > result;
	int pegs = 1;

	// 先将 0 放到所有柱子上。
	number.resize(MAXN + 2);
	for (int i = 1; i <= MAXN; i++)
		number[i].push_back(0);

	// 从数字 1 开始逐个放置，当前柱子不能放下时，增加一个柱子。
	for (int current = 1; pegs <= MAXN;)
	{
		bool successed = false;
		for (int c = 1; c <= pegs; c++)
		{
			int top = current + number[c][number[c].size() - 1];

			// 判断当前数 current 能否与柱子上的数之和为平方数。
			int value = sqrt(top);
			if (value * value == top)
			{
				number[c].push_back(current);
				successed = true;
				break;
			}
		}

		// 数字 current 未能放置，需要增加一个柱子。
		if (successed == false)
		{
			result.push_back(current - 1);
			pegs++;
			number[pegs].push_back(current);
			current++;
		}
		else
			current++;
	}

	int cases, n;

	cin >> cases;
	while (cases--)
	{
		cin >> n;
		cout << result[n - 1] << endl;
	}

	return 0;
}
