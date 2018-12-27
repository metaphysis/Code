// Cricket Field
// UVa ID: 1312
// Verdict: Accepted
// Submission Date: 2018-12-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 110;

struct tree
{
	int x, y;
	tree (int x = 0, int y = 0): x(x), y(y) {}
} trees[MAXV];

int N, W, H;

bool cmpXY(tree a, tree b)
{
	return (a.x == b.x) ? (a.y < b.y) : (a.x < b.x);
}

bool cmpX(tree a, tree b)
{
	return a.x < b.x;
}

bool cmpY(tree a, tree b)
{
	return a.y < b.y;
}

int main(int ac, char *av[])
{
	int cases, cnt;

	cin >> cases;
	while (cases--)
	{
		cin >> N >> W >> H;

		for (int i = 0; i < N; i++)
			cin >> trees[i].x >> trees[i].y;
		cnt = N;
        trees[cnt++] = tree(0, 0);
		trees[cnt++] = tree(W, H);

		int maxSide = 0, xx, yy, lowY, topY, leftX, rightX;
		sort(trees, trees + cnt, cmpX);
		for (int i = 0; i < cnt; i++)
		{
			lowY = 0, topY = H;
			for (int j = i + 1; j < cnt; j++)
			{
				if (trees[j].x == trees[i].x) continue;
				else
				{
					int side = min(trees[j].x - trees[i].x, topY - lowY);
					if (side > maxSide)
					{
					    maxSide = side;
					    xx = trees[i].x, yy = lowY;
					}
					if (trees[j].y < trees[i].y)
						lowY = max(lowY, trees[j].y);
					else
						topY = min(topY, trees[j].y);
				}
			}
		}

		sort(trees, trees + cnt, cmpY);
		for (int i = 0; i < cnt; i++)
		{
			leftX = 0, rightX = W;
			for (int j = i + 1; j < cnt; j++)
			{
				if (trees[j].y == trees[i].y) continue;
				else
				{
					int side = min(trees[j].y - trees[i].y, rightX - leftX);
					if (side > maxSide)
					{
					    maxSide = side;
					    xx = leftX, yy = trees[i].y;
					}
					if (trees[j].x < trees[i].x)
						leftX = max(leftX, trees[j].x);
					else
						rightX = min(rightX, trees[j].x);
				}
			}
		}
		
		cout << xx << ' ' << yy << ' ' << maxSide << '\n';
		if (cases) cout << '\n';
	}

	return 0;
}
