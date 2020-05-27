// Herding Frosh （新生集会）
// PC/UVa IDs: 111401/10135, Popularity: C, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-08
// UVa Run Time: 0.112s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 求凸包一般常用的有两种算法，一种是 Andrew 凸包扫描算法，一种是 Graham 凸包扫描算法。两种方法
// 各有特点，Andrew 凸包扫描算法只需对坐标按 x，y 排序，仅使用一些简单的乘法，相对来说比 Graham
// 凸包扫描算法来得简单，容易编写。
//
// 本题中由于多了一个电话柱，简单的求凸包不能得到正确的答案，需要分两种情况。假设已经求出了所有新
// 生点集所对应的凸包，如果原点在此凸包外，那么依照题意，丝带必须绕过原点，则只需将原点加入新生点
// 集中求凸包，凸包的周长加上多余需要的两米即为答案。若原点在凸包内，则丝带可以从任意两个按相对于
// 原点极角排序的相邻点绕到电话柱子上，此时需要逐个枚举可能的长度，然后求最小值才为正确答案。如何
// 处理后一种情况是有点棘手的，有两种方法，一种是将凸包的顶点与原点相连，则各个凸包顶点与原点形成
// 了一系列 “扇面” 三角形，设某个三角形的顶点为 V1 和 V2，有两种情况，一种是有新生点落在此三角
// 形 V1V2O 内（不包括边界上），一种是此三角形内无新生点，对于后一种情况，丝带的最短长度即为原凸
// 包的周长减去线段 V1V2 的长度，再加上线段 V1O，V2O 的长度。若三角形内有新生点，则可以将这些新
// 生点分成 A，B 两部分，求原点 O，点 V1 和 A 形成的点集的部分凸包，再求原点 O，点 V2 和 B 形
// 成的点集的部分凸包，丝带的长度即为这两个部分凸包的周长加上原凸包的周长减去线段 V1V2，V1O，V2O
// 的长度，注意要枚举所有可能的 A 和 B，这可以通过将在三角形 V1V2O 中的点按相对于原点的极角排序
// 然后依此选择相邻的两个点来分割 A 和 B。
//
// 如果对 Graham 凸包扫描算法有深刻的理解，你可以得到原点在凸包内时，求丝带最小长度一个简便的算法。
// 先将点按照相对于原点的极角排序，然后任意选择两个相邻的点，假设为 p1，p2，按照 Graham 凸包扫描
// 算法的思想开始扫描，不过这里需要将起始点设置为原点，最后一点设置为 p2，在扫描结束时再加上点 p2，
// 那么扫描所得到的 “包” 的形状恰恰就是题目所求丝带的形状。这里需要费点心思的是按相对于原点的极角
// 排序，需要分象限处理。同时需要将重复点和与原点重合的点去掉。
 
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
 
using namespace std;
 
#define MAXPOLY 1010
#define EPSILON (1E-9)
 
struct point
{
	double x;
	double y;
};
 
point origin = (point) { 0.0, 0.0 };
 
struct polygon
{
	int vertexNumber;
	point vertex[MAXPOLY];
};
 
double calDistance(point first, point second)
{
	return sqrt(pow(first.x - second.x, 2) + pow(first.y - second.y, 2));
}
 
// 叉积，判断点 first，second，third 组成的两条线段的转折方向。当叉积大于 0，则形成一个右拐，
// 否则共线（cp = 0）或左拐（cp > 0）。
double crossProduct(point first, point second, point third)
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
			container.vertex[i] = vertex[i];
		container.vertexNumber = vertexNumber;
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
		container.vertex[container.vertexNumber++] = lower[i];
}
 
double convexHullLength(polygon &container)
{
	double length = 0.0;
	for (int i = 0; i < container.vertexNumber; i++)
	{
		int j = (i + 1) % container.vertexNumber;
		length += calDistance(container.vertex[i], container.vertex[j]);
	}
	return length;
}
 
