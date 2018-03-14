// The 3n+1 problem
// UVa ID: 100
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.032s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net。
	
#include <bits/stdc++.h>

using namespace std;

#define min(a, b) ((a) <= (b) ? (a) : (b))
#define max(a, b) ((a) >= (b) ? (a) : (b))

#define MAXSIZE 1000000
	
int cache[MAXSIZE];

// 计算循环节长度。
int counter(long long number)
{
	if (number == 1)
		return 1;
	
	// 模 2 计算可用与计算代替，除 2 计算可用右移计算代替。
	if (number & 1)
		number += (number << 1) + 1;
	else
		number >>= 1;
	
	// 若 number 在缓存范围内则根据情况取用。
	if (number < MAXSIZE )
	{
		if (!cache[number])
			cache[number] = counter(number);
		return 1 + cache[number];
	}
	
	return 1 + counter(number);
}
	
int main(int ac, char *av[])
{
	// 对于 GUN C++ 编译器，使用默认参数，在编译时会自动将全局数组 cache 中未初始化
	// 的元素初始化为 0，故可以不需要显式的进行初始化的工作。对于其他编译器应该根据
	// 情况调整。
	//
	// memset(cache, 0, sizeof(cache));
	//
	int first, second, start, end;

	while (cin >> first >> second)
	{
		// 得到给定范围的上下界。
		start = min(first, second);
		end = max(first, second);
		
		// 查找最大步长值。
		int result = 0, steps;
		for (int i = start; i <= end; i++)
			if ((steps = counter(i)) > result)
				result = steps;

		// 输出。
		cout << first << " " << second << " " << result << endl;
	}
	
	return 0;
}
