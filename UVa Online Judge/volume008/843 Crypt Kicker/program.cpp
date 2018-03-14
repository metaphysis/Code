// Crypt Kicker （解密）
// PC/UVa IDs: 110204/843, Popularity: B, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-05-23
// UVa Run Time: 0.536s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
bool finished = false;	// 提前退出递归的标志。
	
// 将每行输入拆分为不重复的单词。
bool parse2word(string line, vector < string > &word)
{
	istringstream iss(line);
	string w;
	bool found;
	
	while (iss >> w)
	{
		found = false;
		for (int i = 0; i < word.size(); i++)
			if (w == word[i])
				found = true;
		if (!found)
			word.push_back(w);
	}
	
	return word.size() > 0;
}
	
bool cmp(char a, char b)
{
	return a < b;
}
	
// 检查是否有两个密文字母映射到同一明文字母。
bool conflicts(string cipher)
{
	// 先予以排序，若有相同字母，则排序后肯定相邻。
	sort(&cipher[0], &cipher[0] + cipher.length(), cmp);
	
	for (int i = 0; i < cipher.length() - 1; i++)
		if (cipher[i] != '*' && cipher[i + 1] != '*' && 
					cipher[i] == cipher[i + 1])
			return true;
	
	return false;
}
	
// 根据当前密码 cipher，尝试匹配单词 d 和 w。
bool match(string d, string w, string &cipher)
{
	// 保存当前密码以便不能匹配时恢复。
	string tmp = cipher;
	
	// 单词长度不同，肯定无法匹配。
	if (d.length() != w.length())
		return false;
	
	// 根据明文单词d和密文单词 w 逐个字符进行匹配。	
	for (int i = 0; i < w.length(); i++)
	{	
		// 当密文字符 w[i] 尚无对应明文字符匹配时，将密文字符 w[i] 和明文字符 d[i] 匹配。
		if (cipher[w[i] - 'a'] == '*')
			cipher[w[i] - 'a'] = d[i];
		else
		{
			// 密文字符 w[i] 已有明文字符匹配，则检测当前的明文字符 d[i] 是否
			// 与密码中的相同，因为不能两个密文字符映射同一明文字符，故当两者不同
			// 时返回 false。
			if (cipher[w[i] - 'a'] != d[i])
			{
				cipher = tmp;
				return false;
			}
		}
	}
	
	if (conflicts(cipher))
	{
		cipher = tmp;
		return false;
	}
	
	return true;
}
	
// 根据获取的密码输出。
void output(string line, string cipher)
{
	for (int i = 0; i < line.length(); i++)
		if (line[i] == ' ')
			cout << ' ';
		else
			cout << cipher[line[i] - 'a'];
	cout << endl;
}
	
// 解密。
void decipher(vector<string> &dict, vector<string> &word, int start, string &cipher)
{
	// 保存当前密码，以便不能匹配时恢复。
	string tmp = cipher;
	
	// 检测是否已经匹配了所有单词。
	if (start == word.size())
	{
		// 检测密码是否存在冲突。
		finished = !conflicts(cipher);
		return;
	}
	
	// 从序号为start的单词开始匹配。
	for (int i = 0; i < dict.size(); i++)
		// 如果能匹配成功单词 word[start]，则匹配单词 word[start + 1]。
		if (match(dict[i], word[start], cipher))
		{
			// 递归向前匹配。
			decipher(dict, word, start + 1, cipher);
			
			// 根据标志决定是否提前结束递归。
			// 若未匹配到最后一个单词，恢复密码为之前保存的值。
			if (finished)
				return;
			else
				cipher = tmp;
		}
}
	
int main(int argc, char *argv[])
{
	string line;
	int count;
	vector < string > dict;
	map < string, int > exist;
	map < string, int >::iterator it;
	vector < string > word;
	
	cin >> count;
	cin.ignore();
	
	// 读入单词字典，注意可能有重复的单词存在。使用 map 来提高查找性能。
	for (int i = 0; i < count; i++)
	{
		getline(cin, line);
		it = exist.find(line);
		if (it == exist.end())
		{
			dict.push_back(line);
			exist.insert(make_pair< string, int >(line, dict.size() - 1));
		}
	}
	
	// 读入密文，对每一行进行解码。
	while (getline(cin, line))
	{
		if (line.length() == 0)
		{
			cout << endl;
			continue;
		}
		
		word.clear();
		parse2word(line, word);
		
		finished = false;
		string cipher(26, '*');
	
		if (!(word.size() > dict.size()))
			decipher(dict, word, 0, cipher);
		
		output(line, cipher);
	}
	
	return 0;
}
