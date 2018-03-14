// A Multiplication Game （乘法游戏）
// PC/UVa IDs: 110505/847, Popularity: A, Success rate: high Level: 3
// Verdict: Accepted
// Submission Date: 2011-05-29
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
void ones(int number, bool win)
{
	if (number <= 9 && win)
	{
		cout << "Stan wins." << endl;
		return;
	}
	if (number <= 2 && !win)
	{
		cout << "Ollie wins." << endl;
		return;
	}
	
	if (win)
		ones(ceil(number / 9.0), !win);
	else
		ones(ceil(number / 2.0), !win);
}
	
int main(int ac, char *av[])
{
	int number;
	
	while (cin >> number)
		ones(number, true);
	
	return 0;
}
