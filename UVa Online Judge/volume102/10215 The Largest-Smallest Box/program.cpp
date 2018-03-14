// The Largest/Smallest Box... （最大/最小的盒子）
// PC/UVa IDs: 111306/10215, Popularity: A, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-11-02
// UVa Run Time: 0.040s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 容易知道，盒子的容积为：
//
// V = (L - 2 * x) * (W - 2 * x) * x = 4 * (x * x * x) - 2 * (L + W) * (x * x) +
// L * W * x 
//
// 要求其极值，很明显，当 x = 0 或 x = min(L, W) / 2 时有最小值 0，但是最大值就不是那么容易
// 看出来了，可以通过对该式求导得出。上式的导数为：
//
// V‘ = 12 * x * x - 4 * (L + W) * x + L * W
//
// 解导数为 0 时的方程，方程的一个解即为取最大值时 x 的值。值得注意的是，由于本题并未采用 Special
// Judge，需要在结果加上一个很小的常数才能 AC，而在 Programming Challenges 上加上很小的常数
// 反而错误。

#include <bits/stdc++.h>

using namespace std;

#define EPSILON (1E-7)

int main(int ac, char *av[])
{
	double L, W;

	cout.precision(3);
	cout.setf(ios::fixed | ios::showpoint);

	while (cin >> L >> W)
	{
		cout << (L + W - sqrt((double)(L * L - L * W + W * W))) / 6.0 + EPSILON;
		cout << " 0.000 ";
		cout << (min(L, W) * 0.5 + EPSILON) << endl;
	}

	return 0;
}
