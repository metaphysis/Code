// Ant on a Chessboard （棋盘上的蚂蚁）
// PC/UVa IDs: 111201/10161, Popularity: B, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 观察可知，副对角线上的数字后一项与前一项之差形成一个等差数列，可以推出通项公式：
//
// an = (n - 1) * n + 1, n >= 1
//
// 可由数学归纳法证明其正确性。
//
// 根据步数可以得知步数数字所处的列或者行，那么可以由通项公式得知对角线数字，然后再通过列或者行的
// 奇偶性以及与副对角线数字的关系得到步数数字的确切位置。
//
// 实际上可以看作蚂蚁以一种特殊的顺序遍历了一个矩阵，不是像通常的行优先，或者列优先，但归根结底遍
// 历一个 n x m 矩阵中的所有元素，任何一种遍历方式都可以看作是从 nm 种有序数对到 1 和 nm 之间
// 唯一整数的映射。

#include <iostream>
#include <cmath>

using namespace std;

int main(int ac, char *av[])
{
	int step;

	while (cin >> step, step)
	{
		// 确定步数数字所在的列或者行。
		int column = (int)ceil(sqrt(step));

		// 确定对角线上的数字：column * （column - 1） + 1。
		int diagonal = column * (column - 1) + 1;

		// 根据对角线数字以及步数数字与对角线数字的关系来确定位置。
		if (column & 1)
		{
			if (step >= diagonal)
				cout << (column - (step - diagonal)) << " " << column << endl;
			else
				cout << column << " " << (column - (diagonal - step)) << endl;	
		}
		else
		{
			if (step >= diagonal)
				cout << column << " " << (column - (step - diagonal)) << endl;
			else
				cout << (column - (diagonal - step)) << " " << column << endl;
		}
	}

	return 0;
}
