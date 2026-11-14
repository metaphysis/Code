[UVa 367 Halting Factor Replacement Systems](https://blog.csdn.net/metaphysis/article/details/161611411)

## 题目描述

**因子替换系统**（$\texttt{Factor Replacement System, FRS}$）通过应用规则将输入整数转换为另一个整数。每条规则指定输入整数的质因子集合如何被另一组质因子替换。

例如：
- 规则1: $150 \rightarrow 49$（因为 $150 = 2 \times 3 \times 5^2$，$49 = 7^2$）
- 规则2: $2 \rightarrow 1$

规则1规定：如果整数包含一个因子 $2$、一个因子 $3$ 和两个因子 $5$，则移除这些因子，替换为两个因子 $7$。

$\texttt{FRS}$ 规则是**有序**的。对于给定的输入，按顺序检查规则以找到匹配。当找到匹配时，应用规则一次，然后从第一条规则重新开始。当没有规则可应用时，$\texttt{FRS}$ 停止。

给定一个 $\texttt{FRS}$ 的规则和若干正整数，输出将 $\texttt{FRS}$ 应用于每个整数的结果。保证 $\texttt{FRS}$ 对每个输入整数都会停止。

### 输入格式

每个 $\texttt{FRS}$ 描述以一行包含非负整数 $n$（$n \leq 15$）开始，表示规则数量。接下来 $n$ 行包含规则，每行两个正整数（左部和右部）。下一行包含非负整数 $k$，表示输入整数的数量。接下来 $k$ 行每行包含一个整数。当 $n = 0$ 时程序停止。

### 输出格式

对于每个数据集，输出一行标识数据集编号。对于每个输入整数，输出一行包含输入整数和最终的 $\texttt{FRS}$  值。不同 FRS 的输出后跟一个空行。

### 样例输入

```
2
150 49
2 1
2
450
44
2
9 4
3 1
1
27
0
```

### 样例输出

```
FRS #1:
     450 becomes 147
     44 becomes 11

FRS #2:
     27 becomes 4
```

---

## 题目分析

### 问题的本质

这是一个**整数变换系统**的模拟问题。给定一组有序的替换规则，反复应用第一条可匹配的规则，直到无法再应用任何规则。

### 规则匹配的数学意义

规则 $L \rightarrow R$ 意味着：如果当前数能被 $L$ 整除，则将该数除以 $L$ 再乘以 $R$。

即：
$$
new = current \div L \times R
$$

这是因为 $L$ 和 $R$ 的质因子分解决定了替换关系。

### 大整数处理

题目提示：输出值可能超过 $32$ 位整数的范围，甚至超过浮点数范围。因此需要使用**高精度整数**（$\texttt{BigInteger}$）。

### 算法流程

对于每个输入整数：
1. 将当前数初始化为输入值
2. 重复以下过程：
   - 按顺序检查每条规则
   - 如果当前数能被规则左部整除，则应用规则（除以左部，乘以右部）
   - 从第一条规则重新开始
3. 当没有规则可应用时停止

---
## 参考代码

```cpp
// Halting Factor Replacement Systems
// UVa ID: 367
// Verdict: Accepted
// Submission Date: 2016-07-08
// UVa Run Time: 0.070s
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
    
    int lastDigit() const { return digits.front(); }
    ~BigInteger() {};

private:
    void zeroJustify(void);

    static const int base = 10000;
    static const int width = 4;

    int sign;
    vector<int> digits;
};

BigInteger operator+(const BigInteger&, const BigInteger&);
BigInteger operator-(const BigInteger&, const BigInteger&);

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

ostream& operator<<(ostream& os, const BigInteger& number)
{
    os << (number.sign > 0 ? "" : "-");
    os << number.digits[number.digits.size() - 1];
    for (int i = number.digits.size() - 2; i >= 0; i--)
        os << setw(number.width) << setfill('0') << number.digits[i];
    return os;
}

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

bool operator==(const BigInteger& x, const BigInteger& y) { return compare(x, y) == 0; }
bool operator<(const BigInteger& x, const BigInteger& y) { return compare(x, y) < 0; }
bool operator<=(const BigInteger& x, const BigInteger& y) { return compare(x, y) <= 0; }

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

BigInteger operator-(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;
    if (x.sign == NEGATIVE || y.sign == NEGATIVE)
    {
        z = y;
        z.sign = -y.sign;
        return x + z;
    }

    if (x < y)
    {
        z = y - x;
        z.sign = NEGATIVE;
        return z;
    }

    z.sign = POSITIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()));
    fill(z.digits.begin(), z.digits.end(), 0);

    int index = 0, borrow = 0;
    for (; index < x.digits.size(); index++)
    {
        int difference = x.digits[index] - borrow;
        difference -= index < y.digits.size() ? y.digits[index] : 0;
        borrow = 0;
        if (difference < 0)
        {
            difference += z.base;
            borrow = 1;
        }
        z.digits[index] = difference % z.base;
    }

    z.zeroJustify();
    return z;
}

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

BigInteger operator/(const BigInteger& x, const BigInteger& y)
{
    BigInteger z, r;
    z.sign = x.sign * y.sign;
    r.sign = POSITIVE;
    z.digits.resize(x.digits.size() - y.digits.size() + 1);
    r.digits.resize(y.digits.size() + 1);
    fill(z.digits.begin(), z.digits.end(), 0);
    fill(r.digits.begin(), r.digits.end(), 0);

    for (int i = x.digits.size() - 1; i >= 0; i--)
    {
        r.digits.insert(r.digits.begin(), x.digits[i]);
        int low = 0, high = z.base - 1, middle = (high + low + 1) >> 1;
        while (low < high)
        {
            if ((y * BigInteger(middle)) <= r)
                low = middle;
            else
                high = middle - 1;
            middle = (high + low + 1) >> 1;
        }

        for (int index = 0; index < y.digits.size(); index++)
        {
            int difference = r.digits[index] - middle * y.digits[index];
            int borrow = 0;
            if (difference < 0)
                borrow = (z.base - 1 - difference) / z.base;
            r.digits[index + 1] -= borrow;
            difference += z.base * borrow;
            r.digits[index] = difference % z.base;
        }
        z.digits.insert(z.digits.begin(), middle);
    }

    z.zeroJustify();
    return z;
}

BigInteger operator%(const BigInteger& x, const BigInteger& y)
{
    return (x - (x / y) * y);
}

const BigInteger ZERO = BigInteger(0), ONE = BigInteger(1), TWO = BigInteger(2);

vector<pair<BigInteger, BigInteger>> replacement;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);

    long long rules, left, right, integers, number, cases = 0;
    while (cin >> rules, rules)
    {
        replacement.clear();
        
        // 读取规则
        for (int i = 1; i <= rules; i++)
        {
            cin >> left >> right;
            replacement.push_back({BigInteger(left), BigInteger(right)});
        }
        
        cout << "FRS #" << ++cases << ":" << endl;
        
        cin >> integers;
        for (int i = 1; i <= integers; i++)
        {
            cin >> number;
            cout << "     " << number << " becomes ";
            
            BigInteger result = BigInteger(number);
            // 重复应用规则直到无法再应用
            while (true)
            {
                bool updated = false;
                for (auto& rule : replacement)
                {
                    if ((result % rule.first) == ZERO)
                    {
                        result = result / rule.first * rule.second;
                        updated = true;
                        break;  // 从第一条规则重新开始
                    }
                }
                if (!updated) break;
            }
            
            cout << result << endl;
        }
        
        cout << endl;
    }
    
    return 0;
}
```
