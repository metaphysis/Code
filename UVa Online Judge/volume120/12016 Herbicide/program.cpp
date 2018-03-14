// UVa Problem 12016 - Herbicide
// Verdict: Accepted
// Submission Date: 2016-08-28
// UVa Run Time: 2.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题为计算几何题，本质是点定位问题。使用射线法判断点是否在除草剂形成的多边形内。
// 由于本题给定的坐标均为整数，同时数据量大，容易 TLE，故使用叉积判断点在直线上或
// 射线与线段有交点。不检测多边形上的点以提高效率。

#include <bits/stdc++.h>

using namespace std;

#define MAXPOLY 1010

struct point
{
	int x;
	int y;
};

struct polygon
{
	int n;
	int top, left, right, bottom;
	int vertex[MAXPOLY];
	point p[MAXPOLY];

	bool inRectBox(point & pt)
	{
		return (left <= pt.x && pt.x <= right) && (bottom <= pt.y && pt.y <= top);
	}
};

point weeds[MAXPOLY];
polygon herbicide[MAXPOLY];
int weedsCount, polygonCount;

// 使用射线法判断点是否在多边形内。
bool pointInPolygon(point & pt, polygon & polygons)
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

// 计算在多边形内的杂草数量。
int countWeeds(polygon & polygons)
{
	int inCount = 0;

	for (int i = 0; i < (polygons.n + 1); i++)
		// 多边形上的顶点不检测，提高效率。
		for (int j = polygons.vertex[i] + 1;
		     j <= polygons.vertex[i + 1] - 1; j++)
			// 包围盒实验。
			if (polygons.inRectBox(weeds[j]))
				if (pointInPolygon(weeds[j], polygons))	
					inCount++;

	return inCount + polygons.n;
}

int main(int ac, char *av[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
	int cases, currentCase = 1;
	int tmpIndex;

	cin >> cases;
	while (cases--)
	{
		// 读入杂草坐标数据。
		cin >> weedsCount;
		for (int i = 1; i <= weedsCount; i++)
			cin >> weeds[i].x >> weeds[i].y;

		// 读入除草剂形成的多边形顶点数据。
		cin >> polygonCount;
		for (int i = 0; i < polygonCount; i++)
		{
			cin >> herbicide[i].n;

			// 多边形的外接矩形边界。
			herbicide[i].top = 0;
			herbicide[i].left = 0;
			herbicide[i].bottom = 0;
			herbicide[i].right = 0;

			// 读入多边形顶点。
			for (int j = 0; j < herbicide[i].n; j++)
			{
				cin >> tmpIndex;
				herbicide[i].p[j] = weeds[tmpIndex];
				herbicide[i].vertex[j + 1] = tmpIndex;

				if (herbicide[i].top < weeds[tmpIndex].y)
					herbicide[i].top = weeds[tmpIndex].y;
				if (herbicide[i].left > weeds[tmpIndex].x)
					herbicide[i].left = weeds[tmpIndex].x;
				if (herbicide[i].bottom > weeds[tmpIndex].y)
					herbicide[i].bottom = weeds[tmpIndex].y;
				if (herbicide[i].right < weeds[tmpIndex].x)
					herbicide[i].right = weeds[tmpIndex].x;
			}

			// 为了减少检测点数，将多边形上的点的序数存入数组，然后排序，检测不是
			// 顶点的那些点。
			herbicide[i].vertex[0] = 0;
			herbicide[i].vertex[herbicide[i].n + 1] =
			    weedsCount + 1;
			sort(herbicide[i].vertex,
			    herbicide[i].vertex + herbicide[i].n + 1);
		}

		// 判断多边形内有多少杂草，在多边形边界上的亦算在内，多边形可能为凹多边形。
		cout << "Case #" << currentCase++ << ":" << '\n';
		for (int i = 0; i < polygonCount; i++)
			cout << countWeeds(herbicide[i]) << '\n';
	}

	return 0;
}
