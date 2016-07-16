// Fermat vs. Pythagoras
// UVa ID: 106
// Verdict: Accepted
// Submission Date: 2011-11-21
// UVa Run Time: 0.236s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 该题可以归结为数论问题。
//
// 若是用穷举法生成 1000000 以内所有的勾股数，会超时，故需要考虑其他方法。如果方程有
// 一个通解，那么根据通解生成 x，y，z，肯定方便得多，有没有这样的通解公式呢，答案是肯
// 定的，推导如下：
//
// 本题的要求是当 x，y，z ∈ N，给定一个数 n，找出所有的 x，y，z ≤ n，使得
// x² + y² = z² 成立。
//
// 先假定 x，y，z 互质，若不互质，则可设 x = w * x0，y = w * y0，z = w * z0，将其
// 转化为互质的情形后讨论。由于 x，y，z 互质，故 x，y 中至少有一个是奇数。下面用反证
// 法证明 x 和 y 中有且只有一个奇数。假定 x，y 都为奇数，设：
//
//    x = 2 * a + 1
//    y = 2 * b + 1
//    x² + y² = (2 * a + 1)² + (2 * b + 1)² = 4(a² + b² + a + b) + 2 = z²
//
// 则 z² 是偶数，若 z² 为偶数，则 z 必为偶数，那么 z² 必能被 4 整除，与上式矛盾，因
// 此 x，y 中只有一个奇数。
//
// 假设 x 为奇数，y 为偶数，由于奇数的平方是奇数，偶数的平方是偶数，和 z² 必为奇数，
// 则 z 为奇数。那么 z + x 和 z - x 都是偶数，不妨设 z + x = 2u，z - x = 2v（这是
// 费马提到的一种方法），解得：
//
//    z = u + v
//    x = u - v
//
// 而且由于 x，y，z 互质，则 u，v 也必定互质，若不互质，则可设 u = w * u0，
// v = w * v0，则 z 和 x 有大于 1 的公约数 w，与前提条件矛盾。给原方程两边同除以 4 
// 得：
//
// x² / 4 + y² / 4 = z² / 4
//
// 然后移项: (y / 2)² = (z / 2)² - (x / 2)²
//
// 右边是个平方差公式：
//
// (z / 2)² - (x / 2)² = (z + x) / 2 * (z - x) / 2
//
// 然后把刚才的 u，v 代入上式：
//
// (z + x) / 2 * (z - x) / 2 = (2 u / 2) * (2 v / 2) = u * v
//
// 也就是说 (y / 2)² = u * v，说明 u * v 是一个平方数，又因为 u，v 互质，所以 u 和
//  v 本身都是平方数（为什么？a 和 b 互质，a * b 为完全平方数，设 a * b = u²，则由
// 于(a，b) = 1，所以 a = a * (a，b) = (a²，a * b) = (a²，u²) = (a，u)²，同理
// b = (b，u)²）。
//
// 那么，设 u = a²，v = b²，则 a，b 同样也是一奇一偶，互质的两个数（为什么？因为 u 
// 和 v 互质，则必有一个奇数，又由于 y 为偶数，则 u 和 v 不能同为奇数，故必是一奇一
// 偶。由于奇数的平方是奇数，偶数的平方是偶数，则 a 和 b 也是一奇一偶，若 a 和 b 不
// 互质，可推出 u 和 v 不互质，矛盾）。
//
// 从刚才的 (y / 2)² = u * v，代入 a，b 解出 (y / 2)² = a² * b²，y / 2 = a * b，
// y = 2 * a * b。y 解出，将 a，b 代入 x，z 得：
//
// x = u - v = a² - b²
// z = u + v = a² + b²
//
// 综上所述，可得到下式：
//
// x = a² - b²， y = 2 * a * b， z = a² + b²，(a 与 b 互质，a > b，且一奇一偶)。
//
// 题目要求统计 (x，y，z) 三元组的数量时只统计 x，y 和 z 两两互质的的情况，这个问题
// 用上面的算法就可以解决了。但对于统计 p 的数量，题目并不限定三元组是两两互质的。上
// 式不能生成所有的勾股数。但所有非两两互质的 x0，y0，z0 都可由一组互质的 x，y，z 乘
// 以系数得到。

#include <iostream>
#include <cmath>

using namespace std;

#define MAXN 1000001

bool used[MAXN];

int gcd(int a， int b)
{
	return a < b ? gcd(b， a) : (b ? gcd(b， a % b) : a);
}

int main(int argc， char const *argv[])
{
	int n， limit， x， y， z;

	while (cin >> n)
	{
		for (int i = 1; i <= n; i++)
			used[i] = false;

		// 根据 z = a² + b²，则有 a，b < (n)^(1/2)。
		limit = floor(sqrt(n));
		
		int total = 0;
		for (int i = 1; i < limit; i++)
			// 满足一奇一偶的要求。j 每次自增 2，保证了奇偶性。
			for (int j = i + 1; j <= limit; j += 2)
				// 若 i，j 互质，则 x，y，z 互质，同时要求 z <= n。
				if ((z = (i * i + j * j)) <= n && gcd(i， j) == 1)
				{
					// 两两互质的解。
					x = j * j - i * i;
					y = 2 * i * j;

					total++;

					// 求出所有非两两互质的解。
					for (int start = 1; z * start <= n; start++)
						used[x * start] = used[y * start] = used[z * start] = true;
				}

		// 统计未使用的数字个数。
		int unused = 0;
		for (int i = 1; i <= n; i++)
			if (!used[i])
				unused++;

		cout << total << " " << unused << endl;
	}

	return 0;
}
