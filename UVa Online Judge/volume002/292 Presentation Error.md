[UVa 292 Presentation Error](https://blog.csdn.net/metaphysis/article/details/161387098)

## 题目分析

本题要求实现一个判断程序输出结果类型的算法。在程序设计竞赛中，选手提交的程序输出可能被判定为以下几种情况：

- **`Accepted`**：完全正确
- **`Presentation Error`**：输出格式有误，但核心内容正确
- **`Wrong Answer`**：答案错误

题目中给出了一套精确的判定规则，以消除评委之间的主观性。规则的核心在于理解 **`JuryOut`**（标准答案）和 **`SubmitOut`**（选手输出）之间的比较过程。

### 规则解析

判定算法分为以下步骤：

$1$. **预处理**：删除每行末尾的空白字符（空格和制表符），然后删除所有末尾的空行。

$2$. **完全相同判定**：如果经过步骤 $1$ 后，两个输出完全相同，则判定为 `Accepted`。

$3$. **大小写转换**：将两个输出中的所有字母转换为大写（包括方括号内的内容）。

$4$. **提取核心内容**：标准答案中，方括号 `[` 和 `]` 之间的内容称为 **`Essentials`**（核心内容），记作 $E_1$ 到 $E_n$。方括号本身不是输出的一部分，因此在选手输出中不应该出现。

$5$. **格式错误判定**：如果每个 $E_i$ 都在选手输出中按顺序出现（不重叠，且 $E_i$ 出现在 $E_{i-1}$ 之后），则判定为 `Presentation Error`。

$6$. **答案错误判定**：否则判定为 `Wrong Answer`。

### 输入格式

- 第一行：测试用例数量 $N$
- 每个测试用例：
  - 第一行：标准答案的行数 $J$ 和选手输出的行数 $S$
  - 接下来 $J$ 行：标准答案的内容
  - 接下来 $S$ 行：选手输出的内容

限制条件：
- 两个输出各不超过 $10$ 行
- 每行最多 $80$ 个字符
- 核心内容非空，不跨行，首尾字符不是空白字符
- 核心内容不会嵌套

## 解题思路

根据题目描述的判定规则，我们可以设计如下解题流程：

### 第一步：读取与存储数据

读取测试用例数量后，对每个测试用例：
1. 读取 $J$ 和 $S$
2. 读取 $J$ 行标准答案，存储到 `jury` 字符串中
3. 读取 $S$ 行选手输出，存储到 `submit` 字符串中

在实际实现中，可以直接将整个输出拼接成一个字符串，每行之间用换行符 `\n` 分隔，这样可以方便地进行后续的字符串查找操作。

### 第二步：预处理

根据规则第 $1$ 步，需要：
$1$. 删除每行末尾的空白字符（使用 `isblank` 判断）
$2$. 删除末尾的空行

在字符串拼接的实现方式下，删除每行末尾空白字符可以在读取每一行时完成。删除末尾空行则通过检查字符串末尾是否有多余的换行符来实现。

### 第三步：完全相同判定（规则第 $2$ 步）

比较预处理后的两个字符串是否完全相同。但需要注意的是，标准答案中的方括号 `[` 和 `]` 不是实际输出的一部分，因此在比较时需要忽略它们。

具体做法：同时遍历两个字符串，当遇到标准答案中的 `[` 或 `]` 时跳过，否则比较字符是否相等。

如果遍历结束后两个字符串都恰好处理完毕，则说明完全相同，输出 `Accepted`。

### 第四步：大小写转换（规则第 $3$ 步）

将两个输出中的所有字母转换为大写。注意：在提取核心内容时，核心内容也需要转换为大写以便后续查找。

### 第五步：提取核心内容（规则第 $4$ 步）

遍历标准答案字符串，每当遇到 `[` 时，提取其后直到 `]` 之前的内容作为一个核心内容，存储到 `En` 向量中。由于核心内容不会嵌套，这个过程比较简单。

### 第六步：格式错误判定（规则第 $5$ 步）

检查每个核心内容 $E_i$ 是否按顺序出现在选手输出中：

- 使用 `find` 函数从上次匹配位置之后开始查找
- 如果找不到任何一个核心内容，返回 `false`
- 如果所有核心内容都按顺序找到，返回 `true`

如果返回 `true`，则输出 `Presentation Error`。

### 第七步：答案错误判定（规则第 $6$ 步）

如果以上都不满足，输出 `Wrong Answer`。

## 算法复杂度

- 时间复杂度：$O(L)$，其中 $L$ 是输入字符串的总长度
- 空间复杂度：$O(L)$，用于存储字符串和核心内容

## 注意事项

$1$. 核心内容提取时不需要转换大小写？实际上规则第 $3$ 步要求将所有字母转换为大写，因此核心内容也应当转换为大写后再存储。

$2$. 比较完全相同时要忽略方括号，但核心内容比较时方括号已经移除，直接比较字符串即可。

$3$. 换行符的处理：由于输出可能有多个行，拼接时保留换行符可以确保跨行的核心内容查找正确。

$4$. 空行删除：只有末尾的空行需要删除，中间的空行保留。

## 代码实现

```cpp
// Presentation Error
// UVa ID: 292
// Verdict: Accepted
// Submission Date: 2019-04-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 删除字符串末尾的连续空行
void trim(string &s) {
    // 删除末尾连续的 "\n\n" 对（即连续两个换行符）
    while (s.length() >= 2 && s[s.length() - 1] == '\n' && s[s.length() - 2] == '\n')
        s.pop_back();
    // 如果只剩一个换行符，也删除
    if (s.length() == 1 && s.back() == '\n') s.pop_back();
}

// 将字符串中的所有字母转换为大写
void toUpper(string &s) {
    for (int i = 0; i < s.length(); i++)
        if (isalpha(s[i]))
            s[i] = toupper(s[i]);
}

// 从标准答案字符串中提取核心内容（方括号之间的部分）
// 注意：核心内容会转换为大写后存储
void addEssential(vector<string> &En, string &s) {
    for (int i = 0; i < s.length(); i++)
        if (s[i] == '[') {
            i++;  // 跳过 '['
            string block;
            // 提取直到 ']' 之前的内容
            while (i < s.length() && s[i] != ']') {
                block += s[i];
                i++;
            }
            toUpper(block);  // 核心内容转换为大写
            En.push_back(block);
        }
}

// 判断是否为 Presentation Error
// 检查所有核心内容是否按顺序出现在选手输出中
bool pe(vector<string> &En, string &submit) {
    int i = 0, j = 0;  // i 表示当前核心内容索引，j 表示在 submit 中的搜索位置
    while (i < En.size() && j < submit.length()) {
        // 从位置 j 开始查找当前核心内容
        j = submit.find(En[i], j);
        if (j == submit.npos) return false;  // 未找到
        j += En[i].length();  // 移动到匹配内容之后，确保不重叠
        i++;
    }
    return i == En.size();  // 所有核心内容都找到了
}

// 判断两个输出是否完全相同（忽略标准答案中的方括号）
bool identical(string &s, string &t) {
    int i = 0, j = 0;
    while (i < s.length() && j < t.length()) {
        // 跳过标准答案中的 '[' 和 ']'
        if (s[i] == '[' || s[i] == ']') i++;
        // 比较字符
        else if (s[i] == t[j]) i++, j++;
        else return false;
    }
    // 处理标准答案末尾可能剩余的 ']'
    if (i < s.length() && s[i] == ']') i++;
    // 两个字符串都必须恰好处理完毕
    return i == s.length() && j == t.length();
}

int main() {
    int cases, n1, n2;
    string line;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++) {
        cin >> n1 >> n2;
        cin.ignore(256, '\n');
        vector<string> En;      // 存储核心内容
        string jury, submit;    // 存储标准答案和选手输出
        // 读取标准答案
        for (int i = 1; i <= n1; i++) {
            getline(cin, line);
            // 提取核心内容（在删除末尾空白之前，保证方括号被正确识别）
            addEssential(En, line);
            // 删除行末空白字符（空格和制表符）
            while (line.length() > 0 && isblank(line.back())) line.pop_back();
            jury += line;
            jury += '\n';  // 添加换行符分隔不同行
        }
        // 读取选手输出
        for (int i = 1; i <= n2; i++) {
            getline(cin, line);
            // 删除行末空白字符
            while (line.length() > 0 && isblank(line.back())) line.pop_back();
            submit += line;
            submit += '\n';
        }
        // 删除末尾空行
        trim(jury); trim(submit);
        // 规则第 2 步：判断是否完全相同（忽略方括号）
        if (identical(jury, submit)) {
            cout << "Accepted\n";
            continue;
        }
        // 规则第 3 步：将选手输出中的字母转换为大写
        // 注意：标准答案只需要提取核心内容，不需要整体转换
        toUpper(submit);
        // 规则第 5 步：判断是否为 Presentation Error
        if (pe(En, submit)) cout << "Presentation Error\n";
        else cout << "Wrong Answer\n";
    }
    return 0;
}
```

## 样例验证

使用题目提供的样例输入：

```cpp
4
1 2
Just one line?
Just one line?
2 2
The first characters of the alphabet are: [abcde]
Here they come: a b c d e
1 1
That's it: [abcde]
That's it: AbcDE
1 1
[2] and [3] make [5]
I guess 2 and 3 are less than 50.
```

程序输出：

```cpp
Accepted
Wrong Answer
Presentation Error
Presentation Error
```

与题目要求的输出一致，验证了算法的正确性。
