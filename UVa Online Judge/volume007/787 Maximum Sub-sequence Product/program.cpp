// Maximum Sub-sequence Product
// UVa ID: 787
// Verdict: Accepted
// Submission Date: 2016-12-01
// UVa Run Time: 0.030s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

// 十进制下的四则运算。
const int BASE = 10;

struct BigInteger
{
    int sign;
    string digits;

    bool operator<(BigInteger x) const
    {
        if (sign * x.sign == -1)
            return sign == -1;
        {
            bool bigger = false;
            if (digits.length() != x.digits.length())
                 bigger = digits.length() > x.digits.length();
            else
            {
                for (int i = 0; i < digits.length(); i++)
                    if (digits[i] != x.digits[i])
                    {
                        bigger = digits[i] > x.digits[i];
                        break;
                    }
            }

            if (sign == -1)
                return bigger;
            else
                return !bigger;
        }
    }
};

// 移除计算结果的前导0。
void zeroJustify(string &number)
{
    while (number.front() == '0' && number.length() > 1)
        number.erase(number.begin());
}

// 两个非负整数的乘法。
BigInteger multiplicate(BigInteger &number1, BigInteger &number2)
{
    // 预分配存储空间。
    string number3(number1.digits.length() + number2.digits.length(), 0);

    // 从最低位开始相乘。
    int length1 = number1.digits.length() - 1, length2 = number2.digits.length() - 1;
    for (int i = length1; i >= 0; i--)
        for (int j = length2; j >= 0; j--)
        {
            int k = number3.length() - 1 - (length1 - i + length2 - j);
            number3[k] += (number2.digits[j] - '0') * (number1.digits[i] - '0');
            number3[k - 1] += number3[k] / BASE;
            number3[k] %= BASE;
        }

    // 将数值转换为对应的数字字符。
    for (int i = 0; i < number3.length(); i++) number3[i] += '0';

    zeroJustify(number3);

    int sign = number1.sign * number2.sign;
    if (number3 == "0") sign = 1;

    return (BigInteger){sign, number3};
}

BigInteger maximum_product(BigInteger data[], int n)
{
    BigInteger maximum = data[0], max_current = data[0], min_current = data[0];

    for (int i = 1; i < n; i++)
    {
        BigInteger next_max = multiplicate(max_current, data[i]);
        BigInteger next_min = multiplicate(min_current, data[i]);

        max_current = max(data[i], max(next_max, next_min));
        min_current = min(data[i], min(next_max, next_min));

        maximum = max(maximum, max_current);
    }

    return maximum;
}

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int n = 0;
    BigInteger data[110];

    string number;
    while (cin >> number)
    {
        if (number == "-999999")
        {
            BigInteger result = maximum_product(data, n);
            if (result.sign == -1) cout << '-';
            cout << result.digits << '\n';
            n = 0;
        }
        else
        {
            int sign = 1;
            if (number.front() == '-')
            {
                sign = -1;
                number.erase(number.begin());
            }
            data[n++] = (BigInteger){sign, number};
        }
    }

    return 0;
}
