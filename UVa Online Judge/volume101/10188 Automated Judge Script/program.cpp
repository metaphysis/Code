// Automated Judge Script （自动评测脚本）
// PC/UVa IDs: 110305/10188, Popularity: B, Success rate: average Level: 1
// Verdict: Accepted
// Submission Date: 2016-01-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;

// AC 的含义是精确匹配。
bool isAC(vector < string > solutions, vector < string > answers)
{
	if (solutions.size() != answers.size())
		return false;
	
	for (int i = 0; i < solutions.size(); i++)
		if (solutions[i] != answers[i])
			return false;

	return true;
}
	
bool isPE(vector < string > solutions, vector < string > answers)
{
	string numberInSolutions, numberInAnswers;
	
	for (int m = 0; m < solutions.size(); m++)
		for (int n = 0; n < solutions[m].length(); n++)
			if (isdigit(solutions[m][n]))
				numberInSolutions += solutions[m][n];
				
	for (int m = 0; m < answers.size(); m++)
		for (int n = 0; n < answers[m].length(); n++)
			if (isdigit(answers[m][n]))
				numberInAnswers += answers[m][n];
	
	if (numberInSolutions.length() != numberInAnswers.length())
		return false;
		
	for (int i = 0; i < numberInSolutions.length(); i++)
		if (numberInSolutions[i] != numberInAnswers[i])
			return false;
	
	return true;
}
	
int main(int ac, char *av[])
{
	int number;
	vector < string > solution, answer;
	string line;
	string output[3] = {"Accepted", "Presentation Error", "Wrong Answer"};
	int cases = 0;
	
	while (cin >> number, number)
	{
		solution.clear();
		answer.clear();
		
		// 读入正确答案。
		cin.ignore();
		for (int i = 0; i < number; i++)
		{
			getline(cin, line);
			solution.push_back(line);
		}
		
		// 读入提交。
		cin >> number;
		cin.ignore();
		for (int i = 0; i < number; i++)
		{
			getline(cin, line);
			answer.push_back(line);
		}
		
		// 0 = AC，1 = PE， 2 = WA。
		int status;
		if (isAC(solution, answer))
			status = 0;
		else if (isPE(solution, answer))
			status = 1;
		else
			status = 2;
	
		cases++;
		cout << "Run #" << cases << ": " << output[status] << endl;
	}
	
	return 0;
}
