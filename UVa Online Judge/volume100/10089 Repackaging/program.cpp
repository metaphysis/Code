// Repackaging （重新打包）
// PC/UVa IDs: 110708/10089, Popularity: C, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-19
// UVa Run Time: 0.048s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 题目实质是什么？求解不定方程组吗？
// 我所想到的是，假设有 n 种包装规格，每种包装规格中有 a，b，c 三种不同大小的杯子，
// 问题问的是以下方程是否有解：
//
// x1 * a1 + x2 * a2 + ... + xn * an = k
// x1 * b1 + x2 * b2 + ... + xn * bn = k
// x1 * c1 + x2 * c2 + ... + xn * cn = k
//
// 要求 xi >= 0，k > 0。可以设：
//
//     [a1 a2 a3 ... an]
// A = [b1 b2 b3 ... bn]
//     [c1 c2 c3 ... cn]
//
//     [x1]
//     [x2]
// X = [x3]
//     [..]
//     [xn]
//
//     [k]
// C = [k]
//     [k]
//
// 有 A * X = C，要求矩阵乘积是否有非负数解。可以通过计算方程的系数矩阵和增广矩阵的
// 秩来判断是否有解，但是只能是判断是否有非零解，不能判断是否有非负数解。这个办法好像
// 行不通。
//
// 在 UVa 的 BBS 上查看了一些帖子，有以下几种方法：
//
// 1. 单纯形法来解决，对于我来说难度大了些，没有接触过这个算法，从维基的介绍上可以知道
// 算法比较复杂。
// 2. 转化为 2D 求点是否在凸包内的问题。一个包装规格定义一个 2 维平面的向量
// （S2 - S1，S3 - S1），所求的就是这些向量组成的多边形是否包含原点（0，0），如果
// 包含原点，则有非负整数解，否则无非负整数解。如果无解，向量都严格在经过原点的某条直
// 线的半平面内。可以采用判断两个相邻向量之间的夹角，如果任意两个向量的夹角都不超过
// PI 弧度，则方程有解，否则无解。考虑有 n 个向量 V1 - Vn，按向量与 X 轴成角的大
// 小从小到大排列，如果相邻的某两个向量之间的夹角大于 PI 弧度，则可以从原点作一条直
// 线，使得所有的向量都在这条直线的某一边，则当这 n 个向量都乘以某一个系数后，只会距
// 离直线越来越远，故原点是不会在这些向量围成的多边形中的。若相邻向量的夹角都在 PI
// 弧度以内，则可以将多余的向量去掉，留下三个向量，这三个向量之间的夹角都不超过 PI
// 弧度，设为 W1，W2，W3，则一定有某个向量处于两外两个向量的中间，假设为 W2 处于
// W1 和 W3 中间，则可以找到适当的非负系数使得 x * W1 + y * W3 的和与 -W3 相等。
// 系数是有理数，可以乘以相应的数使得 x 和 y 变成整数。根据以上分析，假设原点不再在
// 众向量围成的多边形内，则所有向量必定在一个小于 PI 弧度的区域内。
// 3. 判断 3D 中点 （1，1，1） 是否在所给包装规格和原点定义的一个棱锥中。
//
// 注意解题过程中应选择 long long 型整数以避免溢出。

#include <bits/stdc++.h>

using namespace std;

struct point
{
	long long x;
	long long y;
};

// 判断所有向量是否都落在一个角度小于 PI 弧度的区域内，若该条件成立，则无非负整数解，若
// 不成立，则表明原点在这些向量所围成的多边形内。
bool repackaging(vector < point > &points)
{
	// vup 和 vbottom 两向量将所有向量包括在内。初始值均为向量 points[0]。
	point vup = points[0], vbottom = points[0];
	for (int i = 0; i < points.size(); i++)
	{
		// 先判断当前向量与 vup 和 vbottom 是否共线。因为本题已经指定
		// 同一包装中 S1 = S2 = S3 的情况不存在。故点不会在坐标轴上。
		// 且有 points[i].x != points[i].y，且不为 0。
		
		// 判断向量 vup 和 vbottom 与 points[i] 是否在同一条直线上。
		if (vup.y * points[i].x == points[i].y * vup.x )
		{
			// 通过向量的点积来判断是同向平行还是异向平行。
			if (points[i].x * vup.x + points[i].y * vup.y < 0)
				return true;
			else
				continue;
		}
		if (vbottom.y * points[i].x == points[i].y * vbottom.x)
		{
			if (points[i].x * vbottom.x + points[i].y * vbottom.y < 0)
				return true;
			else
				continue;
		}
		
		// 按逆时针方向找 vup，如果当前向量在 vup 逆时针的左边，则用当前向量替换 vup。
		if (vup.y * points[i].x < vup.x * points[i].y)
			vup = points[i];
		// 按顺时针方向找 vbottom，如果当前向量在 vbottom 顺时针的右边，则用当前
		// 向量替换 vbottom。
		if (vbottom.y * points[i].x > vbottom.x * points[i].y)
			vbottom = points[i];
			
		// 判断 vup 和 vbottom 成角是否大于等于 PI 弧度，若条件成立表明当前已经检测
		// 的向量构成的区域大于 PI 弧度，原点必在该多边形内。
		// 重合，成角为 2 * PI 弧度。
		if (vup.x == vbottom.x && vup.y == vbottom.y)
			return true;
			
		//  共线，判断是否为异向平行，即成角 PI 弧度。
		if (vup.x * vbottom.y == vup.y * vbottom.x)
		{
			if (vup.x * vbottom.x + vup.y * vbottom.y < 0)
				return true;
			else
				continue;
		}
		
		// 成角在 PI 弧度 和 2 * PI 弧度之间。
		if (vup.y * vbottom.x < vup.x * vbottom.y)
			return true;
	}
	
	// 原点不再向量所围成的多边形内，无解。
	return false;
}

int main(int ac, char *av[])
{
	int n;
	vector < point > points;
	
	while (cin >> n, n)
	{
		points.clear();
		points.resize(n);
		
		for (int i = 0; i < n; i++)
		{
			long long a, b, c;
			cin >> a >> b >> c;
			points[i].x = b - a;
			points[i].y = c - a;
		}
		
		cout << (repackaging(points) ? "Yes" : "No") << endl;
	}
	
	return 0;
}
