[UVa 342 HTML Syntax Checking](https://blog.csdn.net/metaphysis/article/details/161557128)

## 题目描述

本题要求编写一个程序，对用 $\texttt{HTML}$ 编写的简单文本进行语法验证。我们不考虑这些文档的语义，只考虑简化的语法规则。在这些文档中，你会找到普通的文本（行长度任意），其中穿插着标记标签。我们考虑的标记标签总是成对出现。

标记标签很容易识别，因为它们总是出现在尖括号中（即 `<` 和 `>`）。我们考虑的标签总是由不超过 $10$ 个大写字母组成。标签影响的文本区域结束由以正斜杠 `/` 开头的同名标签指示，如 `</TAG>`。标签区域可能跨越多行文本。$\texttt{HTML}$ 标签必须正确嵌套，就像 $\texttt{Pascal}$ 中的 `BEGIN...END` 对或 $\texttt{C/C++}$ 中的 `{` 和 `}` 一样。

### 输入格式

输入包含多个测试用例。每个测试用例以一行包含整数 $NL$ 开始，表示测试用例中的文本行数。$NL$ 不会超过 $32767$。输入结束以 $NL = 0$ 标记。

在指定 $NL$ 的行之后，有 $NL$ 行需要检查语法合规性的文本。注意：没有最大行长度限制。

### 输出格式

对于每个测试用例，输出测试用例编号（从 $1$ 开始编号）。如果文本符合上述规则，输出 `OK`。如果文本有错误，仅输出第一个错误的以下消息之一：

- `line #: bad character in tag name`
- `line #: too many/few characters in tag name`
- `line #: expected </xxxxxxxxxx>`
- `line #: no matching begin tag`

其中 `#` 应替换为检测到违规标签时的行号。

如果检测到错误，输出适当的错误消息后，程序必须跳过错误测试用例中的任何剩余行，以到达下一个测试用例的开头。

### 样例输入

```
6
This is some ordinary text. <BEGIN> This is included in the BEGIN tag </BEGIN>
<START> Here's some stuff and so is this more stuff.</START>
2
This has a null tag < And an extra line after the error
5
This has some good stuff <OKAY> and some bad stuff later on.
<GOOD> All is still okay, but later on we'll have an error. </GOOD>
We're still in the pink!
<THISISTOOLONG> This line will be skipped.
As will this one.
1
This is an interesting error: <ERROR
2
This one is okay <IN></IN>
1
Mismatch <START></STOP>
1
Missing start symbol: <OK></OK></NOTOK> more garbage...
1
<ELEVENChars>Both too long and invalid letter</ELEVENChars>
1
<ELEVENCHARS>Both too long and invalid letter</ELEVENCHARS>
1
<ELEVENCHARS!>Both too long and invalid letter</ELEVENCHARS!>
0
```

### 样例输出

```
Test Case 1
OK
Test Case 2
line 1: too many/few characters in tag name.
Test Case 3
line 3: too many/few characters in tag name.
Test Case 4
line 1: bad character in tag name.
Test Case 5
OK
Test Case 6
line 1: expected </START>
Test Case 7
line 1: no matching begin tag.
Test Case 8
line 1: bad character in tag name.
Test Case 9
line 1: bad character in tag name.
Test Case 10
line 1: too many/few characters in tag name.
```

---

## 题目分析

### 问题的本质

这是一个$\texttt{HTML/XML}$ 标签语法检查问题。需要验证标签的格式和嵌套正确性。

### 语法规则

1. 标签以 `<` 开头，以 `>` 结尾
2. 结束标签以 `</` 开头
3. 标签名由 $1$ 到 $10$ 个大写字母组成
4. 标签必须正确嵌套（先开后闭，后进先出）
5. 普通文本可以包含任意字符（包括空格、换行等）

### 错误类型

| 错误类型 | 触发条件 |
|----------|----------|
| `bad character in tag name` | 标签名中包含非大写字母字符（包括数字、小写字母、符号等） |
| `too many/few characters in tag name` | 标签名为空或长度超过 $10$ |
| `expected </xxxx>` | 遇到结束标签，但栈顶的起始标签名不匹配 |
| `no matching begin tag` | 遇到结束标签，但栈为空（没有对应的起始标签） |
| 文件结束标签未闭合 | 处理完所有行后栈非空 |

### 关键点

- 只报告**第一个**错误
- 检测到错误后，跳过当前测试用例的剩余行
- 标签名只包含大写字母 $A \sim Z$
- 标签名长度 $1 \sim 10$

---
## 参考代码

```cpp
// HTML Syntax Checking
// UVa ID: 342
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.070s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0;
    while (cin >> n, n)
    {
        // 跳过换行符，准备逐字符读取
        cin.ignore(1024, '\n');
        // 不跳过空白字符（以便读取空格和换行）
        cin.unsetf(ios::skipws);
        
        cout << "Test Case " << ++cases << endl;
        
        int lines = 1;           // 当前行号
        char letter;
        bool error = false;      // 是否已发生错误
        stack<string> tags;      // 标签栈，用于验证嵌套
        
        // 逐字符读取
        while (cin >> letter)
        {
            // 换行处理
            if (letter == '\n')
            {
                lines++;
                if (lines > n) break;  // 已读完当前测试用例的所有行
            }
            
            // 已发生错误，跳过剩余输入
            if (error) continue;
            
            // 遇到标签开始
            if (letter == '<')
            {
                string tag;
                bool closing = false;
                
                // 解析标签内容
                while (cin >> letter)
                {
                    if (letter == '\n')
                    {
                        // 标签未闭合（换行在 '>' 之前）
                        cout << "line " << lines << ": bad character in tag name." << endl;
                        error = true;
                        lines++;
                        break;
                    }
                    else if (letter == '/')
                    {
                        if (closing == false)
                        {
                            closing = true;
                            continue;
                        }
                        else
                        {
                            // 结束标签中出现第二个 '/'
                            cout << "line " << lines << ": bad character in tag name." << endl;
                            error = true;
                            break;
                        }
                    }
                    else if (letter == '>')
                    {
                        break;  // 标签结束
                    }
                    else if (letter < 'A' || letter > 'Z')
                    {
                        // 非大写字母
                        cout << "line " << lines << ": bad character in tag name." << endl;
                        error = true;
                        break;
                    }
                    
                    tag += letter;
                    
                    // 标签名过长
                    if (tag.length() > 10)
                    {
                        cout << "line " << lines << ": too many/few characters in tag name." << endl;
                        error = true;
                        break;
                    }
                }
                
                // 如果没有错误，验证嵌套
                if (error == false)
                {
                    // 空标签名
                    if (tag.length() == 0)
                    {
                        cout << "line " << lines << ": too many/few characters in tag name." << endl;
                        error = true;
                    }
                    else if (closing)
                    {
                        // 结束标签
                        if (tags.empty())
                        {
                            cout << "line " << lines << ": no matching begin tag." << endl;
                            error = true;
                        }
                        else if (tags.top() != tag)
                        {
                            cout << "line " << lines << ": expected </" << tags.top() << ">" << endl;
                            error = true;
                        }
                        else
                        {
                            tags.pop();
                        }
                    }
                    else
                    {
                        // 起始标签
                        tags.push(tag);
                    }
                }
                
                if (lines > n) break;
            }
        }
        
        // 文件结束，检查是否有未闭合的标签
        if (error == false && tags.empty() == false)
        {
            cout << "line " << (lines - 1) << ": expected </" << tags.top() << ">" << endl;
            error = true;
        }
        
        if (!error) 
            cout << "OK" << endl;
        
        // 恢复跳过空白字符的设置
        cin.setf(ios::skipws);
    }
    
    return 0;
}
```
