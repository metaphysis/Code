// 8 Queens Chess Problem
// UVa ID: 750
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MATRIX_SIZE = 8;

int column_selected[8] = {0}, column_used[8] = {0};
int offset[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int matrix[100][8][8] = {0}, solutions;

// 检查是否满足对角线规则。
bool is_solution()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int k = 0; k < 4; k++)
        {
            int ii = i, jj = column_selected[i];

            ii += offset[k][0];
            jj += offset[k][1];

            while (0 <= ii && ii < MATRIX_SIZE && 0 <= jj && jj < MATRIX_SIZE)
            {
                if (column_selected[ii] == jj)
                    return false;

                ii += offset[k][0];
                jj += offset[k][1];
            }
        }

    return true;
}

// 保存解决方案。
void save_solutions()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            if (column_selected[i] == j)
                matrix[solutions][i][j] = 1;
    solutions++;
}

void backtrack(int index)
{
    // 当行数达到棋盘的最大行数时进行验证。
    if (index == MATRIX_SIZE && is_solution())
        save_solutions();
    else
    {

        // 未达到棋盘最大行数，继续进行递归回溯。意在递归的前后设置对应位向量的值。
        for (int i = 0; i < MATRIX_SIZE; i++)
            if (!column_used[i])
            {
                column_used[i] = 1;
                column_selected[index] = i;
                backtrack(index + 1);
                column_used[i] = 0;
            }
    }
}

// 初始化值。
int main(int argc, char *argv[])
{
    int row, column, cases;
    
    backtrack(0);
    
    cin >> cases;
    for (int c = 1; c <= cases; c++)
    {
        if (c > 1) cout << '\n';

        cout << "SOLN       COLUMN\n";
        cout << " #      1 2 3 4 5 6 7 8\n";
        cout << '\n';
        
        cin >> row >> column;

        vector<string> rows;
        for (int i = 0; i < solutions; i++)
        {
            if (matrix[i][row - 1][column - 1])
            {
                string row_number;
                for (int j = 0; j < MATRIX_SIZE; j++)
                    for (int k = 0; k < MATRIX_SIZE; k++)
                        if (matrix[i][k][j])
                        {
                            row_number += ' ';
                            row_number += (char)('1' + k);
                            break;
                        }
                
                rows.push_back(row_number);
            }
        }
        
        sort(rows.begin(), rows.end());
        for (int i = 0; i < rows.size(); i++)
            cout << setw(2) << (i + 1) << "     " << rows[i] << '\n';
    }

    return 0;
}
