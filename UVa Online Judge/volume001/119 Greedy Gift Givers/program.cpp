// Greedy Gift Givers
// UVa ID: 119
// Verdict: Accepted
// Submission Date: 2011-11-26
// UVa Run Time: 0.012s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 简单的模拟题。

#include <iostream>
#include <map>

using namespace std;

#define MAXN 15

map< string, int> money;
string name[MAXN];

int main (int argc, char const* argv[])
{
	int n, moneyGive, nReceivers;
	string giver, receiver;
	bool printBlankLine = false;

	while (cin >> n)
	{
		if (printBlankLine)
			cout << endl;
		else
			printBlankLine = true;

		money.clear();
		for (int i = 0; i < n; i++)
		{
			cin >> name[i];
			money[name[i]] = 0;
		}

		for (int i = 1; i <= n; i++)
		{
			cin >> giver >> moneyGive >> nReceivers;
			for (int j = 1; j <= nReceivers; j++)
			{
				cin >> receiver;
				money[receiver] += (moneyGive / nReceivers);
			}
			
			if (nReceivers)
				money[giver] -= (moneyGive / nReceivers * nReceivers);
		}
		
		for (int i = 0; i < n; i++)
			cout << name[i] << " " << money[name[i]] << endl;
	}

	return 0;
}

