// Ones （仅由 1 组成的数）
// PC/UVa IDs: 110504/10127, Popularity: A, Success rate: high Level: 2
// Verdict: Accepted
// Submission Date: 2011-05-29
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <iostream>
	
using namespace std;
	
int main(int ac, char *av[])
{
	int number;
	
	while (cin >> number)
	{
		long long start = 1;
		int counter = 1;
		while (start % number)
		{
			start = (start % number) * (10 % number) + 1;
			counter++;
		}
		
		cout << counter << endl;
	}
	
	return 0;
}
