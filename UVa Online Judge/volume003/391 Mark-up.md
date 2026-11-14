[UVa 391 Mark-up](https://blog.csdn.net/metaphysis/article/details/161705432)

## 题目描述

标记语言是帮助格式化文本文件的计算机语言。特殊关键字用于标记文本，以控制字体、页面样式、段落样式等。$\texttt{TeX}$、$\texttt{troff}$ 和 $\texttt{HTML}$ 都是标记语言的例子。

拼写检查很难适应这些特殊文本。通常，必须创建特殊处理器或拼写检查器来适应标记语言。特殊处理器会识别标记语言并将其从文本中剥离，以便“纯”文本可以被拼写检查器处理。对于本题，你需要为一种小型标记语言编写这样的处理器，使程序的输出是不带标记的纯文本。

### 标记语言命令

每个标记命令以反斜杠 `\` 开头。如果 `\` 后面的字母不是下表中识别的命令，则该字母作为纯文本输出。例如，标记 `\\` 可用于打印单个 `\`。

| 命令 | 功能 |
|------|------|
| `\b` | 切换粗体字体开关（默认关闭） |
| `\i` | 切换斜体字体开关（默认关闭） |
| `\s` | 设置字体大小；`s` 后跟可选数字；如果省略数字，则恢复先前大小 |
| `\*` | 切换标记处理开关（默认开启）；如果关闭，则标记被视为文字文本 |

`\s` 命令后的数字可以包含小数点，因此 `12`、`9.5`、`11.` 和 `.5` 都是有效的数字。

### 输入与输出

输入文件是包含上述标记的纯文本。开始时，标记处理应开启。处理到文件结束。

### 样例输入

```
\s18. \bMARKUP sample\b\s

\*For bold statements use the \b command.\*

If you wish to \iemphasize\i something use the \i command.

For titles use \s14BIG\s font sizes, 14 points usually works well.

Remember that all of the commands toggle except for the \s command.
```

### 样例输出

```
MARKUP sample

For bold statements use the \b command.

If you wish to emphasize something use the \i command.
For titles use BIG font sizes, 14 points usually works well.
Remember that all of the commands toggle except for the \s command.
```

---

## 题目分析

### 问题的本质

这是一个**文本解析**问题。需要识别并处理以 `\` 开头的标记命令，输出纯文本内容。标记处理可以开关（`\*` 命令）。

### 命令处理规则

1. **`\b`**：切换粗体（不输出任何字符）
2. **`\i`**：切换斜体（不输出任何字符）
3. **`\s`**：设置字体大小（不输出任何字符）
   - 后跟可选数字（可能含小数点）
   - 如果数字缺失，恢复先前大小
4. **`\*`**：切换标记处理开关
5. **其他 `\x`**：输出 `x`（例如 `\\` 输出 `\`）
6. **非命令字符**：直接输出

### 处理状态

- `processing`：标记处理是否开启（默认 `true`）
- 当 `processing == false` 时，所有 `\` 后的字符都作为普通字符输出

---
## 参考代码

```cpp
// Mark-up
// UVa ID: 391
// Verdict: Accepted
// Submission Date: 2016-07-04
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    // 不跳过空白字符（保留空格和换行）
    cin.unsetf(ios::skipws);
    char current, next;
    bool processing = true;  // 标记处理开关，默认开启
    
    while (cin >> current)
    {
        if (current == '\\')
        {
            cin >> next;
            // 开关标记处理
            if (next == '*')
            {
                processing = !processing;
                continue;
            }
            
            // 处理开启时
            if (processing)
            {
                if (next == 'b' || next == 'i')
                {
                    continue;  // 切换格式，不输出
                }
                else if (next == 's')
                {
                    // 读取可选数字（可能含小数点）
                    bool pointEncountered = false;
                    while (cin >> next)
                    {
                        if (isdigit(next)) 
                            continue;
                        else if (next == '.' && !pointEncountered)
                        {
                            pointEncountered = true;
                            continue;
                        }
                        else
                        {
                            cin.putback(next);  // 将非数字字符放回
                            break;
                        }
                    }
                }
                else
                {
                    cout << next;  // 未知命令，输出字符本身
                }
            }
            else
            {
                // 处理关闭时，`\` 和后面的字符都作为普通文本输出
                cout << current;
                cin.putback(next);
            }
        }
        else
        {
            cout << current;
        }
    }
    
    return 0;
}
```
