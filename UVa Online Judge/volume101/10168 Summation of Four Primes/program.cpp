// Summation of Four Primes （四素数之和）
// PC/UVa IDs: 110705/10168, Popularity: A, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-11
// UVa Run Time: 0.128s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 这两个猜想对于题目指定范围内的数都已经验证了，能够成立，故需要利用这两个猜想。若数 n <=
// 7，则不可能拆分为 4 个素数之和，若 n 为大于等于 8 的数，当 n 为偶数时，n - 2 - 2 仍为偶
// 数，当 n 为奇数时，n - 2 - 3 为偶数，按照哥德巴赫猜想，任何大于等于 4 的偶数都可以
// 表示成 2 个素数之和。

#include <iostream>
#include <cmath>

using namespace std;

// 判断某数是否为素数。
bool is_prime(long n)
{
	if (n == 2)
		return true;

	if (n % 2 == 0)
		return false;
		
	for (int c = 3; c <= ceil(sqrt(n)); c += 2)
		if (n % c == 0)
			return false;
			
	return true;
}

// 将偶数拆分为 2 个素数之和。
void even(long number, long *a, long *b)
{	
	if (number == 4)
	{
		*a = 2;
		*b = 2;
		return;
	}
	
	for (int c = 3; c <= number / 2; c += 2)
		if (is_prime(c) && is_prime(number - c))
		{
			*a = c;
			*b = number - c;
			
			break;
		}
}

int main(int ac, char *av[])
{
	long n, a, b;
	
	while (cin >> n)
	{
		if (n <= 7)
		{
			cout << "Impossible." << endl;
			continue;
		}
		
		if (n % 2)
		{
			even(n - 5, &a, &b);
			cout << "2 3 " << a << " " << b << endl;
		}
		else
		{
			even(n - 4, &a, &b);
			cout << "2 2 " << a << " " << b << endl;
		}
	}
	
	return 0;
}
