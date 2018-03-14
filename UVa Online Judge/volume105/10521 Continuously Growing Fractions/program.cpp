// Continuously Growing Fractions
// UVa ID: 10521
// Verdict: Accepted
// Submission Date: 2017-07-24
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

// 将两个字符串形式表示的非负整数进行相加操作，返回字符串表示的结果。
string add(string number1, string number2)
{
    // 将结果保存在字符串number1中，为了相加方便，调整加数，使得第一个加数的数位
    // 总是大于第二个加数的数位。由于两个正数相加，和的数位最多为两个加数数位较大值
    // 加一，可以预先分配存储空间以方便计算。
    if (number1.length() < number2.length()) number1.swap(number2);
    number1.insert(number1.begin(), '0');

    // 相加时从低位开始加。初始时进位为0。由于字符串中保存的是数位的ASCII码字符，
    // 需要做相应的转换，使之成为对应的数字值。当前的数位为模基数的值，进位则为除
    // 基数的值。
    int carry = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--)
    {
        int sum = number1[i] - '0' + (j >= 0 ? (number2[j] - '0') : 0) + carry;
        number1[i] = sum % BASE + '0';
        carry = sum / BASE;
    }

    // 移除前导0。
    zeroJustify(number1);

    return number1;
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

void getCF(string number1, string number2, int top)
{
    pair<string, string> r = divide(number1, number2);
    
    if (!top) cout << '{';

    cout << r.first;
    if (r.second != "0") cout << "+1/";
    
    number1 = r.second;
    if (number1 != "0")
    {
        swap(number1, number2);
        getCF(number1, number2, 0);
    }
    
    if (!top) cout << '}';
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    string number1, number2;
    
    while (cin >> number1 >> number2)
    {
        int sign1 = 1, sign2 = 1;
        if (number1.front() == '-') 
        {
            sign1 = -1;
            number1.erase(number1.begin());
        }
        if (number2.front() == '-')
        {
            sign2 = -1;
            number2.erase(number2.begin());
        }
        
        while (number1.length() > 1 && number1.front() == '0')
            number1.erase(number1.begin());
        while (number2.length() > 1 && number2.front() == '0')
            number2.erase(number2.begin());
        
        if (sign1 == -1) cout << '-';
        cout << number1;
        cout << '/';
        if (sign2 == -1) cout << '-';
        cout << number2 << " = ";
        
        if (number1 == "0")
        {
            cout << "0\n";
            continue;
        }
        
        if ((sign1 * sign2) == 1) getCF(number1, number2, 1);
        else
        {
            pair<string, string> r = divide(number1, number2);

            cout << '-';
            if (r.second == "0") cout << r.first;
            else
            {
                cout << add(r.first, "1") << "+1/";
                number1 = subtract(number2, r.second);
                swap(number1, number2);
                getCF(number1, number2, 0);
            }
        }
        
        cout << '\n';
    }
    
    return 0;
}
