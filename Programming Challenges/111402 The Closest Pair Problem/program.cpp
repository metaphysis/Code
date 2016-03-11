// The Closest Pair Problem （最近点对问题）
// PC/UVa IDs: 111402/10245, Popularity: A, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-09
// UVa Run Time: 0.240s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 经典问题，可以使用运行时间为 O（nlgn） 的分治算法，具体可参考 Thomas H. Cormen 《算法导论》
// 第 2 版第 33 章第 4 小节的内容。虽然算法是比较容易理解的，但是自己实际实现起来还是费了一番功
// 夫的，不过在自己实现了之后，对其理解又加深了一步，不断的练习实践，我想这是提高能力的唯一捷径。

#include <iostream>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAXN 10000		// 点的最大数量。
#define MAXDISTANCE (1E10)	// “无限大” 距离值，需要根据具体应用设置。

struct point
{
	double x;
	double y;
};

point points[MAXN];	// 记录点的坐标数据。
int pointsNumber;	// 点的总个数。

// 计算两点的距离，只是计算其距离的平方和。
inline double calDistance(point a, point b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// 分治法求最近点对距离。
double closestDistance(int P[], int Pn, int X[], int Xn, int Y[], int Yn)
{
	// 递归调用的出口，当拆分后点数小于等于 3 个时，使用穷举法计算最近距离。注意初始距离应
	// 设为 “无限大”，“无限大” 的具体值应该根据具体应用设置。
	if (Pn <= 3)
	{
		double distance = MAXDISTANCE;
		for (int i = 0; i < Pn - 1; i++)
			for (int j = i + 1; j < Pn; j++)
			{
				double tmp = calDistance(points[P[i]], points[P[j]]);
				distance = min(distance, tmp);
			}
			
		return distance;
	}
	
	// 分解：把点集 P 划分为两个集合 Pl 和 Pr。并得到相应的 Xl，Xr，Yl，Yr。
	int Pl[MAXN], Pln, Pr[MAXN], Prn;
	int Xl[MAXN], Xln, Xr[MAXN], Xrn;
	int Yl[MAXN], Yln, Yr[MAXN], Yrn;

	// 标记某点是否在划分的集合 Pl 中。初始时，所有点不在集合 Pl 中。
	bool inPl[MAXN];
	memset(inPl, false, sizeof(inPl));

	// 将数组 P 划分为两个数量接近的集合 Pl 和 Pr。Pl 中的所有点在线 l 上或在 l 的左侧，
	// Pr 中的所有点在线 l 上或在 l 的右侧。数组 X 被划分为两个数组 Xl 和 Xr，分别包含
	// Pl 和 Pr 中的点，并按 x 坐标单调递增的顺序排序。类似的，数组 Y 被划分为两个数组 Yl
	// 和 Yr，分别包含 Pl 和 Pr 中的点，并按 y 坐标单调递增的顺序进行排序。对于 Xl，Xr，
	// Yl， Yr，由于参数 X 和 Y 均已排序，只需从中拆分出相应的点即可，并不需要再次排序，
	// 拆分后的仍保持排序的性质不变，这是获得 O（nlgn） 运行时间的关键，否则若再次排序，运
	// 形时间将为 O（n（lgn）^2）。
	int middle = Pn / 2;
	Pln = Xln = middle;
	for (int i = 0; i < Pln; i++)
	{
		Pl[i] = Xl[i] = X[i];
		inPl[X[i]] = true;
	}
	Prn = Xrn = (Pn - middle);
	for (int i = 0; i < Prn; i++)
		Pr[i] = Xr[i] = X[i + middle];

	// 根据某点所属集合，划分 Yl 和 Yr。
	Yln = Yrn = 0;
	for (int i = 0; i < Yn; i++)
		if (inPl[Y[i]])
			Yl[Yln++] = Y[i];
		else
			Yr[Yrn++] = Y[i];

	// 解决：把 P 划分为 Pl 和 Pr 后，再进行两次递归调用，一次找出 Pl 中的最近点对，另一次
	// 找出 Pr 中的最近点对。
	double distanceL = closestDistance(Pl, Pln, Xl, Xln, Yl, Yln);
	double distanceR = closestDistance(Pr, Prn, Xr, Xrn, Yr, Yrn);

	// 合并：最近点对要么是某次递归调用找出的距离为 distance 的点对，要么是 Pl 中的一个点
	// 与 Pr 中的一个点组成的点对，算法确定是否存在其距离小于 distance 的一个点对。
	double minDistance = min(distanceL, distanceR);
	

	// 建立一个数组 Y‘，它是把数组 Y 中所有不在宽度为 2 * minDistance 的垂直带形区域内
	// 的点去掉后所得的数组。数组 Y’ 与 Y 一样，是按 y 坐标顺序排序的。
	int tmpY[MAXN], tmpYn = 0;
	for (int i = 0; i < Yn; i++)
		if (fabs(points[Y[i]].x - points[X[middle]].x) <= minDistance)
			tmpY[tmpYn++] = Y[i];

	// 对数组 Y‘ 中的每个点 p，算法试图找出 Y’ 中距离 p 在 minDistance 单位以内的点。仅
	// 需要考虑在 Y‘ 中紧随 p 后的 7 个点。算法计算出从 p 到这 7 个点的距离，并记录下 Y‘
	// 的所有点对中，最近点对的距离 tmpDistance。
	double tmpDistance = MAXDISTANCE;
	for (int i = 0; i < tmpYn; i++)
	{
		int top = ((i + 7) < tmpYn ? (i + 7) : (tmpYn - 1));
		for (int j = i + 1; j <= top; j++)
		{
			double tmp = calDistance(points[tmpY[i]], points[tmpY[j]]);
			tmpDistance = min(tmpDistance, tmp);
		}	
	}

	// 如果 tmpDistance 小于 minDistance，则垂直带形区域内，的确包含比根据递归调用所找
	// 出的最近距离更近的点对，于是返回该点对及其距离 tmpDistance。否则，就返回递归调用中
	// 发现的最近点对及其距离 minDistance。
	return min(minDistance, tmpDistance);
} 

bool cmpX(int a, int b)
{
	return points[a].x < points[b].x;
}

bool cmpY(int a, int b)
{
	return points[a].y < points[b].y;
}

double calClosestDistance()
{
	// 准备初始条件，注意，在本解决方案中，数组中保存的只是各个点的序号而已，并不是点的坐标，
	// 这样可以减少一些数据复制的时间，同时不影响算法的实现。
	int P[MAXN], Pn;
	int X[MAXN], Xn;
	int Y[MAXN], Yn;

	// 赋初值。
	Pn = Xn = Yn = pointsNumber;
	for (int i = 0; i < pointsNumber; i++)
		P[i] = X[i] = Y[i] = i;

	// 预排序，按 x 坐标和 y 坐标分别排序。
	sort(X, X + Xn, cmpX);
	sort(Y, Y + Yn, cmpY);

	// 调用分治算法。
	return closestDistance(P, Pn, X, Xn, Y, Yn);
}

int main(int ac, char *av[])
{
	cout.precision(4);
	cout.setf(ios::fixed | ios::showpoint);

	while (cin >> pointsNumber, pointsNumber)
	{
		for (int i = 0; i < pointsNumber; i++)
			cin >> points[i].x >> points[i].y;
		
		double minDistance = sqrt(calClosestDistance());
		
		if (minDistance > 10000.0)
			cout << "INFINITY" << endl;
		else
			cout << minDistance << endl;	
	}

	return 0;
}
