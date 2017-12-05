// Minesweeper （扫雷）
// PC/UVa IDs: 110102/10189, Popularity: A, Success rate: high Level: 1
// Verdict: Accepted 
// Submission Date: 2014-03-01
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>

using namespace std;

const int MAXSIZE = 100;

void display(char matrix[][MAXSIZE], int row, int column)
{
    int offset[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
    };

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            // 如果该位置为地雷则原样输出地雷的符号。
            if (matrix[i][j] == '*')
                cout << "*";
            else
            {
                // 统计该点周围8点的地雷总数。
                int mines = 0;
                for (int k = 0; k < 8; k++)
                {
                    int m = i + offset[k][0];
                    int n = j + offset[k][1];

                    if ((0 <= m && x < row) && (0 <= n && n < column) && matrix[m][n] == '*')
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
    int row, column, field = 0;

    while ((cin >> row >> column, row && column))
    {
        memset(matrix, 0, sizeof(matrix));

        for (int i = 0; i < row; i++)
            for (int j = 0; j < column; j++)
                cin >> matrix[i][j];

        if (field > 0)
            cout << endl;
        field++;

        cout << "Field #" << field << ":" << endl;

        display(matrix, row, column);
    }

    return 0;
}
