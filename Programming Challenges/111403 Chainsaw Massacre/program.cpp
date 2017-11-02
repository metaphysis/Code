// Chainsaw Massacre （电锯惊魂）
// PC/UVa IDs: 111403/10043, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-14
// UVa Run Time: 0.196s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 目标是 O（n^2）的算法，否则容易 TLE。本质是找最一个内部为空的长方形，那么可以依次以一棵树作为
// 左边界，往右扫描确定右边界，当左右边界确定后，就可以确定其面积，然后上下再进行一次同样的扫描，即
// 可确定最终的最大矩形面积。

#include <iostream>
#include <algorithm>

using namespace std;

#define MAXTREES 2500	// 虽然题意是最多只有 1000 棵树，但是可能会有重复的坐标。

struct tree
{
	int x;
	int y;
};

tree trees[MAXTREES];
int l, w;

bool cmpXY(tree a, tree b)
{
	return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x);
}

bool cmpX(tree a, tree b)
{
	return a.x < b.x;
}

bool cmpY(tree a, tree b)
{
	return a.y < b.y;
}

int main(int ac, char *av[])
{
	int cases, total;
	int k, x, y, dx, dy;

	cin >> cases;
	while (cases--)
	{
		// 注意左边界的处理，可以将有树的行的左边界置为有树。
		cin >> l >> w;

		// 左上角和右下角的可以先 “种” 树，因为矩形可能以此为边界。
		total = 0;
		trees[total++] = (tree){ 0, 0 };
		trees[total++] = (tree){ l, w };

		// 读取数据。
		while (cin >> k, k)
		{
			if (k == 1)
			{
				cin >> x >> y;
				trees[total++] = (tree){ x, y };
			}
			else
			{
				cin >> x >> y >> dx >> dy;
				for (int i = 1; i <= k; i++)
					trees[total++] = (tree){ x + (i - 1) * dx, y + (i - 1) * dy };
			}
		}

		// 对于每一棵树，以其作为矩形的左边界，往右扫描，直到发现某一列有树，或者达到右
		// 侧边界，则该列为此矩形的右边界。先按横坐标进行排序。
		int maxArea = 0, lowY, topY, leftX, rightX;
		sort(trees, trees + total, cmpX);
		for (int i = 0; i < total; i++)
		{
			lowY = 0;
			topY = w;
			for (int j = i + 1; j < total; j++)
			{
				if (trees[j].x == trees[i].x)
					continue;
				else
				{
					maxArea = max(maxArea, (trees[j].x - trees[i].x) * (topY - lowY));
					if (trees[j].y < trees[i].y)
						lowY = max(lowY, trees[j].y);
					else
						topY = min(topY, trees[j].y);
				}
			}
		}

		// 先确定上界，再确定下界，再确定矩形，先按纵坐标排序。
		sort(trees, trees + total, cmpY);
		for (int i = 0; i < total; i++)
		{
			leftX = 0;
			rightX = l;
			for (int j = i + 1; j < total; j++)
			{
				if (trees[j].y == trees[i].y)
					continue;
				else
				{
					maxArea = max(maxArea, (trees[j].y - trees[i].y) * (rightX - leftX));
					if (trees[j].x < trees[i].x)
						leftX = max(leftX, trees[j].x);
					else
						rightX = min(rightX, trees[j].x);
				}
			}
		}
		
		cout << maxArea << endl;
	}

	return 0;
}
