#include <iostream>
#include <algorithm>

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
    if (sign == -1)
        number1.insert(number1.begin(), '-');

    return number1;
}

// 两个非负整数的乘法。
string multiplicate(string number1, string number2)
{
    // 预分配存储空间。
    string number3(number1.length() + number2.length(), 0);
    
    // 从最低位开始相乘。
    int length1 = number1.length() - 1, length2 = number2.length() - 1;
    for (int i = length1; i >= 0; i--)
		for (int j = length2; j >= 0; j--)
		{
		    int k = number3.length() - 1 - (length1 - i + length2 - j);
			number3[k] += (number2[j] - '0') * (number1[i] - '0');
			number3[k - 1] += number3[k] / BASE;
			number3[k] %= BASE;
		}

    // 将数值转换为对应的数字字符。
	for (int i = 0; i < number3.length(); i++)
        number3[i] += '0';
        
    zeroJustify(number3);
    
    return number3;
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

int main(int argc, char *argv[])
{
    string number1, number2;

    while (cin >> number1 >> number2)
    {
        //pair<string, string> result = divide(number1, number2);
        //cout << result.first << ' ' << result.second << '\n';
        cout << subtract(number1, number2) << '\n';
    }

    return 0;
}
