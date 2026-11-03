
> **摘要**：本题要求计算双重求和 $S=\sum_{j=1}^{n}\sum_{i=1}^{m}\frac{1}{i(i+1)(i+2)(i+3)\,j(j+1)(j+2)(j+3)}$ 的最简分数形式 $\frac{a}{b}$，其中 $1\le m,n\le 10^8$，输入至多 $2000$ 组。由于内外层变量独立，可将双重和分离为两个单重和之积；利用裂项相消得到 $f(k)=\frac{P_k-6}{18P_k}$（$P_k=(k+1)(k+2)(k+3)$），进而 $S=\frac{P_mP_n-6(P_m+P_n)+36}{324P_mP_n}$。因 $P_mP_n\approx 10^{48}$ 超出 64 位整数范围，需用十进制字符串实现大整数加、减、乘、取模与除法，并用欧几里得算法约分。每组数据仅需常数次大整数运算，复杂度可视为 $O(1)$。

## 题目描述

给定两个整数 $m$ 和 $n$（$1 \le m, n \le 10^8$），计算双重求和

$$
S = \sum_{j=1}^{n}\sum_{i=1}^{m} \frac{1}{i(i+1)(i+2)(i+3)\,j(j+1)(j+2)(j+3)}
$$

并将其表示为最简分数 $\dfrac{a}{b}$。要求输出 $a$ 和 $b$，且 $a$ 和 $b$ 可能超出 64 位无符号整数范围。

输入包含至多 $2000$ 组数据，以 `0 0` 结束。每组输出四行：第一行为 `Case X:`，第二行为 $a$，第三行为一条长度等于 $b$ 的十进制位数的横线，第四行为 $b$，并在每组后输出一个空行。

## 输入格式

输入文件包含若干行，每行两个整数 $m$ 和 $n$，以 `0 0` 结束。

## 输出格式

对于每组输入，输出四行，格式如题目描述所示。

## 样例

输入

```
30 30
3 5
0 0
```

输出

```
Case 1:
29757025
----------
9644811264

Case 2:
209
-----
72576
```

## 题目分析

双重求和的内外层变量完全独立，因此可以将双重求和分离为两个单重求和之积：

$$
S = \left( \sum_{i=1}^{m} \frac{1}{i(i+1)(i+2)(i+3)} \right) \cdot
\left( \sum_{j=1}^{n} \frac{1}{j(j+1)(j+2)(j+3)} \right)
$$

定义函数

$$
f(k) = \sum_{t=1}^{k} \frac{1}{t(t+1)(t+2)(t+3)}
$$

利用部分分式或裂项技巧：

$$
\frac{1}{t(t+1)(t+2)(t+3)}
= \frac{1}{3}\left( \frac{1}{t(t+1)(t+2)} - \frac{1}{(t+1)(t+2)(t+3)} \right)
$$

求和后相邻项相消（ $\texttt{telescoping}$ ），得到

$$
f(k) = \frac{1}{18} - \frac{1}{3(k+1)(k+2)(k+3)}
= \frac{(k+1)(k+2)(k+3) - 6}{18\,(k+1)(k+2)(k+3)}
$$

记 $P_k = (k+1)(k+2)(k+3)$，则

$$
f(k) = \frac{P_k - 6}{18 P_k}
$$

因此原式

$$
S = f(m) \cdot f(n)
= \frac{(P_m - 6)(P_n - 6)}{324 \, P_m P_n}
$$

通分得

$$
S = \frac{P_m P_n - 6(P_m + P_n) + 36}{324 \, P_m P_n}
$$

令分子 $A = P_m P_n - 6(P_m + P_n) + 36$，分母 $B = 324 P_m P_n$。约分后得到最简分数 $\dfrac{a}{b}$，即 $a = \dfrac{A}{\gcd(A,B)}$，$b = \dfrac{B}{\gcd(A,B)}$。

由于 $m, n \le 10^8$，$P_k \approx (10^8)^3 = 10^{24}$，乘积 $P_m P_n \approx 10^{48}$，远超 $64$ 位整数范围，必须使用高精度整数（大整数）进行运算。

## 解题思路

### 大整数实现

采用十进制字符串表示非负大整数，重载加法、减法（要求左操作数不小于右操作数）、乘法、取模和除法。由于所有运算均为非负整数运算，实现较为简洁。

- **加法**：按位从低位到高位模拟，处理进位。
- **减法**：模拟借位，要求结果非负（调用前确保被减数不小于减数）。
- **乘法**：使用竖式乘法，结果数组长度为两数位数之和。
- **取模**：模拟长除法，逐位累加余数，当余数不小于除数时反复减去。
- **除法**：同取模过程，记录商每一位。

### 最大公约数

利用欧几里得算法，对大整数取模，迭代至余数为零。

### 具体计算步骤

1. 对于每组 $(m, n)$：
   - 计算 $P_m = (m+1)(m+2)(m+3)$，$P_n = (n+1)(n+2)(n+3)$，均用大整数乘法。
   - 计算 $A = P_m \cdot P_n - 6(P_m + P_n) + 36$。
   - 计算 $B = 324 \cdot P_m \cdot P_n$。
   - 计算 $g = \gcd(A, B)$。
   - 输出 $a = A / g$，$b = B / g$，并输出横线，长度为 $b$ 的十进制位数。

### 复杂度分析

每组数据需进行常数次大整数乘法（位数约 $48$ 位十进制，即约 $160$ 位二进制）、加减法和取模。大整数操作的时间复杂度为 $O(L^2)$，其中 $L$ 为十进制位数（此处 $L \le 50$），因此每组数据时间复杂度可视为常数。总输入最多 $2000$ 组，完全可行。

