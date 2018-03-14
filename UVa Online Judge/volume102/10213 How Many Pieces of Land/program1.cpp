// How Many Pieces of Land? （土地分割）
// PC/UVa IDs: 110602/10213, Popularity: B, Success rate: average Level: 2
// Verdict: Accepted
// Submission Date: 2016-03-01
// UVa Run Time: 0.009s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int POSITIVE = 1, NEGATIVE = -1, EQUAL = 0;

class BigInteger
{
    friend ostream & operator<<(ostream &, const BigInteger &);

    friend int compare(const BigInteger &, const BigInteger &);
    friend bool operator<(const BigInteger &, const BigInteger &);
    friend bool operator<=(const BigInteger &, const BigInteger &);

    friend BigInteger operator+(const BigInteger &, const BigInteger &);
    friend BigInteger operator-(const BigInteger &, const BigInteger &);
    friend BigInteger operator*(const BigInteger &, const BigInteger &);
    friend BigInteger operator/(const BigInteger &, const BigInteger &);
    friend BigInteger operator^(const BigInteger &, const unsigned int &);
    friend BigInteger operator<<(const BigInteger &, unsigned int);

  public:
     BigInteger()
    {
    };

    BigInteger(const long long &);
    BigInteger(const string &);

    ~BigInteger()
    {
    };

  private:
    void zeroJustify(void);
    bool lessOrEqual(const BigInteger &, const int &, const BigInteger &);

    vector < int >digits;
    static const int base = 10000;
    static const int width = 4;
    int sign;
};

BigInteger operator+(const BigInteger &, const BigInteger &);
BigInteger operator-(const BigInteger &, const BigInteger &);

BigInteger::BigInteger(const long long &value)
{
    if (value == 0)
    {
        sign = POSITIVE;
        digits.push_back(0);
    }
    else
    {
        long long number = value;
        sign = (number >= 0 ? POSITIVE : NEGATIVE);
        if (sign == NEGATIVE)
            number = -number;

        while (number)
        {
            digits.push_back(number % base);
            number /= base;
        }
    }

    zeroJustify();
};

BigInteger::BigInteger(const string & value)
{
    if (value.length() == 0)
    {
        sign = POSITIVE;
        digits.push_back(0);
    }
    else
    {
        sign = value[0] == '-' ? NEGATIVE : POSITIVE;

        string block;
        int index = value.length() - 1;

        while (index >= 0)
        {
            if (isdigit(value[index]))
                block.insert(block.begin(), value[index]);

            if (block.length() == width)
            {
                digits.push_back(stoi(block));
                block.clear();
            }

            index--;
        }

        if (block.length() > 0)
            digits.push_back(stoi(block));
    }

    zeroJustify();
}

ostream & operator<<(ostream & os, const BigInteger & integer)
{
    os << (integer.sign > 0 ? "" : "-");
    os << integer.digits[integer.digits.size() - 1];
    for (int i = integer.digits.size() - 2; i >= 0; i--)
        os << setw(integer.width) << setfill('0') << integer.digits[i];
    return os;
}

void BigInteger::zeroJustify(void)
{
    for (int i = digits.size() - 1; i >= 1; i--)
        if (digits[i] == 0)
            digits.erase(digits.begin() + i);
        else
            break;

    if (digits.size() == 1 && digits[0] == 0)
        sign = POSITIVE;
}

BigInteger operator+(const BigInteger & a, const BigInteger & b)
{
    BigInteger c;

    // 如果两个加数的符号不同，转换为减法运算。
    if (a.sign != b.sign)
    {
        if (a.sign == NEGATIVE)
        {
            c = a;
            c.sign = POSITIVE;
            return (b - c);
        }
        else
        {
            c = b;
            c.sign = POSITIVE;
            return (a - c);
        }
    }

    // 两个加数的符号相同。
    c.sign = a.sign;

    // 确保 a 的位数不比 b 的位数少。
    if (a.digits.size() < b.digits.size())
        return (b + a);

    int carry = 0;
    int index = 0;

    while (index < a.digits.size() && index < b.digits.size())
    {
        int sum = a.digits[index] + b.digits[index] + carry;
        carry = sum / c.base;
        c.digits.push_back(sum % c.base);
        index++;
    }

    while (index < a.digits.size())
    {
        int sum = a.digits[index] + carry;
        carry = sum / c.base;
        c.digits.push_back(sum % c.base);
        index++;
    }

    if (carry)
        c.digits.push_back(1);

    c.zeroJustify();

    return c;
}

int compare(const BigInteger & a, const BigInteger & b)
{
    if (a.sign == POSITIVE && b.sign == NEGATIVE)
        return POSITIVE;

    if (a.sign == NEGATIVE && b.sign == POSITIVE)
        return NEGATIVE;

    if (a.digits.size() > b.digits.size())
        return POSITIVE * a.sign;

    if (a.digits.size() < b.digits.size())
        return NEGATIVE * a.sign;

    int index = a.digits.size() - 1;
    while (index >= 0)
    {
        if (a.digits[index] > b.digits[index])
            return POSITIVE * a.sign;

        if (a.digits[index] < b.digits[index])
            return NEGATIVE * a.sign;

        index--;
    }

    return EQUAL;
}

bool operator<(const BigInteger & a, const BigInteger & b)
{
    return compare(a, b) < 0;
}

bool operator<=(const BigInteger & a, const BigInteger & b)
{
    return compare(a, b) <= 0;
}

