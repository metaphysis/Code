// UVa Problem 111 - History Grading
// Verdict: Accepted
// Submission Date: 2011-11-25
// UVa Run Time: 0.052s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 可以将问题转化为求最长上升子序列的问题。

#include <iostream>
#include <sstream>

using namespace std;

#define MAXN 25

int order[MAXN], events[MAXN], length[MAXN], n;

int getScores(void)
{
	for (int i = 1; i <= n; i++)
		length[i] = 1;

	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			if (events[j] < events[i] && (length[j] + 1) > length[i])
				length[i] = length[j] + 1;
	
	int maxLength = 1;
	for (int i = 1; i <= n; i++)
		maxLength = max(maxLength, length[i]);

	return maxLength;
}

int getIndex(int index)
{
	for (int i = 1; i <= n; i++)
		if (order[i] == index)
			return i;
}

int main (int argc, char *argv[])
{
	string line;
	int index;

	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> index;
		order[index] = i;
	}

	cin.ignore();

	while (getline(cin, line))
	{
		istringstream iss(line);

		for (int i = 1; i <= n; i++)
		{
			iss >> index;
			events[index] = getIndex(i);
		}
		
		cout << getScores() << endl;
	}

	return 0;
}

