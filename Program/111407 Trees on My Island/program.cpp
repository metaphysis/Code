// Trees on My Island （岛上的树）
// PC/UVa IDs: 111402/10088, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-10
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 运用面积不变的性质，使用多边形面积计算公式和 Pick 定理求解。Pick 定理需要计算边界上的格点数。
// 在本题中需要一点小技巧。

#include <iostream>

using namespace std;

typedef long long int lint;

#define MAXPOLY 1050

struct point
{
	lint x;
	lint y;
};

struct polygon
{
	lint n;
	point p[MAXPOLY];
};

// 求数的绝对值。
lint abs(lint x)
{
	return (x >= 0 ? x : (-x));
}

// 求两数的最大公约数。
lint gcd(lint a, lint b)
{
	if (b == 0)
		return a;

	if (b > a)
		return gcd(b, a);
	else
		return gcd(b, a % b);
}

// 利用有向面积计算多边形的面积。
lint calArea(polygon &contour)
{
	lint total = 0.0;

	for (lint i = 0; i < contour.n; i++)
	{
		lint j = (i + 1) % contour.n;
		total += (contour.p[i].x * contour.p[j].y -
				contour.p[j].x * contour.p[i].y);
	}

	return abs(total);
}

// 计数多边形边界上的格点。
lint boundaryPolints(polygon &contour)
{
	// 判断在多边形相邻两点之间的连线有多少个格点，实质上是要判断过多边形顶点的直线在给定范围内
	// 整数解的个数。
	lint points = 0;
	for (lint i = 0; i < contour.n; i++)
	{
		lint j = (i + 1) % contour.n;
		
		// 先处理特殊情况。
		if (contour.p[i].x == contour.p[j].x)
			points += (abs(contour.p[j].y - contour.p[i].y) - 1);
		else if (contour.p[i].y == contour.p[j].y)
			points += (abs(contour.p[j].x - contour.p[i].x) - 1);
		else
		{
			// 求横坐标和纵坐标的差的绝对值。
			lint xDiff = abs(contour.p[j].x - contour.p[i].x);
			lint yDiff = abs(contour.p[j].y - contour.p[i].y);

			// 当 x 变化 xDiff 个单位时，y 变化 yDiff 个单位，只要找到这样的
			// 的点：点的横坐标在（min（p[i].x，[j].x），max（p[i].x，[j].x））
			// 范围内且为整数，求这些点的总数，即是此段线段上多边形的边界格点数。
			// 这个可以通过求 xDiff 和 yDiff 的最大公约数（GCD）来得到（为什么
			// ？你可以思考一下，很简单的一个关系）。
			points += gcd(xDiff, yDiff) - 1;
		}
	}
	
	return (points + contour.n);
}

int main (int argc, char const* argv[])
{
	lint vertexNumber;
	polygon contour;
	
	while (cin >> vertexNumber, vertexNumber)
	{
		contour.n = vertexNumber;
		for (lint i = 0; i < vertexNumber; i++)
			cin >> contour.p[i].x >> contour.p[i].y;
		
		// 统计该多边形的边界上的格点数。
		lint vertexBoundary = boundaryPolints(contour);

		// 由多边形面积计算公式计算多边形面积，注意计算结果是面积实际值乘以 2，这样避免
		// 了小数。
		lint area = calArea(contour);

		// Pick 定理。
		cout << (2 * area + 4 - 2 * vertexBoundary) / 4 << endl;	
	}

	return 0;
}


