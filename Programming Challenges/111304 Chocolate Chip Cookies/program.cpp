// Chocolate Chip Cookies （巧克力片饼干）
// PC/UVa IDs: 111304/10136, Popularity: C, Success rate: average Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-05
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 若两片巧克力距离小于等于模具的直径，则可以移动模具，使得两片巧克力同时处于模具的边界上，这样再
// 确定处于这个模具内的巧克力片数量就变得相对容易了，由于要使得模具内的巧克力片最多，只需枚举所有
// 这样的模具位置，求其模具内巧克力片的最大值即可。

#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

#define MAXN 200

struct point
{
	double x, y;
};

point chips[MAXN], center, median;
int totalChips;

// 计算圆心在 center 处，半径为 2.5cm 的模具内有多少巧克力片。
int chipsInCutter()
{
	int nCount = 0;
	for (int i = 0; i < totalChips; i++)
	{
		double distance = sqrt(pow(chips[i].x - center.x, 2) +
			pow(chips[i].y - center.y, 2));
		if (distance <= 2.50)
			nCount++;
	}
	return nCount;
}

int main(int ac, char *av[])
{
	istringstream iss;
	string line;
	int cases;
	bool printEmptyLine = false;

	cin >> cases;
	cin.ignore();
	getline(cin, line);

	while (cases--)
	{
		// 读取巧克力片的位置。
		totalChips = 0;
		while (getline(cin, line), line.length())
		{
			iss.clear();
			iss.str(line);
			iss >> chips[totalChips].x >> chips[totalChips].y;
			totalChips++;
		}

		// 若两点距离小于等于模具的直径，则可求出模具的圆心位置，使得两点刚好在模具的
		// 边界上，注意，如果任意两点的距离都大于 5.0 cm，则最大巧克力片数为 1。
		int maxChips = 1;
		for (int i = 0; i < totalChips - 1; i++)
			for (int j = i + 1; j < totalChips; j++)
			{
				double distance = sqrt(pow(chips[i].x - chips[j].x, 2) + 
						pow(chips[i].y - chips[j].y, 2));

				if (distance > 5.0)
					continue;

				// 先处理特殊情况。
				if (chips[i].x == chips[j].x)
				{
					center.x = chips[i].x + sqrt(2.50 * 2.50 -
						pow(fabs(chips[i].y - chips[j].y) / 2.0, 2));
					center.y = (chips[i].y + chips[j].y) / 2.0;
					maxChips = max(maxChips, chipsInCutter());

					center.x = chips[i].x - sqrt(2.50 * 2.50 -
						pow((chips[i].y - chips[j].y) / 2.0, 2));
					maxChips = max(maxChips, chipsInCutter());
					continue;
				}

				if (chips[i].y == chips[j].y)
				{
					center.x = (chips[i].x + chips[j].x) / 2.0;
					center.y = chips[i].y + sqrt(2.50 * 2.50 -
						pow(fabs(chips[i].x - chips[j].x) / 2.0, 2));
					maxChips = max(maxChips, chipsInCutter());

					center.y = chips[i].y - sqrt(2.50 * 2.50 -
						pow(fabs(chips[i].x - chips[j].x) / 2.0, 2));
					maxChips = max(maxChips, chipsInCutter());
					continue;
				}

				// 根据经过圆心 center 的直线与过点 i，j 的直线垂直的关
				// 系计算圆心的坐标。先求出点 i，j 连线的中点。注意会有两
				// 个圆满足条件（若两点距离为 5.0cm，则两圆重合）。
				point median;
				median.x = (chips[i].x + chips[j].x) / 2.0;
				median.y = (chips[i].y + chips[j].y) / 2.0;

				// 求点 i，j 连线中点至圆心的距离，进而求圆心坐标。
				double slope = -(chips[j].x - chips[i].x) /
					(chips[j].y - chips[i].y);

				double segment = sqrt(2.50 * 2.50 -
					(pow(chips[i].x - chips[j].x, 2) +
					pow(chips[i].y - chips[j].y, 2)) / 4.0);

				double A = atan(slope);

				center.x = median.x + segment * cos(A);
				center.y = median.y + segment * sin(A);
				maxChips = max(maxChips, chipsInCutter());

				center.x = median.x - segment * cos(A);
				center.y = median.y - segment * sin(A);
				maxChips = max(maxChips, chipsInCutter());
			}

		if (printEmptyLine)
			cout << endl;
		else
			printEmptyLine = true;

		cout << maxChips << endl;
	}

	return 0;
}