BigInteger operator-(const BigInteger & a, const BigInteger & b)
{
    BigInteger c;

    c.sign = POSITIVE;

    if (a.sign == NEGATIVE || b.sign == NEGATIVE)
    {
        c = b;
        c.sign = -b.sign;
        c = a + c;

        return c;
    }

    if (a < b)
    {
        c = b - a;
        c.sign = NEGATIVE;

        return c;
    }

    int borrow = 0;
    int index = 0;

    while (index < a.digits.size() && index < b.digits.size())
    {
        int subtract = a.digits[index] - borrow - b.digits[index];
        borrow = 0;
        if (subtract < 0)
        {
            subtract += c.base;
            borrow = 1;
        }
        c.digits.push_back(subtract % c.base);
        index++;
    }

    while (index < a.digits.size())
    {
        int subtract = a.digits[index] - borrow;
        borrow = 0;
        if (subtract < 0)
        {
            subtract += c.base;
            borrow = 1;
        }
        c.digits.push_back(subtract % c.base);
        index++;
    }

    c.zeroJustify();

    return c;
}

BigInteger operator<<(const BigInteger & a, unsigned int b)
{
    BigInteger c;

    c.sign = a.sign;
    c.digits.resize(a.digits.size());
    copy(a.digits.begin(), a.digits.end(), c.digits.begin());

    for (int i = 0; i < b; i++)
        c.digits.insert(c.digits.begin(), 0);

    c.zeroJustify();

    return c;
}

BigInteger operator*(const BigInteger & a, const BigInteger & b)
{
    BigInteger c;

    c.sign = a.sign * b.sign;
    c.digits.resize(a.digits.size() + b.digits.size());
    fill(c.digits.begin(), c.digits.end(), 0);

    for (int i = 0; i < b.digits.size(); i++)
        for (int j = 0; j < a.digits.size(); j++)
        {
            c.digits[i + j] += a.digits[j] * b.digits[i];
            c.digits[i + j + 1] += c.digits[i + j] / c.base;
            c.digits[i + j] %= c.base;
        }

    c.zeroJustify();

    return c;
}

// 判断 b * middle<= subtracted 是否成立，成立返回 true，否则返回 false。
bool BigInteger::lessOrEqual
    (const BigInteger & b, const int &middle, const BigInteger & subtracted)
{
    // 由于存在关系 subtracted.digits.size() = b.digits.size() + 1，若 b * middle
    // 的最高位大于 subtracted，则可确定 b * middle > subtracted。
    int carry = b.digits[b.digits.size() - 1] * middle;
    if ((carry / b.base) > subtracted.digits[subtracted.digits.size() - 1])
        return false;

    // 逐位比较，当两个数位不等时，记录比较结果，最后一次的比较结果决定了 b * middle
    // 和 subtracted 的大小关系。
    bool flag = true;
    carry = 0;
    for (int i = 0; i < b.digits.size(); i++)
    {
        int sum = b.digits[i] * middle + carry;
        carry = sum / b.base;
        sum %= base;
        if (subtracted.digits[i] != sum)
            flag = sum < subtracted.digits[i];
    }

    // 进位需要与 subtracted 的最高位比较。
    if (carry != subtracted.digits[subtracted.digits.size() - 1])
        flag = carry < subtracted.digits[subtracted.digits.size() - 1];

    return flag;
}

BigInteger operator/(const BigInteger & a, const BigInteger & b)
{
    BigInteger c;
    BigInteger subtracted;

    c.sign = a.sign * b.sign;

    // 要为商 c 和表示被减数的 subtracted 分配存储空间。
    c.digits.resize(a.digits.size() - b.digits.size() + 1);
    subtracted.digits.resize(b.digits.size() + 1);

    // 初始化值。
    fill(c.digits.begin(), c.digits.end(), 0);
    fill(subtracted.digits.begin(), subtracted.digits.end(), 0);

    for (int i = a.digits.size() - 1; i >= 0; i--)
    {
        // 获取被除数。
        for (int j = subtracted.digits.size() - 1; j > 0; j--)
            subtracted.digits[j] = subtracted.digits[j - 1];
        subtracted.digits[0] = a.digits[i];

        // 通过二分试除法得到对应位的商。
        int high = c.base - 1, low = 0;
        int middle = (high + low + 1) >> 1;
        while (high > low)
        {
            if (c.lessOrEqual(b, middle, subtracted))
                low = middle;
            else
                high = middle - 1;
            middle = (high + low + 1) >> 1;
        }

        // 从 subtracted 中减去 middle 个 b。
        int borrow, index = 0;
        for (; index < b.digits.size(); index++)
        {
            // 决定借位的数量。
            int difference =
                subtracted.digits[index] - middle * b.digits[index];
            if (difference < 0)
                borrow = (c.base - 1 - difference) / c.base;
            else
                borrow = 0;

            // 高位减去借位数量。
            subtracted.digits[index + 1] -= borrow;

            // 低位加上借位。
            difference += c.base * borrow;
            subtracted.digits[index] = difference % c.base;
        }

        // 将对应位的商存入结果中。
        for (int j = c.digits.size() - 1; j > 0; j--)
            c.digits[j] = c.digits[j - 1];
        c.digits[0] = middle;
    }

    // 清除前导 0。
    c.zeroJustify();

    return c;
}


BigInteger operator^(const BigInteger & a, const unsigned int &b)
{
    if (b == 0)
        return BigInteger(1);

    if (b == 1)
        return a;

    if (b == 2)
        return a * a;

    return ((a ^ (b / 2)) ^ 2) * (a ^ (b % 2));
}

int main(int argc, char *argv[])
{
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int cases;
    string number;

    cin >> cases;
    while (cases--)
    {
        cin >> number;
        BigInteger a(number);

        cout << ((a ^ 4) - BigInteger("6") * (a ^ 3) +
            BigInteger("23") * (a ^ 2) - BigInteger("18") * a +
            BigInteger("24")) / BigInteger("24") << "\n";
    }

    return 0;
}
