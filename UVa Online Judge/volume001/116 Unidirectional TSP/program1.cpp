// Unidirectional TSP
// UVa ID: 116
// Verdict: Wrong Answer
// Submission Date: 2018-09-30
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
	int m, n, minRow, preRow;
	int matrix[11][101], parent[11][101], weight;
	
	while (cin >> m >> n)
	{
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				cin >> matrix[i][j];

        // From left to right, Wrong Answer.
		for (int j = 2; j <= n; j++)
		{
			for (int i = 1; i <= m; i++)
			{
				weight = INT_MAX;

				preRow = (i == 1 ? m : i - 1);
				if (weight > matrix[preRow][j - 1])
				{
					weight = matrix[preRow][j - 1];
					minRow = preRow;
				}
				else if (weight == matrix[preRow][j - 1] && minRow > preRow)
					minRow = preRow;

				if (weight > matrix[i][j - 1])
				{
					weight = matrix[i][j - 1];
					minRow = i;
				}
				else if (weight == matrix[i][j - 1] && minRow > i)
					minRow = i;

				preRow = (i == m ? 1 : i + 1);
				if (weight > matrix[preRow][j - 1])
				{
					weight = matrix[preRow][j - 1];
					minRow = preRow;
				}
				else if (weight == matrix[preRow][j - 1] && minRow > preRow)
					minRow = preRow;

				matrix[i][j] += weight;
				parent[i][j] = minRow;
			}
		}

		weight = INT_MAX;
		for (int i = 1; i <= m; i++)
			if (matrix[i][n] < weight)
			{
				weight = matrix[i][n];
				minRow = i;
			}

		vector<int> tags;
		tags.push_back(minRow);
		int next = n, preRow = minRow;
		while (next > 1)
		{
			tags.push_back(parent[preRow][next]);
			preRow = parent[preRow][next];
			next--;
		}
		reverse(tags.begin(), tags.end());
        for (int i = 0; i < n; i++)
        {
            if (i) cout << ' ';
            cout << tags[i];
        }
		cout << "\n";
		cout << matrix[minRow][n] << "\n";
	}

	return 0;
}
