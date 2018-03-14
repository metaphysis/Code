// WERTYU （WERTYU 键盘）
// PC/UVa IDs: 110301/10082, Popularity: A, Success rate: high Level: 1
// Verdict: Accepted
// Submission Date: 2011-05-17
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
int main(int ac, char *av[])
{
	string keyboard = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
	string line;
	
	while(getline(cin, line))
	{
		for (int i = 0; i < line.length(); i++)
			if (line[i] == ' ')
				cout << " ";
			else
				cout << keyboard[keyboard.find_first_of(line[i]) - 1];
		cout << endl;
	}
	
	return 0;
}
