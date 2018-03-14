// Rope Crisis in Ropeland! （绳子王国的危机！）
// PC/UVa IDs: 111302/10180, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-02
// UVa Run Time: 0.696s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 根据情况判断绳子是否需要绕过柱子，若需绕过柱子则根据边角关系计算即可。

#include <bits/stdc++.h>

using namespace std;

// 计算需要绕过柱子时的绳子最小长度。
double linePlusArc(double x1, double y1, double x2, double y2, double r)
{
	// 设坐标（x1，y1）为点 M，坐标（x2，y2）为点 N，圆心为 O，将两队
	// 所在点和圆心连接成一个三角形 OMN，边长分别为 a（MO），b（NO），
	// c（MN），则边 c 对应的角 C 可以由余弦定理求出。
	double a = sqrt(x1 * x1 + y1 * y1);
	double b = sqrt(x2 * x2 + y2 * y2);
	double c = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	double C = acos((a * a + b * b - c * c) / (2.0 * a * b));

	// 设经过点 M 与圆相切的直线 L 与圆的切点为 P，则 MPO 构成一个直角
	// 三角形，边 MP 对应的角可以很容易求出。
	 double angleMP = acos(r / a);

	 // 同样的，将经过点 N 与圆相切的直线 L‘ 与圆的切点记为 Q，则 NQO
	 // 构成一个三角形，边 NQ 对应的角也可以很容易求出。
	 double angleNQ = acos(r / b);

	 // 则在柱子上的绳子部分长度可以容易的求出。
	 double length = r * (C - angleMP - angleNQ);

	 // 再加上线段 MP，NQ 的长度即为所需绳子的最小长度。
	 length += (sqrt(a * a - r * r) + sqrt(b * b - r * r));

	 return length;
}

// 计算需要的绳子最小长度。
double ropeLength(double x1, double y1, double x2, double y2, double r)
{
	// 两点相同。
	if (x1 == x2 && y1 == y2)
		return 0.0;

	// 两点横坐标相同，在同一竖线上。
	if (x1 == x2)
	{
		// 若竖线与原点距离小于 r 则绳子需要绕过柱子。
		if ((x1 > 0 ? x1 : (-x1)) < r)
		{
			if (y1 * y2 > 0)
				return fabs(y1 - y2);
			else
				return linePlusArc(x1, y1, x2, y2, r);
		}
		else
			return fabs(y1 - y2);
	}

	// 根据对称性计算。
	if (y1 == y2)
		return ropeLength(y1, x1, y2, x2, r);
	
	// 点 M 和 N 构成的直线斜率不为无穷大，可以使用斜截式来表示。则原点到直线的距离可以方
	// 便的求出。
	double slope = (double)(y1 - y2) / (double)(x1 - x2);
	double intercept = y1 - slope * x1;
	double distance = fabs(intercept) * cos(atan(fabs(slope)));

	// 若原点与直线的距离小于 r 且两队在柱子的两侧，则绳子需要绕过柱子。
	// 否则，不需绕过柱子。
	if (distance < r)
	{
		// 设过两队的直线为 l，求过原点与直线 l 垂直的直线与 l 的交点，若两队的位置
		// 纵坐标均大于交点的纵坐标或者均小于交点的纵坐标，则两队在柱子的一侧。
		double yIntersection = intercept / (slope * slope + 1.0);
		if ((y1 - yIntersection) * (y2 - yIntersection) >= 0.0)
			return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
		else
			return linePlusArc(x1, y1, x2, y2, r);
	}
	else
		return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main(int ac, char *av[])
{
	int cases;
	double x1, y1, x2, y2, r;

	cout.precision(3);
	cout.setf(ios::fixed | ios::showpoint);

	cin >> cases;
	while (cases--)
	{
		cin >> 	x1 >> y1 >> x2 >> y2 >> r;
		cout << ropeLength(x1, y1, x2, y2, r) << endl;
	}

	return 0;
}
