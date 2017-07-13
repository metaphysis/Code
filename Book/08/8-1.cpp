#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MATRIX_SIZE = 8;

int columnSelected[MATRIX_SIZE] = {0}, columnUsed[MATRIX_SIZE] = {0};
int offset[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
int solutions = 0;

// 检查是否满足对角线规则。
bool check()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int k = 0; k < 4; k++)
        {
            int ii = i, jj = columnSelected[i];

            ii += offset[k][0];
            jj += offset[k][1];

            while (0 <= ii && ii < MATRIX_SIZE && 0 <= jj && jj < MATRIX_SIZE)
            {
                if (columnSelected[ii] == jj)
                    return false;

                ii += offset[k][0];
                jj += offset[k][1];
            }
        }

    return true;
}

// 输出放置方案，放置皇后的位置以Q表示。
void display()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
            if (columnSelected[i] == j)
                cout << " Q";
            else
                cout << " *";
        cout << '\n';
    }
    cout << '\n';
}

void backtrack(int index)
{
    // 当行数达到棋盘的最大行数时进行验证。
    if (index == MATRIX_SIZE && check())
    {
        solutions++;
        display();
    }
    else
    {
        // 未达到棋盘最大行数，继续进行递归回溯。注意在递归的前后设置对应位向量的值。
        for (int i = 0; i < MATRIX_SIZE; i++)
            if (!columnUsed[i])
            {
                columnUsed[i] = 1;
                columnSelected[index] = i;
                backtrack(index + 1);
                columnUsed[i] = 0;
            }
    }
}


int main(int argc, char *argv[])
{
    // 回溯并输出具体放置方案和总的方案数。
    solutions = 0;
    backtrack(0);
    cout << solutions << '\n';

    return 0;
}
