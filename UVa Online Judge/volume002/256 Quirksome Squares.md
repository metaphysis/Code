[UVa 256 Quirksome Squares](https://blog.csdn.net/metaphysis/article/details/161283555)

## 题目描述

我们称一个具有偶数位 $2n$ 的数字为 **`quirksome number`**，如果将其十进制表示从中间分成两个长度为 $n$ 的字符串（允许前导零），然后计算这两个数字的和的平方，结果等于原数本身。

例如，$3025$ 是一个 $4$ 位 `quirksome number`，因为 $(30 + 25)^2 = 3025$。  
另一个例子是 $0001$，因为 $(00 + 01)^2 = 0001$。

题目要求：对于输入中给定的位数（只可能是 $2$、$4$、$6$、$8$），输出所有对应位数的 `quirksome numbers`，且输出时需要保持固定位数（包含前导零），并按照升序排列。

## 输入格式

输入文件包含若干行，每行一个数字，取自集合 $\{2, 4, 6, 8\}$，表示需要输出的数字的位数。

## 输出格式

对于输入文件中的每个位数，输出该位数下所有的 `quirksome numbers`，每个数字占一行，保持固定宽度（含前导零）。不同位数的输出顺序与输入顺序一致。

## 题目分析

### 数学转化

设一个数字有 $2n$ 位，将其从中间分开，前半部分为整数 $a$，后半部分为整数 $b$。根据定义，有：

$$
(a + b)^2 = 10^n \cdot a + b
$$

其中 $a$ 和 $b$ 的取值范围都是 $[0, 10^n - 1]$。

这是一个关于 $a$ 和 $b$ 的二次方程。我们可以将其改写为：

$$
(a + b)^2 - b = 10^n \cdot a
$$

或者更常用的形式是直接枚举 $a$ 和 $b$，但由于 $n$ 最大为 $4$（因为 $2n \leq 8$），$10^n \leq 10000$，所以直接枚举 $a$ 和 $b$ 是完全可行的，但更好的方法是枚举 $a + b$ 的值。

设 $s = a + b$，那么条件变为：

$$
s^2 = 10^n \cdot a + b
$$

同时 $b = s - a$，代入得：

$$
s^2 = 10^n \cdot a + (s - a) = a \cdot (10^n - 1) + s
$$

整理得：

$$
a = \frac{s^2 - s}{10^n - 1}
$$

由于 $a$ 必须是 $[0, 10^n - 1]$ 内的整数，因此 $10^n - 1$ 必须整除 $s^2 - s$，且计算出的 $a$ 和 $b = s - a$ 都应在合法范围内。

更简单的思路是直接枚举 $a$（或 $b$），然后检查 $(a + b)^2$ 是否等于 $10^n \cdot a + b$。由于 $10^n \leq 10000$，枚举量很小。

## 解题思路

### 方法一：枚举 $a + b$（推荐）

设 $n$ 为位数的一半（$n = 1, 2, 3, 4$）。枚举 $s$ 从 $0$ 到 $2 \times (10^n - 1)$，计算 $s^2$，然后：

1. 将 $s^2$ 转换为字符串，并在前面补零，使其总长度为 $2n$。
2. 取前 $n$ 个字符作为 $a$，后 $n$ 个字符作为 $b$。
3. 检查 $a + b$ 是否等于 $s$。如果相等，则该数字是一个 `quirksome number`。

这种方法非常直接，且易于实现。

### 方法二：枚举平方数

枚举所有可能的平方数 $n$（从 $0$ 到 $10^{2n} - 1$），然后判断 $\sqrt{n}$ 是否为整数，再判断拆分后的两数之和的平方是否等于 $n$。由于 $n$ 的枚举范围是 $10^{2n}$，对于 $n=8$ 位时是 $10^8$，在可接受范围内（但代码中 $n$ 的递增方式并不是逐个递增，而是利用了连续平方数的递推公式 $n = n + 2 \times start + 1$，这是一种高效枚举完全平方数的方法）。

在原代码中，`start` 和 `n` 的更新方式实际上是在枚举所有完全平方数：  
$(k+1)^2 = k^2 + 2k + 1$，所以从 $k=0$ 开始，每次加 $2k+1$ 就能得到下一个平方数。

然后对于每个平方数 $n$，它调用 `add(n, base)` 函数来检查是否满足 `quirksome` 性质。其中 `base = 10^n` 是分割的基数。
### 主程序逻辑

1. 初始化 `start = 0, n = 0, up = 100, base = 10`。
2. 对于 $i = 0, 1, 2, 3$（对应位数 $2, 4, 6, 8$）：
   - 循环枚举平方数 $n$，直到 $n < up$（$up$ 是当前位数下的最大值 $+1$）。
   - 对每个 $n$，检查是否是 `quirksome number`（通过 `add` 函数）。
   - 利用平方数递推公式更新 $n$。
   - 完成当前位数范围后，更新 `base` 和 `up` 进入下一个位数范围。
3. 最后读入输入，根据位数输出对应列表中的数字。

## 时间复杂度

由于 $8$ 位数对应的最大平方数候选不超过 $10^8$，而平方数的个数只有 $10^4$ 个（因为 $\sqrt{10^8} = 10^4$），所以整个预处理过程非常快。加上存储和输出，复杂度完全可以接受。

## 代码实现

```cpp
// Quirksome Squares
// UVa ID: 256
// Verdict: Accepted
// Submission Date: 2016-05-09
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 存储不同位数（2,4,6,8）对应的 quirksome numbers
// numbers[0] 对应 2 位，numbers[1] 对应 4 位，依此类推
vector<vector<string>> numbers(4);

// 检查数字 n 是否为 quirksome number
// base = 10^digits，用于分割数字的前后两部分
void add(int n, int base) {
    // 计算前半部分和后半部分
    string first = to_string(n / base), second = to_string(n % base);
    
    int digits = 1;  // 位数的一半，从 1 到 4
    while (digits < 5)
    {
        // 补前导零，使前半部分和后半部分长度都为 digits
        while (first.length() < digits)
            first = '0' + first;
            
        while (second.length() < digits)
            second = '0' + second;
        
        // 拼接得到完整的数字字符串
        string last = first + second;
        // 如果拼接后的数字等于原数 n，且长度正好是 2*digits，则符合条件
        if (n == stoi(last) && last.length() == digits * 2)
        {
            numbers[digits - 1].push_back(last);
        }
               
        digits++;
    }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    
    int start = 0, n = 0, up = 100, base = 10;
    // 依次处理 2,4,6,8 四种位数
    for (int i = 0; i < 4; i++)
    {
        // 枚举当前位数范围内的所有完全平方数
        // 利用完全平方数的递推公式：下一个平方数 = 当前数 + 2*start + 1
        while (n < up)
        {
            // 计算拆分后的两部分的和
            int temp = n / base + n % base;
            // 如果和平方等于原数，则是 quirksome number
            if (temp * temp == n)
                add(n, base);
            // 递推得到下一个平方数
            n = n + 2 * start + 1;
            start++;        
        }
        
        // 更新到下一个位数的起始值
        start = base;
        n = up;
        base *= 10;
        up = base * base;
    }
            
    int digits;
    while (cin >> digits)
    {
        // digits 是总位数（2,4,6,8），除以 2 得到半位数，再减 1 得到数组下标
        digits /= 2;
        digits--;
        
        // 输出对应位数的所有 quirksome numbers
        for (int i = 0; i < numbers[digits].size(); i++)
            cout << numbers[digits][i] << "\n";
    }
    
    return 0;
}
```

## 总结

本题的核心在于理解 `quirksome number` 的数学定义，并通过预处理所有可能的数字来高效回答多组查询。由于位数只有 $4$ 种可能，且每种位数的数字数量非常少，直接枚举平方数并判断拆分条件是简单而高效的做法。需要注意输出时保持固定宽度，前导零不能省略。
