// Hotter Colder （冷热游戏）
// PC/UVa IDs: 111404/10084, Popularity: C, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-09
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题的实质是半平面与凸多边形求交问题，表示半平面的直线即相邻两个位置连线的垂直平分线。由于初始
// 区域为凸多边形，每次切割后仍为凸多边形。

#include <bits/stdc++.h>

using namespace std;

#define MAXPOLY 60

#define EPSILON (1E-7)

#define SAME_LINE 0
#define PARALLE_LINE 1
#define LINE_NO_INTERSECT 2
#define LINE_INTERSECT 3

#define LIE_ON_LINE 0
#define BELOW_LINE (-1)
#define ABOVE_LINE 1

struct point
{
	double x;
	double y;
};

struct polygon
{
	int n;
	point p[MAXPOLY];
};

struct line
{
	double a, b, c;
};

struct segment
{
	point p1, p2;
};

polygon region;
double lastX = 0.0, lastY = 0.0, lastArea = 100.0;
bool isLineOrEmpty;

// 判断两条直线是否平行。
bool parallel(line l1, line l2)
{
	return ((fabs(l1.a - l2.a) <= EPSILON) && (fabs(l1.b - l2.b) <= EPSILON));
}

// 判断两条直线是否重合。
bool same(line l1, line l2)
{
	return (parallel(l1, l2) && (fabs(l1.c - l2.c) <= EPSILON));
}

// 点是否在线段的包围盒内。
bool pointInBox(point p, point b1, point b2)
{
	return ((p.x >= min(b1.x, b2.x)) && (p.x <= max(b1.x, b2.x))
		&& (p.y >= min(b1.y, b2.y)) && (p.y <= max(b1.y, b2.y)));
}

// 求两直线的交点。
int getIntersection(line l1, line l2, segment s, point &p)
{
	if (same(l1, l2))
		return SAME_LINE;

	if (parallel(l1, l2))
		return PARALLE_LINE;

	p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
	if (fabs(l1.b) > EPSILON)
		p.y = -(l1.a * p.x + l1.c) / l1.b;
	else
		p.y = -(l2.a * p.x + l2.c) / l2.b;
		
	if (pointInBox(p, s.p1, s.p2))
		return LINE_INTERSECT;
	else
		return LINE_NO_INTERSECT;
}

// 通过两点求直线方程。
void pointToLine(point p1, point p2, line &l)
{
	if (p1.x == p2.x)
	{
		l.a = 1;
		l.b = 0;
		l.c = -p1.x;
	}
	else
	{
		l.b = 1;
		l.a = -(p1.y - p2.y) / (p1.x - p2.x);
		l.c = -(l.a * p1.x) - (l.b * p1.y);
	}
}

// 使用斜率和一点求直线方程。
void pointAndSlopeToLine(point p, double m, line &l)
{
	l.a = -m;
	l.b = 1;
	l.c = -((l.a * p.x) + (l.b * p.y));
}

// 利用有向面积计算多边形的面积，注意最后结果取绝对值，因为顶点顺序可能并不是按逆时针方向给出。
double getArea(point vertex[], int vertexNumber)
{
	double total = 0.0;

	for (int i = 0; i < vertexNumber; i++)
	{
		int j = (i + 1) % vertexNumber;
		total += (vertex[i].x * vertex[j].y - vertex[j].x * vertex[i].y);
	}

	return fabs(total / 2.0);
}

// 判断点和直线的关系。
int relationPointLine(line l, point p)
{
	if (fabs(l.a * p.x + l.b * p.y + l.c) <= EPSILON)
		return LIE_ON_LINE;

	if ((l.a * p.x + l.b * p.y + l.c) > 0)
		return ABOVE_LINE;
	else
		return BELOW_LINE;
}

