[UVa 202 Repeating Decimals](https://blog.csdn.net/metaphysis/article/details/161006375)

## 题目分析

本题要求计算有理分数的循环小数表示，并找出循环节的长度。给定一个非负整数分子 $n$ 和正整数分母 $m$（均不超过 $3000$），需要输出分数的小数展开形式，以及循环节的长度。

题目对循环节的定义是：从小数点右侧开始，第一个最小的重复数字串，且该串无限重复且中间无其他数字。

输出格式要求：将分数写为 `a/b = 整数部分.小数部分` 的形式，循环节用括号括起。如果循环节开始位置在第 $50$ 位之后，或者整个循环节无法在 $50$ 位内完整显示，则在第 $50$ 位后输出 `...`。

## 解题思路

### 核心思想

求循环节的方法基于**长除法**（模拟手动除法）的原理。当我们用分子除以分母时，余数决定了下一步的计算。一旦某个余数重复出现，后续的计算过程就会循环，从小数点后第一次出现该余数的位置开始形成循环节。

### 算法步骤

1. **整数部分处理**：先计算整数部分 `n / m`，然后令 $n = n \bmod m$ 作为小数部分计算的起始余数。

2. **模拟除法生成小数**：不断将余数乘以 $10$ 后除以分母，得到下一位小数，并更新余数。由于分母最大为 $3000$，余数只有 $0$ 到 $m-1$ 共 $m$ 种可能，因此循环节的长度一定不超过 $m$。

3. **检测循环节**：在模拟过程中，使用数组 `position[r]` 记录余数 $r$ 首次出现的位置（即小数位数）。当某个余数 $r$ 第二次出现时，就找到了循环节：
   - 循环开始位置 = `position[r]`
   - 循环节长度 = 当前位置 - 循环开始位置

4. **输出格式**：
   - 如果余数为 $0$，说明分数是有限小数，循环节就是 `"0"`。
   - 输出时，只显示到第 $50$ 位或循环节第一次结束的位置。如果循环节开始后在第 $50$ 位内无法完整显示，则在第 $50$ 位后添加 `...`。

### 时间复杂度

由于分母 $m \leq 3000$，模拟过程最多进行 $3001$ 次就能找到循环节，时间复杂度为 $O(m)$，非常高效。

## 代码实现

```cpp
// Repeating Decimals
// UVa ID: 202
// Verdict: Accepted
// Submission Date: 2016-03-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int cycleLength;
string cycleText, startText;
int maxLength = 6000;

// 寻找循环节的函数，n 为余数，m 为分母
void findCycle(int n, int m) {
    string digits;  // 存储小数部分的所有数字

    // 生成足够多的小数位，以便寻找循环节
    while (digits.length() < maxLength) {
        n *= 10;
        // 处理中间出现的 0，例如 1/100 的情况
        while (n < m && digits.length() < maxLength) {
            n *= 10;
            digits.push_back('0');
        }

        // 得到下一位小数
        digits.push_back(n / m + '0');
        n %= m;  // 更新余数
    }

    int start = 0;
    // 从第 0 位开始尝试寻找循环节
    while (start < maxLength) {
        int length = 1;
        // 尝试不同的循环节长度，最大不超过 maxLength/2
        while (length < maxLength / 2) {
            int tempStart = start;
            int tempEnd = (maxLength - start) / length * length + start;

            bool good = true;
            // 检查从 start 开始，每隔 length 个字符是否重复
            while (tempStart + 2 * length <= tempEnd) {
                if (digits.substr(tempStart, length) ==
                    digits.substr(tempStart + length, length))
                    tempStart += length;
                else {
                    good = false;
                    break;
                }
            }

            // 找到循环节，且长度小于分母（合理的循环节长度）
            if (good && length < m) {
                cycleText = digits.substr(start, length);   // 循环节字符串
                cycleLength = length;                       // 循环节长度
                startText = digits.substr(0, start);        // 循环节前的部分
                return;
            }

            length++;
        }
        
        start++;
    }
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);

    int n, m;

    while (cin >> n >> m) {
        // 可以整除的情况，循环节为 0
        if (n % m == 0) {
            cout << n << "/" << m << " = " << (n / m) << ".(0)\n";
            cout << "   1";
        } else {
            // 寻找循环节，用余数 n % m 开始
            findCycle(n % m, m);

            cout << n << "/" << m << " = " << (n / m) << "." << startText << "(";

            // 如果循环节起始位置加上循环节长度超过 50，截断显示
            if ((cycleLength + startText.length()) > 50) {
                cout << cycleText.substr(0, 50 - startText.length());
                cout << "...";
            } else cout << cycleText;

            cout << ")\n";
            cout << "   " << cycleLength;
        }

        cout << " = number of digits in repeating cycle\n\n";
    }

	return 0;
}
```

## 总结

本题的关键在于理解循环小数的产生原理：余数重复是循环节出现的充分必要条件。通过模拟长除法并记录余数的首次出现位置，可以高效地找到循环节。输出格式要求较细，需要注意第 $50$ 位截断时的边界处理。
