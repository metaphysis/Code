// Arithmetic Operations With Large Integers
// UVa ID: 288
// Verdict: Accepted
// Submission Date: 2016-05-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>

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
    friend BigInteger operator^(const BigInteger&, const BigInteger&);
    friend BigInteger operator^(const BigInteger&, const unsigned int&);
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

    // 采用 10000 作为基数。数位宽度为 4。
    static const int base = 10000;
    static const int width = 4;

    int sign;
    vector < int > digits;
};

BigInteger operator+(const BigInteger&, const BigInteger&);
BigInteger operator-(const BigInteger&, const BigInteger&);

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

// 将十进制的字符串转换为大整数。
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

        // 四个数字作为一组，转换为整数存储到数位数组中。
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

    // 移除前导零。
    zeroJustify();
}

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

// 比较两个高精度整数的大小。
// x 大于 y，返回 1，x 小于 y，返回 -1，x 等于 y，返回 0。
// 为了除法的需要，对未经前导零调整的整数也能正确处理。
int compare(const BigInteger& x, const BigInteger& y)
{
    // 符号不同，正数大于负数。
    if (x.sign == POSITIVE && y.sign == NEGATIVE ||
            x.sign == NEGATIVE && y.sign == POSITIVE)
        return (x.sign == POSITIVE ? 1 : -1);

    // 确定 x 和 y 的有效数位，即前导零不计入有效数位。
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

// 等于比较运算符。
bool operator==(const BigInteger& x, const BigInteger& y)
{
    return compare(x, y) == 0;
}

// 小于比较运算符。
bool operator<(const BigInteger& x, const BigInteger& y)
{
    return compare(x, y) < 0;
}

// 小于等于比较运算符。
bool operator<=(const BigInteger& x, const BigInteger& y)
{
    return compare(x, y) <= 0;
}

// 高精度整数加法。
BigInteger operator+(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;

    // 如果两个加数的符号不同，转换为减法运算。
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

    // 确保 x 的位数比 y 的位数多，便于计算。
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

// 高精度整数减法。
BigInteger operator-(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;

    // 当 x 和 y 至少有一个是负数，转换为加法运算。
    if (x.sign == NEGATIVE || y.sign == NEGATIVE)
    {
        z = y;
        z.sign = -y.sign;
        return x + z;
    }

    // 都为正数，确保 x 大于 y，便于计算。
    if (x < y)
    {
        z = y - x;
        z.sign = NEGATIVE;
        return z;
    }

    // 设置符号位并预先分配存储空间。
    z.sign = POSITIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()));

    fill(z.digits.begin(), z.digits.end(), 0);

    // 逐位相减，考虑借位。
    int index = 0, borrow = 0;
    for (; index < x.digits.size(); index++)
    {
        // 获取对应位的差。
        int difference = x.digits[index] - borrow;
        difference -= index < y.digits.size() ? y.digits[index] : 0;

        // 确定是否有借位。
        borrow = 0;
        if (difference < 0)
        {
            difference += z.base;
            borrow = 1;
        }

        // 保存相应位差的结果。
        z.digits[index] = difference % z.base;
    }

    // 移除前导零。
    z.zeroJustify();

    return z;
}

