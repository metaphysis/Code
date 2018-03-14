// Marbles （弹珠）
// PC/UVa IDs: 110707/10090, Popularity: B, Success rate: low Level: 1
// Verdict: Accepted
// Submission Date: 2011-06-14
// UVa Run Time: 0.080s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 求不定方程 n1 * x + n2 * y = n 的正整数解，且要求 x * c1 + y * c2 最小。相
// 当于求解一元线性同余式，首先根据情况判断是否有解。若有解，先求出同余式 n1 * x ≡ n
// (mod n2) 的解，若 GCD(n1, n2) = 1，则该同余式在模 n2 的意义下有唯一解，即扩展
// Euclid算法输出的 x'，则上述同余式的解即为 n / GCD(n1, n2) * x' + k * n2 /
// GCD(n1, n2)，即不定方程 n1 * x + n2 * y = n，x = n / GCD(n1, n2) * x'
// + k * n2 / GCD(n1, n2)，若有 c1 * n2 < c2 * n1, 则 x 和 y 在保证为正整数
// 的情况下 x 越大，花费约少，若 c1 * n2 > c2 * n1，则 x 应为最小的正整数则花费较
// 少，若相等，则任意满足条件的 x，y 花费相同。为何会这样？因为假设有 M 颗弹珠，全部
// 用第一种规格的盒子装，花费是 M / n1 * c1，若用第二种规格的盒子装，则花费为 M /
// n2 * c2，若有 M / n1 * c1 < M / n2 * c2，则用第一种规格的盒子越多，花费越省，
// 化简可以得到：c1 * n2 < c2 * n1，反之 c1 * n2 > c2 * n1，则用第二种规格的盒
// 子越多，花费越省，若相等，则任意满足方程的非负整数 x，y 所产生的花费都是相等的。注意
// 本题中数据类型的使用，因为 1 ≤ n ≤ 2,000,000,000，所以最好使用 long long 型整
// 数以免中间计算结果出错导致 WA。

#include <bits/stdc++.h>

using namespace std;

// 根据扩展的 Euclid 算法获得满足 a * x + b * y = GCD(a, b) 的 x，y。
long long gcd(long long a, long long b, long long *x, long long *y)
{
	long long tx, ty;
	long long g;
	
	if (b > a)
		return gcd(b, a, y, x);
	
	if (b == 0)
	{
		*x = 1;
		*y = 0;
			
		return a;
	}
	
	g = gcd(b, a % b, &tx, &ty);
	
	*x = ty;
	*y = tx - floor(a / b) * ty;
	
	return g;
}

int main(int ac, char *av[])
{
	long long n, c1, n1, c2, n2, x, y;
	
	while (cin >> n, n)
	{
		cin >> c1 >> n1 >> c2 >> n2;

		long long g = gcd(n1, n2, &x, &y);
		
		// 根据一次线性同余式，若 gcd(a, n) 不能整除 b，则同余式无解。
		if (n % g != 0)
		{
			cout << "failed" << endl;
			continue;
		}
		
		// 有通解。x = n2 / GCD(n1, n2) * k + n / GCD(n1, n2) * x'，
		// y = n / GCD(n1, n2) * y' - n1 / GCD(n1, n2) * k，k 为任意整数。
		// 可根据 x >= 0 和 y >= 0 求出 k 的取值范围。注意正数和负数的取低值和高
		// 值，需要将其转换为单精度或双精度数后取才能获得正确的取值范围，否则是整数之
		// 间的除法，可能会得到错误的取值范围。
		long long lowk = ceil(-n * x / (double)n2);
		long long upk = floor(n * y / (double)n1);
		
		// 区间有可能为空，这是需要注意的，忽略了这点，导致了几次 WA 提交。
		if (lowk > upk)
		{
			cout << "failed" << endl;
			continue;
		}
		
		// 若 c1 * n2 <= c2 * n1，此种情况下 x 越大花费越少，则 k 取上限。反
		// 之 k 取下限，x 越小花费越少。等于的情况可放到任意一个情况中，因为所产生
		// 的费用都是相等的。
		if (c1 * n2 <= c2 * n1)
		{
			x = n2 / g * upk + n / g * x;
			y = n / g * y - n1 / g * upk;
		}
		else
		{
			x = n2 / g * lowk + n / g * x;
			y = n / g * y - n1 / g * lowk;
		}
		
		cout << x << " " << y << endl;
	}
	
	return 0;
}
