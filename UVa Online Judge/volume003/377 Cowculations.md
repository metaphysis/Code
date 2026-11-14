[UVa 377 Cowculations](https://blog.csdn.net/metaphysis/article/details/161642581)


## 题目描述

一种原始的奶牛文化被著名人类学家 $\texttt{Dr. Bo Vine}$ 发现。在达拉斯附近的某片牧场上出土了数百块计算石板。$\texttt{Dr. Vine}$ 在意识到它们代表数学计算后，成功破译了这些石板的秘密。他说：“我一直怀疑奶牛比它们让我们认为的更聪明，这就是证据。重大突破是认识到它们不能用牛蹄数数，但能用蹄子思考。但现在我有数百块石板，需要帮助验证我的假设。”

编写程序帮助 $\texttt{Dr. Vine}$ 验证他的假设。

### 石板格式

每块石板包含 $6$ 行：
- 第 $1$ 行：第一个奶牛数字（$5$ 个符号）
- 第 $2$ 行：第二个奶牛数字（$5$ 个符号）
- 第 $3$、$4$、$5$ 行：三个操作（每个操作一个符号）
- 第 $6$ 行：结果数字（$8$ 个符号）

### 符号系统

奶牛数字使用四种符号：`V`、`U`、`C`、`D`，表示数字 $0$、$1$、$2$、$3$。每个数字实际上是四进制表示，但符号顺序是**从左到右**（最高位在左）。

例如：
- `VVVVV` = $0$
- `VVVVU` = $1$
- `VVVUV` = $4$（因为 `U` 在倒数第二位）

### 操作

- **`A`**（加法）：$Num_2 = Num_1 + Num_2$（使用给定的加法表，考虑进位）
- **`R`**（右移）：$Num_2$ 右移一位，最右边符号丢失，最左边补 `V`（$0$）
- **`L`**（左移）：$Num_2$ 左移一位，最左边符号保留，最右边补 `V`（$0$）
- **`N`**（空操作）：$Num_2$ 不变

### 加法表

加法表定义了两位符号相加的结果和进位。例如：
- `U A V` = `U`（结果），进位为 `U`（$1$）
- `C A C` = `V`（$0$），进位为 `U`（$1$）

### 验证过程

初始时 $Num_1$ = 第 $1$ 行数字，$Num_2$ = 第 $2$ 行数字。依次应用三个操作。最终 $Num_2$ 应与第 $6$ 行数字匹配（第 $6$ 行数字总是 $8$ 位，如位数不足则在左边补 `V`）。

---

## 题目分析

### 问题的本质

这是一个**四进制计算器模拟**问题。需要：
1. 将奶牛数字（`V`、`U`、`C`、`D`）转换为整数
2. 模拟加法（使用给定的加法表）和移位操作
3. 将最终结果与预期结果比较

### 四进制转换

`V` = $0$，`U` = $1$，`C` = $2$，`D` = $3$。字符串从左到右是高位到低位。

转换公式：
```
value = value * 4 + digit
```

### 加法实现

加法表可以编码为两个 $4 \times 4$ 的矩阵：
- 结果矩阵：`result[dig1][dig2]`
- 进位矩阵：`carry[dig1][dig2]`

```cpp
int addResult[4][4] = {
    {0,1,2,3},  // V+V=V, V+U=U, V+C=C, V+D=D
    {1,2,3,0},  // U+V=U, U+U=C, U+C=D, U+D=V
    {2,3,0,1},  // C+V=C, C+U=D, C+C=V, C+D=U
    {3,0,1,2}   // D+V=D, D+U=V, D+C=U, D+D=C
};

int addCarry[4][4] = {
    {0,0,0,0},  // V...
    {0,0,0,1},  // U+D 产生进位
    {0,0,1,1},  // C+C 和 C+D 产生进位
    {0,1,1,1}   // D+U、D+C、D+D 产生进位
};
```

### 移位实现

- **右移**：`number2 / 4`（因为四进制，右移一位相当于除以 $4$）
- **左移**：`number2 * 4`（左移一位相当于乘以 $4$）

### 结果比较

最终 $Num_2$ 需要与第 $6$ 行数字比较。第 $6$ 行总是 $8$ 位，但 $Num_2$ 可能不足 $8$ 位，需要在左边补 `V`（$0$）后比较。

实际上，由于 $Num_2$ 是整数，将其转换为四进制字符串，左边补零（`V`）到 $8$ 位，然后与输入字符串比较。

---
## 参考代码

```cpp
// Cowculations
// UVa ID: 377
// Verdict: Accepted
// Submission Date: 2016-06-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

map<char, int> digits;

// 将奶牛数字字符串转换为整数
int getNumber(string& text)
{
    int value = 0;
    for (auto c : text)
        value = value * 4 + digits[c];
    return value;
}

// 模拟操作
int cowculation(int number1, int number2, string& op)
{
    if (op == "A") return number1 + number2;
    if (op == "R") return number2 / 4;
    if (op == "L") return number2 * 4;
    return number2;  // 'N'
}

// 将整数转换为 8 位奶牛数字字符串
string toString(int value)
{
    string result(8, 'V');  // 初始全为 V（0）
    int idx = 7;
    while (value > 0)
    {
        switch (value % 4)
        {
            case 0: result[idx] = 'V'; break;
            case 1: result[idx] = 'U'; break;
            case 2: result[idx] = 'C'; break;
            case 3: result[idx] = 'D'; break;
        }
        value /= 4;
        idx--;
    }
    return result;
}

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    
    int n;
    string line;
    getline(cin, line);
    n = stoi(line);

    // 建立符号到数字的映射
    digits['V'] = 0, digits['U'] = 1, digits['C'] = 2, digits['D'] = 3;
    
    cout << "COWCULATIONS OUTPUT" << endl;
    
    string text1, text2, text3, op1, op2, op3;
    for (int i = 1; i <= n; i++)
    {
        getline(cin, text1);
        getline(cin, text2);
        getline(cin, op1);
        getline(cin, op2);
        getline(cin, op3);
        getline(cin, text3);
        
        int number1 = getNumber(text1);
        int number2 = getNumber(text2);
        int number3 = getNumber(text3);

        // 依次应用三个操作
        number2 = cowculation(number1, number2, op1);
        number2 = cowculation(number1, number2, op2);
        number2 = cowculation(number1, number2, op3);

        // 比较结果
        if (toString(number2) == text3)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    
    cout << "END OF OUTPUT" << endl;
    
    return 0;
}
```
