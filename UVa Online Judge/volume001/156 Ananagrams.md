[UVa 156 Ananagrams](https://blog.csdn.net/metaphysis/article/details/158609702)

## 题目分析

本题要求找出字典中那些无法通过字母重排得到其他单词的单词。这类单词被称为 `ananagrams`。

### 题目理解

题目首先介绍了字谜游戏中的常见概念：
- $\texttt{anagram}$（变位词）：由相同字母组成但顺序不同的单词，如 $\texttt{OPTS}$、$\texttt{SPOT}$、$\texttt{STOP}$、$\texttt{POTS}$ 和 $\texttt{POST}$。
- $\texttt{ananagram}$（非变位词）：无论怎样重新排列字母，都无法形成另一个单词，如 $\texttt{QUIZ}$。

题目强调，$\texttt{ananagram}$ 的定义依赖于所考虑的领域。例如：
- 在一般英语中，$\texttt{ATHENE}$ 可能被认为是非变位词。
- 但在化学领域，化学家会立刻想到 $\texttt{ETHANE}$。

本题要求在一个限定领域的词典中找出相对的非变位词。注意：
- 单个字母的单词天然是非变位词（无法重新排列）。
- 词典中最多包含 $1000$ 个单词。
- 输入中大小写字母被视为相同（`tIeD` 和 `EdiT` 互为变位词）。
- 输出要求按字典序（区分大小写）输出结果。

### 输入格式

输入由多行组成，每行不超过 $80$ 个字符，包含多个单词。单词由最多 $20$ 个大小写字母组成，不会跨行。单词之间由空格分隔。输入以单独一行的 `#` 结束。

### 输出格式

按字典序（区分大小写）输出所有相对的非变位词，每行一个单词。题目保证至少有一个这样的单词。

### 关键点分析

1. **变位词的判定**：两个单词互为变位词当且仅当它们包含的字母完全相同（忽略大小写和顺序）。因此，可以将每个单词转换为小写，然后对字母排序，得到的字符串作为该单词的“标准化表示”。

2. **非变位词的判定**：一个单词是非变位词，当且仅当它的标准化表示在词典中只出现一次。如果有多个单词的标准化表示相同，则它们都不是非变位词。

3. **大小写处理**：输入单词保留原始大小写，但变位词判断时需忽略大小写。输出时需按原始单词输出。

4. **排序要求**：输出需按字典序（区分大小写）排列。`C++` 中 $\texttt{std::string}$ 的默认比较操作就是字典序比较，且区分大小写（`ASCII` 码顺序）。

5. **输出顺序**：题目要求输出的是原始单词，而不是标准化后的形式。

## 解题思路

### 算法设计

解题思路非常直接：

1. **读取所有单词**：逐行读取输入，遇到 `#` 时停止。将每个单词存入 $\texttt{vector<string> allWords}$ 中，同时将其标准化后存入 $\texttt{multiset<string> lowerCase}$ 中。

2. **标准化处理**：
   - 将单词转换为小写：使用 $\texttt{transform}$ 函数配合 $\texttt{::tolower}$。
   - 对字母排序：使用 $\texttt{sort}$ 函数对字符串排序。

3. **统计出现次数**：使用 $\texttt{multiset}$ 可以方便地统计某个标准化单词的出现次数。$\texttt{multiset}$ 允许重复元素，并且支持 $\texttt{count}$ 操作。

4. **筛选非变位词**：遍历 $\texttt{allWords}$ 中的每个单词，对其标准化后，检查在 $\texttt{lowerCase}$ 中的出现次数。如果出现次数为 $1$，则说明该单词是非变位词，将其原始形式加入结果向量 $\texttt{ananagrams}$。

5. **排序输出**：对结果向量进行排序，然后逐行输出。

### 复杂度分析

- 时间复杂度：$O(n \cdot k \log k + n \log n)$，其中 $n$ 是单词数（最多 $1000$），$k$ 是单词长度（最多 $20$）。排序每个单词需要 $O(k \log k)$，对所有单词筛选需要 $O(n \cdot k \log k)$，最后对结果排序需要 $O(n \log n)$。总体在题目限制下非常高效。
- 空间复杂度：$O(n \cdot k)$，用于存储所有单词及其标准化形式。

### 数据结构选择

- $\texttt{vector<string> allWords}$：按输入顺序存储原始单词，便于后续遍历。
- $\texttt{multiset<string> lowerCase}$：存储所有标准化后的单词，利用其 $\texttt{count}$ 方法统计出现次数。也可以使用 $\texttt{map<string, int>}$ 来统计频率，但 $\texttt{multiset}$ 的实现更简洁。

### 注意事项

- 使用 $\texttt{transform}$ 时，需要包含 $\texttt{<algorithm>}$ 头文件。
- $\texttt{::tolower}$ 前面加 $\texttt{::}$ 是为了使用 C 标准库的 $\texttt{tolower}$ 函数，避免与 `C++` 中可能重载的版本冲突。
- 输出顺序区分大小写，而标准库的 $\texttt{sort}$ 默认按照 `ASCII` 码排序，恰好满足要求。

## 代码实现

```cpp
// Ananagrams
// UVa ID: 156
// Verdict: Accepted
// Submission Date: 2016-02-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    vector<string> allWords;
    multiset<string> lowerCase;
    string line;
    while (cin >> line, line != "#") {
        allWords.push_back(line);
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        sort(line.begin(), line.end());
        lowerCase.insert(line);
    }
    vector<string> ananagrams;
    for (int i = 0; i < allWords.size(); i++) {
        string word = allWords[i];
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        sort(word.begin(), word.end());
        if (lowerCase.count(word) == 1)
            ananagrams.push_back(allWords[i]);
    }
    sort(ananagrams.begin(), ananagrams.end());
    for (int i = 0; i < ananagrams.size(); i++) cout << ananagrams[i] << endl;
    return 0;
}
```

## 总结

本题的核心在于理解变位词的判定方法：将单词标准化（小写 + 排序）后进行比较。通过统计标准化单词的出现次数，可以轻松识别出非变位词。代码实现简洁明了，充分利用了 `STL` 容器和算法的优势。对于初学者来说，这是一个很好的练习字符串处理和 `STL` 使用的题目。
