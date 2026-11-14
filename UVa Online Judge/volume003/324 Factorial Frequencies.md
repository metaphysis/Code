[UVa 324 Factorial Frequencies](https://blog.csdn.net/metaphysis/article/details/161513362)

## 题目描述

$\texttt{Madam Phoenix}$ 的掌相算命生意日渐萧条，她决定为客户提供一些数字命理学的服务。她已经成功说服客户，阶乘的十进制表示中各个数字出现的频率能够预示他们的未来。与掌相不同，她无法凭空变出这些频率，因此需要你来帮忙计算这些数值。

回想一下，$n!$（$n$ 的阶乘）的定义是 $1 \times 2 \times 3 \times \dots \times n$。由于她可能使用星期几、月份中的第几天或一年中的第几天作为 $n$ 的值，你需要能够确定 $366!$（有 $781$ 位数字）以内数字的各位数字出现次数。

### 输入格式

输入数据是一个整数列表，表示需要计算数字频率的阶乘数。所有输入值都小于等于 $366$ 且大于 $0$，最后一个整数为 $0$。遇到 $0$ 时停止程序。

### 输出格式

输出格式应与下面示例相似。

### 样例输入

```
3 8 100 0
```

### 样例输出

```
3! -- 
     (0)    0    (1)    0    (2)    0    (3)    0    (4)    0
     (5)    0    (6)    1    (7)    0    (8)    0    (9)    0

8! -- 
     (0)    2    (1)    0    (2)    1    (3)    1    (4)    1
     (5)    0    (6)    0    (7)    0    (8)    0    (9)    0

100! -- 
     (0)   30    (1)   15    (2)   19    (3)   10    (4)   10
     (5)   14    (6)   19    (7)    7    (8)   14    (9)   20
```

---

## 题目分析

### 问题的本质

这是一个**大整数计算 + 数字统计**问题。需要计算 $n!$（$n \leq 366$）的十进制表示，然后统计数字 $0 \sim 9$ 出现的频率。

$366!$ 是一个巨大的数，有 $781$ 位，远超标准整数类型（即使是 $64$ 位整数也只能存储约 $20$ 位数字）。因此必须使用**高精度整数**（大整数）运算。

### 高精度整数的选择

实现高精度整数有两种常见方式：
1. **使用数组/向量存储每一位数字**（十进制或 $10000$ 进制）
2. **使用现有的大整数库**（如 `Python` 的任意精度整数）

在 `C++` 中，需要自己实现大整数类或使用第三方库。本题的参考代码实现了一个完整的 `BigInteger` 类，使用基数为 $10000$（即每 $4$ 位十进制数字存储为一个单元），这称为**压位高精度**。

### 压位高精度的优势

- 减少存储空间：每个单元存储 $4$ 位数字，而不是 $1$ 位
- 提高运算速度：减少循环次数
- 加法/乘法的进位处理更高效

### 阶乘计算策略

由于输入包含多个 $n$ 值，且 $n \leq 366$，我们可以采用**记忆化**策略：
- 预先计算并缓存已计算过的阶乘
- 当需要计算新值时，从已知的最大值开始递增计算

例如，如果已经计算过 $5!$，要计算 $10!$，只需从 $6$ 乘到 $10$ 即可，不需要重新从 $1$ 开始。

---
## 参考代码

```cpp
// Factorial Frequencies
// UVa ID: 324
// Verdict: Accepted
// Submission Date: 2016-06-26
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int POSITIVE = 1, NEGATIVE = -1, EQUAL = 0;

class BigInteger
{
    friend ostream& operator<<(ostream&, const BigInteger&);

    friend int compare(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);
    friend bool operator==(const BigInteger&, const BigInteger&);

    friend BigInteger operator+(const BigInteger&, const BigInteger&);
    friend BigInteger operator-(const BigInteger&, const BigInteger&);
    friend BigInteger operator*(const BigInteger&, const BigInteger&);
    friend BigInteger operator/(const BigInteger&, const BigInteger&);
    friend BigInteger operator%(const BigInteger&, const BigInteger&);
    friend BigInteger operator^(const BigInteger&, const unsigned int&);
    friend BigInteger operator^(const BigInteger&, const BigInteger&);
    friend BigInteger operator<<(const BigInteger&, const unsigned int&);

public:
    BigInteger() {};
    BigInteger(const long long&);
    BigInteger(const string&);
    
    int lastDigit() const
    {
        return digits.front();
    }
    
    ~BigInteger() {};

private:
    void zeroJustify(void);

    // 采用 10000 作为基数，数位宽度为 4
    static const int base = 10000;
    static const int width = 4;

    int sign;
    vector<int> digits;
};

// 将长整型数转换为大整数
BigInteger::BigInteger(const long long& value)
{
    if (value == 0)
    {
        sign = POSITIVE;
        digits.push_back(0);
    }
    else
    {
        sign = (value >= 0 ? POSITIVE : NEGATIVE);
        long long number = abs(value);
        while (number)
        {
            digits.push_back(number % base);
            number /= base;
        }
    }
    zeroJustify();
};

// 将十进制的字符串转换为大整数
BigInteger::BigInteger(const string& value)
{
    if (value.length() == 0)
    {
        sign = POSITIVE;
        digits.push_back(0);
    }
    else
    {
        sign = value[0] == '-' ? NEGATIVE : POSITIVE;
        string block;
        for (int index = value.length() - 1; index >= 0; index--)
        {
            if (isdigit(value[index]))
                block.insert(block.begin(), value[index]);
            if (block.length() == width)
            {
                digits.push_back(stoi(block));
                block.clear();
            }
        }
        if (block.length() > 0)
            digits.push_back(stoi(block));
    }
    zeroJustify();
}

// 重载输出运算符
ostream& operator<<(ostream& os, const BigInteger& number)
{
    os << (number.sign > 0 ? "" : "-");
    os << number.digits[number.digits.size() - 1];
    for (int i = number.digits.size() - 2; i >= 0; i--)
        os << setw(number.width) << setfill('0') << number.digits[i];
    return os;
}

// 移除无效的前导零
void BigInteger::zeroJustify(void)
{
    for (int i = digits.size() - 1; i >= 1; i--)
    {
        if (digits[i] == 0)
            digits.erase(digits.begin() + i);
        else
            break;
    }
    if (digits.size() == 1 && digits[0] == 0)
        sign = POSITIVE;
}

// 比较两个高精度整数的大小
int compare(const BigInteger& x, const BigInteger& y)
{
    if (x.sign == POSITIVE && y.sign == NEGATIVE ||
        x.sign == NEGATIVE && y.sign == POSITIVE)
        return (x.sign == POSITIVE ? 1 : -1);

    int xDigitNumber = x.digits.size() - 1;
    for (; xDigitNumber && x.digits[xDigitNumber] == 0; xDigitNumber--);
    int yDigitNumber = y.digits.size() - 1;
    for (; yDigitNumber && y.digits[yDigitNumber] == 0; yDigitNumber--);

    if (xDigitNumber > yDigitNumber)
        return (x.sign == POSITIVE ? 1 : -1);
    if (xDigitNumber < yDigitNumber)
        return (x.sign == NEGATIVE ? 1 : -1);

    for (int index = xDigitNumber; index >= 0; index--)
    {
        if (x.digits[index] > y.digits[index])
            return (x.sign == POSITIVE ? 1 : -1);
        if (x.digits[index] < y.digits[index])
            return (x.sign == NEGATIVE ? 1 : -1);
    }
    return 0;
}

// 比较运算符重载
bool operator==(const BigInteger& x, const BigInteger& y) { return compare(x, y) == 0; }
bool operator<(const BigInteger& x, const BigInteger& y) { return compare(x, y) < 0; }
bool operator<=(const BigInteger& x, const BigInteger& y) { return compare(x, y) <= 0; }

// 高精度整数加法
BigInteger operator+(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;
    if (x.sign == NEGATIVE && y.sign == POSITIVE)
    {
        z = x;
        z.sign = POSITIVE;
        return (y - z);
    }
    else if (x.sign == POSITIVE && y.sign == NEGATIVE)
    {
        z = y;
        z.sign = POSITIVE;
        return (x - z);
    }

    if (x.digits.size() < y.digits.size())
        return (y + x);

    z.sign = x.sign + y.sign >= 0 ? POSITIVE : NEGATIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()) + 1);
    fill(z.digits.begin(), z.digits.end(), 0);

    int index = 0, carry = 0;
    for (; index < x.digits.size(); index++)
    {
        int sum = x.digits[index] + carry;
        sum += index < y.digits.size() ? y.digits[index] : 0;
        carry = sum / z.base;
        z.digits[index] = sum % z.base;
    }
    z.digits[index] = carry;
    z.zeroJustify();
    return z;
}

// 高精度整数乘法
BigInteger operator*(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;
    z.sign = x.sign * y.sign;
    z.digits.resize(x.digits.size() + y.digits.size());
    fill(z.digits.begin(), z.digits.end(), 0);

    for (int i = 0; i < y.digits.size(); i++)
        for (int j = 0; j < x.digits.size(); j++)
        {
            z.digits[i + j] += x.digits[j] * y.digits[i];
            z.digits[i + j + 1] += z.digits[i + j] / z.base;
            z.digits[i + j] %= z.base;
        }

    z.zeroJustify();
    return z;
}

const BigInteger ONE = BigInteger(1);

// 统计 n! 中各个数字的出现频率并输出
void getCountOfDigits(int n, BigInteger x)
{
    stringstream ss;
    ss << x;
    string line;
    ss >> line;
    
    map<int, int> digitCounter;
    for (int i = 0; i <= 9; i++)
        digitCounter[i] = 0;
        
    for (auto c : line)
        digitCounter[c - '0']++;
    
    cout << n << "! --" << endl;
    for (auto p : digitCounter)
    {
        cout << setw(6) << right << "(" + to_string(p.first) + ")";
        cout << setw(6) << right << p.second;
        if (p.first % 10 == 4) cout << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    int n, nExisted = 0;
    map<int, BigInteger> calculated;
    calculated[0] = ONE;  // 0! = 1
    
    while (cin >> n, n)
    {
        // 如果当前需要计算的 n 大于已计算的最大值，则递推计算
        if (n > nExisted)
        {
            BigInteger x = calculated[nExisted];
            for (int i = nExisted + 1; i <= n; i++)
            {
                x = x * BigInteger(i);
                calculated[i] = x;
            }
            nExisted = n;
        }
        
        getCountOfDigits(n, calculated[n]);
    }
    
    return 0;
}
```
