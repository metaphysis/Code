[UVa 268 Double Trouble](https://blog.csdn.net/metaphysis/article/details/161309742)

## 题目分析

### 问题描述

本题要求我们在给定的进制 $p$ 下，寻找最小的 “$\texttt{double-trouble}$” 数。所谓 $\texttt{double-trouble}$ 数，是指将一个数的最后一位数字移动到最前面（即右旋转一位）后，得到的新数恰好是原数的两倍。

例如，在十进制（$p = 10$）中，数 $X = 421052631578947368$ 就是一个 $\texttt{double-trouble}$ 数，因为 $2X = 842105263157894736$，而后者正是将 $X$ 的最后一位数字 $8$ 移动到最前面得到的。

需要注意的是，在二进制（$p = 2$）中，最小的 $\texttt{double-trouble}$ 数是 $01$（而不是 $1$），因为前导零是必要的——右旋转后得到 $10$，而 $10_2 = 2_{10}$ 恰好是 $01_2 = 1_{10}$ 的两倍。前导零的存在保证了旋转后数字的位数不变。

### 输入输出格式

- **输入**：多个测试用例，每行一个整数 $p$（$2 \leq p < 200$），以文件结束符结束。
- **输出**：对于每个 $p$，按指定格式输出最小的 $\texttt{double-trouble}$ 数。每个数字（包括前导零）用十进制表示，数字之间用单个空格分隔。

### 样例分析

**输入**：
```
2
10
35
```

**输出**：
```
For base 2 the double-trouble number is
0 1
For base 10 the double-trouble number is
0 5 2 6 3 1 5 7 8 9 4 7 3 6 8 4 2 1
For base 35 the double-trouble number is
11 23
```

## 解题思路

### 数学建模

设我们在 $p$ 进制下寻找最小的 $\texttt{double-trouble}$ 数。记这个数为 $X$，其长度为 $n$（即 $n$ 位数字）。由于可能存在前导零，$X$ 的每一位数字 $d_{n-1}, d_{n-2}, \dots, d_0$ 都满足 $0 \leq d_i \leq p-1$，且 $d_{n-1}$ 可能为零。

将 $X$ 右旋转一位后得到的新数为：

$$
X' = d_0 \cdot p^{n-1} + d_{n-1} \cdot p^{n-2} + \dots + d_1
$$

根据 $\texttt{double-trouble}$ 的定义，有：

$$
X' = 2X
$$

而 $X$ 本身可以表示为：

$$
X = d_{n-1} \cdot p^{n-1} + d_{n-2} \cdot p^{n-2} + \dots + d_0
$$

### 建立等式

将 $X'$ 与 $2X$ 的关系用数学式子表达。注意 $X'$ 也可以从 $X$ 通过运算得到：

$$
X' = (X - d_0) / p + d_0 \cdot p^{n-1}
$$

这个公式的含义是：去掉 $X$ 的最后一位 $d_0$，将剩下的数除以 $p$（相当于右移一位），然后加上 $d_0$ 乘以 $p^{n-1}$（将其放在最高位）。

于是有：

$$
\frac{X - d_0}{p} + d_0 \cdot p^{n-1} = 2X
$$

两边同时乘以 $p$：

$$
X - d_0 + d_0 \cdot p^n = 2pX
$$

整理得：

$$
d_0 \cdot (p^n - 1) = (2p - 1)X
$$

即：

$$
X = \frac{d_0 \cdot (p^n - 1)}{2p - 1}
$$

由于 $X$ 必须是整数，因此 $(2p - 1) \mid d_0 \cdot (p^n - 1)$。又因为 $d_0$ 是 $X$ 的最后一位数字，且 $X' = 2X$ 的最高位是 $d_0$，$2X$ 的最高位不可能为零，所以 $d_0 \neq 0$。因此 $d_0$ 的取值范围是 $1 \leq d_0 \leq p-1$。

### 确定位数 $n$

我们需要找到最小的 $X$，即位数 $n$ 最小的数。对于给定的 $p$，我们从最小的 $n$ 开始尝试，看是否存在 $d_0 \in [1, p-1]$ 使得 $X$ 为整数且每一位数字都在 $0$ 到 $p-1$ 之间。

从上述公式可得：

$$
X = \frac{d_0 \cdot (p^n - 1)}{2p - 1}
$$

令 $m = 2p - 1$，则：

$$
X = \frac{d_0 \cdot (p^n - 1)}{m}
$$

为了 $X$ 是整数，需要 $m \mid d_0 \cdot (p^n - 1)$。由于 $d_0 < p$，而 $m = 2p - 1 > p$（当 $p \geq 2$ 时），$d_0$ 和 $m$ 不一定互质。但我们可以利用同余式：

$$
d_0 \cdot (p^n - 1) \equiv 0 \pmod{m}
$$

即：

$$
d_0 \cdot p^n \equiv d_0 \pmod{m}
$$

两边除以 $d_0$（注意 $d_0$ 可能与 $m$ 不互质，需要谨慎处理）。更好的方法是直接检查条件：存在 $d_0$ 使得 $m \mid d_0 \cdot (p^n - 1)$。

等价地，$(p^n - 1)$ 必须包含 $m / \gcd(m, d_0)$ 这个因子。由于 $d_0$ 可以在 $1$ 到 $p-1$ 之间选择，我们可以直接枚举 $d_0$。

### 代码中的求解方法

参考给出的代码，其算法流程如下：

1. 初始化 $n = 2$，$pow = p^2 \mod m$（其中 $m = 2p - 1$）。
2. 循环尝试每个位数 $n$：
   - 枚举 $x$（即 $d_0$）从 $1$ 到 $p-1$。
   - 检查 $x \cdot (pow - 1) \mod m$ 是否等于 $0$。
   - 若等于 $0$，则找到可行的 $d_0$。
3. 若找到，跳出循环；否则：
   - $pow = (pow \cdot p) \mod m$。
   - $n$ 自增 $1$，继续循环。

这里 $pow$ 实际上维护的是 $p^n \mod m$ 的值，因为 $p^n$ 会随着位数增长而变得非常大，我们只需要其模 $m$ 的值。

条件 $x \cdot (p^n - 1) \equiv 0 \pmod{m}$ 等价于 $x \cdot (p^n \mod m - 1) \equiv 0 \pmod{m}$，这正是代码中的判断逻辑。

### 从 $X$ 的公式生成各位数字

找到 $n$ 和 $d_0$ 后，我们有：

$$
X = \frac{d_0 \cdot (p^n - 1)}{m}
$$

其中 $m = 2p - 1$。但直接计算 $p^n$ 可能过大。我们需要逐位生成 $X$ 的数字。

观察之前推导出的另一个关系式：

$$
X' = 2X \quad \text{且} \quad X' = \frac{X - d_0}{p} + d_0 \cdot p^{n-1}
$$

这给出了一个递推关系。但代码中采用了另一种巧妙的方法：利用乘法运算来生成数字。

设 $X$ 的各位数字为 $a_{n-1}, a_{n-2}, \dots, a_0$（其中 $a_{n-1}$ 是最高位）。由于 $2X$ 是 $X$ 的右旋转，$2X$ 的各位数字为 $a_0, a_{n-1}, a_{n-2}, \dots, a_1$。

这意味着：

$$
2 \times (a_{n-1} a_{n-2} \dots a_0)_p = (a_0 a_{n-1} a_{n-2} \dots a_1)_p
$$

从最低位开始考虑乘法过程。设 $carry$ 为进位，从最低位向高位逐位计算：

- 第 $0$ 位：$2 \times a_0 = a_1 + carry_0 \cdot p$？需要仔细推导。

更清晰的方法：考虑竖式乘法 $2X$。$2X$ 的最低（最右）位是 $a_1$（因为 $2X$ 是 $X$ 右旋转后得到的，其最后一位是原来的倒数第二位 $a_1$）。同时，$2X$ 的最低位的值也是 $2 \times a_0 \mod p$，并产生进位 $carry$。所以：

$$
2 \times a_0 = a_1 + carry_1 \cdot p
$$

类似地，下一位：

$$
2 \times a_1 + carry_1 = a_2 + carry_2 \cdot p
$$

依此类推，直到最高位：

$$
2 \times a_{n-1} + carry_{n-1} = a_0 + carry_n \cdot p
$$

由于 $2X$ 和 $X$ 位数相同（可能有前导零，但这里 $a_{n-1}$ 可能为零），最后的进位 $carry_n$ 必须为零，否则 $2X$ 会比 $X$ 多一位。

这一组方程可以用来求解各位数字。但代码采用了另一种方式：先构造一个临时序列，再进行修正。

### 代码中的数字生成算法

阅读代码，其生成数字的步骤如下：

```cpp
vector<int> digits(n);
int carry = 0;
for (int i = 0; i < digits.size(); i++) {
    int temp = (base - 1) * x + carry;
    digits[i] = temp % base;
    carry = temp / base;
}
if (carry)
    digits.push_back(carry);
```

这里的 $base - 1$ 即 $p-1$，$x$ 即 $d_0$。这段代码实际上在计算：

$$
(p-1) \cdot d_0 \cdot (1 + p + p^2 + \dots + p^{n-1}) \quad \text{?}
$$

不太直观。让我们重新理解。

从公式 $X = \frac{d_0 \cdot (p^n - 1)}{m}$ 出发，其中 $m = 2p-1$。注意 $p^n - 1 = (p-1)(p^{n-1} + p^{n-2} + \dots + 1)$。所以：

$$
X = \frac{d_0 \cdot (p-1) \cdot (p^{n-1} + \dots + 1)}{m}
$$

分子中的 $(p-1) \cdot d_0$ 是一个常数。代码中的循环是在计算一个 $n$ 位的数，每一位通过累加进位得到。实际上，这是在模拟除法过程：将 $(p-1) \cdot d_0$ 乘以 $(1 + p + p^2 + \dots)$ 后再除以 $m$。

更准确地说，代码先计算了 $(p-1) \cdot d_0$ 乘以一个 $n$ 位的全 $1$ 数（即 $111\dots1_p$）得到中间结果，然后再通过一个除法过程进行修正。最后的 `while` 循环截取前 $n$ 位作为结果。

这个算法本质上是在求解 $X$ 的各位数字，通过模拟 $X = \frac{d_0 \cdot (p^n - 1)}{m}$ 的运算，利用进位和借位来避免大整数运算。

## 算法总结

1. 对于给定的进制 $p$，令 $m = 2p - 1$。
2. 从位数 $n = 2$ 开始，枚举可能的末位数字 $d_0$（从 $1$ 到 $p-1$）。
3. 检查 $d_0 \cdot (p^n - 1) \equiv 0 \pmod{m}$ 是否成立（利用模运算快速计算 $p^n \mod m$）。
4. 找到满足条件的 $n$ 和 $d_0$ 后，根据公式 $X = \frac{d_0 \cdot (p^n - 1)}{m}$ 逐位生成数字。
5. 输出结果，数字之间用空格分隔。

## 时间复杂度

由于 $p < 200$，位数 $n$ 的增长速度较快，实际运算量很小。每次检查 $d_0$ 只需 $O(1)$ 次模运算，找到最小 $n$ 后生成数字也只需 $O(n)$ 时间，效率非常高。

## 代码实现

```cpp
// Double Trouble
// UVa ID: 268
// Verdict: Accepted
// Submission Date: 2016-05-22
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int main() {         
    int base;
    // 循环读取每一个进制数，直到文件结束
    while (cin >> base) {
        // 初始化位数 n = 2，pow 表示 base^n % (2*base-1)
        int n = 2, x, pow = base * base;
        // m = 2 * base - 1，用于模运算
        int m = 2 * base - 1;
        // 循环寻找最小的位数 n 和末位数字 x（即 d0）
        while (true) {
            bool found = false;
            // 枚举末位数字 x，范围为 1 到 base-1
            for (x = 1; x <= (base - 1); x++) {
                // 检查 x * (base^n - 1) 是否能被 m 整除
                // 等价于检查 x * (pow - 1) % m == 0
                int r = x * (pow - 1) % m;
                if (r == 0) {
                    found = true;
                    break;
                }
            }
            // 如果找到了合适的 x，退出循环
            if (found) break;
            // 否则增加位数 n，更新 pow = base^n % m
            pow = (pow * base) % m;
            n++;
        }

        // 生成 double-trouble 数的各位数字
        vector<int> digits(n);
        int carry = 0;
        // 模拟乘法：计算 (base-1) * x 乘以一个全 1 数
        for (int i = 0; i < digits.size(); i++) {
            int temp = (base - 1) * x + carry;
            digits[i] = temp % base;
            carry = temp / base;
        }
        // 如果最后有进位，加入数组
        if (carry) digits.push_back(carry);

        // 模拟除法：将之前得到的结果除以 m = 2*base-1
        int borrow = 0;
        for (int i = digits.size() - 1; i >= 0; i--) {
            int temp = borrow * base + digits[i];
            digits[i] = temp / m;
            borrow = temp % m;
        }

        // 截取前 n 位作为最终结果
        while (digits.size() > n) digits.erase(digits.end() - 1);

        // 按照题目格式输出结果
        cout << "For base " << base << " the double-trouble number is" << endl;
        // 注意数字需要从最高位到最低位输出，即逆序输出
        for (int i = digits.size() - 1; i >= 0; i--) cout << digits[i] << " ";
        cout << endl;
    }
    return 0;
}
```

## 注意事项

- 前导零是必要的，输出时不能省略。
- 数字之间用单个空格分隔，最后一个数字后也有一个空格。
- 输出格式要求：`For base $p$ the double-trouble number is` 单独一行，下一行是各个数字。
- 对于 $p = 35$ 的样例输出 `11 23`，表示该数的两个数字分别是 $11$ 和 $23$（在 $35$ 进制中，$11$ 和 $23$ 是合法的单个数码，即 $11_{35}$ 和 $23_{35}$）。
