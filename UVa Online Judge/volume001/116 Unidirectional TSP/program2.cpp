// Unidirectional TSP
// UVa ID: 116
// Verdict: Wrong Answer
// Submission Date: 2018-09-30
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int m, n;

int dfs(int i, int j)
{
}

int main(int argc, char *argv[])
{
	int m, n, minRow, preRow;
	int matrix[11][101], parent[11][101], weight;
	
	while (cin >> m >> n)
	{
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				cin >> matrix[i][j];
		dfs(0, 0);
	}

	return 0;
}
