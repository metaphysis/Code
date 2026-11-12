[UVa 171 Car Trialling](https://blog.csdn.net/metaphysis/article/details/160660062)

## 题目分析

本题要求判断一段比赛指令是否符合特定的语法规则。这些规则模拟了真实汽车导航比赛中的指令格式，指令中会包含各种“陷阱”来迷惑参赛者。

### 问题本质

这是一个上下文无关文法（$\texttt{Context-Free Grammar}$）的识别问题。题目使用 $\texttt{BNF}$（巴科斯范式）描述了指令的语法规则，我们需要实现一个解析器来判断输入字符串是否属于该文法定义的语言。

### 文法规则整理

根据题目描述，文法可以整理如下（为方便理解，使用更直观的表示）：

```
instruction        → navigational | time-keeping | navigational AND time-keeping
navigational       → directional | navigational AND THEN directional
directional        → how direction | how direction where
how                → GO | GO when | KEEP
direction          → RIGHT | LEFT
when               → FIRST | SECOND | THIRD
where              → AT sign
sign               → "signwords"
signwords          → s-word | signwords s-word
s-word             → letter | s-word letter
letter             → A..Z
time-keeping       → record | change
record             → RECORD TIME
change             → cas TO nnn KMH
cas                → CHANGE AVERAGE SPEED | CAS
nnn                → digit | nnn digit
digit              → 0..9
```

### 关键细节

1. **区分大小写**：关键字（如 `GO`、`KEEP`）是大小写敏感的，必须使用大写形式。
2. **空格处理**：
   - 项目之间至少有一个空格
   - 但引号（`"`）前、后以及句点（`.`）前没有空格
   - 输出时需要将多个连续空格压缩为单个空格
3. **引号内容**：`signwords` 中的空格在输入中实际存在，但会被特殊处理
4. **数字序列**：`nnn` 代表一个或多个数字的序列

## 解题思路

### 整体策略

本题采用**归约（$\texttt{Reduction}$）方法**：将输入字符串转换为词法单元（$\texttt{Token}$）序列，然后反复应用文法产生式进行归约，若能归约成单一的 `INSTRUCTION` 单元，则指令合法。

这种方法类似于 $\texttt{LR}$ 语法分析的归约过程，通过预定义的归约规则逐步将符号序列缩减。

### 步骤一：空格规整与引号处理

输入字符串中，引号内的空格需要特殊处理（因为引号内容应视为一个整体），而其他位置的多余空格需要压缩。

处理逻辑：
- 遍历字符串，用 `_` 替换引号之间的空格（临时标记）
- 使用 `istringstream` 分割单词时，连续空格会被自动忽略
- 最后在输出时，将引号间的 `_` 还原为空格

```cpp
// 将引号内的空格替换为 '_'
bool quoteStart = false;
for (int i = 0; i < line.length(); i++) {
    if (line[i] == '\"') quoteStart = !quoteStart;
    else if ((line[i] == ' ' || line[i] == '\t') && quoteStart) line[i] = '_';
}
```

### 步骤二：词法分析（$\texttt{Tokenization}$）

将字符串分割为单词，并识别每个单词的词法单元类型。

单词类型包括：
- **关键字**：`GO`, `KEEP`, `RIGHT`, `LEFT`, `FIRST`, `SECOND`, `THIRD`, `AT`, `RECORD`, `TIME`, `TO`, `KMH`, `CHANGE`, `AVERAGE`, `SPEED`, `CAS`, `AND`, `THEN`
- **数字序列** `nnn`：全由数字组成
- **引号字符串** `signwords`：以 `"` 开头和结尾，中间只包含大写字母、下划线和句点

非法字符检测：
- 输入中出现下划线 `_` 或井号 `#` 直接判定为非法
- `signwords` 中不能以 `_` 开头或结尾，不能出现字母之外的非句点字符

```cpp
int getSymbol(string word) {
    // 检查是否为关键字
    int symbol = find(texts, texts + 22, word) - texts;
    if (symbol >= GO && symbol <= THEN)
        return symbol;
    // 检查是否为 n
    if (isdigit(word[0])) {
        for (char c : word)
            if (!isdigit(c)) return NONE;
        return NNN;
    }
    // 检查是否为 signwords
    if (word[0] == '\"' && word.back() == '\"' && word.length() >= 3) {
        // 验证内容字符
        for (int i = 1; i < word.length() - 1; i++) {
            char c = word[i];
            if (c == '.') continue;
            if (c == '_') continue;
            if (!isupper(c)) return NONE;
        }
        return SIGNWORDS;
    }
    return NONE;
}
```

### 步骤三：语法归约

这是算法的核心部分。我们预定义一个归约规则表 `groups`，每条规则包含：

- 一个**目标符号**（归约后产生的新符号）
- 一个**左侧上下文**（可选）
- 一个**右侧上下文**（可选）

归约规则采用如下格式：`{symbol, left, right, result}`，含义为：
- 若当前符号为 `symbol`，且左侧符号为 `left`（若 `left != NONE`），右侧符号为 `right`（若 `right != NONE`），则可以使用该规则
- 将匹配的符号（可能包括左右符号）归约为 `result`

例如：
```cpp
{AVERAGE, CHANGE, SPEED, CAS}         // CHANGE AVERAGE SPEED → CAS
{RIGHT, NONE, NONE, DIRECTION}        // RIGHT → DIRECTION
{AND, NAVIGATIONAL, TIME_KEEPING, INSTRUCTION}  // navigational AND time-keeping → instruction
```

归约过程采用**迭代扫描**：
1. 扫描符号序列
2. 找到第一个可应用的归约规则
3. 执行归约（替换符号，必要时删除相邻符号）
4. 重复直到无法归约或只剩下一个符号

```cpp
bool isInstruction(string line) {
    if (translateToSymbol(line) == false) return false;
    for (int i = 0; i < groupCount; i++) {
        while (true) {
            bool found = false;
            for (int j = 0; j < symbols.size(); j++) {
                if (symbols[j] == groups[i][0]) {
                    // 检查边界条件
                    if (groups[i][1] != NONE && j == 0) continue;
                    if (groups[i][2] != NONE && j == symbols.size() - 1) continue;
                    // 匹配成功，执行归约
                    // ... 归约逻辑
                    found = true;
                    break;
                }
            }
            if (!found) break;
        }
    }
    return (symbols.size() == 1 && symbols[0] == INSTRUCTION);
}
```

### 归约规则设计

归约规则的设计遵循自底向上的原则：

| 优先级 | 规则示例 | 说明 |
|--------|----------|------|
| $1$ | `AVERAGE CHANGE SPEED → CAS` | 合并多词单元 |
| $2$ | `TO NNN KMH → TO_NNN_KMH` | 合并速度单位 |
| $3$ | `RIGHT → DIRECTION` | 单项归约 |
| $4$ | `HOW WHERE → DIRECTIONAL` | 组合归约 |
| $5$ | `AND THEN → AND_THEN` | 合并连接符 |
| $6$ | `DIRECTIONAL AND_THEN DIRECTIONAL → NAVIGATIONAL` | 递归组合 |
| $7$ | `NAVIGATIONAL AND TIME_KEEPING → INSTRUCTION` | 顶层归约 |

需要注意归约规则的顺序：先归约较小的结构，再处理较大的组合。

### 步骤四：输出格式化

输出要求：
- 行号右对齐在 $3$ 个字符宽度内
- 格式：`XXX. instruction`（`XXX` 为行号，后面跟点号和空格）
- 多个连续空格压缩为单个空格
- 非法指令输出 `Trap!`

```cpp
string spaceReduced(string line) {
    // 使用 istringstream 自动压缩空格
    istringstream iss(line);
    string word;
    vector<string> words;
    while (iss >> word) words.push_back(word);
    // 重建字符串，保留引号内的空格（原本用 '_' 标记）
    // 将 '_' 还原为空格
    // ...
}
```

## 算法复杂度分析

- **时间复杂度**：$O(n \cdot m)$，其中 $n$ 为符号序列长度，$m$ 为归约规则数量。由于每条指令不超过 $75$ 个字符，符号数量有限，实际运行非常快。
- **空间复杂度**：$O(n)$，用于存储符号序列。

## 注意事项

1. **归约顺序**：必须反复扫描所有规则，因为一次归约后可能产生新的可归约模式。
2. **边界处理**：归约时需要检查左右符号是否越界。
3. **引号内空格**：临时替换为 `_` 后，输出时需要还原为空格。
4. **非法字符**：`_` 和 `#$` 等字符直接判为 `Trap!`。

## 代码实现

```cpp
// Car Trialling
// UVa ID: 171
// Verdict: Accepted
// Submission Date: 2016-03-06
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋. metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int GO = 0, KEEP = 1, RIGHT = 2, LEFT = 3, FIRST = 4, SECOND = 5,
    THIRD = 6, AT = 7, RECORD = 8, TIME = 9, TO = 10, KMH = 11,
    CHANGE = 12, AVERAGE = 13, SPEED = 14, CAS = 15, NNN = 16, SIGNWORDS = 17,
    AND = 18, THEN = 19, QUOTE = 20, NONE = 21, TO_NNN_KMH = 22,
    TIME_KEEPING = 23, WHEN = 24, DIRECTION = 25, DIRECTIONAL = 26,
    INSTRUCTION = 27, AND_THEN = 28, NAVIGATIONAL = 29, WHERE = 30, HOW = 31;

string debug[] = {
    "GO", "KEEP", "RIGHT", "LEFT", "FIRST", "SECOND",
    "THIRD", "AT", "RECORD", "TIME", "TO", "KMH",
    "CHANGE", "AVERAGE", "SPEED", "CAS", "NNN", "SIGNWORDS",
    "AND", "THEN", "QUOTE", "NONE", "TO_NNN_KMH",
    "TIME_KEEPING", "WHEN", "DIRECTION", "DIRECTIONAL",
    "INSTRUCTION", "AND_THEN", "NAVIGATIONAL", "WHERE", "HOW"
};

string texts[] = { "GO", "KEEP", "RIGHT", "LEFT", "FIRST", "SECOND",
    "THIRD", "AT", "RECORD", "TIME", "TO", "KMH",
    "CHANGE", "AVERAGE", "SPEED", "CAS", "NNN", "#SIGNWORDS",
    "AND", "THEN", "#QUOTE", "#NONE"
};

const int groupCount = 22;

int groups[22][4] = {
    {AVERAGE, CHANGE, SPEED, CAS},
    {THEN, AND, NONE, AND_THEN},
    {NNN, TO, KMH, TO_NNN_KMH},
    {TO_NNN_KMH, CAS, NONE, TIME_KEEPING},
    {TIME, RECORD, NONE, TIME_KEEPING},
    {AT, NONE, SIGNWORDS, WHERE},
    {FIRST, NONE, NONE, WHEN},
    {SECOND, NONE, NONE, WHEN},
    {THIRD, NONE, NONE, WHEN},
    {RIGHT, NONE, NONE, DIRECTION},
    {LEFT, NONE, NONE, DIRECTION},
    {KEEP, NONE, NONE, HOW},
    {WHEN, GO, NONE, HOW},
    {GO, NONE, NONE, HOW},
    {DIRECTION, HOW, WHERE, DIRECTIONAL},
    {DIRECTION, HOW, NONE, DIRECTIONAL},
    {AND_THEN, DIRECTIONAL, DIRECTIONAL, NAVIGATIONAL},
    {AND_THEN, NAVIGATIONAL, DIRECTIONAL, NAVIGATIONAL},
    {DIRECTIONAL, NONE, NONE, NAVIGATIONAL},
    {AND, NAVIGATIONAL, TIME_KEEPING, INSTRUCTION},
    {TIME_KEEPING, NONE, NONE, INSTRUCTION},
    {NAVIGATIONAL, NONE, NONE, INSTRUCTION}
};

vector < int > symbols;

string spaceReduced(string line) {
    istringstream iss(line);
    string word;
    vector < string > words;
    while (iss >> word) words.push_back(word);
    bool inQuote = false;
    string newLine;
    for (int i = 0; i < words.size(); i++) {
        if (words[i].find('\"') != string::npos) {
            if (inQuote == false) {
                newLine += words[i];
                inQuote = true;
                if (words[i].length() > 1) newLine += " ";
            } else {
                inQuote = false;
                if (words[i].length() > 1) {
                    newLine += words[i];
                    newLine += " ";
                } else {
                    newLine.erase(newLine.end() - 1);
                    newLine += words[i];
                }
            }
        } else {
            newLine += words[i];
            newLine += " ";
        }
    }
    if (newLine[newLine.length() - 1] == ' ') newLine.erase(newLine.end() - 1);
    if (line.length() > 0 && isblank(line.front())) newLine = ' ' + newLine;
    if (line.length() > 0 && isblank(line.back())) newLine = newLine + ' ';
    return newLine;
}

int getSymbol(string word) {
    int symbol = find(texts, texts + 22, word) - texts;
    if (symbol >= GO && symbol <= THEN)  return symbol;
    if ('0' <= word[0] && word[0] <= '9') {
        for (int i = 0; i < word.length(); i++)
            if (word[i] < '0' || word[i] > '9')
                return NONE;
        return NNN;
    }
    if (word[0] == '\"' && word.length() >= 3 && word[word.length() - 1] == '\"') {
        if (word[1] == '_' || word[word.length() - 2] == '_') return NONE;
        for (int i = 1; i < word.length() - 1; i++) {
            if (word[i] == '.') {
                if (word[i - 1] == '_') return NONE;
                else continue;
            }
            if (word[i] == '_') continue;
            if ((word[i] < 'A' || word[i] > 'Z')) return NONE;
        }
        return SIGNWORDS;
    }
    return NONE;
}

bool translateToSymbol(string line) {
    if (line.find('_') != line.npos || line.find('#') != line.npos) return false;
    bool quoteStart = false;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] == '\"') quoteStart = !quoteStart;
        else if ((line[i] == ' ' || line[i] == '\t') && quoteStart) line[i] = '_';
    }
    symbols.clear();
    istringstream iss(line);
    string word;
    while (iss >> word) {
        int symbol = getSymbol(word);
        if (symbol == NONE) return false;
        symbols.push_back(symbol);
    }
    return true;
}

bool isInstruction(string line) {
    if (translateToSymbol(line) == false) return false;
    for (int i = 0; i < groupCount; i++) {
        while (true) {
            bool found = false;
            for (int j = 0; j < symbols.size(); j++) {
                if (symbols[j] == groups[i][0]) {
                    if (groups[i][1] != NONE && j == 0) continue;
                    if (groups[i][2] != NONE && j == (symbols.size() - 1)) continue;
                    if (groups[i][1] == NONE && groups[i][2] == NONE) {
                        found = true;
                        symbols[j] = groups[i][3];
                        break;
                    }
                    if (groups[i][1] != NONE && groups[i][2] != NONE) {
                        if (symbols[j - 1] == groups[i][1] && symbols[j + 1] == groups[i][2]) {
                            found = true;
                            symbols[j - 1] = groups[i][3];
                            symbols.erase(symbols.begin() + j + 1);
                            symbols.erase(symbols.begin() + j);
                            break;
                        }
                    } else if (groups[i][1] != NONE && symbols[j - 1] == groups[i][1]) {
                        found = true;
                        symbols[j - 1] = groups[i][3];
                        symbols.erase(symbols.begin() + j);
                        break;
                    } else if (groups[i][2] != NONE && symbols[j + 1] == groups[i][2]) {
                        found = true;
                        symbols[j] = groups[i][3];
                        symbols.erase(symbols.begin() + j + 1);
                        break;
                    }
                }
            }
            if (found == false) break;
        }
    }
    return (symbols.size() == 1 && symbols[0] == INSTRUCTION);
}

int main() {
    string line, result;
    int lineNumber = 1;
    while (getline(cin, line), line != "#") {
        result = "Trap!";
        if (isInstruction(line)) result = spaceReduced(line);
        cout << setw(3) << right << (lineNumber++) << ". " << result << '\n';
    }
    return 0;
}
```

## 总结

本题的核心是实现一个基于归约的语法分析器。关键在于：
1. 正确识别各类词法单元
2. 设计合理的归约规则顺序
3. 妥善处理引号内空格的保留与压缩

通过这种方法，可以有效地判断输入是否符合给定的文法规则，并正确输出格式化结果。
