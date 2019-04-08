// Immortal Rabbits
// UVa ID: 12924
// Verdict: Accepted
// Submission Date: 2019-04-08
// UVa Run Time: 4.410s
//
// 版权所有（C）2019，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int POSITIVE = 1, NEGATIVE = -1, EQUAL = 0;

class BigInteger
{
    friend ostream& operator<<(ostream&, const BigInteger&);
    friend BigInteger operator+(const BigInteger&, const BigInteger&);

public:
    BigInteger() {};
    BigInteger(const long long&);
    ~BigInteger() {};

private:
    void zeroJustify(void);

    // 采用10000作为基数。数位宽度为4。
    static const int base = 10000;
    static const int width = 4;

    int sign;
    vector < int > digits;
};

// 将长整型数转换为大整数。
BigInteger::BigInteger(const long long& value)
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
        long long number = abs(value);
        while (number)
        {
            digits.push_back(number % base);
            number /= base;
        }
    }

    // 移除前导零。
    zeroJustify();
};

// 重载输出符号以输出大整数。
ostream& operator<<(ostream& os, const BigInteger& number)
{
    os << (number.sign > 0 ? "" : "-");
    os << number.digits[number.digits.size() - 1];
    for (int i = number.digits.size() - 2; i >= 0; i--)
        os << setw(number.width) << setfill('0') << number.digits[i];
    return os;
}

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

// 高精度整数加法。
BigInteger operator+(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;

    // 确保x的位数比y的位数多，便于计算。
    if (x.digits.size() < y.digits.size())
        return (y + x);

    // 两个加数的符号相同时才进行加法运算。预先为结果分配存储空间。
    z.sign = x.sign + y.sign >= 0 ? POSITIVE : NEGATIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()) + 1);

    fill(z.digits.begin(), z.digits.end(), 0);

    // 逐位相加，考虑进位。
    int index = 0, carry = 0;
    for (; index < x.digits.size(); index++)
    {
        // 获取对应位的和。
        int sum = x.digits[index] + carry;
        sum += index < y.digits.size() ? y.digits[index] : 0;

        // 确定进位。
        carry = sum / z.base;

        // 将和保存到结果的相应位中。
        z.digits[index] = sum % z.base;
    }

    // 保存最后可能产生的进位。
    z.digits[index] = carry;

    // 移除前导零。
    z.zeroJustify();

    return z;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases, A, B, m;
    cin >> cases;
    for (int cs = 1; cs <= cases; cs++)
    {
        cin >> A >> B >> m;
        if (m == 0) cout << A << '\n';
        else if (m == 1) cout << B << '\n';
        else
        {
            BigInteger F1(A), F2(B), F3(0);
            for (int i = 2; i <= m; i++)
            {
                F3 = F1 + F2;
                F1 = F2, F2 = F3;
            }
            cout << F3 << '\n';
        }
    }

    return 0;
}
