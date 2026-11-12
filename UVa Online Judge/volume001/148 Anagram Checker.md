[UVa 148 Anagram Checker](https://blog.csdn.net/metaphysis/article/details/157510235)

## 题目分析

本题要求编写一个程序，从给定的字典中找出所有能够由指定短语中的字母重组而成的单词组合。输入分为两部分：首先是字典部分（每行一个单词，按字母顺序排序），然后是需要检查的短语列表（每行一个短语）。两个部分均以单独一行的 `#` 结束。

字典最多包含 $2000$ 个单词，每个单词或短语的长度不超过 $20$ 个字符。所有输入均为大写字母，且不限于英语单词。

输出要求：对于每个短语，输出所有可能的字典单词组合（按字母顺序排列），这些组合中的单词全部来自字典，且恰好用尽短语中的所有字母（忽略空格），且不能与原短语完全相同（即不能只是原单词的顺序不同）。如果没有找到任何组合，则不输出任何内容（包括空行）。

## 解题思路

这个问题本质上是一个**搜索与剪枝**问题。由于字典和短语的规模不大（$2000$ 个单词，每个短语最多 $20$ 个字母），我们可以使用**回溯法（$\texttt{backtracking}$）** 结合**字母计数法**来高效求解。

### 核心思路

1. **字母计数表示**  
   每个单词和短语都可以用一个长度为 $26$ 的数组表示，记录每个字母出现的次数。这种表示方式便于快速判断单词是否可由给定字母组成，以及是否已用尽所有字母。

2. **预处理字典**  
   读取字典时，为每个单词存储其原始字符串和对应的字母计数数组。

3. **处理每个短语**  
   - 计算短语的字母计数（忽略空格）作为目标数组 `goalCount`。
   - 将原短语按空格分割成单词列表 `single`，用于后续排除与原短语完全相同的组合。
   - 使用回溯法从字典中选取单词组合，使得组合的字母计数等于 `goalCount`。
   - 在回溯过程中，利用字母计数进行剪枝：如果当前选取的单词会导致某个字母的数量超过目标值，则跳过该单词。

4. **回溯搜索**  
   - 状态：当前已选取的单词列表、当前字母计数数组 `currentCount`。
   - 终止条件：已选取单词的总长度等于短语字母总数（即所有字母已用尽）。
   - 剪枝条件：
     - 单词长度超过剩余可用字母数。
     - 单词的某个字母数量加上当前计数超过目标值。
   - 去重：确保输出组合的单词按字母顺序排列，并排除与原短语单词列表完全相同（只是顺序不同）的组合。

5. **输出格式**  
   输出时，先输出原短语，后跟 `=`，再依次输出按字母顺序排序的单词组合。

### 算法复杂度分析

- 字典大小：$M \leq 2000$
- 短语字母数：$L \leq 20$
- 回溯的深度取决于单词长度，但剪枝能显著减少搜索空间。
- 最坏情况下搜索空间是指数级的，但实际由于字母限制和剪枝，运行效率较高。

### 实现细节

- 使用结构体 `item` 存储单词及其字母计数。
- 使用全局数组 `used` 标记字典单词是否已被使用。
- 回溯函数 `backtrack` 从起始索引开始，避免重复组合。
- 输出前对单词组合按字母顺序排序，并比较与原短语单词列表是否相同。

---

## 代码实现

```cpp
// Anagram Checker
// UVa ID: 148
// Verdict: Accepted
// Submission Date: 2016-01-22
// UVa Run Time: 0.059s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct item {
    string word;
    int count[26];
};

item words[2001];
int goalCount[26], currentCount[26];
vector<string> single;
bool used[2001];
int wordGet[2001], indexGet, total;
string targetLine;

void isGood() {
    bool good = true;
    for (int i = 0; i < 26; i++)
        if (currentCount[i] != goalCount[i]) {
            good = false;
            break;
        }
    if (!good) return;
    if (indexGet == single.size()) {
        vector<string> t1(single), t2;
        for (int i = 0; i < indexGet; i++)
            t2.push_back(words[wordGet[i]].word);
        sort(t1.begin(), t1.end());
        sort(t2.begin(), t2.end());
        bool good = false;
        for (int i = 0; i < t1.size(); i++)
            if (t1[i] != t2[i]) {
                good = true;
                break;
            }
        if (!good) return;
    }
    cout << targetLine << " =";
    for (int i = 0; i < indexGet; i++) cout << " " << words[wordGet[i]].word;
    cout << endl;
}

void backtrack(int start, int length, int target) {
    if (length == target) {
        isGood();
        return;
    }
    for (int i = start; i < total; i++) {
        if (used[i]) continue;
        if ((length + words[i].word.length()) > target) continue;
        bool good = true;
        for (int j = 0; j < 26; j++)
            if ((words[i].count[j] + currentCount[j]) > goalCount[j]) {
                good = false;
                break;
            }
        if (!good) continue;
        wordGet[indexGet++] = i;
        used[i] = true;
        for (int j = 0; j < 26; j++) currentCount[j] += words[i].count[j];
        backtrack(i + 1, length + words[i].word.length(), target);
        for (int j = 0; j < 26; j++) currentCount[j] -= words[i].count[j];
        used[i] = false;
        indexGet--;
    }
}

int main() {
    string line;
    total = 0;
    while (getline(cin, line), line != "#") {
        item aItem;
        aItem.word = line;
        memset(aItem.count, 0, sizeof(aItem.count));
        for (int i = 0; i < line.length(); i++) aItem.count[line[i] - 'A']++;
        words[total++] = aItem;
    }
    while (getline(cin, line), line != "#") {
        int alphaCount = 0;
        targetLine.assign(line);
        memset(goalCount, 0, sizeof(goalCount));
        for (int i = 0; i < line.length(); i++) 
            if (isalpha(line[i])) {
                goalCount[line[i] - 'A']++;
                alphaCount++;
            }
   
        single.clear();
        istringstream iss(line);
        string word;
        while (iss >> word) single.push_back(word);
        memset(currentCount, 0, sizeof(currentCount));
        memset(used, 0 , sizeof(used));
        indexGet = 0;
        backtrack(0, 0, alphaCount);
    }
	return 0;
}
```

---

## 总结

本题通过**字母计数法**和**回溯剪枝**高效解决了多单词字母重组问题。关键在于：
- 使用计数数组代替字符串直接比较，提升效率。
- 在回溯过程中尽早剪枝，减少无效搜索。
- 输出时注意排序和去重，符合题目要求。
