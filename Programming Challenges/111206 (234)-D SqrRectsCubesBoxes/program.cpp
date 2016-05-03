// (2/3/4)-D Sqr/Rects/Cubes/Boxes? （2/3/4维立方体？）
// PC/UVa IDs: 111206/10177, Popularity: B, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.016s

#include <iostream>
#include <cmath>

using namespace std;

#define MAXN 101
#define MAXD 6

#define S2 0
#define R2 1
#define S3 2
#define R3 3
#define S4 4
#define R4 5

long long count[MAXN][MAXD];
int main(int ac, char *av[])
{
	for (int n = 1; n < MAXN; n++)
	{
		count[n][S2] = count[n - 1][S2] + pow(n, 2);
		count[n][S3] = count[n - 1][S3] + pow(n, 3);
		count[n][S4] = count[n - 1][S4] + pow(n, 4);
		
		count[n][R2] = count[n][S3] - count[n][S2];
		count[n][R3] = count[n][S3] * (n - 1) * (n + 2) / 2;
		count[n][R4] = pow(n * (n + 1) / 2, 4) - count[n][S4];	
	}

	int size;
	while (cin >> size)
	{
		for (int d = 0; d < MAXD; d++)
			cout << (d ? " " : "") << count[size][d];
		cout << endl;
	}

	return 0;
}