// 将所有点按相对于原点 O 的极角排序。
bool smallerAngle(point first, point second)
{
	// 判断位于不同半平面时的情况。
	if (first.y == 0 && second.y == 0 && first.x * second.x <= 0)
		return first.x > second.x;
	if (first.y == 0 && first.x >= 0 && second.y != 0)
		return true;
	if (second.y == 0 && second.x >= 0 && first.y != 0)
		return false;
	if (first.y * second.y < 0)
		return first.y > second.y;
 
	// 位于同一半平面，使用叉积判断。
	double cp = crossProduct(origin, first, second);
	return cp > 0 || (cp == 0 && fabs(first.x) < fabs(second.x));
}
 
// 当原点在凸包内部时，按题意求最小的丝带长度。
double minConvexHullLength(point in[], int &n)
{
	double length = 1e20;
 
	// 移除所有重复点和原点重合的点，因为后继需要使用叉积判断转折方向，若有重复点，叉积将不
	// 不能正常工作。
	sort(in, in + n, leftLower);
 
	int hole = 0;
	for (int i = 0; i < n; i++)
	{
		if (in[i].x == 0 && in[i].y == 0)
			continue;
		if (hole == 0)
			in[hole++] = in[i];
		else if (in[hole - 1].x == in[i].x && in[hole - 1].y == in[i].y)
			continue;
		else
			in[hole++] = in[i];
	}
	n = hole;
 
	// 将所有点按照相对于原点 O 的极角排序，若极角相同，按距离排序。
	sort(in, in + n, smallerAngle);
 
	// 任意选取一个点 i 开始 Graham 扫描，注意扫描结束点选择为点 i - 1，最初点为原点。
	polygon out;
	for (int i = 0; i < n; i++)
	{
		int top = 1, current = i + 1;
		out.vertex[0] = origin;
		out.vertex[1] = in[i];
 
		while (current < (i + n))
		{
			// 注意这里需要加上 top >= 1，因为起始时有可能会共线，回退不能没有
			// 限制。
			if (top >= 1 && crossProduct(out.vertex[top - 1],
					out.vertex[top], in[current % n]) <= 0)
				top--;
			else
			{
				top++;
				out.vertex[top] = in[current % n];
				current++;
			}
		}
 
		// 点 i 的前一点总算在所求点之内，因为丝带需要从此点经过。
		top++;
		out.vertex[top] = in[(i - 1 + n) % n];
		out.vertexNumber = top;
 
		// 返回找到的较小值。
		length = min(length, convexHullLength(out));
	}
	
	return length;
}
 
int main(int ac, char *av[])
{
	point frosh[MAXPOLY];
	polygon silk;
	int cases, vertexNumber, froshNumber;
	bool printBlankLine = false;
 
	cout.precision(2);
	cout.setf(ios::fixed | ios::showpoint);
 
	cin >> cases;
	while (cases--)
	{
		cin >> froshNumber;
		frosh[0] = origin;
		for (int i = 1; i <= froshNumber; i++)
			cin >> frosh[i].x >> frosh[i].y;
		froshNumber++;
 
		convexHull(frosh, froshNumber, silk);
 
		// 计算凸包的周长。
		double minLength = convexHullLength(silk) + 2.0;
 
		// 判断原点是否在凸包的边界上，或者原点为凸包的一个顶点。
		bool onPolygon = false;
		for (int i = 0; i < silk.vertexNumber; i++)
		{
			int j = (i + 1) % silk.vertexNumber;
			// 判断原点与凸包的顶点 i 和 j 是否共线。
			if (fabs(crossProduct(origin, silk.vertex[i],
					silk.vertex[j])) <= EPSILON)
			{
				onPolygon = true;
				break;
			}
		}
 
		// 原点在凸包内。
		if (!onPolygon)
			minLength = minConvexHullLength(frosh, froshNumber) + 2.0;
		
		if (printBlankLine)
			cout << endl;
		else
			printBlankLine = true;
 
		cout << minLength << endl;
	}
 
	return 0;
}
