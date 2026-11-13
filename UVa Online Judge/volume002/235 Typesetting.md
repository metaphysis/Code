[UVa 235 Typesetting](https://blog.csdn.net/metaphysis/article/details/161210988)

## 题目分析

本题是一个文字排版模拟问题。题目要求根据给定的字体宽度表，对输入的文本段落进行排版，使得每行尽可能多地放置单词，并按照指定格式输出每行的信息。

关键要点如下：

1. **字体宽度表**：输入首先给出 $N$ 个字符在 $6$ 种不同字体下的宽度（$10$ 点字体的宽度）。字符宽度与点大小呈线性关系，缩放时需要四舍五入（$.5$ 向上取整）。

2. **排版规则**：
   - 初始字体为字体 $1$，初始点大小为 $10$。
   - 特殊标记 `\*fN\*` 用于切换字体（$N$ 为 $1$ 到 $6$），`\*sN\*` 用于切换点大小（$N$ 为 $1$ 到 $99$）。
   - 单词之间至少有一个空格，空格宽度与当前字体和前一个单词的字体、点大小相同。
   - 每行尽可能多地放置单词，最后一个单词后面没有空格。
   - 如果单个单词超过行宽，则单独占一行，输出负的空格宽度（超出部分的长度）。

3. **输出格式**：对于每个段落，首先输出 `Paragraph X`，然后按行输出 `Line Y: first ... last (Z whitespace)`。其中 $Z$ 为行末剩余的空格宽度，如果单词超长则为负值。

## 解题思路

本题的模拟过程可以分为以下几个步骤：

### 1. 读取字体宽度表

使用一个二维数组 `font[110][10]` 存储字符宽度，`font[i][j]` 表示第 $i$ 个字符在字体 $j$ 下的宽度。同时使用 `map<char, int>` 将字符映射到其在表格中的索引。

需要注意：空格字符也需要记录宽度，输入中可能以空格开头表示空格的宽度数据。

### 2. 处理每个段落

对于每个段落：

- 首先读取 $L$（段落行数）和 $W$（排版行宽，单位为单位）。
- 将 $L$ 行文本拼接成一个字符串，单词之间用空格分隔，以便使用字符串流进行解析。

### 3. 核心排版逻辑

在 `process` 函数中实现：

- **状态变量**：
  - `size`：当前字体编号（$1$ 到 $6$）
  - `point`：当前点大小
  - `currentWidth`：当前行已使用的宽度
  - `spaceWidth`：当前空格宽度（根据当前字体和点大小计算）
  - `firstWord`、`lastWord`：当前行的第一个和最后一个单词

- **单词宽度计算**：
  $$ wordWidth = \sum_{i=0}^{len-1} \left\lfloor \frac{font[idx[word[i]]][size] \times point + 5}{10} \right\rfloor $$

  使用整数运算 `(width * point + 5) / 10` 实现四舍五入。

- **断行判断**：
  - 如果当前行已有单词，且 `currentWidth + spaceWidth + wordWidth >= W`，或者单词本身宽度 `wordWidth >= W`，则需要换行。
  - 换行时输出当前行的信息，并重置 `currentWidth` 和 `firstWord`。

- **单词超长处理**：
  - 如果 `wordWidth >= W`，单独输出一行，空格宽度为 `W - wordWidth`（可能为负）。

- **行尾处理**：
  - 所有单词处理完毕后，如果 `currentWidth > 0`，输出最后一行。

### 4. 精度注意事项

题目特别强调使用整数运算进行四舍五入，避免使用浮点 `round` 函数，否则会得到 `Wrong Answer`。

## 代码实现

```cpp
// Typesetting
// UVa ID: 235
// Verdict: Accepted
// Submission Date: 2025-10-06
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int font[110][10];          // 字体宽度表，font[i][j]表示第i个字符在字体j下的宽度
map<char, int> idx;         // 字符到表格索引的映射
int paragraph = 1;          // 段落计数器
int L, W;                   // L：段落行数，W：行宽

// 处理单个段落的排版
void process(string lines) {
    int printedLines = 1;           // 行计数器
    int size = 1, point = 10;       // 当前字体和点大小，初始为字体1、10点
    int currentWidth = 0, spaceWidth;   // 当前行已用宽度、空格宽度
    string firstWord, lastWord, word;   // 当前行的首单词、末单词、当前单词
    istringstream iss(lines);           // 字符串流，用于提取单词和标记
    cout << "Paragraph " << paragraph++ << '\n';
    
    while (iss >> word) {
        // 处理字体或点大小切换标记
        if (word[0] == '*') {
            if (word[1] == 'f') size = stoi(word.substr(2));   // 切换字体
            if (word[1] == 's') point = stoi(word.substr(2));  // 切换点大小
            continue;
        }
        
        // 计算当前单词的宽度
        int wordWidth = 0;
        for (int i = 0; i < word.length(); i++)
            // 使用整数运算实现四舍五入：加5再整除10
            wordWidth += (font[idx[word[i]]][size] * point + 5) / 10;
        
        // 判断是否需要换行
        if ((currentWidth && currentWidth + spaceWidth + wordWidth >= W) || wordWidth >= W) {
            // 输出当前行（如果非空）
            if (currentWidth) {
                cout << "Line " << printedLines++ << ": " << firstWord << " ... " << lastWord;
                cout << " (" << (W - currentWidth) << " whitespace)\n";
                currentWidth = 0;
            }
            // 处理单词超长的情况
            if (wordWidth >= W) {
                cout << "Line " << printedLines++ << ": " << word;
                if (wordWidth == W) cout << " ... " << word;
                cout << " (" << (W - wordWidth) << " whitespace)\n";
                wordWidth = 0;
            }
        }
        
        // 将当前单词添加到行中
        if (currentWidth) currentWidth += spaceWidth;
        else firstWord = word;
        if (wordWidth) {
            currentWidth += wordWidth;
            lastWord = word;
        }
        
        // 计算当前字体和点大小下的空格宽度
        spaceWidth = (font[idx[' ']][size] * point + 5) / 10;
    }
    
    // 处理最后一行
    if (currentWidth) {
        cout << "Line " << printedLines++ << ": " << firstWord << " ... " << lastWord;
        cout << " (" << (W - currentWidth) << " whitespace)\n";
    }
}

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    int n = stoi(line);                 // 读取字符表大小
    
    // 读取字体宽度表
    for (int i = 1; i <= n; i++) {
        getline(cin, line);
        istringstream iss(line);
        // 如果行以空格开头，说明是空格字符的宽度数据
        if (line.front() == ' ') idx.insert(make_pair(' ', i));
        else {
            char character;
            iss >> character;
            idx.insert(make_pair(character, i));
        }
        // 读取6种字体下的宽度
        for (int j = 1; j <= 6; j++) iss >> font[i][j];
    }
    
    // 处理每个段落
    while (getline(cin, line)) {
        istringstream iss(line);
        iss >> L >> W;
        if (L == 0) break;              // 空段落表示输入结束
        
        string allLines;                // 拼接段落的所有行
        for (int i = 1; i <= L; i++) {
            getline(cin, line);
            allLines += line + ' ';     // 添加空格分隔单词
        }
        process(allLines);
    }
    
    return 0;
}
```
