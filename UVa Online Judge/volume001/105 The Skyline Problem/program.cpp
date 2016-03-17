// UVa Problem 105 - Skyline Problem
// Verdict: Accepted
// Submission Date: 2011-11-22
// UVa Run Time: 0.036s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 最初是想把交点都求出来，然后判断交点是否在矩形内，但是写出来的代码丑陋难看，心想，
// 难道没有更好的方法吗？仔细观察了一下题目给的图，灵机一动，难道不能用数组来模拟高楼
// 吗？反正坐标最大也就是10000，使用一维数组来表示横坐标，数组的值来表示纵坐标，那么
// 矩形的 “并” 就相当容易表示了，只要判断在某横坐标位置最大的纵坐标即可，可以使用类似
// 于填充法的思想来建立 “高楼” 数组，对于一个给定的矩形 （L，H，R），将数组下标为
// [L, R] 范围内的值全部置为 H，当然前提条件是数组的先前值小于H，这就相当于实现了更
// 高的楼将较矮的楼覆盖的效果，从而方便的表示了矩形的 “并集”，那么再按要求输出坐标值
// 就不难了。

#include <iostream>
#include <cstring>

using namespace std;

#define MAXN 10010

int grid[MAXN];

int main (int argc, char const* argv[])
{
	int left, height, right, leftMost, rightMost = 0;
	bool leftSetted = false;

	memset(grid, 0, sizeof(grid));

	while (cin >> left >> height >> right)
	{
		for (int i = left; i <= right; i++)
			grid[i] = max(grid[i], height);

		if (!leftSetted)
		{
			leftMost = left;
			leftSetted = true;
		}
		
		rightMost = max(rightMost, right);
	}

	cout << leftMost << " " << grid[leftMost];

	int current = leftMost;
	for (int i = leftMost; i <= rightMost; i++)
	{
		if (grid[i] == grid[current])
			continue;
		else
		{
			if (grid[i] > grid[current])
				cout << " " << i << " " << grid[i];
			else
				cout << " " << (i - 1) << " " << grid[i];
				
			current = i;
		}
	}

	cout << " " << rightMost << " 0\n";

	return 0;
}

