// How Big Is It? （它有多大？）
// PC/UVa IDs: 111308/10012, Popularity: B, Success rate: low Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-05
// UVa Run Time: 0.272s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 8;

struct cycle
{
	double x, y;
	double r;
};

double smallestWidth;

double calWidth(double radius[], int m, int used[])
{
	double width = 0.0;
	cycle packedCycles[MAXN];

	packedCycles[0] = cycle{radius[used[0]], radius[used[0]], radius[used[0]]};
	for (int i = 1; i < m; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			double tmpX = packedCycles[j].x, tmpY = radius[used[i]];

			double centerDist = packedCycles[j].r + radius[used[i]];
			double yDiff = fabs(packedCycles[j].r - radius[used[i]]);

			tmpX += sqrt(pow(centerDist, 2) - pow(yDiff, 2));
			if (tmpX < radius[used[i]])
				tmpX = radius[used[i]];

			bool successed = true;
			for (int k = 0; k < i; k++)
				if (k != j)
				{
					centerDist = pow(tmpX - packedCycles[k].x, 2);
					centerDist += pow(tmpY - packedCycles[k].y, 2);
					centerDist = sqrt(centerDist);
					
					if (centerDist < (packedCycles[k].r + radius[used[i]]))
					{
						successed = false;
						break;
					}
				}

			if (successed)
			{
				packedCycles[i] = (cycle){tmpX, tmpY, radius[used[i]]};
				break;
			}
		}
	}

	double maxRight = 0.0;
	for (int i = 0; i < m; i++)
		maxRight = max(maxRight, packedCycles[i].x + packedCycles[i].r);

	return maxRight;
}

void backtrack(double radius[], int m, int c, int used[], bool unused[])
{
	if (c == m)
		smallestWidth = min(smallestWidth, calWidth(radius, m, used));
	else
	{
		for (int i = 0; i < m; i++)
			if (unused[i])
			{
				unused[i] = false;
				used[c] = i;
				backtrack(radius, m, c + 1, used, unused);
				unused[i] = true;
			}
	}
}

int main(int ac, char *av[])
{
	int cases, m;
	double radius[MAXN];
	int used[MAXN];
	bool unused[MAXN];

	cout.precision(3);
	cout.setf(ios::fixed | ios::showpoint);
		
	cin >> cases;
	while (cases--)
	{
		cin >> m;

		smallestWidth = 0.0;
		for (int i = 0; i < m; i++)
		{
			cin >> radius[i];
			smallestWidth += radius[i];
		}

		smallestWidth *= 2.0;
		memset(unused, true, sizeof(unused));
		backtrack(radius, m, 0, used, unused);

		cout << smallestWidth << endl;
	}

	return 0;
}
