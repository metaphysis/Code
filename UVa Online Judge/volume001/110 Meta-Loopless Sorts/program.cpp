// Meta-Loopless Sorts
// UVa ID: 110
// Verdict: Accepted
// Submission Date: 2011-11-25
// UVa Run Time: 0.196s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 啊哈，又是一道很有意思的模拟题。本题解是依照题目所给的示例模拟生成插入排序的 Pascal 程序。

#include <bits/stdc++.h>

using namespace std;

int n;
string tab(2, ' ');

string substr(string s, int start, int length)
{
	if (start >= s.length())
		return "";
	return s.substr(start, length);
}

void writeln(string space, string sequences)
{
	cout << space << "writeln(";
	for (int i = 0; i < sequences.length(); i++)
		cout << (i ? "," : "") << sequences[i];
	cout << ")\n";
}

void sort(string space, string sequences)
{
	char c = (char) ('a' + sequences.length());
	for (int i = sequences.length(); i >= 0; i--)
	{
		if (i)
		{
			cout << space << "if " << sequences[(i ? (i - 1) : i)];
			cout << " < " << c << " then\n";
		}

		string tmp = substr(sequences, 0, i) + c +
			substr(sequences, i, sequences.length() - i);

		if (tmp.length() == n)
			writeln(space + (i ? tab : ""), tmp);
		else
			sort(space + tab, tmp);

		if (i)
		{
			cout << space << "else\n";
			space += tab;
		}
	}
}

int main(int argc, char const *argv[])
{
	int cases;
	bool printBlankLine = false;
	
	cin >> cases;
	while (cases--)
	{
		cin >> n;

		if (printBlankLine)
			cout << "\n";
		else
			printBlankLine = true;

		cout << "program sort(input,output);\n";

		cout << "var\n";
		for (int i = 0; i < n; i++)
			cout << (i ? "," : "") << (char) ('a' + i);
		cout << " : integer;\n";

		cout << "begin\n";

		cout << (tab + "readln(");
		for (int i = 0; i < n; i++)
			cout << (i ? "," : "") << (char) ('a' + i);
		cout << ");\n";

		sort("", "");

		cout << "end.\n";
	}

	return 0;
}
