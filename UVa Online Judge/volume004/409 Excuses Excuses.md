[UVa 409 Excuses Excuses](https://blog.csdn.net/metaphysis/article/details/161737160)

## 题目描述

题目要求在一组借口中找出包含关键词最多的“最差借口”。关键词匹配时不区分大小写，且关键词必须作为独立的单词出现，即关键词前后必须是行首、行尾、非字母字符或空格。如果同一个关键词在同一个借口中出现多次，每次出现都单独计数。如果多个借口并列包含最多关键词，则全部输出。

## 输入格式

输入包含多组数据。每组数据格式如下：
- 第一行包含两个整数 $K$ 和 $E$（$1 \le K \le 20$，$1 \le E \le 20$），分别表示关键词数量和借口数量。
- 接下来 $K$ 行，每行一个关键词，由小写字母组成，长度 $L$（$1 \le L \le 20$）。
- 接下来 $E$ 行，每行一个借口，长度不超过 $70$ 个字符，可包含大小写字母、数字、空格以及标点符号（逗号、句点、感叹号、问号等）。每个借口至少包含一个非空格字符。

## 输出格式

对于每组数据，首先输出一行 `Excuse Set #X`，其中 $X$ 从 $1$ 开始递增。接下来输出所有最差借口（即包含关键词次数最多的借口），每行一个，顺序任意。每组输出后跟一个空行。

## 样例

输入

```
5 3
dog
ate
homework
canary
died
My dog ate my homework.
Can you believe my dog died after eating my canary... AND MY HOMEWORK?
This excuse is so good that it contain 0 keywords.
6 5
superhighway
crazy
thermonuclear
bedroom
war
building
I am having a superhighway built in my bedroom.
I am actually crazy.
1234567890. . . . . . . . . . . . . . . . . . . . . 0987654321?????!!!!!
There was a thermonuclear war!
I ate my dog, my canary, and my homework ... note outdated keywords?
```

输出

```
Excuse Set #1
Can you believe my dog died after eating my canary... AND MY HOMEWORK?

Excuse Set #2
I am having a superhighway built in my bedroom.
There was a thermonuclear war!
```

## 题目分析

本题的核心是在每个借口中统计关键词出现的次数。关键词匹配需要满足以下条件：
- 不区分大小写（借口需转换为小写后匹配）。
- 关键词必须作为独立的单词出现，即前后不能有字母字符。具体来说，关键词的前一个字符（如果有）必须是行首、空格或非字母字符；后一个字符（如果有）必须是行尾、空格或非字母字符。
- 关键词可以重复出现，每次出现单独计数。

### 关键词存储

由于 $K \le 20$，关键词数量较少，可以直接使用 $\texttt{set<string>}$ 存储所有关键词（全部为小写）。匹配时只需检查从借口中提取的单词是否在集合中。

### 借口预处理

借口可能包含大写字母，因此需要先将整个借口转换为小写，以便与关键词进行匹配。转换后，原借口字符串需要保留用于输出，因此需要单独存储原始借口。

### 单词提取

遍历借口字符串的每个字符：
- 如果当前字符是字母，则开始提取一个连续的字母序列（即一个单词）。
- 提取完成后，检查该单词是否在关键词集合中，若在则计数器加 $1$。
- 如果当前字符不是字母，则跳过。

注意：数字和标点符号被视为单词的分隔符，不会成为单词的一部分。题目中借口可以包含数字，但关键词只由字母组成，因此数字不会匹配任何关键词。

### 统计与输出

对于每组数据：
- 计算每个借口中匹配的关键词数量，存入数组。
- 找出最大值 $\textit{maxFreq}$。
- 输出所有频率等于 $\textit{maxFreq}$ 的原始借口。
- 每组输出后打印一个空行。

### 复杂度分析

- 每组数据中，每个借口的长度为 $L \le 70$，单词提取复杂度 $O(L)$。
- 关键词查找使用 $\texttt{set}$，单次查找 $O(\log K)$。
- 总复杂度 $O(E \times L \times \log K)$，$E \le 20$，$L \le 70$，$K \le 20$，完全可接受。

## 代码实现

```cpp
// Excuses, Excuses!
// UVa ID: 409
// Verdict: Accepted
// Submission Date: 2016-07-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    string word, line;
    int K, E, cases = 0;
    while (cin >> K >> E)
    {
        cout << "Excuse Set #" << ++cases << '\n';
        
        set<string> keywords;
        vector<string> execuses;
        vector<int> frequencies;
        for (int i = 1; i <= K; i++)
        {
            cin >> word;
            keywords.insert(word);
        }
        
        cin.ignore(1024, '\n');
        for (int i = 1; i <= E; i++)
        {
            getline(cin, line);
            execuses.push_back(line);
            for (int i = 0; i < line.length(); i++)
                line[i] = tolower(line[i]);
            
            int index = 0, frequency = 0;
            while (index < line.length())
            {
                if (isalpha(line[index]))
                {
                    string block;
                    while (index < line.length() && isalpha(line[index]))
                    {
                        block += line[index];
                        index++;
                    }
                    if (keywords.find(block) != keywords.end())
                        frequency++;
                }
                else
                    index++;
            }
            
            frequencies.push_back(frequency);
        }
        
        int max_frequency = *max_element(frequencies.begin(), frequencies.end());
        for (int i = 0; i < frequencies.size(); i++)
            if (frequencies[i] == max_frequency)
                cout << execuses[i] << '\n';
                
        cout << '\n';
    }
    
    return 0;
}
```