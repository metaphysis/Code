// UVa Problem 922 - Rectangle by the Ocean
// Verdict: Accepted
// Submission Date: 2011-11-08
// UVa Run Time: 0.028s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题为计算几何题，使用有向面积计算多边形的面积。使用穷举法枚举可能的矩形
// 左下角和右上角坐标，判断矩形是否至少有三个角落在多边形上，注意枚举时的坐
// 标选择顺序，可以适当的选择自动得到最小字典序的结果。

#include <bits/stdc++.h>

using namespace std;

#define MAXPOLY 300

struct point
{
	int x;
	int y;
};

struct rect
{
	int left, lower;
	int right, upper;
};

struct polygon
{
	int n;
	int top, left, right, bottom;
	point p[MAXPOLY];
};

// 点（i，j）是否在多边形上。
int on[MAXPOLY][MAXPOLY];

// 使用穷举法逐个枚举可能矩形的左下角和右上角坐标。
void rectangle(polygon &contour, double area)
{
	double minDiff = area, currentDiff;
	rect tmp;

	// 初始化。
	for (int i = 0; i <= (contour.right - contour.left); i++)
		for (int j = 0; j <= (contour.top - contour.bottom); j++)
			on[i][j] = 0;

	// 将多边形上的点标记为在多边形上，除此之外，在多边形外接矩形内的点均不在多边形上。注意
	// 坐标的变换。
	for (int i = 0; i < contour.n; i++)
		on[contour.p[i].x - contour.left][contour.p[i].y - contour.bottom] = 1;

	// 枚举可能的矩形，注意枚举的顺序。
	for (int i = 0; i <= contour.right - contour.left; i++)
		for (int j = 0; j <= contour.top - contour.bottom; j++)
			for (int m = i; m <= contour.right - contour.left; m++)
				for (int n = j; n <= contour.top - contour.bottom; n++)
				{
					// 判断是否符合至少三个角落在多边形上的条件。
					if (on[i][j] + on[i][n] +
						on[m][j] + on[m][n] < 3)
						continue;

					// 比较差值，注意是 “尽可能接近“，应取绝对值。
					currentDiff = fabs((m - i) * (n - j) - area);
					if (currentDiff < minDiff)
					{
						minDiff = currentDiff;
						tmp = (rect) {
						contour.left + i,
						contour.bottom + j,
						contour.left + m,
						contour.bottom + n };
					}
				}

	// 输出结果。
	cout << ((int)(area)) << "." << ((int)(area * 10.0) % 10) << " ";
	cout << tmp.left << " " << tmp.lower << " ";
	cout << tmp.right << " " << tmp.upper << endl;
}

// 由多边形的顶点坐标求多边形的面积。
double calArea(polygon &contour)
{
	double total = 0.0;

	for (int i = 0; i < contour.n; i++)
	{
		int j = (i + 1) % contour.n;
		total += (contour.p[i].x * contour.p[j].y -
				contour.p[j].x * contour.p[i].y);
	}

	return fabs(total / 2.0);
}

int main(int ac, char *av[])
{
	int cases;
	polygon contour;

	cin >> cases;
	while (cases--)
	{
		cin >> contour.n;
		for (int i = 0; i < contour.n; i++)
			cin >> contour.p[i].x >> contour.p[i].y;

		// 找到多边形外接矩形边界。
		contour.top = contour.p[0].y;
		contour.left = contour.p[0].x;
		contour.bottom = contour.p[0].y;
		contour.right = contour.p[0].x;
		for (int i = 1; i < contour.n; i++)
		{
			contour.top = max(contour.top, contour.p[i].y);
			contour.left = min(contour.left, contour.p[i].x);
			contour.bottom = min(contour.bottom, contour.p[i].y);
			contour.right = max(contour.right, contour.p[i].x);
		}

		rectangle(contour, calArea(contour));
	}

	return 0;
}
