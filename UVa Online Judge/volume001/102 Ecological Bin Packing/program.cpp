// UVa Problem 102 - Ecological Bin Packing
// Verdict: Accepted
// Submission Date: 2011-10-16
// UVa Run Time: 0.164s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <sstream>

using namespace std;

#define MAXN 3
#define MAXTYPES 6

int bottles[MAXN][MAXN], total;
string sequences[MAXTYPES] = { "132", "123", "312", "321", "213", "231" };
string bins[MAXTYPES] = { "BCG", "BGC", "CBG", "CGB", "GBC", "GCB" };

int move(string sequence)
{
	int movements = total;

	for (int i = 0; i < sequence.length(); i++)
		for (int j = 0; j < MAXN; j++)
			if (j == i)
				movements -= bottles[j][sequence[i] - '1'];

	return movements;
}

int main(int ac, char *av[])
{
	string line;

	while (getline(cin, line))
	{
		istringstream iss(line);

		total = 0;
		for (int i = 0; i < MAXN; i++)
			for (int j = 0; j < MAXN; j++)
			{
				iss >> bottles[i][j];
				total += bottles[i][j];
			}

		int minimum = total, marker;
		for (int i = 0; i < MAXTYPES; i++)
		{
			int movements = move(sequences[i]);
			if (minimum > movements)
			{
				minimum = movements;
				marker = i;
			}
		}

		cout << bins[marker] << " " << minimum << endl;
	}

	return 0;
}
