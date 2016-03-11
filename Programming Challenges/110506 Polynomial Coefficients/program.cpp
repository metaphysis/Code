// Polynomial Coefficients （多项式系数）
// PC/UVa IDs: 110506/10105, Popularity: B, Success rate: high Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-29
// UVa Run Time: 0.024s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
	
using namespace std;
	
long long unsigned factorial(int m)
{
	if (m == 0)
		return 1;
	if (m == 1)
		return 1;
	return m * factorial(m - 1);
}
	
int main(int ac, char *av[])
{
	int n, k, tmp;
	
	while (cin >> n >> k)
	{
		long long unsigned numerator = factorial(n);
		long long unsigned denominator = 1;
		while (k--)
		{
			cin >> tmp;
			denominator *= factorial(tmp);
		}
		
		cout << numerator / denominator << endl;
	}
	
	return 0;
}
