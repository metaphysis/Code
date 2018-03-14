// The Stern-Brocot Number System （Stern-Brocot 代数系统）
// PC/UVa IDs: 110507/10077, Popularity: C, Success rate: high Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-29
// UVa Run Time: 0.016s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
struct fraction
{
	long long unsigned numerator;
	long long unsigned denominator;
};
	
int main(int ac, char *av[])
{
	long long unsigned up, down;
	fraction left, right, middle;
	
	while (cin >> up >> down, (up - down))
	{
		left.numerator = 0;
		left.denominator = 1;
	
		right.numerator = 1;
		right.denominator = 0;
	
		middle.numerator = 1;
		middle.denominator = 1;
		
		while (1)
		{			
			if (up * middle.denominator == down * middle.numerator)
				break;
			
			if (up * middle.denominator > down * middle.numerator)
			{
				cout << "R";
			
				left.numerator =  middle.numerator;
				left.denominator = middle.denominator;
			
				middle.numerator = (left.numerator + right.numerator);
				middle.denominator = (left.denominator + right.denominator);
			}
			else
			{
				cout << "L";
			
				right.numerator =  middle.numerator;
				right.denominator = middle.denominator;
			
				middle.numerator = (left.numerator + right.numerator);
				middle.denominator = (left.denominator + right.denominator);			
			}
		}
		
		cout << endl;
	}
	
	return 0;
}
