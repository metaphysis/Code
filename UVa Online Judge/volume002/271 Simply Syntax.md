[UVa 271 Simply Syntax](https://blog.csdn.net/metaphysis/article/details/161332792)

## 题目分析

题目要求判断给定的字符串是否符合 $\texttt{Hedonian}$ 语言的语法规则。

### 语法规则总结

根据题目描述，$\texttt{Hedonian}$ 语言的语法规则非常简洁：

1. **合法字符集**：只有小写字母 `p` 到 `z` 以及大写字母 `N`、`C`、`D`、`E`、`I` 是合法字符。
2. **原子句子**：任何单个字符从 `p` 到 `z` 都是一个正确的句子。
3. **否定规则**：如果 $s$ 是一个正确的句子，那么 $Ns$ 也是一个正确的句子。
4. **二元运算规则**：如果 $s$ 和 $t$ 是正确的句子，那么 $Cst$、$Dst$、$Est$、$Ist$ 也都是正确的句子。
5. **封闭性**：只有上述规则能够确定句子的正确性。

### 关键理解

注意到这些规则定义了一种**前缀表达式**（$\texttt{Polish Notation}$）的语法结构：

- 小写字母 `p` ~ `z` 是原子操作数（叶子节点）
- `N` 是一元运算符，作用于其后一个子表达式
- `C`、`D`、`E`、`I` 是二元运算符，作用于其后两个子表达式

例如，句子 `CpIsz` 的解析结构为：`C p (I s z)`，即先应用 `I` 于 `s` 和 `z`，再应用 `C` 于 `p` 和 `Isz` 的结果。

## 解题思路

### 方法选择

判断一个字符串是否符合这种前缀语法，常见的方法有：

1. **递归下降解析**：从字符串开头递归地解析表达式
2. **栈模拟归约**：从字符串末尾向前扫描，使用栈来归约子表达式
3. **自顶向下替换**：反复将符合模式的子串替换为标记

本题的参考代码采用了第三种方法——**反复归约（$\texttt{Reduction}$）**策略。

### 归约法的核心思想

归约法的基本思路是：

- 将句子中的每个字符映射为符号
- 原子句子（`p` ~ `z`）映射为 `SENTENCE` 类型
- 运算符（`N`、`C`、`D`、`E`、`I`）映射为对应的类型编号
- 不断寻找可以归约的模式，将其替换为 `SENTENCE`
- 如果最终整个字符串被归约为一个 `SENTENCE`，则句子合法

### 归约模式表

代码中定义了一个 $5 \times 4$ 的归约表 `T`：

| 运算符 | 模式左部 | 模式中间 | 模式右部 | 归约结果 |
|:---:|:---:|:---:|:---:|:---:|
| C   | SENTENCE | C   | SENTENCE | SENTENCE |
| D   | SENTENCE | D   | SENTENCE | SENTENCE |
| E   | SENTENCE | E   | SENTENCE | SENTENCE |
| I   | SENTENCE | I   | SENTENCE | SENTENCE |
| N   | N        | -1  | SENTENCE | SENTENCE |

- `SENTENCE` 表示已经归约好的子句
- `NONE`（值为 $-1$）表示对应位置不存在（因为 `N` 是一元运算符，只有右操作数）
- 对于 `N` 模式，匹配 `[N, SENTENCE]` 的相邻两个符号，替换为一个 `SENTENCE`
- 对于二元运算符，匹配 `[SENTENCE, 运算符, SENTENCE]` 的相邻三个符号，替换为一个 `SENTENCE`

### 算法步骤

1. **初始化**：读取一行字符串，调用 `translateToSymbol()` 将每个字符转换为对应的符号编号，存入向量 `S` 中。

2. **归约循环**：
   - 设置标志 `replaced = false`
   - 遍历 $5$ 种归约模式
   - 在 `S` 中查找匹配当前模式的子序列
   - 如果找到匹配，删除相应的元素，并在原位置插入归约结果 `SENTENCE`
   - 设置 `replaced = true`
   - 继续扫描，直到当前模式无法找到更多匹配
   - 完成所有 $5$ 种模式的扫描后，如果 `replaced == false`，则退出循环

3. **判断结果**：循环结束后，检查 `S` 的大小是否为 $1$ 且唯一的元素是 `SENTENCE`。若是，则输出 `YES`，否则输出 `NO`。

### 算法正确性说明

由于语法规则是封闭的，任何合法句子都可以通过不断应用逆规则（从复合句子归约为子句子）最终归约为一个原子句子。反之，如果某个字符串不合法，则归约过程会在某个阶段卡住，无法归约为单一符号。

该归约过程类似于 **自底向上** 的语法分析，每个归约步骤都对应语法规则的一条逆应用。

### 时间复杂度

每个归约步骤减少至少一个符号，因此归约次数为 $O(n)$，其中 $n$ 为字符串长度。每次查找匹配需要扫描向量，总体时间复杂度为 $O(n^2)$。考虑到每个句子最长 $256$ 个字符，该复杂度完全可以接受。

## 代码实现

```cpp
// Simply Syntax
// UVa ID: 271
// Verdict: Accepted
// Submission Date: 2016-05-10
// UVa Run Time: 0.060s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 定义符号常量
const int NONE = -1;      // 表示不存在（用于一元运算符N）
const int N = 0;          // 运算符N的编号
const int C = 1;          // 运算符C的编号
const int D = 2;          // 运算符D的编号
const int E = 3;          // 运算符E的编号
const int I = 4;          // 运算符I的编号
const int SENTENCE = 5;   // 归约后的句子标记

vector<int> S;  // 存储当前待归约的符号序列

// 归约规则表
// 每行对应一种归约模式：[左部, 中间, 右部, 归约结果]
// NONE 表示该位置不参与匹配
int T[5][4] = {
    {SENTENCE, C, SENTENCE, SENTENCE},  // 模式：SENTENCE C SENTENCE -> SENTENCE
    {SENTENCE, D, SENTENCE, SENTENCE},  // 模式：SENTENCE D SENTENCE -> SENTENCE
    {SENTENCE, E, SENTENCE, SENTENCE},  // 模式：SENTENCE E SENTENCE -> SENTENCE
    {SENTENCE, I, SENTENCE, SENTENCE},  // 模式：SENTENCE I SENTENCE -> SENTENCE
    {N, NONE, SENTENCE, SENTENCE}       // 模式：N SENTENCE -> SENTENCE（一元运算符）
};

// 将输入的字符串转换为符号编号序列存入向量S
void translateToSymbol(string line)
{
    S.clear();
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == 'N')
            S.push_back(N);
        else if (line[i] == 'C')
            S.push_back(C);
        else if (line[i] == 'D')
            S.push_back(D);
        else if (line[i] == 'E')
            S.push_back(E);
        else if (line[i] == 'I')
            S.push_back(I);
        else  // 小写字母p~z，属于原子句子
            S.push_back(SENTENCE);
    }
}

// 判断句子是否合法
bool isSentence(string line)
{
    // 将字符串转换为符号序列
    translateToSymbol(line);

    while (true)
    {
        bool replaced = false;
        
        // 依次尝试5种归约模式
        for (int i = 0; i < 5; i++)
        {
            // 扫描整个符号序列
            for (int j = 0; j < S.size(); )
            {
                // 检查当前位置是否匹配模式的左部
                if ((S[j] != T[i][0]) ||
                    // 如果模式有中间符号（不是NONE），检查前一个位置
                    (~T[i][1] && (!j || S[j - 1] != T[i][1])) ||
                    // 如果模式有右部符号（不是NONE），检查后一个位置
                    (~T[i][2] && (j == (S.size() - 1) || S[j + 1] != T[i][2])))
                {
                    j++;
                    continue;
                }
                
                // 匹配成功，进行归约操作
                // 如果存在中间符号，删除它（位置j-1）
                j = ~T[i][1] ? S.erase(S.begin() + j - 1) - S.begin() : j;
                // 如果存在右部符号，删除它（位置j+1，注意j可能已改变）
                j = ~T[i][2] ? S.erase(S.begin() + j + 1) - S.begin() - 1 : j;
                // 将当前位置替换为归约结果（SENTENCE）
                S[j] = T[i][3];
                
                replaced = true;  // 标记发生过归约
            }
        }
        
        // 如果这一轮没有发生任何归约，说明无法继续归约了
        if (replaced == false)
            break;
    }
    
    // 最终序列长度为1且该符号为SENTENCE时，句子合法
    return S.size() == 1 && S.front() == SENTENCE;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
        cout << (isSentence(line) ? "YES" : "NO") << endl;

    return 0;
}
```
## 总结

本题利用**反复归约**的方法，将复杂的语法判断问题转化为简单的模式匹配和替换问题。关键在于正确构建归约规则表，并理解归约过程是语法规则的逆应用。该方法实现简洁，对于本题的规模（句子长度 $\leq 256$）运行效率足够高。
