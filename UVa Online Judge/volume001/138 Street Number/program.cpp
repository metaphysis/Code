// Street Number
// UVa ID: 138
// Verdict: Accepted
// Submission Date: 2016-01-19
// UVa Run Time: 0.349s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

// 设程序员所在家的号码为 x，街道最末房子号码为 y，则根据等差序列求和公式有：
//
// (1 + (x - 1)) * (x - 1) / 2 * 2 = (x + 1 + y) * (y - x) / 2 * 2
//
// 化简得到：
//
// 2 * x * x = y * y + y = y * (y + 1)
//
// 问题转化为：求相邻两个自然数，他们的乘积的一半为一个平方数。

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
    int pairs = 0;
    long long int y = 8;
    while (pairs < 10)
    {
        long long int x = (long long int)sqrt(y * (y + 1) / 2);
        if ((2 * x * x) == (y * (y + 1)))
        {
            cout << setw(10) << x << setw(10) << y << endl;
            pairs++;
        }
        y++;
    }
    
	return 0;
}
