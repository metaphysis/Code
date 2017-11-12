#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAXV = 8;

int column[MAXV] = {0}, used[MAXV] = {0}, solutions = 0;

// 检查是否满足对角线规则。
bool safe()
{
    for (int i = 0; i < MAXV; i++)
        for (int j = 0; j < i; j++)
            if (abs(i - j) == abs(column[i] - column[j]))
                return false;
    return true;
}

// 输出放置方案，放置皇后的位置以Q表示。
void display()
{
    for (int i = 0; i < MAXV; i++)
    {
        for (int j = 0; j < MAXV; j++)
            cout << (column[i] == j ? " Q" : " *");
        cout << '\n';
    }
    cout << '\n';
}

void backtrack(int depth)
{
    // 当行数达到棋盘的最大行数时进行验证。
    if (depth == MAXV && safe()) {
        display();
        solutions++;
        return;
    }

    // 未达到棋盘最大行数，继续进行递归回溯。注意在递归的前后设置对应位向量的值。
    for (int i = 0; i < MAXV; i++) if (!used[i]) {
        used[i] = 1, column[depth] = i;
        backtrack(depth + 1);
        used[i] = 0;
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
