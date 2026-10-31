## 题目描述

给定一个语法正确的 $\texttt{Pascal}$ 源程序，要求按照指定的顺序对其进行压缩处理。压缩规则共三条，必须严格按顺序执行：

$\texttt{1.}$ 将字符串常量之外的所有连续空格（` `）替换为单个空格。字符串常量由单引号（`'`）界定，且至少包含一个字符。字符串内的两个连续单引号（`''`）表示一个单引号字符本身，不应视为字符串结束。
$\texttt{2.}$ 删除所有注释。注释有两种形式：以 `(*` 开始、`*)` 结束，或以 `{` 开始、`}` 结束。删除时连同注释标记一并移除。
$\texttt{3.}$ 删除所有完全空白的行，即删去注释后，该行仅由空格和换行符组成。

输入保证语法正确，不包含制表符或其他不可打印字符。

## 输入格式

输入文件包含一个任意的、语法正确的 $\texttt{Pascal}$ 源程序，可能包含多行。

## 输出格式

输出压缩后的 $\texttt{Pascal}$ 源程序，结果应仍为语法有效的 $\texttt{Pascal}$ 程序，但风格可能更为紧凑。

## 样例

**输入**

```
Program Test (input, output);
{ this is a great program }
  
Var    X, Y      :     integer     ;

  begin
     readln (X, Y);
         writeln (X,   '  This is Y   ',    Y,     '''Hi!')   ;
    end.
```

**输出**

```
Program Test (input, output);
Var X, Y : integer ;
 begin
 readln (X, Y);
 writeln (X, '  This is Y   ', Y, '''Hi!') ;
 end.

```

## 题目分析

本题属于文本处理与词法分析类问题。核心挑战在于正确区分程序代码与字符串常量、注释，因为注释标记和引号在字符串内不应被识别为语法符号，而字符串内的连续单引号需要作为转义处理。三条规则具有严格的先后顺序，必须在实现中保持该顺序。

### 规则顺序的影响

- 规则 $\texttt{1}$（压缩空格）在规则 $\texttt{2}$（删除注释）之前执行。这意味着注释内部的连续空格也会先被压缩，但注释最终会被删除，因此该顺序对最终结果几乎没有影响（因为注释被删除了）。然而，若注释与代码相邻，压缩空格可能会影响相邻代码间的空格数量。但删除注释后，这些空格可能被重新组合，因此必须按顺序模拟。
- 规则 $\texttt{3}$（删除空行）在最后执行，此时注释已全部移除，仅根据压缩后的内容判断行是否为空。

### 词法状态机

由于注释和空格压缩都必须忽略字符串常量内部的内容，我们需要一个**状态机**来区分当前是否处于字符串常量内部。$\texttt{Pascal}$ 的字符串常量由单引号界定，且使用 `''` 表示转义的单引号字符，因此状态机在遇到 `'` 时需要检查下一个字符是否也是 `'`，若是，则输出一个单引号并跳过两个字符，否则切换字符串状态。

### 字符流处理

输入可能跨多行，注释也可能跨行。因此不能简单地按行处理，而应将整个输入读入一个字符串（保留换行符），然后统一处理。最终输出时再根据换行符拆分并删除空行。

## 解题思路

整个处理流程分为三个独立的阶段，每个阶段均需区分字符串内外：

1. **压缩空格**：遍历整个输入字符串。在字符串外，遇到空格时仅输出一个空格，然后跳过后续所有连续空格；在字符串内，原样保留所有字符（包括空格），并正确处理转义单引号。
2. **删除注释**：再次遍历。在字符串外，检测到 `(*` 或 `{` 时，直接跳过直到匹配的 `*)` 或 `}`；在字符串内，原样保留，同时正确处理转义单引号。
3. **删除空行**：将上一步的结果按换行符分割，检查每行是否只包含空格。若否，则保留该行；否则丢弃。最后将保留下来的行重新拼接，末尾补一个换行符。

三个阶段均使用相同的字符串状态识别逻辑，因此可以复用同一个处理函数或编写独立的函数。由于规则顺序固定，主流程依次调用这三个函数即可。

### 关键细节

