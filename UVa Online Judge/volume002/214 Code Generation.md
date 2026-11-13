[UVa 214 Code Generation](https://blog.csdn.net/metaphysis/article/details/161046423)

## 题目分析

本题要求为 **$\texttt{SIC}$** 模拟机（$\texttt{Simplified Instructional Computer}$）生成汇编代码。输入为合法的后缀表达式（操作数为单个字母，运算符为 `+`、`-`、`*`、`/` 及一元取负 `@`），输出对应的汇编指令。目标机器只有一个寄存器，指令集包括：

- `L`：加载操作数到寄存器
- `A`：寄存器加操作数
- `S`：寄存器减操作数
- `M`：寄存器乘操作数
- `D`：寄存器除操作数
- `N`：寄存器取负
- `ST`：寄存器内容存到临时变量

临时变量形式为 `$n`（$n$ 为单个数字），由汇编器分配。

## 解题思路

题目有两条关键约束：

1. **遇到运算符立即生成代码**（在线处理）
2. **尽量少用临时变量**，且为每个运算符生成最少指令

### 核心思想

由于只有 **$1$** 个寄存器，且后缀表达式天然对应栈求值顺序，可以维护以下状态：

- `previousOperand`：当前寄存器中是否“暂存”了一个未使用的操作数（即该操作数已加载但尚未参与运算）
- `valueInStack`：当前寄存器的值是否已被存入临时变量（用于处理连续操作数的情况）

处理每个输入字符时：

#### 1. 操作数（字母）
- 若已有暂存操作数，需先将其存入临时变量（如果值已在寄存器中）
- 加载新操作数到寄存器

#### 2. 二元运算符（`+` `-` `*` `/`）
- 若 `previousOperand` 非空，说明右操作数已在寄存器中，直接执行运算
- 否则，右操作数来自临时变量的栈顶，从临时栈中取出并运算

**特殊处理减法**：由于只有 **$1$** 个寄存器，`A - B` 需要先取负再加，即 `N` + `A $n`。

**特殊处理除法**：`A / B` 需要将寄存器中的值暂存，加载被除数，再执行除法，涉及 **$2$** 个临时变量。

#### 3. 一元取负（`@`）
- 若寄存器有暂存操作数，先存入临时变量，再加载操作数
- 执行 `N` 指令

### 临时变量管理
使用计数器 `storage` 分配临时变量。当需要栈顶临时变量时，先递减 `storage` 再使用，模拟栈的 **$\texttt{LIFO}$** 行为，确保最少使用临时变量。

### 示例验证
对于输入 `AB+CD+EF++GH+++`，输出与题目样例完全一致。

---

## 代码实现（含注释）

```cpp
// Code Generation
// UVa ID: 214
// Verdict: Accepted
// Submission Date: 2016-04-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int storage;          // 临时变量计数器，从 0 开始分配 $0, $1, $2...
char previousOperand; // 暂存的操作数（尚未参与运算）
bool valueInStack;    // 寄存器的值是否已被存入临时变量

// 处理一个输入字符（操作数或运算符）
void processInput(char input) {
    // 一元取负运算符 @
    if (input == '@')
    {
        // 若存在暂存操作数，先处理暂存
        if (previousOperand)
        {
            if (valueInStack)
            {
                cout << "ST $" << storage++ << endl;
            }
            cout << "L " << previousOperand << endl;
            previousOperand = 0;
            valueInStack = true;
        }
        cout << "N" << endl;
    }
    // 加法运算符 +
    else if (input == '+')
    {
        if (previousOperand)
        {
            // 右操作数为暂存的字母，直接相加
            cout << "A " << previousOperand << endl;
            previousOperand = 0;
        }
        else
            // 右操作数来自临时变量栈顶
            cout << "A $" << --storage << endl;
    }
    // 减法运算符 -（需转换为 N + A）
    else if (input == '-')
    {
        if (previousOperand)
        {
            cout << "S " << previousOperand << endl;
            previousOperand = 0;
        }
        else
            // 寄存器中为右操作数，被减数在栈顶：先取负再加
            cout << "N" << endl << "A $" << --storage << endl;
    }
    // 乘法运算符 *
    else if (input == '*')
    {
        if (previousOperand)
        {
            cout << "M " << previousOperand << endl;
            previousOperand = 0;
        }
        else
            cout << "M $" << --storage << endl;
    }
    // 除法运算符 /（需要两个临时变量）
    else if (input == '/')
    {
        if (previousOperand)
        {
            cout << "D " << previousOperand << endl;
            previousOperand = 0;
        }
        else
        {
            // 寄存器中为右操作数，被除数在栈顶
            // 先将右操作数暂存，加载被除数，再执行除法
            cout << "ST $" << storage++ << endl;
            cout << "L $" << storage - 2 << endl;
            cout << "D $" << --storage << endl;
            storage--;  // 调整临时变量计数
        }
    }
    // 操作数（字母）
    else
    {
        // 若已有暂存操作数，需先存入临时变量
        if (previousOperand)
        {
            if (valueInStack)
            {
                cout << "ST $" << storage++ << endl;
            }
            cout << "L " << previousOperand << endl;
            valueInStack = true;
        }
        previousOperand = input;
    }
}

int main() {
    bool first = true;
    string input;

    while (cin >> input) {
        // 每两个表达式之间输出一个空行
        if (first)
            first = false;
        else
            cout << endl;

        // 初始化状态
        storage = 0;
        previousOperand = 0;
        valueInStack = false;

        // 逐字符处理表达式
        for (int i = 0; i < input.size(); i++)
            processInput(input[i]);
        // 表达式结束，处理剩余暂存操作数
        processInput(0);
    }

    return 0;
}
```

## 总结

本题的核心在于模拟单寄存器机器的后缀表达式求值过程，通过维护 `previousOperand` 和 `valueInStack` 两个状态变量，在遇到运算符时判断操作数来源（寄存器中的暂存操作数还是临时变量的栈顶），从而生成最少指令且最少使用临时变量的汇编代码。对减法和除法的特殊处理是该题的关键难点。
