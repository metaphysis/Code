// Adding Reversed Numbers
// UVa ID: 713
// Verdict: Accepted
// Submission Date: 2016-11-29
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

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

// 将两个字符串形式表示的非负整数进行相加操作，返回字符串表示的结果。
string add(string number1, string number2)
{
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

int main(int argc, char *argv[])
{
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);

    int cases;
    cin >> cases;
    
    string number1, number2, number3;
    for (int c = 1; c <= cases; c++)
    {
        cin >> number1 >> number2;
        
        reverse(number1.begin(), number1.end());
        reverse(number2.begin(), number2.end());

        string number3 = add(number1, number2);

        reverse(number3.begin(), number3.end());
        zeroJustify(number3);
        
        cout << number3 << '\n';
    }
    
	return 0;
}
