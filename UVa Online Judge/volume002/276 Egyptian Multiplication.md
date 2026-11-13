[UVa 276 Egyptian Multiplication](https://blog.csdn.net/metaphysis/article/details/161333751)

## 题目分析

本题来源于著名的 **$\texttt{Rhind Papyrus}$**（莱因德纸草书），要求模拟古埃及人进行乘法运算的方法。古埃及人的数字系统没有零的概念，使用特定的符号表示不同的数位：

- $\texttt{|}$ 表示 $1$
- $\texttt{n}$ 表示 $10$
- $\texttt{9}$ 表示 $100$
- $\texttt{8}$ 表示 $1000$
- $\texttt{r}$ 表示 $10000$

数字的表示方式为：将对应数位的符号重复相应次数，并按照从高位到低位的顺序排列，每个数位的符号组后跟一个空格。例如，数字 $4023$ 表示为 `| | nn 8888`（注意：千位上的 $4$ 用 $\texttt{8888}$ 表示，百位是 $0$ 所以不写任何符号，十位是 $2$ 用 $\texttt{nn}$ 表示，个位是 $3$ 用 $\texttt{|||}$ 表示）。

古埃及人乘法运算的步骤为：

1. 建立两列数字，左列初始为 $1$，右列初始为被乘数 $a$。
2. 不断将两列的数字翻倍（通过复制符号并进位），直到左列的数字超过另一个乘数 $b$。
3. 在左列中标记出那些加起来等于 $b$ 的行（标记 $\texttt{*}$）。
4. 将这些行对应的右列数字相加，得到最终乘积。

## 解题思路

根据题目要求和古埃及乘法的运算规则，我们可以将问题分解为以下几个关键步骤：

### 1. 埃及数字与十进制整数的相互转换

由于我们需要进行翻倍运算和加法运算，最直接的方式是将埃及数字转换为十进制整数进行处理，计算完成后再将结果转换回埃及数字表示法进行输出。

**埃及数字 → 十进制整数**：

解析输入的字符串时，每个数字由若干个符号组组成，每个符号组由同一个符号重复若干次构成。我们只需：

- 用空格分割字符串，得到各个符号组
- 根据符号组的第一个字符确定其对应的数位值（$1$、$10$、$100$、$1000$ 或 $10000$）
- 用符号组的长度乘以该数位值，累加到结果中

例如，`nnn 99` 中，`nnn` 表示 $3 \times 10 = 30$，`99` 表示 $2 \times 100 = 200$，合计为 $230$。

**十进制整数 → 埃及数字**：

从个位开始逐位处理十进制数：

- 取当前位数字 $digitsCount = number \% 10$
- 若 $digitsCount > 0$，则将该位对应的符号重复 $digitsCount$ 次，后跟一个空格
- 将 $number$ 除以 $10$，继续处理下一位

需要注意：埃及数字的书写顺序是从高位到低位（千位、百位、十位、个位），而上述过程从个位开始构建，恰好得到从低位到高位的字符串。但由于最终输出时按照从高位到低位的顺序，我们需要将结果字符串反转吗？实际上不需要，因为我们在构建过程中是从高位向低位处理的——$number \% 10$ 得到的是个位，但我们将符号追加到字符串末尾，由于高位在后构建，最终字符串的顺序确实是从高位到低位吗？让我们仔细思考：

假设数字 $4023$，处理过程：
- 个位 $3$：`||| ` → 字符串为 `||| `
- 十位 $2$：`nn ` → 字符串为 `||| nn `
- 百位 $0$：跳过
- 千位 $4$：`8888 ` → 字符串为 `||| nn 8888 `

观察结果：个位符号组在前，千位符号组在后，这与题目要求的从高位到低位的顺序相反。实际上，题目示例 `"| | nn 8888"` 的顺序是千位（`8888`）、百位（空）、十位（`nn`）、个位（`|||`）。因此我们需要将构建的字符串反转，或者从高位向低位构建。

### 2. 模拟古埃及乘法的翻倍过程

古埃及乘法的本质是**二进制分解**：将乘数 $b$ 表示为 $2$ 的幂次之和。对于 $a \times b$，我们不断将 $1$（左列）和 $a$（右列）翻倍，左列实际上就是 $2^0, 2^1, 2^2, \dots$，右列对应 $a \times 2^0, a \times 2^1, a \times 2^2, \dots$。然后选择那些左列值之和等于 $b$ 的行（即 $b$ 的二进制表示中为 $1$ 的位），将对应右列值相加得到结果。

具体实现时，我们不需要真的构建两列并不断翻倍直到超过 $b$，而是可以直接利用整数的二进制表示：

- 设 $left = 1$，$right = a$，$result = a \times b \pmod{100000}$
- 当 $b > 0$ 时循环：
  - 取 $b$ 的最低位 $bit = b \% 2$
  - 输出当前行的左列数字 $left$ 和右列数字 $right$
  - 若 $bit = 1$，在左列数字后添加标记 $\texttt{*}$
  - 左列翻倍：$left = left \times 2$
  - 右列翻倍：$right = right \times 2$
  - $b$ 右移一位：$b = b / 2$

注意：右列翻倍时，$right$ 的值可能会超过 $100000$，但由于最终结果需要模 $100000$，且翻倍过程中的右列数字也需要用埃及数字输出，所以 $right$ 应保持实际值（不取模），以保证埃及数字表示的正确性。但题目要求最终结果模 $100000$，所以 $result$ 计算时取模。

### 3. 输出格式控制

题目对输出格式有严格要求：

- 左列数字左对齐，右列数字从第 $35$ 个字符位置开始
- 如果有 $\texttt{*}$ 标记，与左列数字之间用一个空格分隔
- 左列数字（包括可能的 $\texttt{*}$ 和空格）占据前 $34$ 个字符位置（不足时填充空格）
- 每个数字的符号组之间用空格分隔，最后一个符号组后也要跟一个空格

使用 `C++` 的 `setw()` 和 `left` 操纵符可以方便地实现宽度控制：`cout << setw(34) << left << text;` 这会将 `text` 左对齐输出在宽度为 $34$ 的字段中，右侧用空格填充。

### 4. 特殊情况处理

- 输入以空行结束，需要逐行读取并判断
- 乘数和被乘数均为非零数
- 结果需要模 $100000$，即只输出低 $5$ 位（万位及以下）

## 算法复杂度

- 每个数字的转换时间复杂度为 $O(L)$，其中 $L$ 为埃及数字字符串的长度
- 乘法模拟的时间复杂度为 $O(\log b)$，即 $b$ 的二进制位数
- 整体时间复杂度对于题目给定的数据范围完全足够

## 代码实现

```cpp
// Egyptian Multiplication
// UVa ID: 276
// Verdict: Accepted
// Submission Date: 2016-05-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 符号到数值的映射表
map<char, int> value;

// 初始化映射表：将埃及符号映射到对应的十进制数值
void initialize()
{
    value.insert(make_pair('|', 1));   // 个位，1
    value.insert(make_pair('n', 10));  // 十位，10
    value.insert(make_pair('9', 100)); // 百位，100
    value.insert(make_pair('8', 1000)); // 千位，1000
    value.insert(make_pair('r', 10000)); // 万位，10000
}

// 将埃及数字字符串转换为十进制整数
int getNumber(string text)
{
    int number = 0;
    string digits;
    istringstream iss(text);
    // 按空格分割，每个部分是一个符号组（如 "nnn" 或 "99"）
    while (iss >> digits)
        // 符号组的长度 * 该符号代表的数值，累加得到十进制数
        number += digits.length() * value[digits.front()];
    return number;
}

// 将十进制整数转换为埃及数字字符串
string displayNumber(int number)
{
    // digits 数组索引 0~4 分别对应个位到万位的符号
    string digits = "|n98r", text;
    int index = 0;
    bool first = true;
    // 从个位开始逐位处理
    while (number > 0)
    {
        int digitsCount = number % 10;  // 获取当前位的数值
        if (digitsCount > 0)
        {
            // 重复该位对应的符号 digitsCount 次
            for (int i = 1; i <= digitsCount; i++)
                text += digits[index];
            text += " ";  // 每个符号组后跟一个空格
        }
        number /= 10;  // 处理下一位
        index++;
    }
    return text;
}

// 执行埃及乘法
void multiplicate(string first, string second)
{
    int a, b;
    
    // 将输入的埃及数字转换为十进制整数
    a = getNumber(first);
    b = getNumber(second);
    
    // left: 左列数字（初始为 1）
    // right: 右列数字（初始为 a）
    // result: 最终乘积（模 100000）
    int leftNumber = 1, rightNumber = a, result = (a * b) % 100000;
    
    // 模拟二进制分解过程
    while (b > 0)
    {
        int bit = b % 2;  // 获取 b 的当前最低位
        
        // 生成左列数字的埃及表示
        string text = displayNumber(leftNumber);
        if (bit > 0)
            text += "*";  // 若该位为 1，添加标记
        // 左对齐输出，宽度为 34 个字符
        cout << setw(34) << left << text;
        
        // 输出右列数字（当前左列值乘以 a）
        cout << displayNumber(leftNumber * rightNumber) << endl;
        
        // 翻倍：左列和右列同时乘以 2
        leftNumber *= 2;
        b /= 2;  // b 右移一位
    }
    
    // 输出最终结果
    cout << "The solution is: " << displayNumber(result) << endl;
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    initialize();  // 初始化符号映射表
    
    string first, second;
    // 逐行读取，直到遇到空行
    while (getline(cin, first), first.length() > 0)
    {
        getline(cin, second);
        multiplicate(first, second);
    }
    
    return 0;
}
```

## 总结

本题的核心在于理解古埃及乘法的本质——二进制分解，并将这一过程用程序模拟出来。通过将埃及数字与十进制整数相互转换，我们能够方便地进行翻倍运算和加法运算。输出格式的控制（左列宽度 $34$、右列起始位置 $35$）是另一个需要注意的细节。掌握了这些要点，就能顺利解决本题。
