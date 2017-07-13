// Permalex
// UVa ID: 153
// Verdict: Accepted
// Submission Date: 2016-02-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int prime[31][5] = {
    {0}, {0}, {1, 2}, {1, 3}, {2, 2, 2}, {1, 5}, {2, 2, 3}, {1, 7},
    {3, 2, 2, 2}, {2, 3, 3}, {2, 2, 5}, {1, 11}, {3, 2, 2, 3},
    {1, 13}, {2, 2, 7}, {2, 3, 5}, {4, 2, 2, 2, 2}, {1, 17},
    {3, 2, 3, 3}, {1, 19}, {3, 2, 2, 5}, {2, 3, 7}, {2, 2, 11}, {1, 23},
    {4, 2, 2, 2, 3}, {2, 5, 5}, {2, 2, 13}, {3, 3, 3, 3},
    {3, 2, 2, 7}, {1, 29}, {3, 2, 3, 5}
};

long long fullPermutation(string line)
{
	vector<int> dividend, divisor;

	for (int i = 2; i <= line.length(); i++)
		for (int j = 1; j <= prime[i][0]; j++)
			dividend.push_back(prime[i][j]);

	int alpha[26] = {0};
	for (int i = 0; i < line.length(); i++)
		alpha[line[i] - 'a']++;

	for (int i = 0; i < 26; i++)
		for (int j = 2; j <= alpha[i]; j++)
			for (int k = 1; k <= prime[j][0]; k++)
			    divisor.push_back(prime[j][k]);

	for (int i = 0; i < divisor.size(); i++)
		for (int j = 0; j < dividend.size(); j++)
			if (divisor[i] == dividend[j])
			{
				dividend.erase(dividend.begin() + j);
				break;
			}

	long long product = 1;
	for (int i = 0; i < dividend.size(); i++)
		product *= dividend[i];

	return product;
}

long long int permutation(string current, string original)
{
	int counter = current.length();
	long long index = 0;
    set<string> cache;

    sort(current.begin(), current.end());

	while (counter--)
	{
		string next(current);
		sort(next.begin() + 1, next.end());

		if (cache.find(next) == cache.end())
		{
			cache.insert(next);
			if (next < original)
			{
			    if (next.front() < original.front())
			        index += fullPermutation(current.substr(1));
			    else if (current.length() > 1)
				    index += permutation(next.substr(1), original.substr(1));
			}
		}

		current += current.front(); current.erase(0, 1);
	}
	
	return index;
}

int main(int argc, char* argv[])
{
	string line, original;
	while (getline(cin, line), line != "#")
	{
	    if (line.length() == 0) continue;
	    long long index = permutation(line, line) + 1;
		cout << setw(10) << right << index << '\n';
    }

	return 0;
}