// 求半平面和凸多边形交的面积。
double area(double x, double y, string status)
{
	// 若坐标未变化，则返回最后计算所得到的面积。
	if (x == lastX && y == lastY)
		return lastArea;

	// 当可能区域为一条线段或者不可能存在这样的区域时，返回 0 值。
	if (isLineOrEmpty)
		return 0.0;

	// 若给出的是 Same，且前后位置坐标不同，则物品在线段的垂直平分线上。
	if (status == "Same")
	{
		isLineOrEmpty = true;
		return 0.0;
	}

	// 求端点为（x，y），（lastX，lastY）的线段的垂直平分线直线方程。
	line l1, l2;

	point middle;
	middle.x = (lastX + x) / 2.0;
	middle.y = (lastY + y) / 2.0;

	if (lastY == y)
	{
		l1.a = 1;
		l1.b = 0;
		l1.c = -middle.x;
	}
	else
	{
		double slope = -(lastX - x) / (lastY - y);
		pointAndSlopeToLine(middle, slope, l1);
	}

	// 判断是那个半平面与凸多边形相交。可以通过起点和垂直平分线的关系以及提示语来判断。若
	// upPlane 为真，表示 a * x + b * y + c > 0 的半平面与凸多边形相交，反之则是另外
	// 一个半平面与之相交。
	bool upPlane = ((l1.a * x + l1.b * y + l1.c) > 0);
	if (status == "Colder")
		upPlane = !upPlane;

	// 判断直线与多边形的相交情况，总是顺时针枚举凸包的顶点，以便生成的凸多边形顶点顺序仍然
	// 是顺时针方向。
	queue<point> up, down;
	for (int i = 0; i < region.n; i++)
	{
		int j = (i + 1) % region.n;

		// 直线和点的位置关系。
		int ri = relationPointLine(l1, region.p[i]);
		int rj = relationPointLine(l1, region.p[j]);
		
		// 凸多边形两个相邻顶点在直线的异侧，表明直线和该线段有交点，求交点。
		if (ri * rj < 0)
		{
			pointToLine(region.p[i], region.p[j], l2);
			point intersect;
			segment s = (segment) { region.p[i], region.p[j] };
			getIntersection(l1, l2, s, intersect);
			
			if (ri < 0)
			{
				down.push(region.p[i]);
				down.push(intersect);
				up.push(intersect);
			}
			else
			{
				up.push(region.p[i]);
				up.push(intersect);
				down.push(intersect);
			}
		}
		// 凸多边形两个顶点或单个顶点在直线上。
		else if (ri * rj == 0)
		{
			if (ri == 0 && rj == 0)
			{
				up.push(region.p[i]);
				down.push(region.p[i]);
			}
			else if (ri == 0 && rj < 0)
			{
				up.push(region.p[i]);
				down.push(region.p[i]);
			}
			else if (ri == 0 && rj > 0)
			{
				down.push(region.p[i]);
				up.push(region.p[i]);
			}
			else if (ri < 0 && rj == 0)
				down.push(region.p[i]);
			else if (ri > 0 && rj == 0)
				up.push(region.p[i]);
		}
		// 凸多边形的两个顶点在直线的同侧。
		else
		{
			if (ri > 0)
				up.push(region.p[i]);
			else
				down.push(region.p[i]);
		}
	}

	// 根据所在半平面取相应的顶点。
	if (upPlane)
	{
		region.n = 0;
		while (!up.empty())
		{
			region.p[(region.n)++] = up.front();
			up.pop();
		}
	}
	else
	{
		region.n = 0;
		while (!down.empty())
		{
			region.p[(region.n)++] = down.front();
			down.pop();
		}	
	}

	// 计算面积。
	return getArea(region.p, region.n);
}

int main (int argc, char const* argv[])
{
	double x, y;
	string status;
	
	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);

	// 初始凸多边形即为给定的正方形范围顶点。	
	region.n = 4;
	region.p[0] = (point) { 0.0, 0.0 };
	region.p[1] = (point) { 0.0, 10.0 };
	region.p[2] = (point) { 10.0, 10.0 };
	region.p[3] = (point) { 10.0, 0.0 };

	lastX = lastY = 0.0;

	isLineOrEmpty = false;

	// 读入位置和结果。	
	while (cin >> x >> y >> status)
	{
		cout << area(x, y, status) << endl;
		lastX = x;
		lastY = y;
	}

	return 0;
}