## 代码实现

```cpp
// Working with Small Numbers
// UVa ID: 11250
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.460s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

class BigInt {
    string digits;
public:
    BigInt() : digits("0") {}
    BigInt(unsigned long long n) { digits = to_string(n); }
    BigInt(const string& s) { digits = s; normalize(); }

    void normalize() {
        size_t pos = digits.find_first_not_of('0');
        if (pos == string::npos) digits = "0";
        else digits = digits.substr(pos);
    }

    bool isZero() const { return digits == "0"; }

    int compare(const BigInt& other) const {
        if (digits.size() != other.digits.size())
            return digits.size() < other.digits.size() ? -1 : 1;
        if (digits == other.digits) return 0;
        return digits < other.digits ? -1 : 1;
    }

    bool operator==(const BigInt& o) const { return digits == o.digits; }
    bool operator!=(const BigInt& o) const { return !(*this == o); }
    bool operator<(const BigInt& o) const { return compare(o) < 0; }
    bool operator>(const BigInt& o) const { return compare(o) > 0; }
    bool operator>=(const BigInt& o) const { return !(*this < o); }

    BigInt operator+(const BigInt& o) const {
        string a = digits, b = o.digits;
        if (a.size() < b.size()) swap(a, b);
        int carry = 0;
        int i = (int)a.size() - 1, j = (int)b.size() - 1;
        for (; i >= 0; --i, --j) {
            int sum = (a[i] - '0') + (j >= 0 ? b[j] - '0' : 0) + carry;
            carry = sum / 10;
            a[i] = char(sum % 10 + '0');
        }
        if (carry) a = "1" + a;
        return BigInt(a);
    }

    BigInt operator-(const BigInt& o) const {
        string a = digits, b = o.digits;
        int borrow = 0;
        int i = (int)a.size() - 1, j = (int)b.size() - 1;
        for (; i >= 0; --i, --j) {
            int diff = (a[i] - '0') - (j >= 0 ? b[j] - '0' : 0) - borrow;
            if (diff < 0) { diff += 10; borrow = 1; }
            else borrow = 0;
            a[i] = char(diff + '0');
        }
        BigInt res(a);
        res.normalize();
        return res;
    }

    BigInt operator*(const BigInt& o) const {
        string a = digits, b = o.digits;
        if (a == "0" || b == "0") return BigInt(0);
        int n = (int)a.size(), m = (int)b.size();
        vector<int> res(n + m, 0);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int mul = (a[i] - '0') * (b[j] - '0');
                int sum = res[i + j + 1] + mul;
                res[i + j + 1] = sum % 10;
                res[i + j] += sum / 10;
            }
        }
        string s;
        for (int x : res)
            if (!(s.empty() && x == 0)) s.push_back(char(x + '0'));
        if (s.empty()) s = "0";
        return BigInt(s);
    }

    BigInt operator%(const BigInt& b) const {
        if (b.isZero()) throw runtime_error("mod by zero");
        BigInt rem("0");
        for (char ch : digits) {
            rem = rem * BigInt(10) + BigInt(ch - '0');
            while (rem >= b) rem = rem - b;
        }
        return rem;
    }

    BigInt operator/(const BigInt& divisor) const {
        if (divisor.isZero()) throw runtime_error("division by zero");
        BigInt rem("0");
        string quot;
        for (char ch : digits) {
            rem = rem * BigInt(10) + BigInt(ch - '0');
            int q = 0;
            while (rem >= divisor) { rem = rem - divisor; ++q; }
            quot.push_back(char(q + '0'));
        }
        BigInt res(quot);
        res.normalize();
        return res;
    }

    string toString() const { return digits; }
};

BigInt gcd(BigInt a, BigInt b) {
    while (!b.isZero()) {
        BigInt r = a % b;
        a = b;
        b = r;
    }
    return a;
}

BigInt getP(unsigned long long k) {
    BigInt a(k + 1), b(k + 2), c(k + 3);
    return a * b * c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    unsigned long long m, n;
    int caseNo = 1;
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;

        BigInt Pm = getP(m);
        BigInt Pn = getP(n);

        BigInt product = Pm * Pn;
        BigInt sum = Pm + Pn;
        BigInt sixSum = BigInt(6) * sum;

        BigInt numerator = product - sixSum + BigInt(36);
        BigInt denominator = BigInt(324) * product;

        BigInt g = gcd(numerator, denominator);
        BigInt a = numerator / g;
        BigInt b = denominator / g;

        string bStr = b.toString();
        int len = (int)bStr.size();
        string line(len, '-');

        cout << "Case " << caseNo << ":" << "\n";
        cout << a.toString() << "\n";
        cout << line << "\n";
        cout << bStr << "\n";
        cout << "\n";

        ++caseNo;
    }

    return 0;
}
```

## 总结

本题的关键在于将双重求和通过裂项转化为关于 $P_k$ 的简单有理函数，从而避免逐项求和。由于 $m$、$n$ 可达 $10^8$，直接模拟求和会溢出且时间不可行，而公式化后仅需常数次大整数运算。

实现大整数类时，需要注意运算的正确性和效率。本题中数值位数不超过 $50$ 位十进制，采用字符串模拟即可，代码简洁且足够通过。

技巧要点：
- 利用 $\texttt{telescoping}$ 化简和式。
- 分离变量将双重和化为单重和之积。
- 使用高精度整数处理超出内置类型范围的结果。
- 约分使用欧几里得算法，注意大整数取模的实现。
