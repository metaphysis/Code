// Factovisors （阶乘与整除）
// PC/UVa IDs: 110704/10139, Popularity: A, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-11
// UVa Run Time: 0.312s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 思路比较简单，计算数 m 和数 2 - n 的 GCD，若 GCD > 1，则 m /= GCD，若最后 m 不为
// 1 则表明 m 不能整除 n!，注意输入可能有一些特殊情况存在，注意处理即可。很奇怪，在
// Programming Challenges 上 AC，RT 为 0.072 秒，可是在 UVa 上面却总是 TLE，后来增加
// 了一句素数测试的语句才 AC，应该是有特殊的测试数据造成的，故需要在循环中及时检查条件，退出
// 循环，以免 TLE。

#include <iostream>
#include <cmath>

using namespace std;

// 判断某数是否为素数。
bool is_prime(long unsigned number)
{
	if (number == 2)
		return true;
	
	if (number % 2 == 0)
		return false;
	
	for (long unsigned c = 3; c <= ceil(sqrt(number)); c += 2)
		if (number % c == 0)
			return false;
		
	return true;
}

// 求两数的 GCD。
long unsigned gcd(long unsigned a, long unsigned b)
{
	if (a < b)
	{
		long unsigned tmp = a;
		a = b;
		b = tmp;
	}
	
	while (b > 0)
	{
		long unsigned tmp = a;
		a = b;
		b = tmp % b;
	}
	
	return a;
}

int main(int ac, char *av[])
{
	long unsigned n, m;
	
	// 读入 n 和 m。
	while (cin >> n >> m)
	{
		bool divided = false;
		long unsigned t = m, g;
		
		// 特殊情况 m = 1。
		if (m == 1)
		{
			divided = true;
			goto print;
		}
		
		// 特殊情况 m = 1。
		if (m == 0)
			goto print;
		
		// 若 m 为素数且 m 大于 n，则 m 和 2 - n 互素。
		if (is_prime(m) && m > n)
			goto print;
		
		// m <= n，当然可以整除。
		if (m <= n)
		{
			divided = true;
			goto print;
		}
		
		// 从 n 到 2 递减找 GCD(m, c)。
		for (long unsigned c = n; c >= 2; c--)
		{
			g = gcd(m, c);
			
			// 当有大于 1 的最大公约数时进行处理，并判断是否满足退出条件。
			if (g > 1)
			{
				m /= g;
				
				// m < c，则可整除。
				if (m < c)
				{
					divided = true;
					goto print;
				}
				
				// m >= c。
				if (is_prime(m))
					goto print;
			}
		}
		
		// 根据结果打印，注意输出单词的差别。
print:
		
		if (divided)
			cout << t << " divides " << n << "!" << endl;
		else
			cout << t << " does not divide " << n << "!" << endl;
	}
	
	return 0;
}