- **单引号转义**：当遇到 `'` 且当前在字符串内时，若下一个字符也是 `'`，则输出两个 `'`，并将指针后移两位，表示一个转义的单引号字符，不改变字符串状态；否则，该 `'` 为字符串结束符，切换状态。
- **注释嵌套**：$\texttt{Pascal}$ 不允许注释嵌套，因此只需找到最近的结束标记即可，无需栈结构。
- **连续空格压缩**：在字符串外，连续空格输出一个后，指针直接跳到下一个非空格字符。

### 复杂度分析

设输入总字符数为 $N$（包括换行符）。

- 压缩空格：单次遍历，$O(N)$。
- 删除注释：单次遍历，$O(N)$。
- 删除空行：分割与检查，$O(N)$。
总时间复杂度 $O(N)$，空间复杂度 $O(N)$。

## 代码实现

```cpp
// Comment Removal
// UVa ID: 723
// Verdict: Accepted
// Submission Date: 2026-07-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 第一步：压缩空格（字符串常量内除外）
// 将非字符串区域内的连续空格替换为单个空格
string compressSpaces(const string& s) {
    string res;
    int n = (int)s.size();
    bool inString = false;
    for (int i = 0; i < n; ) {
        if (!inString) {
            if (s[i] == '\'') {
                inString = true;
                res.push_back(s[i]);
                ++i;
            } else if (s[i] == ' ') {
                res.push_back(' ');
                while (i < n && s[i] == ' ') ++i;
            } else {
                res.push_back(s[i]);
                ++i;
            }
        } else {
            res.push_back(s[i]);
            if (s[i] == '\'') {
                if (i + 1 < n && s[i + 1] == '\'') {
                    res.push_back(s[i + 1]);
                    i += 2;
                } else {
                    inString = false;
                    ++i;
                }
            } else ++i;
        }
    }
    return res;
}

// 第二步：删除注释（(* *) 和 { }），同样需要区分字符串常量
string removeComments(const string& s) {
    string res;
    int n = (int)s.size();
    bool inString = false;
    for (int i = 0; i < n; ) {
        if (!inString) {
            if (i + 1 < n && s[i] == '(' && s[i + 1] == '*') {
                i += 2;
                while (i + 1 < n && !(s[i] == '*' && s[i + 1] == ')')) ++i;
                if (i + 1 < n) i += 2;
                continue;
            }
            if (s[i] == '{') {
                ++i;
                while (i < n && s[i] != '}') ++i;
                if (i < n) ++i;
                continue;
            }
            if (s[i] == '\'') {
                inString = true;
                res.push_back(s[i]);
                ++i;
            } else {
                res.push_back(s[i]);
                ++i;
            }
        } else {
            res.push_back(s[i]);
            if (s[i] == '\'') {
                if (i + 1 < n && s[i + 1] == '\'') {
                    res.push_back(s[i + 1]);
                    i += 2;
                } else {
                    inString = false;
                    ++i;
                }
            } else ++i;
        }
    }
    return res;
}

// 第三步：删除完全空白的行（仅包含空格和换行符的行）
string removeBlankLines(const string& s) {
    vector<string> lines;
    string line;
    istringstream iss(s);
    while (getline(iss, line)) {
        bool onlySpaces = true;
        for (char c : line) {
            if (c != ' ') {
                onlySpaces = false;
                break;
            }
        }
        if (!onlySpaces) lines.push_back(line);
    }
    string result;
    for (size_t i = 0; i < lines.size(); ++i) {
        result += lines[i];
        if (i + 1 < lines.size()) result += '\n';
    }
    if (!lines.empty()) result += '\n';
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string input, line;
    while (getline(cin, line)) {
        input += line;
        input += '\n';
    }
    string step1 = compressSpaces(input);
    string step2 = removeComments(step1);
    string output = removeBlankLines(step2);
    cout << output;
    return 0;
}
```

## 总结

本题的关键在于**正确实现词法状态机**，区分字符串内外的处理逻辑，并**严格按照规定的顺序**执行三个压缩步骤。字符串内对 `''` 转义的处理是容易出错的细节，必须谨慎。三个步骤虽可合并为一个遍历以减少开销，但分开实现更清晰、易于验证。本题也提醒我们，在处理源代码或文本格式时，务必遵循给定的语法规则，尤其是转义字符和注释标记，否则可能产生错误结果。该解法时间复杂度 $O(N)$，能够高效处理任意大小的输入。
