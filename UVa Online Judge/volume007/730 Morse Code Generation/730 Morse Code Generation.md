## 题目描述

本题要求根据给定的摩尔斯电码表和传输速度，模拟报文的发送过程，输出每个字符对应的发射机开启/关闭时间（毫秒）。发送规则遵循摩尔斯电码的时序定义，并按照速度（$\texttt{wpm}$）调整时间间隔。

## 输入格式

输入文件包含两部分：

1. **映射表**：若干行，每行一个字符（大写字母或数字）及其摩尔斯码表示（由点 `.` 和划 `-` 组成），直到出现单独一行仅包含 `@` 的标记行结束。
2. **数据集**：一个或多个数据集，每个数据集以单独一行 `@` 开始（第一个 `@` 已用于结束映射表，但后续每个数据集也以 `@` 开头）。接着一行是一个整数 $w$，表示传输速度（$\texttt{words‑per‑minute}$）。之后是多行报文，报文可能包含大小写字母、数字和空格。报文行之间的换行符（除最后一行外）视为单词间隔。

输入以文件结束（$\texttt{EOF}$）终止。

## 输出格式

对于每个数据集：

- 输出报文的一个副本，每个有效字符（仅限 `A` – `Z` 和 `0` – `9`）占一行。
- 每行以该字符开头，随后输出该字符摩尔斯码中每个符号的开启时间（毫秒）及紧随其后的关闭时间（即字符内间隔），开启时间后跟一个字符 `S`，关闭时间后跟一个字符 `N`。每个时间前后各有一个空格。
- 在所有符号输出完毕后，输出该字符后的间隔时间（字符间间隔或单词间间隔）并跟 `N`。
- 若该字符后紧跟一个空格（即单词分隔），则需要在下一行输出，行首两个空格，然后输出单词间间隔时间和 `N`。
- 两个数据集的输出之间用一个空行分隔。

所有时间值均为整数（四舍五入）。

## 样例

**输入**
```
A .-
B -...
D -..
G --.
O ---
Y -.--
@
5
A BAD BOY
@
13
A good
boy
```

**输出**
```
A 115 S 300 N 346 S 300 N 900 N
  2700 N
B 346 S 300 N 115 S 300 N 115 S 300 N 115 S 300 N 900 N
A 115 S 300 N 346 S 300 N 900 N
D 346 S 300 N 115 S 300 N 115 S 300 N 900 N
  2700 N
B 346 S 300 N 115 S 300 N 115 S 300 N 115 S 300 N 900 N
O 346 S 300 N 346 S 300 N 346 S 300 N 900 N
Y 346 S 300 N 115 S 300 N 346 S 300 N 346 S 300 N 900 N

A 115 S 115 N 346 S 115 N 346 N
  1038 N
G 346 S 115 N 346 S 115 N 115 S 115 N 346 N
O 346 S 115 N 346 S 115 N 346 S 115 N 346 N
O 346 S 115 N 346 S 115 N 346 S 115 N 346 N
D 346 S 115 N 115 S 115 N 115 S 115 N 346 N
  1038 N
B 346 S 115 N 115 S 115 N 115 S 115 N 115 S 115 N 346 N
O 346 S 115 N 346 S 115 N 346 S 115 N 346 N
Y 346 S 115 N 115 S 115 N 346 S 115 N 346 S 115 N 346 N
```

## 题目分析

摩尔斯码的时序定义以“点”为基本单位。一个“划”的长度为三个点。字符内符号之间的间隔（点或划之后）至少为一个点的长度；字符间间隔为三个点；单词间间隔为九个点。

在 $13$ $\texttt{wpm}$ 的基准速度下，每分钟传送 $13 \times 5 = 65$ 个字符，每个字符平均 $8$ 个点长度，故每分钟共有 $65 \times 8 = 520$ 个点单位。因此基准点长为：

$$
\textit{baseDot} = \frac{60000}{520} \approx 115.3846 \text{ ms}
$$

当速度低于 $13$ $\texttt{wpm}$ 时，点信号本身的持续时间保持不变（仍为基准点长），而通过增大字符内间隔来降低整体传送速度；当速度高于或等于 $13$ $\texttt{wpm}$ 时，点信号时长和字符内间隔均随速度同步变化。具体地，若速度为 $w$ $\texttt{wpm}$，则每分钟有 $w \times 5 \times 8 = 40w$ 个点单位，因此点信号时长（高速时）为：

$$
\textit{dot} = \frac{60000}{40w} \text{ ms}
$$

对于低速（$w < 13$），点信号时长固定为 $\textit{baseDot}$，而字符内间隔则为：

$$
\textit{intra} = \frac{60000}{40w} \text{ ms}
$$

（注意：此时 $\textit{intra} > \textit{baseDot}$，从而总速率降低。）

所有时间值都需要四舍五入到最接近的整数。

本题的核心任务是根据报文字符串，依次输出每个字符的开启/关闭时间序列，并正确处理字符间间隔和单词间间隔。

## 解题思路

### 步骤一：解析映射表

逐行读入，每行第一个字符为字母或数字，其余部分为摩尔斯码（由 `.` 和 `-` 组成）。使用 `unordered_map<char, string>` 存储映射关系，直到读入单独一行的 `@`。

### 步骤二：读取每个数据集