// 高精度整数左移运算，左移一位相当于将此数乘以基数。
BigInteger operator<<(const BigInteger& x, const unsigned int& shift)
{
    BigInteger z;

    // 设置符号位，复制向量中的数据。
    z.sign = x.sign;
    z.digits.resize(x.digits.size());
    copy(x.digits.begin(), x.digits.end(), z.digits.begin());

    // 移动指定位数，补零。
    for (int i = 0; i < shift; i++)
        z.digits.insert(z.digits.begin(), 0);

    // 移除前导零。
    z.zeroJustify();

    return z;
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

// 高精度整数除法，为整除运算。
BigInteger operator/(const BigInteger& x, const BigInteger& y)
{
    // z 表示整除得到的商，r 表示每次试除时的被除数。
    BigInteger z, r;

    // 设置商和被除数的符号位。
    z.sign = x.sign * y.sign;
    r.sign = POSITIVE;

    // 为商 z 和表示被除数的 r 预先分配存储空间。
    z.digits.resize(x.digits.size() - y.digits.size() + 1);
    r.digits.resize(y.digits.size() + 1);

    // 初始化值。
    fill(z.digits.begin(), z.digits.end(), 0);
    fill(r.digits.begin(), r.digits.end(), 0);

    // 从高位到低位逐位试除得到对应位的商。
    for (int i = x.digits.size() - 1; i >= 0; i--)
    {
        // 获取被除数，将上一次未被除尽的余数的移到高位加上当前数位继续除。
        r.digits.insert(r.digits.begin(), x.digits[i]);

        // 通过二分试除法得到对应位的商。
        int low = 0, high = z.base - 1, middle = (high + low + 1) >> 1;
        while (low < high)
        {
            if ((y * BigInteger(middle)) <= r)
                low = middle;
            else
                high = middle - 1;
            middle = (high + low + 1) >> 1;
        }

        // 执行减法，从被除数中减去指定数量的 y。
        for (int index = 0; index < y.digits.size(); index++)
        {
            int difference = r.digits[index] - middle * y.digits[index];

            // 确定是否有借位产生。
            int borrow = 0;
            if (difference < 0)
                borrow = (z.base - 1 - difference) / z.base;

            // 高位减去借位数量。
            r.digits[index + 1] -= borrow;

            // 低位加上借位。
            difference += z.base * borrow;
            r.digits[index] = difference % z.base;
        }

        // 将对应位的商存入结果中。
        z.digits.insert(z.digits.begin(), middle);
    }

    // 移除前导零。
    z.zeroJustify();

    return z;
}

// 高精度整数求模运算。适用于同为正整数的情况。
BigInteger operator%(const BigInteger& x, const BigInteger& y)
{
    return (x - (x / y) * y);
}

// 高精度整数乘方运算。
BigInteger operator^(const BigInteger& x, const unsigned int& y)
{
    if (y == 0)
        return BigInteger(1);

    if (y == 1)
        return x;

    if (y == 2)
        return x * x;

    if (y & 1 > 0)
        return ((x ^ (y / 2)) ^ 2) * x;
    else
        return ((x ^ (y / 2)) ^ 2);
}

const BigInteger ZERO = BigInteger(0), ONE = BigInteger(1), TWO = BigInteger(2);

// 高精度整数乘方运算。
BigInteger operator^(const BigInteger& x, const BigInteger& y)
{
    if (y == ZERO)
        return BigInteger(1);

    if (y == ONE)
        return x;

    if (y == TWO)
        return x * x;

    if (y.lastDigit() & 1 > 0)
        return ((x ^ (y / 2)) ^ 2) * x;
    else
        return ((x ^ (y / 2)) ^ 2);
}

struct symbol
{
    char operatorType;
    BigInteger value;
    bool isOperator;
};

// 使用栈来计算后缀表达式的值。从左至右扫描后缀表达式，如果是数字，则压入结果栈，
// 如果是运算符，则取出结果栈栈顶的两个元素进行运算符所指定的运算，然后将运算结果
// 压入结果栈中，直到后缀表达式处理完毕，结果栈的栈顶元素即为表达式的值。
BigInteger calculate(vector <string> postfix)
{
    //cout << postfix.size() << endl;
    //for (int i = 0; i < postfix.size(); i++)
       //cout << postfix[i];
    //cout << endl;
    
    vector <symbol> symbols;
    for (int i = 0; i < postfix.size(); i++)
    {
        symbol s;
        if (isdigit(postfix[i].front()))
        {
            s.value = BigInteger(postfix[i]);
            s.isOperator = false;
        }
        else
        {
            s.operatorType = postfix[i].front();
            s.isOperator = true;
        }
        symbols.push_back(s);
    }
    
    //cout << symbols.size() << endl;
    
    stack<BigInteger> result;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.isOperator == false)
            result.push(s.value);
        else
        {
            BigInteger b = result.top();
            result.pop();
            BigInteger a = result.top();
            result.pop();

            switch (s.operatorType)
            {
                case '+':
                    result.push(a + b);
                    break;
                case '-':
                    result.push(a - b);
                    break;
                case '*':
                    result.push(a * b);
                    break;
                case '^':
                    result.push(a ^ b);
                    break;
                default:
                    break;
            }
            
            //cout << result.top() << endl;
        }
    }
    
    return result.top();
}

