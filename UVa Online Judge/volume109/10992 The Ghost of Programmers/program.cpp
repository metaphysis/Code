// The Ghost of Programmers
// UVa ID: 10992
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.000s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

string add(string, string);
string subtract(string, string);

// 十进制下的四则运算。
const int BASE = 10;

// 移除计算结果的前导0。
void zeroJustify(string &number)
{
    while (number.front() == '0' && number.length() > 1)
        number.erase(number.begin());
}

// 将两个字符串形式表示的非负整数进行相加操作，返回字符串表示的结果。
string add(string number1, string number2)
{
    if (number1.front() == '-')
        return subtract(number2, number1.substr(1));

    if (number2.front() == '-')
        return subtract(number1, number2.substr(1));
    
    // 将结果保存在字符串number1中，为了相加方便，调整加数，使得第一个加数的数位
    // 总是大于第二个加数的数位。由于两个正数相加，和的数位最多为两个加数数位较大值
    // 加一，可以预先分配存储空间以方便计算。
    if (number1.length() < number2.length())
        number1.swap(number2);
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
    if (number1.front() == '-')
    {
        number1 = add(number1.substr(1), number2);
        number1.insert(number1.begin(), '-');
        return number1;
    }
    
    // 比较被减数和减数的大小，如果被减数小于减数，调整两个数使得相减的操作便于实现。
    // 如果减数大于被减数则交换两个数，置计算结果为负数。
    int sign = 1;
    if (!greaterOrEqual(number1, number2))
    {
        sign = -1;
        number1.swap(number2);
        number1.insert(number1.begin(), '0');
    }

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

    // 设置计算结果的符号位。
    if (sign == -1 && number1 != "0")
        number1.insert(number1.begin(), '-');

    return number1;
}

int mod(string number1, int number2)
{
    int remainder = 0;

    for (int i = 0; i < number1.length(); i++)
    {
        remainder = remainder * BASE + (number1[i] - '0');
        remainder %= number2;
    }

    return remainder;
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int cases = 0;

    string n1;
    while (getline(cin, n1))
    {
        if (n1 == "0") break;
        if (cases++) cout << '\n';
        cout << n1 << '\n';

        if (n1.length() <= 4)
        {
            int n = stoi(n1);
            if (n < 2148)
            {
                cout << "No ghost will come in this year\n";
                continue;
            }
        }

        bool printed = false;
        string n2 = subtract(n1, "2148");
        if (mod(n2, 2) == 0)    { cout << "Ghost of Tanveer Ahsan!!!\n"; printed = true; }
        if (mod(n2, 5) == 0)    { cout << "Ghost of Shahriar Manzoor!!!\n"; printed = true; }
        if (mod(n2, 7) == 0)    { cout << "Ghost of Adrian Kugel!!!\n"; printed = true; }
        if (mod(n2, 11) == 0)   { cout << "Ghost of Anton Maydell!!!\n"; printed = true; }
        if (mod(n2, 15) == 0)   { cout << "Ghost of Derek Kisman!!!\n"; printed = true; }
        if (mod(n2, 20) == 0)   { cout << "Ghost of Rezaul Alam Chowdhury!!!\n"; printed = true; }
        if (mod(n2, 28) == 0)   { cout << "Ghost of Jimmy Mardell!!!\n"; printed = true; }
        if (mod(n2, 36) == 0)   { cout << "Ghost of Monirul Hasan!!!\n"; printed = true; }
        if ((mod(n1, 4) == 0 && mod(n1, 100) != 0) || mod(n1, 400) == 0)
        {
            cout << "Ghost of K. M. Iftekhar!!!\n";
            printed = true;
        }
        if (!printed) cout << "No ghost will come in this year\n";
    }

    return 0;
}
