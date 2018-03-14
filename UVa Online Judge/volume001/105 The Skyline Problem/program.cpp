// Skyline Problem
// UVa ID: 105
// Verdict: Accepted
// Submission Date: 2011-11-22
// UVa Run Time: 0.036s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

#define MAXN 10010

int grid[MAXN];

int main (int argc, char const* argv[])
{
	int left, height, right, leftMost, rightMost = 0;
	bool leftSetted = false;

	memset(grid, 0, sizeof(grid));

	while (cin >> left >> height >> right)
	{
		for (int i = left; i <= right; i++)
			grid[i] = max(grid[i], height);

		if (!leftSetted)
		{
			leftMost = left;
			leftSetted = true;
		}
		
		rightMost = max(rightMost, right);
	}

	cout << leftMost << " " << grid[leftMost];

	int current = leftMost;
	for (int i = leftMost; i <= rightMost; i++)
	{
		if (grid[i] == grid[current])
			continue;
		else
		{
			if (grid[i] > grid[current])
				cout << " " << i << " " << grid[i];
			else
				cout << " " << (i - 1) << " " << grid[i];
				
			current = i;
		}
	}

	cout << " " << rightMost << " 0\n";

	return 0;
}

