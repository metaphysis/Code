// Parliament
// UVa ID: 668
// Verdict: Accepted
// Submission Date: 2017-10-26
// UVa Run Time: 0.050s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int POSITIVE = 1, NEGATIVE = -1, EQUAL = 0;

class BigInteger
{
    friend BigInteger operator*(const BigInteger&, const BigInteger&);
    friend int compare(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    
public:
    BigInteger() {};
    BigInteger(const int&);
    ~BigInteger() {};

private:
    void zeroJustify(void);

    // 采用10000作为基数。数位宽度为4。
    static const int base = 10000;
    static const int width = 4;

    int sign;
    vector<int> digits;
};

// 将长整型数转换为大整数。
BigInteger::BigInteger(const int& value)
{
    if (value == 0)
    {
        sign = POSITIVE;
        digits.push_back(0);
    }
    else
    {
        // 不断模基数取余得到各个数位。
        sign = (value >= 0 ? POSITIVE : NEGATIVE);
        int number = abs(value);
        while (number)
        {
            digits.push_back(number % base);
            number /= base;
        }
    }

    // 移除前导零。
    zeroJustify();
};

// 移除无效的前导零。
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

// 比较两个高精度整数的大小。
// x大于y，返回1，x小于y，返回-1，x等于y，返回0。
// 为了除法的需要，对未经前导零调整的整数也能正确处理。
int compare(const BigInteger& x, const BigInteger& y)
{
    // 符号不同，正数大于负数。
    if (x.sign == POSITIVE && y.sign == NEGATIVE ||
            x.sign == NEGATIVE && y.sign == POSITIVE)
        return (x.sign == POSITIVE ? 1 : -1);

    // 确定x和y的有效数位，即前导零不计入有效数位。
    int xDigitNumber = x.digits.size() - 1;
    for (; xDigitNumber && x.digits[xDigitNumber] == 0; xDigitNumber--)
        ;
    int yDigitNumber = y.digits.size() - 1;
    for (; yDigitNumber && y.digits[yDigitNumber] == 0; yDigitNumber--)
        ;

    // 符号相同，同为正数，数位越多越大，同为负数，数位越多越小。
    if (xDigitNumber > yDigitNumber)
        return (x.sign == POSITIVE ? 1 : -1);

    // 符号相同，同为正数，数位越少越小，同为负数，数位越少越大。
    if (xDigitNumber < yDigitNumber)
        return (x.sign == NEGATIVE ? 1 : -1);

    // 符号相同，数位相同，逐位比较。
    for (int index = xDigitNumber; index >= 0; index--)
    {
        if (x.digits[index] > y.digits[index])
            return (x.sign == POSITIVE ? 1 : -1);

        if (x.digits[index] < y.digits[index])
            return (x.sign == NEGATIVE ? 1 : -1);
    }

    // 两数相等。
    return 0;
}

// 小于比较运算符。
bool operator<(const BigInteger& x, const BigInteger& y)
{
    return compare(x, y) < 0;
}

// 高精度整数乘法。
BigInteger operator*(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;

    // 设置符号位并预先分配存储空间。
    z.sign = x.sign * y.sign;
    z.digits.resize(x.digits.size() + y.digits.size());
    fill(z.digits.begin(), z.digits.end(), 0);

    // 一行一行相乘然后相加。
    for (int i = 0; i < y.digits.size(); i++)
        for (int j = 0; j < x.digits.size(); j++)
        {
            z.digits[i + j] += x.digits[j] * y.digits[i];
            z.digits[i + j + 1] += z.digits[i + j] / z.base;
            z.digits[i + j] %= z.base;
        }

    // 移除前导零。
    z.zeroJustify();

    return z;
}

const BigInteger ZERO = BigInteger(0), ONE = BigInteger(1), TWO = BigInteger(2);

BigInteger product[1010];
int memo[1010];

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    for (int i = 0; i <= 1001; i++)
            product[i] = ZERO;
    for (int i = 2; i <= 4; i++)
        product[i] = BigInteger(i), memo[i] = i;
    
    for (int i = 2; i <= 1001; i++)
        for (int j = memo[i] + 1; j + i <= 1001; j++)
        {
            BigInteger t = product[i] * BigInteger(j);
            if (product[i + j] < t)
            {
                product[i + j] = t;
                memo[i + j] = j;
            }
        }
        
    int cases;
    cin >> cases;
    
    int n;
    for (int c = 1; c <= cases; c++)
    {
        cin >> n;
        vector<int> sequence;
        while (n > 0)
        {
            sequence.push_back(memo[n]);
            n -= memo[n];
        }
        if (c > 1) cout << '\n';
        reverse(sequence.begin(), sequence.end());
        for (int i = 0; i < sequence.size(); i++)
        {
            if (i) cout << ' ';
            cout << sequence[i];
        }
        cout << '\n';
    }
    
    return 0;
}
