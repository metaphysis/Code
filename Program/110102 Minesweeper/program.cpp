// Minesweeper （扫雷）
// PC/UVa IDs: 110102/10189, Popularity: A, Success rate: high Level: 1
// Verdict: Accepted 
// Submission Date: 2011-04-09
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

#define MAXSIZE 100

inline bool range_checking(int x, int y, int line, int row)
{
	return (0 <= x && x < line) && (0 <= y && y < row);
}

void display(char matrix[][MAXSIZE], int line, int row)
{
	int bounds[8][2] =
		{ {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0},
		{1, 1} };

	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < row; j++)
		{
			// 如果该位置为地雷则原样输出地雷的符号。
			if (matrix[i][j] == '*')
				cout << "*";
			else
			{
				// 统计该点周围 8 点的地雷总数。
				int mines = 0;
				for (int k = 0; k < 8; k++)
				{
					int m = i + bounds[k][0];
					int n = j + bounds[k][1];

					if (range_checking(m, n, line, row)
						&& matrix[m][n] == '*')
						mines++;
				}

				cout << mines;
			}
		}

		cout << endl;
	}
}

int main(int ac, char *av[])
{
	char matrix[MAXSIZE][MAXSIZE];
	int line, row, field = 0;

	while ((cin >> line >> row, line && row))
	{
		memset(matrix, 0, sizeof(matrix));

		for (int i = 0; i < line; i++)
			for (int j = 0; j < row; j++)
				cin >> matrix[i][j];

		if (field > 0)
			cout << endl;
		field++;

		cout << "Field #" << field << ":" << endl;

		display(matrix, line, row);
	}

	return 0;
}
