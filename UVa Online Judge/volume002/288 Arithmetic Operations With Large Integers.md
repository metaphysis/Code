[UVa 288 Arithmetic Operations With Large Integers](https://blog.csdn.net/metaphysis/article/details/161361582)

## 题目分析

本题要求处理包含大整数的算术表达式，其中大整数最多可达 $1000$ 位。表达式中的运算符包括加法（$+$）、减法（$-$）、乘法（$*$）和幂运算（$\texttt{**}$）。表达式的长度不超过 $3000$ 个字符，每个测试用例最多包含 $100$ 次运算。

题目有以下几个关键限制：

1. **幂运算的限制**：幂运算使用 $\texttt{**}$ 表示，其中底数必须是 $1$ 到 $9$ 之间的一位正整数，指数可以是任意大的正整数。例如，$2\texttt{**}1993$ 是合法的，而 $12\texttt{**}1993$ 不合法，因为底数 $12$ 大于 $9$。

2. **运算优先级**：遵循常规的算术优先级规则，即幂运算优先级最高，乘法和除法次之，加法和减法最低。题目中没有括号，但优先级规则仍然有效。

3. **输入格式**：每个测试用例占一行，表达式中没有空格或其他非法字符。数字作为 $\texttt{ASCII}$ 文本存储，可以有前导零（虽然题目未明确说明，但实现中应考虑）。

4. **输出要求**：输出每个表达式求值的精确结果，每个测试用例的结果占一行。

## 解题思路

### 整体框架

解决本题需要完成以下几个核心任务：

1. **大整数的表示与运算**：由于数字可达 $1000$ 位，远超内置整数类型的范围，必须实现高精度大整数类，支持加法、减法、乘法、幂运算以及比较操作。

2. **表达式解析**：将输入的中缀表达式字符串转换为便于计算的后缀表达式（逆波兰表示法）。

3. **表达式求值**：对后缀表达式进行计算，得到最终结果。

### 大整数类的设计

#### 存储方式

代码采用基数为 $10000$ 的万进制存储方式，每个“数位”存储 $0$ 到 $9999$ 之间的整数。这种表示方法的优点在于：

- 将十进制字符串每 $4$ 位一组转换为整数存储，减少了数位数量，提高了运算效率。
- 基数 $10000$ 保证了两个数位相乘的结果不超过 $10^8$，在 $32$ 位整数范围内不会溢出。

```cpp
static const int base = 10000;  // 基数
static const int width = 4;     // 每组位数
vector<int> digits;             // 从低位到高位存储
int sign;                       // 符号：POSITIVE(1) 或 NEGATIVE(-1)
```

#### 大整数的运算实现

**加法运算**：
- 如果两个加数符号不同，转换为减法运算。
- 确保被加数的位数不少于加数，从低位到高位逐位相加，处理进位。

**减法运算**：
- 如果一个数为负数，转换为加法运算。
- 确保被减数不小于减数，从低位到高位逐位相减，处理借位。

**乘法运算**：
- 使用 $O(n \times m)$ 的竖式乘法，逐位相乘后累加，处理进位。

**幂运算**：
- 使用快速幂算法（二分幂），将指数 $y$ 的二进制表示分解，通过重复平方和乘法计算 $x^y$，时间复杂度为 $O(\log y)$。
- 由于指数可能很大（如 $1993$），快速幂是必要的优化。

**比较运算**：
- 先比较符号，正数大于负数。
- 符号相同时比较数位个数，数位多的绝对值大。
- 数位相同时从高位向低位逐位比较。

### 表达式解析与求值

#### 预处理：将 `**` 转换为 `^`

输入中的幂运算符表示为两个连续的星号 `**`，为了便于解析，首先将其替换为单个字符 `^`：

```cpp
for (int i = line.length(); i >= 1; i--)
    if (line[i] == '*' && line[i - 1] == '*') {
        line.erase(line.begin() + i);
        line[i - 1] = '^';
    }
```

#### 中缀表达式转后缀表达式

使用调度场算法（$\texttt{Shunting-yard algorithm}$）将中缀表达式转换为后缀表达式：

1. 从左到右扫描中缀表达式的每个元素（数字或运算符）。
2. 遇到数字时，直接输出到后缀表达式队列。
3. 遇到运算符时，将其与运算符栈顶的运算符比较优先级：
   - 如果当前运算符优先级高于栈顶运算符，则压入栈。
   - 否则，弹出栈顶运算符并输出，直到栈顶优先级低于当前运算符，然后将当前运算符压栈。
4. 扫描结束后，将栈中剩余运算符依次弹出输出。

优先级定义如下（数值越大优先级越高）：
- 幂运算（`^`）：优先级 $3$
- 乘法（`*`）：优先级 $2$
- 加法（`+`）和减法（`-`）：优先级 $1$

#### 后缀表达式求值

后缀表达式求值的算法非常简洁：

1. 从左到右扫描后缀表达式的每个元素。
2. 遇到数字时，将其转换为大整数并压入结果栈。
3. 遇到运算符时，从结果栈弹出两个操作数（注意弹出顺序：先弹出的是右操作数，后弹出的是左操作数），执行相应的运算，然后将结果压回栈中。
4. 扫描结束后，栈顶元素即为表达式的值。

### 边界情况处理

1. **前导零**：大整数类在运算后应移除前导零，例如 `000123` 应规范化为 `123`。
2. **零值**：大整数类应能正确表示和比较零值，零的符号应为正。
3. **幂运算的指数为 $0$**：任何非零数的 $0$ 次方等于 $1$，$0^0$ 在本题中未定义，但根据题目约束不会出现。
4. **单个数字**：表达式中可能只有一个数字，没有运算符，此时应直接输出该数字。

## 算法复杂度分析

- **时间复杂度**：
  - 大整数加法/减法：$O(n)$，其中 $n$ 为数的位数（以基数为单位）。
  - 大整数乘法：$O(n \times m)$，最坏情况下 $O(n^2)$。
  - 大整数幂运算：$O(\log y \times M(n))$，其中 $M(n)$ 为乘法的复杂度。
  - 表达式解析和求值：$O(L)$，其中 $L$ 为表达式长度。

- **空间复杂度**：$O(n)$，用于存储大整数和表达式栈。

## 代码实现

```cpp
// Arithmetic Operations With Large Integers
// UVa ID: 288
// Verdict: Accepted
// Submission Date: 2016-05-24
// UVa Run Time: 0.000s
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
    friend BigInteger operator^(const BigInteger&, const BigInteger&);
    friend BigInteger operator^(const BigInteger&, const unsigned int&);
    friend BigInteger operator<<(const BigInteger&, const unsigned int&);

public:
    BigInteger() {};

    BigInteger(const long long&);
    BigInteger(const string&);
    
    // 获取最低位的数字（用于快速判断奇偶性）
    int lastDigit() const
    {
        return digits.front();
    }
    
    ~BigInteger() {};

private:
    void zeroJustify(void);

    // 采用 10000 作为基数，数位宽度为 4
    static const int base = 10000;
    static const int width = 4;

    int sign;               // 符号：1 为正数，-1 为负数
    vector<int> digits;     // 数位数组，低位在前，高位在后
};

// 从长整型构造大整数
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
        // 不断模基数取余，得到各个数位
        while (number)
        {
            digits.push_back(number % base);
            number /= base;
        }
    }
    zeroJustify();
};

// 从十进制字符串构造大整数
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
        
        // 每 width 位一组，转换为整数存储
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

// 输出大整数
ostream& operator<<(ostream& os, const BigInteger& number)
{
    os << (number.sign > 0 ? "" : "-");
    os << number.digits[number.digits.size() - 1];
    // 输出时每组宽度为 width，不足的前面补零
    for (int i = number.digits.size() - 2; i >= 0; i--)
        os << setw(number.width) << setfill('0') << number.digits[i];
    return os;
}

// 移除前导零
void BigInteger::zeroJustify(void)
{
    for (int i = digits.size() - 1; i >= 1; i--)
    {
        if (digits[i] == 0)
            digits.erase(digits.begin() + i);
        else
            break;
    }
    // 如果值为零，符号设为正
    if (digits.size() == 1 && digits[0] == 0)
        sign = POSITIVE;
}

// 比较两个大整数的大小
// 返回值：x > y 返回 1，x < y 返回 -1，x == y 返回 0
int compare(const BigInteger& x, const BigInteger& y)
{
    // 符号不同，正数大于负数
    if (x.sign == POSITIVE && y.sign == NEGATIVE ||
            x.sign == NEGATIVE && y.sign == POSITIVE)
        return (x.sign == POSITIVE ? 1 : -1);

    // 计算有效数位（跳过前导零）
    int xDigitNumber = x.digits.size() - 1;
    for (; xDigitNumber && x.digits[xDigitNumber] == 0; xDigitNumber--)
        ;
    int yDigitNumber = y.digits.size() - 1;
    for (; yDigitNumber && y.digits[yDigitNumber] == 0; yDigitNumber--)
        ;

    // 符号相同，比较数位个数
    if (xDigitNumber > yDigitNumber)
        return (x.sign == POSITIVE ? 1 : -1);
    if (xDigitNumber < yDigitNumber)
        return (x.sign == NEGATIVE ? 1 : -1);

    // 数位个数相同，逐位比较
    for (int index = xDigitNumber; index >= 0; index--)
    {
        if (x.digits[index] > y.digits[index])
            return (x.sign == POSITIVE ? 1 : -1);
        if (x.digits[index] < y.digits[index])
            return (x.sign == NEGATIVE ? 1 : -1);
    }
    return 0;
}

bool operator==(const BigInteger& x, const BigInteger& y)
{
    return compare(x, y) == 0;
}

bool operator<(const BigInteger& x, const BigInteger& y)
{
    return compare(x, y) < 0;
}

bool operator<=(const BigInteger& x, const BigInteger& y)
{
    return compare(x, y) <= 0;
}

// 大整数加法
BigInteger operator+(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;

    // 符号不同时转换为减法
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

    // 确保 x 的位数不少于 y
    if (x.digits.size() < y.digits.size())
        return (y + x);

    z.sign = x.sign + y.sign >= 0 ? POSITIVE : NEGATIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()) + 1);
    fill(z.digits.begin(), z.digits.end(), 0);

    // 逐位相加，处理进位
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

// 大整数减法
BigInteger operator-(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;

    // 如果有负数，转换为加法
    if (x.sign == NEGATIVE || y.sign == NEGATIVE)
    {
        z = y;
        z.sign = -y.sign;
        return x + z;
    }

    // 确保 x 不小于 y
    if (x < y)
    {
        z = y - x;
        z.sign = NEGATIVE;
        return z;
    }

    z.sign = POSITIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()));
    fill(z.digits.begin(), z.digits.end(), 0);

    // 逐位相减，处理借位
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

// 大整数左移（相当于乘以基数）
BigInteger operator<<(const BigInteger& x, const unsigned int& shift)
{
    BigInteger z;
    z.sign = x.sign;
    z.digits.resize(x.digits.size());
    copy(x.digits.begin(), x.digits.end(), z.digits.begin());
    for (int i = 0; i < shift; i++)
        z.digits.insert(z.digits.begin(), 0);
    z.zeroJustify();
    return z;
}

// 大整数乘法
BigInteger operator*(const BigInteger& x, const BigInteger& y)
{
    BigInteger z;
    z.sign = x.sign * y.sign;
    z.digits.resize(x.digits.size() + y.digits.size());
    fill(z.digits.begin(), z.digits.end(), 0);

    // 竖式乘法
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

// 大整数除法（整除）
BigInteger operator/(const BigInteger& x, const BigInteger& y)
{
    BigInteger z, r;
    z.sign = x.sign * y.sign;
    r.sign = POSITIVE;
    z.digits.resize(x.digits.size() - y.digits.size() + 1);
    r.digits.resize(y.digits.size() + 1);
    fill(z.digits.begin(), z.digits.end(), 0);
    fill(r.digits.begin(), r.digits.end(), 0);

    // 从高位向低位逐位试除
    for (int i = x.digits.size() - 1; i >= 0; i--)
    {
        r.digits.insert(r.digits.begin(), x.digits[i]);
        
        // 二分查找试商
        int low = 0, high = z.base - 1, middle = (high + low + 1) >> 1;
        while (low < high)
        {
            if ((y * BigInteger(middle)) <= r)
                low = middle;
            else
                high = middle - 1;
            middle = (high + low + 1) >> 1;
        }
        
        // 从被除数中减去试商乘以除数的结果
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

// 大整数取模
BigInteger operator%(const BigInteger& x, const BigInteger& y)
{
    return (x - (x / y) * y);
}

// 快速幂（指数为无符号整型）
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

// 快速幂（指数为大整数）
BigInteger operator^(const BigInteger& x, const BigInteger& y)
{
    if (y == ZERO)
        return BigInteger(1);
    if (y == ONE)
        return x;
    if (y == TWO)
        return x * x;
    // 根据指数最低位判断奇偶性
    if (y.lastDigit() & 1 > 0)
        return ((x ^ (y / 2)) ^ 2) * x;
    else
        return ((x ^ (y / 2)) ^ 2);
}

// 表达式元素结构体
struct symbol
{
    char operatorType;      // 运算符类型
    BigInteger value;       // 数值（当 isOperator 为 false 时有效）
    bool isOperator;        // 是否为运算符
};

// 计算后缀表达式的值
BigInteger calculate(vector<string> postfix)
{
    vector<symbol> symbols;
    // 将后缀表达式字符串转换为 symbol 结构体数组
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
    
    stack<BigInteger> result;
    for (int i = 0; i < symbols.size(); i++)
    {
        symbol s = symbols[i];
        if (s.isOperator == false)
            result.push(s.value);
        else
        {
            // 弹出两个操作数，注意顺序：先弹出的是右操作数
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
        }
    }
    return result.top();
}

// 判断运算符 a 的优先级是否不高于 b
bool lessPriority(char a, char b)
{
    map<char, int> priority;
    priority.insert(pair<char, int>('+', 1));
    priority.insert(pair<char, int>('-', 1));
    priority.insert(pair<char, int>('*', 2));
    priority.insert(pair<char, int>('^', 3));
    return priority[a] <= priority[b];
}

// 将输入字符串解析为元素序列（数字和运算符交替）
vector<string> parse(string line)
{
    vector<string> postfix;
    // 将 "**" 替换为 "^"
    for (int i = line.length(); i >= 1; i--)
        if (line[i] == '*' && line[i - 1] == '*')
        {
            line.erase(line.begin() + i);
            line[i - 1] = '^';
        }
    
    // 分离数字和运算符
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
    return postfix;
}

// 将中缀表达式转换为后缀表达式
vector<string> toPostfix(vector<string> infixNotation)
{
    stack<string> operands;   // 操作数栈（实际存放后缀表达式）
    stack<string> operators;   // 运算符栈

    for (int i = 0; i < infixNotation.size(); i++)
    {
        string c = infixNotation[i];
        if (isdigit(c.front()))
        {
            operands.push(c);   // 数字直接输出
        }
        else
        {
            if (c.front() == '(')
                operators.push(c);
            else if (c.front() == ')')
            {
                // 遇到右括号，弹出运算符直到左括号
                while (!operators.empty() && operators.top().front() != '(')
                {
                    operands.push(operators.top());
                    operators.pop();
                }
                if (!operators.empty())
                    operators.pop();   // 弹出左括号
            }
            else
            {
                // 处理运算符优先级
                if (operators.empty() || operators.top().front() == '('
                    || !lessPriority(c.front(), operators.top().front()))
                    operators.push(c);
                else
                {
                    while (!operators.empty() && lessPriority(c.front(), operators.top().front()))
                    {
                        operands.push(operators.top());
                        operators.pop();
                    }
                    operators.push(c);
                }
            }
        }
    }

    // 弹出剩余运算符
    while (!operators.empty())
    {
        operands.push(operators.top());
        operators.pop();
    }

    // 反转得到正确的后缀表达式顺序
    vector<string> postfixNotation;
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
```

## 总结

本题综合考察了大整数运算的实现和算术表达式求值。通过实现万进制的大整数类，配合快速幂算法，可以有效处理 $1000$ 位大整数和 $1993$ 次幂这样的极端情况。表达式求值部分采用经典的调度场算法和逆波兰表达式求值，代码结构清晰，易于理解和扩展。需要注意的是，幂运算符 $\texttt{**}$ 的优先级最高，且在转换为后缀表达式时要正确处理其右结合性（虽然本题中幂运算的底数仅为一位数字，但实现仍需考虑正确性）。