每个数据集的第一行（在 `@` 之后）是速度 $w$，接下来读取多行报文，直到遇到下一个 `@` 或 $\texttt{EOF}$。由于换行符（除最后一行外）视为单词间隔，拼接报文时在非最后一行末尾添加一个空格。

### 步骤三：提取有效字符及其后间隔类型

遍历拼接后的报文字符串，仅保留字母和数字（将其转换为大写），同时记录该字符后面是否紧邻空格（或字符串末尾）。若后面有空格，则该字符后应使用单词间间隔，否则使用字符间间隔。

### 步骤四：计算时间参数

根据 $w$ 的值计算：

- 点时长 `dot`
- 划时长 `dash = 3 * dot`
- 字符内间隔 `intra`
- 字符间间隔 `interChar = 3 * intra`
- 单词间间隔 `interWord = 9 * intra`

计算时使用 `double` 保持精度，最后调用 `round()` 四舍五入为整数。

### 步骤五：输出每个字符

对于每个有效字符：

1. 输出该字符。
2. 根据其摩尔斯码，对每个符号：
   - 输出该符号的开启时间（点或划）及 `S`。
   - 输出字符内间隔及 `N`。
3. 输出字符间间隔及 `N`，换行。
4. 若该字符后是单词间隔，则在下一行缩进两个空格，输出单词间间隔及 `N`。

### 正确性保证

时间计算公式源自题目对 $13$ $\texttt{wpm}$ 基准的定义，并严格按照低速与高速的区分调整间隔。四舍五入符合输出要求。单词间隔的处理（额外行缩进）与样例一致。

### 复杂度分析

设报文中有效字符总数为 $M$，每个字符的摩尔斯码平均长度为 $c$（本题中 $c \le 4$ 或 $5$ 左右）。算法仅需一次遍历报文并查表，时间复杂度为 $O(M \cdot c)$，空间复杂度为 $O(1)$（不考虑存储映射表）。整体运行效率极高。

## 代码实现

```cpp
// Morse Code Generation
// UVa ID: 730
// Verdict: Accepted
// Submission Date: 2026-07-08
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<char, string> morse;
    string line;
    // 读取映射表，直到单独一行的 '@'
    while (getline(cin, line) && line != "@") {
        if (line.empty()) continue;
        stringstream ss(line);
        char ch;
        string code;
        ss >> ch >> code;
        morse[ch] = code;
    }
    bool firstDataset = true;
    int wpm;
    // 循环读取每个数据集
    while (cin >> wpm) {
        cin.ignore(); // 忽略 wpm 后的换行
        // 读取报文行，直到遇到下一个 '@' 或 EOF
        vector<string> msgLines;
        while (getline(cin, line) && line != "@") {
            msgLines.push_back(line);
        }
        // 拼接报文，换行处插入空格（除最后一行）
        string msg;
        for (size_t i = 0; i < msgLines.size(); ++i) {
            msg += msgLines[i];
            if (i + 1 < msgLines.size()) msg += ' ';
        }
        // 提取有效字符，并记录其后是否有空格（单词分隔）
        vector<pair<char, bool>> chars; // {字符, 是否单词分隔}
        for (size_t i = 0; i < msg.size(); ) {
            if (isalnum(msg[i])) {
                char ch = toupper(msg[i]);
                size_t j = i + 1;
                bool hasSpace = false;
                while (j < msg.size() && msg[j] == ' ') {
                    hasSpace = true;
                    ++j;
                }
                chars.push_back({ch, hasSpace});
                i = j;
            } else ++i;
        }
        // 计算时间参数（使用 double 保持精度，最后四舍五入）
        const double baseDot = 60000.0 / 520.0; // 13 wpm 基准点长
        double dot_real, intra_real;
        if (wpm < 13) {
            dot_real = baseDot;
            intra_real = 60000.0 / (wpm * 40.0);
        } else {
            dot_real = 60000.0 / (wpm * 40.0);
            intra_real = dot_real;
        }
        int dot = (int)round(dot_real);
        int dash = (int)round(3.0 * dot_real);
        int intra = (int)round(intra_real);
        int interChar = (int)round(3.0 * intra_real);
        int interWord = (int)round(9.0 * intra_real); // 3 * interChar
        // 两个数据集之间输出空行
        if (!firstDataset) cout << '\n';
        firstDataset = false;
        // 逐个输出字符
        for (const auto& p : chars) {
            char ch = p.first;
            bool wordSep = p.second;
            string code = morse[ch]; // 查表得到摩尔斯码
            cout << ch;
            // 输出每个符号的 on 和 off（off 为内部间隔）
            for (char c : code) {
                int on = (c == '.') ? dot : dash;
                cout << ' ' << on << " S";
                cout << ' ' << intra << " N";
            }
            // 输出字符间间隔
            cout << ' ' << interChar << " N";
            cout << '\n';
            // 若该字符后是单词分隔，额外输出一行（两个空格缩进）
            if (wordSep) cout << "  " << interWord << " N\n";
        }
    }
    return 0;
}
```

## 总结

本题重点在于准确理解摩尔斯码的时序规则与速度之间的关系，尤其是低速时通过拉长间隔来降低速率。关键的计算公式和四舍五入步骤需严格遵循。输出格式中单词间间隔的特殊缩进是容易忽略的细节。代码实现简洁，只需一次查表和简单循环即可完成，体现了模拟题的典型特征。掌握此类模拟题的核心在于仔细阅读题意，按部就班实现各个规则，并注意输出格式的精确性。
