// SCUD Busters
// UVa ID: 109
// Verdict: Accepted
// Submission Date: 2011-11-24
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题是比较简单的计算几何题，使用模板代码可以很轻松的 AC，解题思路是很直接的，
// 和 UVa 12016 类似。求出每个王国的凸包顶点，判断导弹的落点是否在某个王国的凸
// 包范围内，若在其范围内，则该王国电丧失，该王国的面积计入丧失电力的总面积之中。

#include <bits/stdc++.h>

using namespace std;

#define MAXPOLY 110
#define MAXN 25

struct point
{
	int x;
	int y;
};

struct polygon
{
	int n;
	point p[MAXPOLY];
};

point sites[MAXPOLY];
polygon kingdom[MAXN];
bool powerOff[MAXN];
int kingdomNumber;

// 叉积，判断点 first，second，third 组成的两条线段的转折方向。当叉积大于 0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp > 0）。
int crossProduct(point first, point second, point third)
{
	return (second.x - first.x) * (third.y - first.y) -
		(second.y - first.y) * (third.x - first.x);
}

// Andrew 凸包扫描算法的预排序，先按 x 坐标排序，若 x 坐标相同，则按 y 坐标排序。
bool leftLower(point first, point second)
{
	if (first.x == second.x)
		return first.y < second.y;
	else
		return first.x < second.x;
}

// Andrew 凸包扫描算法。
void convexHull(point vertex[], int vertexNumber, polygon &container)
{
	// 点个数小于等于三个，构成凸包。
	if (vertexNumber <= 3)
	{
		for (int i = 0; i < vertexNumber; i++)
			container.p[i] = vertex[i];
		container.n = vertexNumber;
		return;
	}

	// 排序。
	sort(vertex, vertex + vertexNumber, leftLower);
	
	point upper[MAXPOLY], lower[MAXPOLY];
	int top;

	// 求上凸包。
	upper[0] = vertex[0];
	upper[1] = vertex[1];
	top = 2;
	for (int i = 2; i < vertexNumber; i++)
	{
		upper[top] = vertex[i];
		while (top >= 2 && crossProduct(upper[top - 2],
				upper[top - 1], upper[top]) >= 0)
		{
			upper[top - 1] = upper[top];
			top--;
		}
		top++;
	}

	container.n = 0;
	for (int i = 0; i < top; i++)
		container.p[container.n++] = upper[i];

	// 求下凸包。
	lower[0] = vertex[vertexNumber - 1];
	lower[1] = vertex[vertexNumber - 2];
	top = 2;
	for (int i = vertexNumber - 3; i >= 0; i--)
	{
		lower[top] = vertex[i];
		while (top >= 2 && crossProduct(lower[top - 2],
				lower[top - 1], lower[top]) >= 0)
		{
			lower[top - 1] = lower[top];
			top--;
		}
		top++;
	}

	// 合并下凸包。
	for (int i = 1; i < top - 1; i++)
		container.p[container.n++] = lower[i];
}

// 使用射线法判断点是否在多边形内，在多边形边界上认为点在其内。
bool pointInPolygon(point pt, polygon &polygons)
{
	int nCross = 0;
	int crossProduct;

	for (int i = 0, j = polygons.n - 1; i < polygons.n; j = i++)
	{
		// 排斥实验，检测点是否在线段外接矩形内范围内。
		if (pt.y >= polygons.p[j].y && pt.y <= polygons.p[i].y ||
		    pt.y >= polygons.p[i].y && pt.y <= polygons.p[j].y)
		{
			// 计算叉积。
			crossProduct = (polygons.p[i].x - polygons.p[j].x) *
			    (pt.y - polygons.p[j].y) - (pt.x - polygons.p[j].x) *
			    (polygons.p[i].y - polygons.p[j].y);

			// 点在线段上。
			if (crossProduct == 0 && (pt.x >= polygons.p[j].x &&
						  pt.x <= polygons.p[i].x
						  || pt.x >= polygons.p[i].x
						  && pt.x <= polygons.p[j].x))
				return true;

			// 判断以 pt 为端点的向右射线与线段是否有交点。
			if (crossProduct > 0
			    && polygons.p[i].y > polygons.p[j].y
			    && pt.y != polygons.p[i].y || crossProduct < 0
			    && polygons.p[i].y < polygons.p[j].y
			    && pt.y != polygons.p[j].y)
				nCross++;
		}
	}

	return (nCross & 1);
}

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按逆时针方向给出。
double area(point vertex[], int vertexNumber)
{
	double total = 0.0;

	for (int i = 0; i < vertexNumber; i++)
	{
		int j = (i + 1) % vertexNumber;
		total += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
	}

	return fabs(total / 2.0);
}

int main(int ac, char *av[])
{
	int sitesNumber;
	
	kingdomNumber = 0;
	while (cin >> sitesNumber, sitesNumber > 0)
	{
		for (int i = 0; i < sitesNumber; i++)
			cin >> sites[i].x >> sites[i].y;

		convexHull(sites, sitesNumber, kingdom[kingdomNumber]);
		kingdomNumber++;
	}


	point missile;
	memset(powerOff, false, sizeof(powerOff));
	while (cin >> missile.x >> missile.y)
	{
		for (int i = 0; i < kingdomNumber; i++)
			if (pointInPolygon(missile, kingdom[i]))
				powerOff[i] = true;
	}

	double totalArea = 0.0;
	for (int i = 0; i < kingdomNumber; i++)
		if (powerOff[i])
			totalArea += area(kingdom[i].p, kingdom[i].n);

	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);
	cout << totalArea << endl;

	return 0;
}