// 比较运算符在栈中的优先级顺序。在栈中，括号的优先级最小。
bool lessPriority(char a, char b)
{
    map<char, int> priority;
    priority.insert(pair<char, int>('+', 1));
    priority.insert(pair<char, int>('-', 1));
    priority.insert(pair<char, int>('*', 2));
    priority.insert(pair<char, int>('^', 3));

    return priority[a] <= priority[b];
}

vector <string> parse(string line)
{
    vector <string> postfix;
    for (int i = line.length(); i >= 1; i--)
        if (line[i] == '*' && line[i - 1] == '*')
        {
            line.erase(line.begin() + i);
            line[i - 1] = '^';
        }
    
    //cout << line << endl;
    
    for (int i = 0; i < line.length(); i++)
    {
        string block;
        while (isdigit(line[i]))
            block += line[i++];
        postfix.push_back(block);
        
        if (i < line.length())
        {
            block = line[i];
            postfix.push_back(block);
        }
    }
    
    //for (int i = 0; i < postfix.size(); i++)
        //cout << postfix[i];
    //cout << endl;
    
    return postfix;
}

// 将中缀表达式转换为后缀表达式。
vector <string> toPostfix(vector <string> infixNotation)
{
    stack<string> operands; // 操作数栈。
    stack<string> operators;  // 运算符栈。

    for (int i = 0; i < infixNotation.size(); i++)
    {
        string c = infixNotation[i];
        // 如果是数字，直接压入操作数栈中。
        if (isdigit(c.front()))
            operands.push(c);
        else
        {
            // 如果是左括号，直接压入运算符栈中。
            if (c.front() == '(')
                operators.push(c);
            // 如果是右括号，则弹出运算符栈顶元素，直到遇到左括号。
            else if (c.front() == ')')
            {
                while (!operators.empty() && operators.top().front() != '(')
                {
                    operands.push(operators.top());
                    operators.pop();
                }

                if (!operators.empty())
                    operators.pop();
            }
            else
            {
                // 如果是非括号运算符，当运算符堆栈为空，或者运算符堆栈栈顶元素
                // 为左括号，或者比运算符堆栈栈顶运算符的优先级高，将当前运算符
                // 压入运算符堆栈。
                if (operators.empty() || operators.top().front() == '('
                    || !lessPriority(c.front(), operators.top().front()))
                    operators.push(c);
                else
                {
                    // 当运算符的优先级比运算符堆栈栈顶元素的优先级低或相等时，
                    // 弹出运算符堆栈栈顶元素，直到运算符堆栈为空，或者遇到比
                    // 当前运算符优先级低的运算符。
                    while (!operators.empty() && lessPriority(c.front(), operators.top().front()))
                    {
                        operands.push(operators.top());
                        operators.pop();
                    }

                    // 将当前运算符压入运算符堆栈。
                    operators.push(c);
                }
            }
        }
    }

    // 当中缀表达式处理完毕，运算符堆栈不为空时，逐个弹出压入到操作数堆栈中。
    while (!operators.empty())
    {
        operands.push(operators.top());
        operators.pop();
    }

    // 将操作数堆栈中保存的后缀表达式转换为一个字符串以利于后续值的计算。
    vector <string> postfixNotation;
    while (!operands.empty())
    {
        postfixNotation.insert(postfixNotation.begin(), operands.top());
        operands.pop();
    }

    return postfixNotation;
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
        cout << calculate(toPostfix(parse(line))) << endl;

    return 0;
}
