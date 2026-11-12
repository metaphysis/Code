[UVa 169 Xenosemantics](https://blog.csdn.net/metaphysis/article/details/158808301)

### 题目分析

本题是一道**字符串处理**与**逻辑判定**相结合的难题。题目设定了一个外星语言的消息格式，要求从一段混合字符中提取出符合特定规则的“真词”。核心难点在于理解并实现这些规则，然后按特定顺序输出结果。

**消息格式规则**：
1. 消息是比特流，被分为 $8$ 位一组，但有效部分只包含小写字母。
2. 单词由分隔字母界定，分隔符在消息中可变，但同一对分隔符界定的单词内部不能包含该分隔符。
3. 消息首尾被视为通配符（可与任何字母匹配）。
4. 一个“真词”必须满足：
   - 长度在 $2$ 到 $250$ 之间；
   - 在消息中至少出现两次（字母顺序可以重排）；
   - 与另一个真词在位置上重叠。

**输出要求**：
- 按单词第一次出现的顺序输出，但如果两个单词的第一次出现有重叠，则先结束的单词先输出。
- 每个消息输出后以 `*` 结束。

**数据规模**：消息长度不超过 $1000$ 个字母。

### 解题思路

整个解题过程可以分为以下几个步骤：

#### 1. 数据预处理

输入消息可能跨行，行末的 `-` 表示下一行继续。我们需要将所有小写字母按顺序收集起来，构成一个连续的字符串 `block`，并记录每个字母的原始索引（用于重叠判断）。

```cpp
for (int i = 0; i < line.length(); i++)
    if ('a' <= line[i] && line[i] <= 'z') {
        block += line[i];
        letters.push_back((letter){line[i], block.length() - 1});
    }
```

#### 2. 候选单词提取

根据规则，单词由相同字母（作为分隔符）界定。我们扫描所有相同字母对 $(letters[i], letters[i+1])$，它们之间的子串（长度 $2$–$250$）就是候选单词。

此外，由于消息首尾被视为通配符，还需要考虑从开头到第一个字符之间的部分，以及从最后一个字符到末尾的部分。这些部分只要不包含与之相邻的字符（即分隔符）即可。

```cpp
// 相同字母之间的子串
for (int i = 0; i < letters.size() - 1; i++)
    if (letters[i].character == letters[i + 1].character) {
        int length = letters[i + 1].index - letters[i].index - 1;
        if (length >= 2 && length <= 250)
            words.push_back((word){block.substr(letters[i].index + 1, length), letters[i].index + 1});
    }

// 开头到第一个字符之间的子串
for (int i = 2; i < block.length() && i <= 260; i++) {
    string falseWord = block.substr(0, i);
    if (falseWord.find(block[i]) == falseWord.npos)
        words.push_back((word){falseWord, 0});
}

// 最后一个字符到末尾的子串
for (int i = 2; i < block.length() && i <= 260; i++) {
    int index = block.length() - i;
    string falseWord = block.substr(index, i);
    if (falseWord.find(block[index - 1]) == falseWord.npos)
        words.push_back((word){falseWord, index});
}
```

#### 3. 候选单词分组

单词是否相同取决于其字母组成（顺序可变）。因此我们将每个单词的字母排序后作为键，相同键的单词放入同一组。这样每组就是一个“可能相同的单词”集合。

```cpp
candidates.clear();
for (int i = 0; i < words.size(); i++) {
    string temp = words[i].text;
    sort(temp.begin(), temp.end());
    candidates[temp].push_back(words[i]);
}
```

#### 4. 真词判定

一个组成为真词的条件：
- 组内至少有两个不同的出现位置；
- 该组中至少有一个单词与另一个组的某个单词重叠。

我们用一个布尔数组标记哪些组是真词。遍历所有组，如果某组还未标记，则检查该组内每个单词是否与其它组的任何单词重叠。一旦发现重叠，标记这两个组均为真词。

```cpp
for (int i = 0; i < trueWords.size(); i++) {
    if (isTrueWord[i]) continue;
    for (int j = 0; j < trueWords[i].size(); j++) {
        bool found = false;
        for (int m = 0; m < trueWords.size(); m++) {
            if (m == i) continue;
            for (int k = 0; k < trueWords[m].size(); k++) {
                if (isOverlapped(trueWords[i][j], trueWords[m][k])) {
                    isTrueWord[i] = true;
                    isTrueWord[m] = true;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (found) break;
    }
}
```

#### 5. 重叠判断

两个单词重叠的条件是：它们在原字符串中的区间有交集。我们通过比较起始和结束位置来判断。

```cpp
bool isOverlapped(word x, word y) {
    int xend = x.start + x.text.length() - 1;
    int yend = y.start + y.text.length() - 1;
    return (x.start >= y.start && x.start <= yend) ||
           (xend >= y.start && xend <= yend) ||
           (y.start >= x.start && y.start <= xend) ||
           (yend >= x.start && yend <= xend);
}
```

#### 6. 真词排序与输出

我们需要按第一次出现的位置排序，但如果两个单词的第一次出现重叠，则先结束的优先。这个排序规则通过自定义比较函数实现：

```cpp
bool cmpWord(word x, word y) {
    if (isOverlapped(x, y)) {
        int xend = x.start + x.text.length();
        int yend = y.start + y.text.length();
        if (xend != yend) return xend < yend;
        else return x.start < y.start;
    } else {
        return x.start < y.start;
    }
}
```

最后，将每个真词组的第一个出现（即最早出现的位置）放入列表，排序后输出，并以 `*` 结束。

### 总结

本题的难点在于：
- 正确理解“单词由分隔符界定”的含义；
- 实现重叠判断与真词判定；
- 特殊排序规则的实现。

代码通过预处理、分组、重叠检测和排序等步骤，完整实现了题目要求。由于数据规模较小（$\leq 1000$），这种 $\texttt{O}(n^3)$ 的暴力方法在时间上是可行的。

### 完整代码

```cpp
// Xenosemantics
// UVa ID: 169
// Verdict: Accepted
// Submission Date: 2016-02-19
// UVa Run Time: 0.006s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct letter {
    char character;
    int index;
};

struct word {
    string text;
    int start;
};

bool operator<(letter x, letter y) {
    return x.character < y.character;
}

bool operator<(word x, word y) {
    if (x.start == y.start) return x.text.length() < y.text.length();
    else return x.start < y.start;
}

bool isOverlapped(word x, word y) {
    int xend = x.start + x.text.length() - 1;
    int yend = y.start + y.text.length() - 1;
    return x.start >= y.start && x.start <= yend ||
        xend >= y.start && xend <= yend ||
        y.start >= x.start && y.start <= xend ||
        yend >= x.start && yend <= xend;
}

bool cmpWord(word x, word y) {
    if (isOverlapped(x, y)) {
        int xend = x.start + x.text.length();
        int yend = y.start + y.text.length();
        if (xend != yend) return xend < yend;
        else return x.start < y.start;
    } else return x.start < y.start;
}

string block;
vector<letter> letters;
vector<word> words;
map<string, vector<word>> candidates;
vector<vector<word>> trueWords;

void findTrueWord() {
    if (block.length() <= 3) {
        cout << "*\n";
        return;
    }
    stable_sort(letters.begin(), letters.end());
    words.clear();
    for (int i = 0; i < letters.size() - 1; i++)
        if (letters[i].character == letters[i + 1].character) {
            int length = letters[i + 1].index - letters[i].index - 1;
            if (length < 2 || length > 250) continue;
            string something = block.substr(letters[i].index + 1, length);
            words.push_back((word){something, letters[i].index + 1});
        }

    for (int i = 2; i < block.length() && i <= 260; i++) {
        string falseWord = block.substr(0, i);
        if (falseWord.find(block[i]) != falseWord.npos) continue;
        words.push_back((word){falseWord, 0});
    }
    
    for (int i = 2; i < block.length() && i <= 260; i++) {
        int index = block.length() - i;
        string falseWord = block.substr(index, i);
        if (falseWord.find(block[index - 1]) != falseWord.npos) continue;
        words.push_back((word){falseWord, index});
    }
    sort(words.begin(), words.end());
    candidates.clear();
    for (int i = 0; i < words.size(); i++) {
        string temp = words[i].text;
        sort(temp.begin(), temp.end());
        if (candidates.count(temp) == 0) {
            vector < word > list;
            list.push_back(words[i]);
            candidates[temp] = list;
        } else candidates[temp].push_back(words[i]);
    }

    trueWords.clear();
    for (map<string, vector<word>>::iterator it = candidates.begin(); it != candidates.end(); it++)
        if ((*it).second.size() > 1)
            trueWords.push_back((*it).second);

    vector < bool > isTrueWord;
    for (int i = 0; i < trueWords.size(); i++)
        isTrueWord.push_back(false);

    for (int i = 0; i < trueWords.size(); i++) {
        if (isTrueWord[i]) continue;
        for (int j = 0; j < trueWords[i].size(); j++) {
            bool found = false;
            for (int m = 0; m < trueWords.size(); m++) {
                if (m == i) continue;
                found = false;
                for (int k = 0; k < trueWords[m].size(); k++) {
                    if (isOverlapped(trueWords[i][j], trueWords[m][k])) {
                        isTrueWord[i] = true;
                        isTrueWord[m] = true;
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) break;
       }
    }

    words.clear();
    for (int i = 0; i < trueWords.size(); i++)
        if (isTrueWord[i])
            words.push_back(trueWords[i][0]);
    
    sort(words.begin(), words.end(), cmpWord);
    for (int i = 0; i < words.size(); i++)
        cout << words[i].text << "\n";
    cout << "*\n";
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    string line;
    bool ended = false;
    while (getline(cin, line), line != "#") {
        for (int i = 0; i < line.length(); i++)
            if ('a' <= line[i] && line[i] <= 'z') {
                block += line[i];
                letters.push_back((letter){line[i], (int)block.length() - 1});
            }

        ended = line[line.length() - 1] != '-';

        if (ended) {
            findTrueWord();
            letters.clear();
            block.clear();
            ended = false;
        }
    }
    
	return 0;
}
```
