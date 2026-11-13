[UVa 289 A Very Nasty Text Formatter](https://blog.csdn.net/metaphysis/article/details/161361745)

## 题目分析

本题要求实现一个**文本段落格式化器**，核心功能是将给定段落按照指定的行宽进行两端对齐输出。输入由多个段落组成，每个段落以一个整数 $n$（$3 < n < 10003$）开头，表示该段落每一行（最后一行除外）的长度应为 $n$ 个字符（换行符不计入）。

格式化规则如下：

1. **两端对齐**：通过单词间插入额外空格实现。多余空格应尽可能均匀分布在单词之间，若无法完全均匀，则左侧的空格比右侧的更长。

2. **连字符规则**：当某行无法容纳至少一个完整单词时，允许在单词中间进行断词（即使用连字符 `-`）。应尽可能减少断词次数。但若无论如何都无法使该行达到指定长度，则采用左对齐输出。

3. **最后一行的处理**：每个段落的最后一行不需要进行两端对齐，单词之间只需保持单个空格即可。

输入遵循给定的 EBNF 文法，每个段落以换行符结束，单词由字母组成，可带有指定的标点标记（`..`、`,`、`'`、`"`）。单词长度不超过 $1000$ 个字符。

## 解题思路

本题的核心挑战在于**动态地确定每一行应放置哪些单词**，并在必要时进行断词处理。参考通过的代码，其采用的策略可以概括为**贪心逐行处理**：

### 1. 数据结构与输入解析

代码使用 `list<string>`（或 `vector<string>`）存储当前段落的所有单词。输入的一行中，第一个数字是行宽 $n$，后续的字符串是该段落的单词序列。

### 2. 核心处理函数 `process()`

该函数采用递归方式逐行处理单词列表 `words`，直到所有单词都被输出。

#### 步骤一：贪心收集一行中的单词

每次处理时，从单词列表头部开始，尝试将单词加入当前行。判断条件是：

$$
\text{当前行已有字符总长度} + \text{已有单词数} + \text{下一个单词长度} \le n
$$

这里加 `已有单词数` 是因为单词之间至少需要一个空格。如果满足条件，则将该单词移入缓冲区 `buffer`。

#### 步骤二：根据缓冲区情况分三类处理

##### 情况 $A$：缓冲区为空（`buffer.size() == 0`）

这意味着当前行的剩余空间连一个完整单词都放不下。此时必须进行断词：

- 从当前单词的前 $n-1$ 个字符后添加连字符 `-` 并输出。
- 将该单词的剩余部分（从第 $n-1$ 个字符开始）放回单词列表头部，供下一行处理。

##### 情况 $B$：缓冲区只有一个单词（`buffer.size() == 1`）

此时需要判断是否可以从下一个单词中“借”一部分来凑满一行，以减少断词次数：

- 如果存在下一个单词，且 `当前单词长度 + 3 <= n`（$3$ 对应一个空格、一个连字符和一个字符的最小需求），则从下一个单词中截取适当长度的前缀，与当前单词拼接后加上连字符输出。
- 截取长度 `cut = n - 当前单词长度 - 2`（$2$ 对应空格和连字符）。
- 否则，直接输出当前单词（左对齐，不加额外空格）。

##### 情况 $C$：缓冲区有两个及以上单词

此时可以进行两端对齐格式化：

- 计算需要插入的总空格数：`space = n - length`，其中 `length` 是缓冲区中所有单词的长度之和。
- 将 `space` 个空格从左到右依次分配给相邻单词之间的间隙（共 `buffer.size() - 1` 个间隙）。由于空格是逐个分配，左侧间隙会优先获得多余空格，满足“左侧空格更长”的要求。
- 如果当前行已经是段落的最后一行（即 `words` 为空），则不再插入额外空格，只在单词之间保留一个空格。

#### 步骤三：递归处理剩余单词

输出当前行后，若 `words` 非空，则递归调用 `process()` 处理剩余单词。

### 3. 算法复杂度

每个单词最多被断词一次，每行的处理时间为 $O(\text{该行单词数})$，总体时间复杂度为 $O(\text{总字符数})$，能够满足题目要求。

## 关键细节说明

1. **空格分配的均匀性**：通过 `while (space > 0)` 循环逐个给每个间隙增加一个空格，保证了左侧间隙优先获得多余空格。

2. **断词的最小化**：只有在缓冲区为空（无法容纳任何完整单词）或缓冲区只有一个单词且可以借词时才进行断词，其他情况尽量完整放置单词。

3. **最后一行特殊处理**：当 `words.empty()` 时，不再进行两端对齐，仅在单词间输出单个空格。

## 代码实现

```cpp
// A Very Nasty Text Formatter
// UVa ID: 289
// Verdict: Accepted
// Submission Date: 2016-06-07
// UVa Run Time: 0.080s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

list <string> words;  // 存储当前段落的单词列表
int n;                // 当前段落每行的目标长度

void process()
{
    vector<string> buffer;  // 存储当前行要放置的单词
    
    int length = 0;  // 当前行所有单词的字符总长度（不含空格）
    // 贪心收集能够放入当前行的单词
    while (!words.empty())
    {
        // 判断条件：当前总长度 + 单词间空格数 + 下一个单词长度 <= n
        if (length + buffer.size() + words.front().length() <= n)
        {
            length += words.front().length();
            buffer.push_back(words.front());
            words.erase(words.begin());
        }
        else
            break;
    }
    
    // 情况 1：缓冲区为空，必须断词
    if (buffer.size() == 0)
    {
        int cut = n - 1;  // 连字符占 1 个位置，所以截取 n-1 个字符
        cout << words.front().substr(0, cut) << "-" << endl;
        // 剩余部分放回原处继续处理
        words.front() = words.front().substr(cut);
    }
    // 情况 2：缓冲区只有一个单词
    else if (buffer.size() == 1)
    {
        // 尝试从下一个单词借词以减少断词次数
        if (!words.empty() && (buffer.front().length() + 3 <= n))
        {
            string next_word = words.front();
            int cut = n - buffer.front().length() - 2;  // 减 2 表示空格和连字符
            cout << buffer.front() << " " << next_word.substr(0, cut);
            cout << "-" << endl;
            // 剩余部分放回
            words.front() = next_word.substr(cut);
        }
        else
            cout << buffer.front() << endl;  // 左对齐输出
    }
    // 情况 3：缓冲区有两个及以上单词，进行两端对齐
    else
    {
        // 如果不是段落的最后一行，需要插入额外空格
        if (!words.empty())
        {
            int space = n - length;  // 需要分配的总空格数
            // 从左到右逐个分配空格，确保左侧间隙优先得到更多空格
            while (space > 0)
            {
                for (int i = 0; i < buffer.size() - 1 && space > 0; i++)
                {
                    buffer[i] += ' ';
                    space--;
                }
            }
        }
        else  // 最后一行，只保留一个空格
        {
            for (int i = 0; i < buffer.size() - 1; i++)
                buffer[i] += ' ';
        }
        
        // 输出当前行
        for (int i = 0; i < buffer.size(); i++)
            cout << buffer[i];
        cout << endl;
    }
    
    // 递归处理剩余单词
    if (words.size())
        process();
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);  // 加速输入输出
    
    string line;
    while (getline(cin, line))
    {
        words.clear();
        string word;
        istringstream iss(line);
        // 解析当前行的所有单词
        while (iss >> word)
            words.push_back(word);
            
        // 第一个数字是行宽 n
        n = stoi(words.front());
        words.erase(words.begin());
        
        // 处理当前段落
        process();
    }
    
    return 0;
}
```
