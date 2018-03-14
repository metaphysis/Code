// Bee Breeding
// UVa ID: 808
// Verdict: Accepted
// Submission Date: 2018-03-14
// UVa Run Time: 0.020s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// Similar to UVa 10182.

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 10000;

int offset[5][2] = { { -1, 0 }, { 0, -1 }, { 1, -1 }, { 1, 0 }, { 0, 1 } };
pair<int, int> maja[MAXN + 2000];

int main(int ac, char *av[])
{
	for (int i = 1, j = 1, k = 0; i < MAXN ; i += j, j += 6, k++)
	{
		maja[i] = make_pair(0, k);
		for (int m = 0; m < k; m++)
			maja[i - m] = make_pair(m, k - m);

		int current = i;
		for (int m = 0; m < 5; m++)
			for (int n = 0; n < k; n++)
			{
				int x = maja[current].first + offset[m][0];
				int y = maja[current].second + offset[m][1];
				maja[current + 1] = make_pair(x, y);
				current++;
			}
	}

	int a, b, d;
	while (cin >> a >> b)
	{
	    if (a == 0 && b == 0) break;
	    pair<int, int> v = make_pair(maja[a].first - maja[b].first, maja[a].second - maja[b].second);
		if (v.first * v.second < 0)
		    d = max(abs(v.first), abs(v.second));
		else
		    d = abs(v.first + v.second);
	    cout << "The distance between cells " << a << " and " << b << " is " << d << ".\n";
	}

	return 0;
}
