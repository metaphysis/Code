// Herding Frosh （新生集会）
// PC/UVa IDs: 111401/10135, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-08
// UVa Run Time: 0.112s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 本题中由于多了一个电话柱，简单的求凸包不能得到正确的答案，需要分两种情况。假设已经求出了所有新
// 生点集所对应的凸包，如果原点在此凸包外，那么依照题意，丝带必须绕过原点，则只需将原点加入新生点
// 集中求凸包，凸包的周长加上多余需要的两米即为答案。若原点在凸包内，则丝带可以从任意两个按相对于
// 原点极角排序的相邻点绕到电话柱子上，此时需要逐个枚举可能的长度，然后求最小值才为正确答案。先将
// 点按照相对于原点的极角排序，然后任意选择两个相邻的点，假设为 p1和p2，按照 Graham 凸包扫描
// 算法的思想开始扫描，不过这里需要将起始点设置为原点，最后一点设置为 p2，在扫描结束时再加上点 p2，
// 那么扫描所得到的 “包” 的形状恰恰就是题目所求丝带的形状。

#include <bits/stdc++.h>

using namespace std;

const int MAXPOLY = 1010;
const double EPSILON = 1E-7;

struct point
{
	double x, y;
};

point origin = (point) { 0.0, 0.0 };

struct polygon
{
	int vertexNumber;
	point vertex[MAXPOLY];
};

double distanceOfPoints(point a, point b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// 叉积。
int crossProduct(point a, point b, point c)
{
	return (c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y);
}

// 从点 a 向点 b 望去，点 c 位于线段 ab 的右侧，返回 true。
bool cw(point a, point b, point c)
{
	return crossProduct(a, b, c) > EPSILON;
}
// 从点 a 向点 b 望去，点 c 位于线段 ab 的左侧时，返回 true。
bool ccw(point a, point b, point c)
{
	return crossProduct(a, b, c) < -EPSILON;
}

// 当三点共线时，返回true。
bool collinear(point a, point b, point c)
{
	return fabs(crossProduct(a, b, c)) <= EPSILON;
}

// 判断是否向左转或共线。
bool ccwOrCollinear(point a, point b, point c)
{
	return ccw(a, b, c) || collinear(a, b, c);
}

// Andrew 凸包扫描算法的预排序，按 y 坐标排序。
bool lowerLeft(point a, point b)
{
	return (a.y == b.y) ? (a.x < b.x) : (a.y < b.y);
}

// Andrew 凸包扫描算法。
void andrewConvexHull(point vertex[], int vertexNumber, polygon& container)
{
	// 点个数小于等于三个，构成凸包。
	if (vertexNumber <= 3)
	{
		for (int i = 0; i < vertexNumber; i++)
			container.vertex[i] = vertex[i];
		container.vertexNumber = vertexNumber;
		return;
	}

	// 排序。
	sort(vertex, vertex + vertexNumber, lowerLeft);

	point upper[MAXPOLY], lower[MAXPOLY];
	int top;

	// 求上凸包。
	upper[0] = vertex[0];
	upper[1] = vertex[1];
	top = 2;
	for (int i = 2; i < vertexNumber; i++)
	{
		upper[top] = vertex[i];
		while (top >= 2 && ccwOrCollinear(upper[top - 2], upper[top - 1], upper[top]))
		{
			upper[top - 1] = upper[top];
			top--;
		}
		top++;
	}

	container.vertexNumber = 0;
	for (int i = 0; i < top; i++)
		container.vertex[container.vertexNumber++] = upper[i];

	// 求下凸包。
	lower[0] = vertex[vertexNumber - 1];
	lower[1] = vertex[vertexNumber - 2];
	top = 2;
	for (int i = vertexNumber - 3; i >= 0; i--)
	{
		lower[top] = vertex[i];
		while (top >= 2 && ccwOrCollinear(lower[top - 2], lower[top - 1], lower[top]))
		{
			lower[top - 1] = lower[top];
			top--;
		}
		top++;
	}

	// 合并下凸包。
	for (int i = 1; i < top - 1; i++)
		container.vertex[container.vertexNumber++] = lower[i];
}

// 求凸包的长度。
double convexHullLength(polygon& container)
{
	double length = 0.0;
	for (int i = 0; i < container.vertexNumber; i++)
	{
		int j = (i + 1) % container.vertexNumber;
		length += distanceOfPoints(container.vertex[i], container.vertex[j]);
	}
	return length;
}

// 按极角大小排序，极角相同则按离原点距离排序。
bool smallerAngle(point a, point b)
{
    double angle1 = atan2(a.y, a.x);
    double angle2 = atan2(b.y, b.x);
    
    if (fabs(angle1 - angle2) <= EPSILON)
        return (distanceOfPoints(a, origin) - distanceOfPoints(b, origin) < 0);
    return angle1 < angle2;
}

// 去除重复点的比较函数。
bool cmpPoint(point a, point b)
{
    return a.x == b.x && a.y == b.y;
}

// 当原点在凸包内部时，按题意求最小的丝带长度。
double minConvexHullLength(point students[], int &n)
{
	double length = 1e20;

	// 排序，移除重复点。
	sort(students, students + n, lowerLeft);
    n = unique(students, students + n, cmpPoint) - students;

	// 将所有点按照相对于原点的极角排序，若极角相同，按距离排序。
	sort(students, students + n, smallerAngle);

	// 任意选取一个点 i 开始 Graham 扫描，注意扫描结束点选择为点 i - 1，起始点为原点。
	polygon out;
	for (int i = 0; i < n; i++)
	{
		int top = 1, current = i + 1;
		out.vertex[0] = origin;
		out.vertex[1] = students[i];

		while (current < (i + n))
		{
			// 注意这里需要加上 top >= 1，因为起始时有可能会共线，回退不能没有限制。
			if (top >= 1 && cw(out.vertex[top - 1], out.vertex[top],
			    students[current % n]))
				top--;
			else
			{
				top++;
				out.vertex[top] = students[current % n];
				current++;
			}
		}

		// 点 i 的前一点总是算在所求点之内，因为丝带需要从此点经过。
		top++;
		out.vertex[top] = students[(i - 1 + n) % n];
		out.vertexNumber = top;

		// 返回找到的较小值。
		length = min(length, convexHullLength(out));
	}
	
	return length;
}

int main(int ac, char *av[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    
	point frosh[MAXPOLY];
	polygon silk;
	int cases, vertexNumber, froshNumber;

	cin >> cases;
	for (int c = 1; c <= cases; c++)
	{
	    if (c > 1)
	        cout << '\n';
	        
		cin >> froshNumber;
		frosh[0] = origin;
		for (int i = 1; i <= froshNumber; i++)
			cin >> frosh[i].x >> frosh[i].y;
		froshNumber++;

		andrewConvexHull(frosh, froshNumber, silk);

		// 计算凸包的周长。
		double minLength = convexHullLength(silk) + 2.0;

		// 判断原点是否在凸包的边界上，或者原点为凸包的一个顶点。
		bool onPolygon = false;
		for (int i = 0; i < silk.vertexNumber; i++)
		{
			int j = (i + 1) % silk.vertexNumber;
			// 判断原点与凸包的顶点 i 和 j 是否共线。
			if (collinear(silk.vertex[i], silk.vertex[j], origin))
			{
				onPolygon = true;
				break;
			}
		}

		// 原点在凸包内。
		if (!onPolygon)
			minLength = minConvexHullLength(frosh, froshNumber) + 2.0;

		cout << fixed << setprecision(2) << minLength << '\n';
	}

	return 0;
}
