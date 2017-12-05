// Is This Integration? （需要积分吗？）
// PC/UVa IDs: 111307/10209, Popularity: A, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-11-01
// UVa Run Time: 0.120s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 设斜线部分的面积为 X，打点部分的面积为 Y，网格部分的面积为 Z，则有以下方程：
//
// X + 3 * Y / 4 + Z / 2 = PI * a * a / 4
// X + Y + Z = a * a
//
// 要解方程，必须还有一个独立方程，这个可以由计算左下角和右下角两个四分之一圆重叠部分的面积来得到，
// 这个重叠的面积很容易计算，仔细观察一下图就可以得到。
//
// X + Y / 2 + Z / 4 = PI * a * a / 3 - sqrt(3) * a * a / 4
//
// 联立三个方程可得：
//
// X = a * a * (1 - sqrt(3) + PI / 3)
// Y = a * a * (2 * sqrt(3) - 4 + PI / 3)
// Z = a * a * (4 - sqrt(3) - 2 * PI / 3)

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define PI 3.141592653589793

int main(int ac, char *av[])
{
	double a, x, y, z;
	
	while (cin >> a)
	{
		x = a * a * (1 - sqrt(3) + PI / 3);
		y = a * a * (2 * sqrt(3) - 4 + PI / 3);
		z = a * a * (4 - sqrt(3) - 2 * PI / 3);
		
		cout.precision(3);
		cout.setf(ios::fixed | ios::showpoint);
		cout << x << " " << y << " " << z << endl;
	}

	return 0;
}
