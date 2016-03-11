// UVa Problem 121 - Pipe Fitters
// Verdict: Accepted
// Submission Date: 2011-12-18
// UVa Run Time: 0.056s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 可以归类为网格题，简单题。

#include <iostream>
#include <cmath>

using namespace std;

int grid(double width, double height)
{
	int nGrid = 0;
	
	nGrid = floor(width) * floor(height);

	return nGrid;
}

int skew(double width, double height)
{
	if (height < 1.0)
		return 0;

	int layers = floor(2.0 * (height - 1.0) / sqrt(3.0) + 1.0);
	int pipes_per_odd_full_row = floor(width);
	int pipes_per_even_full_row = pipes_per_odd_full_row - 1;
	
	if ((width - pipes_per_odd_full_row) >= 0.5)
		pipes_per_even_full_row = pipes_per_odd_full_row;
	
	int nSkew = ceil(layers / 2.0) * pipes_per_odd_full_row + 
		floor(layers / 2.0) * pipes_per_even_full_row;

	return nSkew;
}

int main(int ac, char *av[])
{
	double a, b;
	
	while (cin >> a >> b)
	{
		int nGrid = grid(a, b);
		int nSkew = max(skew(a, b), skew(b, a));
		
		if (nGrid >= nSkew)
			cout << nGrid << " grid" << endl;
		else
			cout << nSkew << " skew" << endl;
	}

	return 0;
}
