// Fmt （Fmt 程序）
// PC/UVa IDs: 110308/848, Popularity: C, Success rate: low Level: 2
// Verdict: Accepted
// Submission Date: 2011-05-22
// UVa Run Time: 0.008s
//
// 版权所有（C）2011，邱秋。metaphysis # yeah dot net
	
#include <bits/stdc++.h>

using namespace std;
	
#define WIDTH 72	// 一行最大宽度
	
string buffer;	// 缓冲区。
	
// 判断某行是否是空行。
bool empty_line(string & line)
{
	return line.length() == 0;
}
	
// 判断该行是否是新行。
bool new_line(string & line)
{
	if (empty_line(line))
		return false;
	return line[0] == ' ';
}
	
// 移除行末尾的空格。
void trim_line(string & line)
{
	for (string::iterator it = line.end() - 1; it >= line.begin(); it--)
		if (*it == ' ')
			line.erase(it);
		else
			break;
}
	
// 处理缓冲区的内容。
void process_buffer()
{
	// 当缓存区有内容时输出。
	if (buffer.length() > 0)
	{
		if (buffer.length() <= WIDTH)
		{
			cout << buffer << endl;
			buffer.clear();
			return;
		}
	
		string line, word;
		string::iterator it = buffer.begin();
		string spaces;
	
		// 首先读入该行的前导空格。
		for (; it != buffer.end() && *it == ' '; spaces.append(1, ' '), it++)
			;
	
		// 将前导空格附加到输出行。
		line.append(spaces);
		spaces.clear();
	
		// 读取非空格字符直到遇到空格。
		for (; it != buffer.end() && *it != ' '; line.append(1, *it), it++)
			;
	
		// 判断是否需要输出该行。
		if (line.length() >= WIDTH)
		{
			cout << line << endl;
			line.clear();
		}
	
		// 输出行字符数小于或等于宽度 WIDTH，继续读取字符，直到缓冲区结束。
		while (line.length() <= WIDTH && it != buffer.end())
		{
			// 判断是否需要读入一个新的单词。
			if (word.length() == 0)
			{
				// 读入前导空格。
				for (; it != buffer.end() && *it == ' '; spaces.append(1, ' '), it++)
					;
				// 读入单词。
				for (; it != buffer.end() && *it != ' '; word.append(1, *it), it++)
					;
			}
	
			// 判断单词长度是否大于 WIDTH，决定是否占一行输出。
			if (word.length() >= WIDTH)
			{
				cout << line << endl << word << endl;
				line.clear();
				word.clear();
				spaces.clear();
			}
			else
			{
				// 若当前输出行为空，则需将前导空格去掉。
				if (line.length() == 0)
					spaces.clear();
	
				// 判断当前行加上空格和单词的长度是否超过指定长度，若超过则直接输出当前行
				// 空格清空，单词留到下一行。若未超过则将其合成一行内容。由于两个单词之间可能
				// 是多个空格，所以采用了单独读取空格的方式。
				if ((line.length() + spaces.length() + word.length()) <= WIDTH)
				{
					line.append(spaces).append(word);
					word.clear();
					spaces.clear();
				}
				else
				{
					cout << line << endl;
					line.clear();
					spaces.clear();
				}
			}
		}
	
		// 判断是否有内容仍需要输出。
		if (line.length() > 0)
			cout << line << endl;
		if (word.length() > 0)
			cout << word << endl;
	
		buffer.clear();
	}
}

int main(int ac, char *av[])
{
	string line;
	
	while (getline(cin, line))
	{
		// 截去行末尾的空格。
		trim_line(line);
	
		// 截去行末尾的空格后，空行和只有空格的空白行将都变成空行，有利于判断。
		// 若遇到空行或新行，表示要将前面缓冲区的内容处理输出。
		if (empty_line(line) || new_line(line))
		{
			process_buffer();
			
			// 换行。
			if (empty_line(line))
				cout << endl;
			else
				buffer.append(line);
		}
		else
		{
			// 若缓冲区内容为空，直接将新的一行附加到缓冲区，否则需要在缓冲区和
			// 新一行内容间附加一个空格。
			if (buffer.length() == 0)
				buffer.append(line);
			else
				buffer.append(1, ' ').append(line);
		}
	}
	
	// 处理缓冲区内剩余的内容。
	process_buffer();
	
	return 0;
}
