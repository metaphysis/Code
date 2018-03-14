// Searching Quickly
// UVa ID: 123
// Verdict: Accepted
// Submission Date: 2012-01-03
// UVa Run Time: 0.056s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
//
// [解题方法]
// 简单的字符串处理和排序题。
//
// 提交时错误了一次，因为没有注意到需要忽略的关键词可能会重复给出的情况，修正后就 AC 了。

#include <bits/stdc++.h>

using namespace std;

struct title
{
	string content;
	string keyword;
	int indexKeyword;
	int indexInput;
};

string toLower(string s)
{
	string r;
	for (int i = 0; i < s.length(); i++)
		r += (s[i] >= 'A' && s[i] <= 'Z' ? (s[i] + 32) : s[i]);
	return r;
}

string toUpper(string s)
{
	string r;
	for (int i = 0; i < s.length(); i++)
		r += (s[i] >= 'a' && s[i] <= 'z' ? (s[i] - 32) : s[i]);
	return r;
}

bool cmp(title a, title b)
{
	if (a.keyword == b.keyword)
	{
		if (toLower(a.content) == toLower(b.content))
			return a.indexKeyword < b.indexKeyword;
		else
			return a.indexInput < b.indexInput;
	}

	return a.keyword < b.keyword;
}

int main (int argc, char const* argv[])
{
	set<string> ignore;
	vector<title> titles;
	string line;
	
	while (getline(cin, line))
	{
		if (line != "::")
		{
			// 可能会给出重复的关键词，需要消除。
			if (ignore.find(line) == ignore.end())
				ignore.insert(line);
		}
		else
		{
			int count = 0;
			while (getline(cin, line))
			{
				string all = toLower(line);

				int i = 0;
				while (i < line.length())
				{
					if (line[i] == ' ')
						i++;
					else
					{
						// 将句子中出现的单词逐个分离出来。
						int start = i;
						string tmp;
						while (i < line.length() && line[i] != ' ')
						{
							tmp += line[i];
							i++;
						}
						int end = i;

						// 若不是需要忽略的关键词，则生成一个标题。
						tmp = toLower(tmp);
						if (ignore.find(tmp) == ignore.end())
						{
							string keyword = toUpper(tmp);
							string content = all.substr(0, start) + keyword + all.substr(end);
							title t = (title) {content, keyword, start, count};
							titles.push_back(t);
						}
					}
				}
				
				count++;
			}
		}	
	}

	// 按指定规则排序。
	sort(titles.begin(), titles.end(), cmp);
	
	for (int i = 0; i < titles.size(); i++)
		cout << titles[i].content << endl;

	return 0;
}
