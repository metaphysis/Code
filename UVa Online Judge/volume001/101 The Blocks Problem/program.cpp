// UVa Problem 101 - The Blocks Problem
// Verdict: Accepted
// Submission Date: 2011-10-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cstring>
#include <set>

using namespace std;

#define MAXN 25

int blocks[MAXN];
int state[MAXN][MAXN];
int nBlocks;

void returning(int x, pair < int, int > xIndex)
{
	for (int i = xIndex.second + 1; i < blocks[xIndex.first]; i++)
	{
		int tmp = state[xIndex.first][i];
		state[tmp][blocks[tmp]++] = tmp;
	}

	blocks[xIndex.first] = xIndex.second + 1;
}

void moveOver(int a, int b, pair < int, int > aIndex, pair < int, int > bIndex)
{
	returning(a, aIndex);

	state[bIndex.first][blocks[bIndex.first]++] = a;
	blocks[aIndex.first] = aIndex.second;
}

void moveOnto(int a, int b, pair < int, int > aIndex, pair < int, int > bIndex)
{
	returning(b, bIndex);
	moveOver(a, b, aIndex, bIndex);
}

void pileOver(int a, int b, pair < int, int > aIndex, pair < int, int > bIndex)
{
	int current = aIndex.second;
	while (current < blocks[aIndex.first])
		state[bIndex.first][blocks[bIndex.first]++] =
			state[aIndex.first][current++];

	blocks[aIndex.first] = aIndex.second;
}

void pileOnto(int a, int b, pair < int, int > aIndex, pair < int, int > bIndex)
{
	returning(b, bIndex);
	pileOver(a, b, aIndex, bIndex);
}

pair < int, int > findIndex(int x)
{
	for (int i = 0; i < nBlocks; i++)
		for (int j = 0; j < blocks[i]; j++)
			if (state[i][j] == x)
				return make_pair(i, j);
}

void print(void)
{
	for (int i = 0; i < nBlocks; i++)
	{
		cout << i << ":";
		for (int j = 0; j < blocks[i]; j++)
			cout << " " << state[i][j];
		cout << endl;
	}
}

int main(int ac, char *av[])
{
	int a, b, aIndex, bIndex;
	string command, action;

	cin >> nBlocks;
	for (int i = 0; i < nBlocks; i++)
	{
		blocks[i] = 0;
		state[i][blocks[i]++] = i;
	}

	while (cin >> command, strcmp(command.data(), "quit"))
	{
		cin >> a >> action >> b;

		if (a == b)
			continue;

		pair < int, int > aIndex = findIndex(a);
		pair < int, int > bIndex = findIndex(b);
		if (aIndex.first == bIndex.first)
			continue;

		if (strcmp(command.data(), "move") == 0)
		{
			if (strcmp(action.data(), "onto") == 0)
				moveOnto(a, b, aIndex, bIndex);
			else
				moveOver(a, b, aIndex, bIndex);

		}
		else if (strcmp(action.data(), "onto") == 0)
			pileOnto(a, b, aIndex, bIndex);
		else
			pileOver(a, b, aIndex, bIndex);
	}

	print();

	return 0;
}
