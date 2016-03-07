// Carmichael Numbers （Carmichael 数）
// PC/UVa IDs: 110702/10006, Popularity: A, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2011-06-10
// UVa Run Time: 0.336s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// 此题关键是应用求模公式 x^y mod n = (x mod n)^y mod n。这里用到了预先计算给定范围内所有
// Carmichael 数的方法，因为在这区间里的数并不多！如果使用求模的方式，注意使用
// (x mod n) ^ y mod n = ((x mod n) ^ (y / 2) mod n) * ((x mod n) ^ (y / 2)
//  mod n) * ((x mod n) ^ (y % 2) mod n) mod n，减少计算时间，否则容易TLE。

#include <iostream>
#include <cmath>

using namespace std;

#define CAPACITY 15

void print(int n, bool normal)
{
	if (normal)
		cout << n << " is normal." << endl;
	else
		cout << "The number " << n << " is a Carmichael number." << endl;
}

int main(int ac, char *av[])
{
	int n;
	int array[CAPACITY] =
		{ 561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341,
			41041, 46657, 52633, 62745, 63973 };

	while (cin >> n, n)
	{
		bool normal = true;
		for (int c = 0; c < CAPACITY; c++)
			if (array[c] == n)
			{
				normal = false;
				break;
			}

		print(n, normal);
	}

	return 0;
}
