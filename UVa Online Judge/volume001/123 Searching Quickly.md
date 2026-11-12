[UVa 123 Searching Quickly](https://blog.csdn.net/metaphysis/article/details/156709396)

## 一、问题分析

本题要求实现一个 **$\texttt{KWIC（Key Word In Context）}$索引** 生成程序。给定一个**忽略词列表**和一个**标题列表**，程序需要为每个标题中的每个关键词（即不在忽略词列表中的词）生成一条索引记录，并将所有索引按**关键词的字典序**排序后输出。

在输出时，关键词需要转换为**全大写**，标题中其余词则转为**全小写**。若同一关键词在多条索引中出现，则按这些标题在输入中的原始顺序排列；若同一标题中有多个相同关键词，则按它们在标题中出现的从左到右的顺序依次输出。

**关键限制条件**：
- 忽略词数量 $≤ 50$
- 标题数量 $≤ 200$
- 总字符数（忽略词 $+$ 标题） $≤ 10000$
- 标题中单词数 $≤ 15$
- 输入仅包含字母和空格

---

## 二、解题思路

### 1. 数据读取与存储
- 先读取忽略词，直到遇到分隔符 `::` 。
- 将忽略词存入一个 `set<string>` 中以便快速查找，注意**忽略词可能重复给出**，需去重。
- 然后读取所有标题，对每个标题进行处理。

### 2. 标题处理
- 将标题转换为全小写版本，便于后续处理和比较。
- 遍历标题中的每个单词：
  - 判断其是否在忽略词集合中。
  - 若不是忽略词，则它是一个关键词，需要生成一条索引记录。
- 生成索引时：
  - 关键词用全大写替换原单词。
  - 记录该关键词在标题中的起始位置（用于同一标题内多个相同关键词的排序）。
  - 记录该标题在输入中的顺序（用于同关键词下不同标题的排序）。
- 将生成的索引存入一个结构体数组中。

### 3. 排序规则
需要自定义比较函数，按以下优先级排序：
1. **关键词字典序**（升序）
2. 若关键词相同，则按**标题在输入中的出现顺序**排序
3. 若同一标题中出现多个相同关键词，则按**关键词在标题中的从左到右顺序**排序

### 4. 输出
按排序后的顺序逐行输出索引内容即可。

---

## 三、算法复杂度分析
- 设标题数为 $n$，每个标题单词数 ≤ $15$，则总关键词数 $≤ 15n$。
- 排序复杂度为 $O(m \log m)$，其中 $m$ 为总关键词数，最坏情况 $m ≈ 3000$，完全可行。
- 查找忽略词使用 `set`，每次查找 $O(\log k)$，$k ≤ 50$，非常快。

---

## 四、代码实现

```cpp
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

struct title {
	string content;
	string keyword;
	int indexKeyword;
	int indexInput;
};

string toLower(string s) {
	string r;
	for (int i = 0; i < s.length(); i++)
		r += (s[i] >= 'A' && s[i] <= 'Z' ? (s[i] + 32) : s[i]);
	return r;
}

string toUpper(string s) {
	string r;
	for (int i = 0; i < s.length(); i++)
		r += (s[i] >= 'a' && s[i] <= 'z' ? (s[i] - 32) : s[i]);
	return r;
}

bool cmp(title a, title b) {
	if (a.keyword == b.keyword) 	{
		if (toLower(a.content) == toLower(b.content)) return a.indexKeyword < b.indexKeyword;
		else return a.indexInput < b.indexInput;
	}
	return a.keyword < b.keyword;
}

int main (int argc, char const* argv[]) {
	set<string> ignore;
	vector<title> titles;
	string line;
	while (getline(cin, line)) {
		if (line != "::") {
			// 可能会给出重复的关键词，需要消除。
			if (ignore.find(line) == ignore.end()) ignore.insert(line);
		} else {
			int count = 0;
			while (getline(cin, line)) {
				string all = toLower(line);
				int i = 0;
				while (i < line.length()) {
					if (line[i] == ' ') i++;
					else {
						// 将句子中出现的单词逐个分离出来。
						int start = i;
						string tmp;
						while (i < line.length() && line[i] != ' ') {
							tmp += line[i];
							i++;
						}
						int end = i;
						// 若不是需要忽略的关键词，则生成一个标题。
						tmp = toLower(tmp);
						if (ignore.find(tmp) == ignore.end()) {
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
	for (int i = 0; i < titles.size(); i++) cout << titles[i].content << endl;
	return 0;
}
```
