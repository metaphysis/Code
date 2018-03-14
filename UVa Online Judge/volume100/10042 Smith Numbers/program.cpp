// Smith Numbers （Smith 数）
// PC/UVa IDs: 110706/10042, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-06-10
// UVa Run Time: 0.060s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 对数进行素因子分解即可。因为所求数小于 10E9，若某数是合数，则其素因子至少有一个小于或等于
// sqrt(10E9)，则可先计算 2 - sqrt(10E9) 之间的素数以备用。

#include <bits/stdc++.h>

using namespace std;

#define UPBOUND 31623	// ceil(sqrt(10E9))	

vector < int > prime;	// 存储 2 - ceil(sqrt(10E9)) 之间的素数，方便解题。

// 判断数 n 是否是素数。
bool is_prime(int n)
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

// 预先产生 2 - ceil(sqrt(10E9)) 之间的素数。
void find_prime()
{
	prime.push_back(2);
	for (int c = 3; c < UPBOUND; c += 2)
		if (is_prime(c))
			prime.push_back(c);
}

// 计算数 number 的数位之和。
int digits_sum(int number)
{
	int sum = 0;
	while (number)
	{
		sum += (number % 10);
		number /= 10;
	}
	
	return sum;
}

void smith(int number)
{
	int current = number + 1;
	while (1)
	{
		// 如果是素数，不是 Smith 数。
		if (is_prime(current))
		{
			current++;
			continue;
		}
		
		// 计算数 current 的数位数字之和。
		int tmp = current;
		int sum = digits_sum(current), tsum = 0;
		
		// 计算数 current 的素因子之和。
		while (1)
		{
			int memo = tmp;
			for (int c = 0; c < prime.size(); c++)
				if (tmp % prime[c] == 0)
				{
					tmp /= prime[c];
					tsum += digits_sum(prime[c]);
					break;
				}
			
			// 若 tmp 为 1，表明找到了所有的素因子，若 tmp 未变化，则表明在
			// 2 - sqrt(10E9) 之间已经没有 tmp 的素因子存在，则 tmp 必定
			// 是一个素数。
			if (tmp == 1 || memo == tmp)
				break;
		}
		
		// 此时若 tmp 不为 1，则必定是素数，因为若是合数，在 2 - sqrt(10E9) 之间
		// 都没有它的素因子，这是不可能的，若这样，该数的素因子都大于sqrt(10E9)，则
		// 该数必定大于 10E9，与题目条件不符合。
		if (tmp > 1)
			tsum += digits_sum(tmp);
		
		// 判断素因子和与数位和是否相等。
		if (tsum == sum)
		{
			cout << current << endl;
			break;
		}
		
		current++;
	}
}

int main(int ac, char *av[])
{
	int cases, number;
	
	find_prime();
	
	cin >> cases;
	while (cases--)
	{
		cin >> number;
		smith(number);
	}

	return 0;
}
