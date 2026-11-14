[UVa 328 The Finite State Text-Processing Machine](https://blog.csdn.net/metaphysis/article/details/161513859)

## 题目描述

有限状态机（$\texttt{FSM}$）本质上是一个有向图。图中的每个节点称为**状态**；在 $\texttt{FSM}$ 执行过程中，其中一个状态是当前状态。两个状态之间的有向边称为**转移**。当条件满足时，当前状态的一个转移发生，当前状态变更为转移所指向的新状态。

在本题中，输入包含多个 $\texttt{FSM}$ 的描述。每个转移关联：
- 一个**输入字符集**（触发该转移的字符集合）
- 一个**输出字符串**（转移发生时打印）

当当前输入数据字符属于转移的输入集时，该转移发生，输出字符串被打印。

### 特殊符号

在输入集和输出字符串中，以下特殊构造可能出现：

| 符号 | 含义 |
|------|------|
| `\b` | 空格（`blank`） |
| `\n` | 换行符（`end of line`） |
| `\\` | 单个反斜杠 |
| `\0` | 不输出任何内容（仅输出字符串） |
| `\c` | 匹配任何字符（仅输入集）/打印当前输入字符（仅输出字符串） |

### 输入格式

输入由多对 {$\texttt{FSM}$ 描述, $\texttt{FSM}$ 的输入} 组成。

$\texttt{FSM}$ 描述：
- 第一行：状态数量 $n$
- 对于每个状态：
  - 状态名称
  - 从该状态出发的转移数量
  - 对于每个转移：
    - 输入字符集
    - 目标状态名称
    - 输出字符串

- 起始状态总是命名为 `START`
- 最终状态命名为 `END`（不在描述中出现）

$\texttt{FSM}$ 描述之后的第一完整行开始是输入字符，直到处理结束。

### 输出格式

对于每个 $\texttt{FSM}$，输出一行 `Finite State Machine X:`，然后下一行输出处理结果。

### 样例输入

```
1
START 3
AEIOUaeiou START \*
\n END \n
\c START \c
This is input for example one.
2
START 3
\c START \c
Xx SKIP \c
\n END \n
SKIP 4
AEIOU START \0
aeiou START \0
Xx SKIP \c
\n END \n
XaXxe Test Xio iXix0
3
START 12
\c START \c
! FINIS \0
A TWO a
E TWO e
I TWO i
O TWO o
U TWO u
a TWO A
e TWO E
i TWO I
o TWO O
u TWO U
TWO 4
\c TWO \c
AEIOU START \c
aeiou START \c
! FINIS \0
FINIS 2
\c FINIS \0
\n END \n
This is some data for FSM number 3. ! IGNORED
0
```

### 样例输出

```
Finite State Machine 1:
Th*s *s *np*t f*r *x*mpl* *n*.
Finite State Machine 2:
XXx Test Xo iXx
Finite State Machine 3:
ThIs is oMe dAta fOr FSM numbEr 3.
```

---

## 题目分析

### 问题的本质

这是一个**有限状态自动机**的模拟问题。需要：
1. 解析 $\texttt{FSM}$ 描述，构建状态转移表
2. 处理输入字符，模拟自动机运行
3. 按照转移规则输出相应字符串

### 关键难点

1. **输入集的表示**：输入集可以是多个字符的集合（如 `AEIOUaeiou`），也可以是 `\c`（匹配任何字符），也可以是转义序列
2. **优先级规则**：如果多个转移的输入集都包含当前字符，需要选择**最特定**的匹配（即普通字符优先于 `\c`）
3. **特殊字符处理**：`\b`、`\n`、`\\`、`\0`、`\c` 需要正确解析

### 输入集的匹配规则

从样例可以看出，匹配优先级为：
1. 首先精确匹配输入字符串（如 `"A"`、`"\n"` 等）
2. 然后检查是否属于某个字符集合（如 `"AEIOU"` 中的任意字符）
3. 最后考虑 `\c`（匹配任何字符）

在代码实现中，对于每个状态和当前输入字符，按以下顺序查找匹配的转移：
1. 精确匹配（`machine[current_state].count(input)`）
2. 遍历所有转移，检查输入集是否包含当前字符（需处理转义字符）
3. 查找 `\c` 转移

---
## 参考代码

```cpp
// The Finite State Text Processing Machine
// UVa ID: 328
// Verdict: Accepted
// Submission Date: 2016-07-07
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 转移结构体
struct transition
{
    string next_state;  // 目标状态
    string output;      // 输出字符串
};

// 状态转移表：当前状态 -> (输入集 -> 转移)
map<string, map<string, transition>> machine;

// 处理输出字符串中的转义序列
// output: 输出字符串
// input_char: 当前输入字符（用于 \c）
void display(string output, char input_char)
{
    int position = 0;
    while (position < output.length())
    {
        if (output[position] == '\\')
        {
            if (output[position + 1] == 'b')      // \b -> 空格
                cout << " ";
            else if (output[position + 1] == 'c') // \c -> 当前输入字符
                cout << input_char;
            else if (output[position + 1] == 'n') // \n -> 换行
                cout << endl;
            else if (output[position + 1] == '\\')// \\ -> 反斜杠
                cout << "\\";
            // \0 不输出任何内容
            position++;
        }
        else
            cout << output[position];
        position++;
    }
}

// 将输入字符转换为输入集表示形式
string getInput(char input)
{
    if (isblank(input))      // 空格
        return "\\b";
    else if (input == '\n')  // 换行
        return "\\n";
    else if (input == '\\')  // 反斜杠
        return "\\";
    else                     // 普通字符
        return string(1, input);
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    int n, cases = 0, state_number;
    string line, state_name, input, next_state, output;
    
    while (cin >> n)
    {
        if (n == 0) break;

        machine.clear();

        // 解析 FSM 描述
        for (int i = 1; i <= n; i++)
        {
            cin >> state_name >> state_number;

            while (cin >> input >> next_state >> output)
            {
                // 存储转移
                machine[state_name].insert(make_pair(input, (transition){next_state, output}));
                state_number--;
                if (state_number == 0)
                {
                    // 跳过该行剩余内容
                    cin.ignore(1024, '\n');
                    break;
                }
            }
        }

        cout << "Finite State Machine " << ++cases << ":" << endl;
        
        bool exit_processing = false;
        string current_state = "START";

        // 读取输入并处理
        while (getline(cin, line))
        {
            line += '\n';  // 每行末尾添加换行符
            
            for (int i = 0; i < line.length(); i++)
            {
                // 将当前字符转换为输入集表示
                input = getInput(line[i]);

                // 1. 精确匹配
                if (machine[current_state].count(input))
                {
                    display(machine[current_state][input].output, line[i]);
                    current_state = machine[current_state][input].next_state;
                }
                else
                {
                    bool transitionIsHere = false;
                    // 2. 遍历所有转移，检查输入集是否包含当前字符
                    for (auto pair : machine[current_state])
                    {
                        int position = pair.first.find(input);
                        // 需要处理转义字符的情况
                        if (position != pair.first.npos && 
                            (input.length() == 2 || position == 0 || pair.first[position - 1] != '\\'))
                        {
                            transitionIsHere = true;
                            display(pair.second.output, line[i]);
                            current_state = pair.second.next_state;
                            break;
                        }
                    }

                    // 3. 如果没有匹配，尝试 \c（匹配任何字符）
                    if (!transitionIsHere)
                    {
                        input = "\\c";
                        if (machine[current_state].count(input))
                        {
                            display(machine[current_state][input].output, line[i]);
                            current_state = machine[current_state][input].next_state;
                        }
                    }
                }
                
                // 到达 END 状态，停止处理
                if (current_state == "END")
                {
                    exit_processing = true;
                    break;
                }
            }
            
            if (exit_processing)
                break;
        }
    }

    return 0;
}
```
