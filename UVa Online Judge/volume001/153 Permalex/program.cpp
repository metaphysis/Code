// Permalex
// UVa IDs: 153
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

int prime[31][5] = { {0}, {0}, {1, 2}, {1, 3}, {2, 2, 2}, {1, 5}, {2, 2, 3}, {1, 7},
{3, 2, 2, 2}, {2, 3, 3}, {2, 2, 5}, {1, 11}, {3, 2, 2, 3}, {1, 13}, {2, 2, 7},
{2, 3, 5}, {4, 2, 2, 2, 2}, {1, 17}, {3, 2, 3, 3}, {1, 19}, {3, 2, 2, 5},
{2, 3, 7}, {2, 2, 11}, {1, 23}, {4, 2, 2, 2, 3}, {2, 5, 5}, {2, 2, 13}, {3, 3, 3, 3},
{3, 2, 2, 7}, {1, 29}, {3, 2, 3, 5} };

long long int computeN(string line)
{
	vector<int> dividend;
	vector<int> divisor;

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
			
	long long int product = 1;
	for (int i = 0; i < dividend.size(); i++)
		product *= dividend[i];

	return product;
}

long long int compute(string line, string original)
{
	int time = line.length();
	long long int index = 0;
    set<string> produced;
    
    sort(line.begin(), line.end());
    
	while (time--)
	{
		string temp(line);
		sort(temp.begin() + 1, temp.end());
		if (produced.count(temp) == 0)
		{
			produced.insert(temp);
			if (temp < original)
			{
			    if (temp[0] < original[0])
			        index += computeN(line.substr(1));
			    else if (line.length() > 1)
				    index += compute(temp.substr(1), original.substr(1));
			}
		}
		line += line[0];
		line.erase(0, 1);
	}
	
	return index;
}

int main(int argc, char* argv[])
{
	string line, original;
	while (getline(cin, line), line != "#")
	{
	    if (line.length() == 0)
	        continue;
		cout << setw(10) << right << (compute(line, line) + 1) << endl;
    }

	return 0;
}
