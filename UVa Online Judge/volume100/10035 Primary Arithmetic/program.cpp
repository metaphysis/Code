// Primary Arithmetic （小学生算术）
// PC/UVa IDs: 110501/10035, Popularity: A, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-27
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
	int first, second;
	
	while (cin >> first >> second, first || second)
	{
		int carry = 0;
		int counter = 0;
		while (first && second)
		{
			carry = (((first % 10 + second % 10 + carry) > 9) ? 1 : 0);
			counter += carry;
			first /= 10;
			second /= 10;
		}
		
		while (first)
		{
			carry = ((first % 10 + carry > 9) ? 1 : 0);
			counter += carry;
			first /= 10;
		}
		
		while (second)
		{
			carry = ((second % 10 + carry > 9) ? 1 : 0);
			counter += carry;
			second /= 10;		
		}
		
		if (counter > 1)
			cout << counter << " carry operations." << endl;
		else if (counter == 1)
			cout << "1 carry operation." << endl;
		else
			cout << "No carry operation." << endl;
	}
	
	return 0;
}
