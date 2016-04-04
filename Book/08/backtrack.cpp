#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MATRIX_SIZE = 8;

vector < int > columnSelected;
vector < bool > columnUsed;
int solutions, steps[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

// 检查是否满足对角线规则。
bool isSolution()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int k = 0; k < 4; k++)
        {
            int ii = i, jj = columnSelected[i];

            ii += steps[k][0];
            jj += steps[k][1];

            while (0 <= ii && ii < MATRIX_SIZE && 0 <= jj && jj < MATRIX_SIZE)
            {
                if (columnSelected[ii] == jj)
                    return false;

                ii += steps[k][0];
                jj += steps[k][1];
            }
        }

    solutions++;

    return true;
}

// 输出放置方案，放置皇后的位置以 Q 表示。
void display()
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
            if (columnSelected[i] == j)
                cout << " Q";
            else
                cout << " *";
        cout << endl;
    }
    cout << endl;
}

void backtrack(int index)
{
    // 当行数达到棋盘的最大行数时进行验证。
    if (index == MATRIX_SIZE)
    {
        if (isSolution())
            display();

        return;
    }

    // 未达到棋盘最大行数，继续进行递归回溯。
    // 注意在递归的前后设置对应位向量的值。
    for (int i = 0; i < MATRIX_SIZE; i++)
        if (columnUsed[i] == false)
        {
            columnUsed[i] = true;
            columnSelected[index] = i;
            backtrack(index + 1);
            columnUsed[i] = false;
        }
}

// 初始化值。
int main(int argc, char *argv[])
{
    columnUsed.resize(MATRIX_SIZE);
    columnSelected.resize(MATRIX_SIZE);

    solutions = 0;
    fill(columnUsed.begin(), columnUsed.end(), false);

    backtrack(0);

    cout << solutions << endl;

    return 0;
}
