// Simplifying Fractions
// UVa ID: 10814
// Verdict: Accepted
// Submission Date: 2017-07-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 十进制下的四则运算。
const int BASE = 10;

// 移除计算结果的前导0。
void zeroJustify(string &number)
{
    while (number.front() == '0' && number.length() > 1)
        number.erase(number.begin());
}

// 判断第一个数是否不小于第二个数。
// 比较数的大小时，如果数位不等，由于都是非负整数，数位多的肯定大于数位少的；
// 如果数位相同，则从高位至低位逐个数位来进行比较。
bool greaterOrEqual(string &number1, string &number2)
{
    if (number1.length() != number2.length())
        return number1.length() > number2.length();

    for (int i = 0; i < number1.length(); i++)
        if (number1[i] != number2[i])
            return number1[i] > number2[i];
            
    return true;
}

// 两个非负整数的减法。
string subtract(string number1, string number2)
{
    // 逐位相减，不够的向高位借位。
    int borrow = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--)
    {
        int diff = number1[i] - '0' - (j >= 0 ? (number2[j] - '0') : 0) - borrow;
        borrow = 0;
        if (diff < 0)
        {
            diff += BASE;
            borrow = 1;
        }
        number1[i] = diff + '0';
    }

    // 移除前导0。
    zeroJustify(number1);

    return number1;
}

// 非负整数的除法。
pair<string, string> divide(string number1, string number2)
{
    string row, quotient, remainder;
    for (int i = 0; i < number1.length(); i++)
    {
        // 将试除数不断左移，加上被除数的对应位。
        row.push_back(number1[i]);
        quotient.push_back('0');
        
        // 去除未除尽数的前导零。
        zeroJustify(row);
        
        // 当试除数大于除数时，将对应位的商加1然后减去除数，重复此步骤直到试除数
        // 小于除数。
        while (greaterOrEqual(row, number2))
        {
            quotient.back() += 1;
            row = subtract(row, number2);
        }
    }

    // 获取余数。
    remainder = row;

    // 去除前导零。
    zeroJustify(quotient);
    zeroJustify(remainder);

    return make_pair(quotient, remainder);
}

string gcd(string number1, string number2)
{
    if (number2 == "0") return number1;
    
    pair<string, string> r = divide(number1, number2);
    
    return gcd(number2, r.second);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    
    string p, slash, q;
    for (int c = 1; c <= N; c++)
    {
        cin >> p >> slash >> q;
        
        string g = gcd(p, q);
        
        pair<string, string> r1 = divide(p, g);
        pair<string, string> r2 = divide(q, g);
        
        cout << r1.first << " / " << r2.first << '\n';
    }
    
    return 0;
}
