[UVa 337 Interpreting Control Sequences](https://blog.csdn.net/metaphysis/article/details/161545062)

## 题目描述

几乎所有文本模式终端都是专用的计算机系统，包含串行端口、键盘、$\texttt{CRT}$、微处理器、$\texttt{RAM}$ 和 $\texttt{ROM}$ 中的控制程序。

当字符到达终端时（无论是来自键盘还是串行端口），终端的软件将其分类为**显示字符**（将显示在 $\texttt{CRT}$ 上）或**控制序列引入字符**。控制序列用于指示终端执行诸如清屏、移动光标、更改字体等操作。

在本题中，假设你在为一个具有 $10$ 行 $10$ 列显示屏的小型终端编写软件。行和列编号为 $0$ 到 $9$。控制序列的引入字符是 **`^`**（脱字符）。紧随控制序列引入符的字符（或两个字符）将指示软件执行特殊功能。

### 控制序列列表

| 序列 | 功能 |
|------|------|
| `^b` | 将光标移动到当前行的开头；光标行不变 |
| `^c` | 清空整个屏幕；光标行和列不变 |
| `^d` | 如果可能，将光标向下移动一行；光标列不变 |
| `^e` | 擦除光标行上从光标列开始到行尾的字符；光标行和列不变 |
| `^h` | 将光标移动到 $(0,0)$；屏幕内容不变 |
| `^i` | 进入插入模式 |
| `^l` | 如果可能，将光标向左移动一列；光标行不变 |
| `^o` | 进入覆盖模式 |
| `^r` | 如果可能，将光标向右移动一列；光标行不变 |
| `^u` | 如果可能，将光标向上移动一行；光标列不变 |
| `^^` | 在当前光标位置写入一个脱字符（`^`），就像它不是特殊字符一样；受当前模式影响 |
| `^##` | 将光标移动到指定行和列；`#` 表示十进制数字，第一个 `#` 是新行号，第二个 `#` 是新列号 |

### 显示字符处理

- **覆盖模式**（初始模式）：接收的字符替换光标位置的字符
- **插入模式**：光标位置及右侧的字符向右移动一列，新字符放置在光标位置；光标行最右侧的字符丢失
- 无论何种模式，光标都会向右移动一列（如果可能）

### 输入格式

输入包含多个测试用例。每个测试用例以一行包含整数 $N$ 开始。接下来 $N$ 行数据，每行的每个字符按读取顺序输入终端软件。输入数据中不含制表符，行结束符应被忽略。空白字符是正常的显示字符。最后一个测试用例后跟一行包含整数 `0`。

每个测试用例开始时，屏幕是空的（全部为空格），终端处于覆盖模式，光标在 $(0,0)$。

### 输出格式

对于每个测试用例，输出一行用例编号，然后将屏幕图像用“框”包围输出，格式如样例所示。

### 样例输入

```
7
This is bad^h^c
^05^^
^14/ \^d^b
/
\
^u^d^d^l^l^l^l^l^l^l^l^l
^r^r< ACM >^l^l^d/^b
\
^b^d
\ /
^d^l^lv
7
^i9^l8^l7^l6^l5^l4^l3^l2^l1^l0
^o^d^lThis is #1^d^bThis is #2
^d^bThis is #3^d^bThis is #4
^d^bThis is #5^d^bThis is #6
^d^bThis is #7^d^bThis is #8
^i^d^bThis is #9^d^bThis is #10
^54^e Hello^d^l^l^l^lWorld
0
```

### 样例输出

```
Case 1
+----------+
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
+----------+
Case 2
+----------+
|0123456789|
|This is #1|
|This is #2|
|This is #3|
|This is #4|
|This Hello|
|This World|
|This is #7|
|This is #8|
|This is #0|
+----------+
```

---

## 题目分析

### 问题的本质

这是一个**终端模拟器**的实现问题。需要模拟一个 $10 \times 10$ 的字符终端，处理：
1. 普通字符的显示（覆盖/插入模式）
2. 控制序列的执行（光标移动、清屏、擦除、模式切换等）

### 终端状态

需要维护三个状态：
- **屏幕内容**：$10 \times 10$ 的字符数组，初始全为空格
- **光标位置**：`(row, column)`，初始为 $(0,0)$
- **模式**：覆盖模式（$\texttt{OVERWRITE}$）或插入模式（$\texttt{INSERT}$），初始为覆盖模式

### 控制序列解析

解析输入的字符流，遇到 `^` 时，开始解析控制序列：
- 如果下一个字符是 `^`，则表示显示一个脱字符
- 如果下一个字符是数字（`0`~`9`），则表示 `^##` 格式，读取两个数字作为新坐标
- 否则，根据控制字符执行对应操作

### 插入模式的实现

在插入模式下，向光标位置插入字符时，需要将光标位置及右侧的字符向右移动一列：

```cpp
for (int c = 9; c > column; c--)
    bitmap[row][c] = bitmap[row][c - 1];
bitmap[row][column] = character;
```

### 光标移动边界

光标不能移出屏幕范围（$0 \leq row \leq 9$，$0 \leq column \leq 9$）。

---

## 参考代码

```cpp
// Interpreting Control Sequences
// UVa ID: 337
// Verdict: Accepted
// Submission Date: 2016-07-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int OVERWRITE = 1, INSERT = 2;
char bitmap[10][10];   // 屏幕内容
int mode = OVERWRITE;  // 当前模式
int row = 0, column = 0;  // 光标位置

// 覆盖模式：直接替换光标处字符
void overwrite(char character)
{
    bitmap[row][column] = character;
}

// 插入模式：将光标及右侧字符右移，然后放入新字符
void insert(char character)
{
    for (int c = 9; c > column; c--)
        bitmap[row][c] = bitmap[row][c - 1];
    bitmap[row][column] = character;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n, cases = 0;
    string line;

    while (getline(cin, line))
    {
        n = stoi(line);
        if (n == 0)
            break;
        
        // 初始化终端状态
        mode = OVERWRITE;
        row = 0;
        column = 0;
        memset(bitmap, ' ', sizeof(bitmap));
        
        // 处理 N 行输入
        for (int i = 1; i <= n; i++)
        {
            getline(cin, line);
            int position = 0;
            while (position < line.length())
            {
                if (line[position] == '^')
                {
                    position++;  // 跳过 '^'
                    if (line[position] == 'b')
                    {
                        column = 0;
                    }
                    else if (line[position] == 'c')
                    {
                        memset(bitmap, ' ', sizeof(bitmap));
                    }
                    else if (line[position] == 'd')
                    {
                        row = row < 9 ? (row + 1) : row;
                    }
                    else if (line[position] == 'e')
                    {
                        for (int c = column; c <= 9; c++)
                            bitmap[row][c] = ' ';
                    }
                    else if (line[position] == 'h')
                    {
                        row = 0, column = 0;
                    }
                    else if (line[position] == 'i')
                    {
                        mode = INSERT;
                    }
                    else if (line[position] == 'l')
                    {
                        column = column > 0 ? (column - 1) : column;
                    }
                    else if (line[position] == 'o')
                    {
                        mode = OVERWRITE;
                    }
                    else if (line[position] == 'r')
                    {
                        column = column < 9 ? (column + 1) : column;
                    }
                    else if (line[position] == 'u')
                    {
                        row = row > 0 ? (row - 1) : row;
                    }
                    else if (line[position] == '^')
                    {
                        // 显示脱字符
                        if (mode == OVERWRITE)
                            overwrite('^');
                        else
                            insert('^');
                        column = column < 9 ? (column + 1) : column;
                    }
                    else
                    {
                        // ^## 格式：移动到指定位置
                        row = line[position] - '0';
                        position++;
                        column = line[position] - '0';
                    }
                }
                else
                {
                    // 普通字符
                    if (mode == OVERWRITE)
                        overwrite(line[position]);
                    else
                        insert(line[position]);
                    column = column < 9 ? (column + 1) : column;
                }

                position++;
            }
        }

        // 输出结果
        cout << "Case " << ++cases << endl;
        cout << "+----------+" << endl;
        for (int i = 0; i < 10; i++)
        {
            cout << '|';
            for (int j = 0; j < 10; j++)
                cout << bitmap[i][j];
            cout << '|' << endl;
        }
        cout << "+----------+" << endl;
    }

    return 0;
}
```
