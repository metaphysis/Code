// 500!
// UVa ID: 623
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 0.010s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int POSITIVE = 1, NEGATIVE = -1, EQUAL = 0;

class BigInteger {
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
    friend BigInteger operator^(const BigInteger&, const unsigned int&);
    friend BigInteger operator^(const BigInteger&, const BigInteger&);
    friend BigInteger operator<<(const BigInteger&, const unsigned int&);

public:
    BigInteger() {};
    BigInteger(const long long&);
    BigInteger(const string&);
    int lastDigit() const { return digits.front(); }
    ~BigInteger() {};

private:
    void zeroJustify(void);
    static const int base = 10000;
    static const int width = 4;
    int sign;
    vector<int> digits;
};

BigInteger operator+(const BigInteger&, const BigInteger&);
BigInteger operator-(const BigInteger&, const BigInteger&);

BigInteger::BigInteger(const long long& value) {
    if (value == 0) {
        sign = POSITIVE;
        digits.push_back(0);
    } else {
        sign = (value >= 0 ? POSITIVE : NEGATIVE);
        long long number = abs(value);
        while (number) {
            digits.push_back(number % base);
            number /= base;
        }
    }
    zeroJustify();
}

BigInteger::BigInteger(const string& value) {
    if (value.length() == 0) {
        sign = POSITIVE;
        digits.push_back(0);
    } else {
        sign = value[0] == '-' ? NEGATIVE : POSITIVE;
        string block;
        for (int index = value.length() - 1; index >= 0; index--) {
            if (isdigit(value[index]))
                block.insert(block.begin(), value[index]);
            if (block.length() == width) {
                digits.push_back(stoi(block));
                block.clear();
            }
        }
        if (block.length() > 0)
            digits.push_back(stoi(block));
    }
    zeroJustify();
}

ostream& operator<<(ostream& os, const BigInteger& number) {
    os << (number.sign > 0 ? "" : "-");
    os << number.digits[number.digits.size() - 1];
    for (int i = number.digits.size() - 2; i >= 0; i--)
        os << setw(number.width) << setfill('0') << number.digits[i];
    return os;
}

void BigInteger::zeroJustify(void) {
    for (int i = digits.size() - 1; i >= 1; i--) {
        if (digits[i] == 0)
            digits.erase(digits.begin() + i);
        else
            break;
    }
    if (digits.size() == 1 && digits[0] == 0)
        sign = POSITIVE;
}

int compare(const BigInteger& x, const BigInteger& y) {
    if (x.sign == POSITIVE && y.sign == NEGATIVE || x.sign == NEGATIVE && y.sign == POSITIVE)
        return (x.sign == POSITIVE ? 1 : -1);
    int xDigitNumber = x.digits.size() - 1;
    for (; xDigitNumber && x.digits[xDigitNumber] == 0; xDigitNumber--);
    int yDigitNumber = y.digits.size() - 1;
    for (; yDigitNumber && y.digits[yDigitNumber] == 0; yDigitNumber--);
    if (xDigitNumber > yDigitNumber)
        return (x.sign == POSITIVE ? 1 : -1);
    if (xDigitNumber < yDigitNumber)
        return (x.sign == NEGATIVE ? 1 : -1);
    for (int index = xDigitNumber; index >= 0; index--) {
        if (x.digits[index] > y.digits[index])
            return (x.sign == POSITIVE ? 1 : -1);
        if (x.digits[index] < y.digits[index])
            return (x.sign == NEGATIVE ? 1 : -1);
    }
    return 0;
}

bool operator==(const BigInteger& x, const BigInteger& y) {
    return compare(x, y) == 0;
}

bool operator<(const BigInteger& x, const BigInteger& y) {
    return compare(x, y) < 0;
}

bool operator<=(const BigInteger& x, const BigInteger& y) {
    return compare(x, y) <= 0;
}

BigInteger operator+(const BigInteger& x, const BigInteger& y) {
    BigInteger z;
    if (x.sign == NEGATIVE && y.sign == POSITIVE) {
        z = x;
        z.sign = POSITIVE;
        return (y - z);
    } else if (x.sign == POSITIVE && y.sign == NEGATIVE) {
        z = y;
        z.sign = POSITIVE;
        return (x - z);
    }
    if (x.digits.size() < y.digits.size())
        return (y + x);
    z.sign = x.sign + y.sign >= 0 ? POSITIVE : NEGATIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()) + 1);
    fill(z.digits.begin(), z.digits.end(), 0);
    int index = 0, carry = 0;
    for (; index < x.digits.size(); index++) {
        int sum = x.digits[index] + carry;
        sum += index < y.digits.size() ? y.digits[index] : 0;
        carry = sum / z.base;
        z.digits[index] = sum % z.base;
    }
    z.digits[index] = carry;
    z.zeroJustify();
    return z;
}

BigInteger operator-(const BigInteger& x, const BigInteger& y) {
    BigInteger z;
    if (x.sign == NEGATIVE || y.sign == NEGATIVE) {
        z = y;
        z.sign = -y.sign;
        return x + z;
    }
    if (x < y) {
        z = y - x;
        z.sign = NEGATIVE;
        return z;
    }
    z.sign = POSITIVE;
    z.digits.resize(max(x.digits.size(), y.digits.size()));
    fill(z.digits.begin(), z.digits.end(), 0);
    int index = 0, borrow = 0;
    for (; index < x.digits.size(); index++) {
        int difference = x.digits[index] - borrow;
        difference -= index < y.digits.size() ? y.digits[index] : 0;
        borrow = 0;
        if (difference < 0) {
            difference += z.base;
            borrow = 1;
        }
        z.digits[index] = difference % z.base;
    }
    z.zeroJustify();
    return z;
}

BigInteger operator<<(const BigInteger& x, const unsigned int& shift) {
    BigInteger z;
    z.sign = x.sign;
    z.digits.resize(x.digits.size());
    copy(x.digits.begin(), x.digits.end(), z.digits.begin());
    for (int i = 0; i < shift; i++)
        z.digits.insert(z.digits.begin(), 0);
    z.zeroJustify();
    return z;
}

BigInteger operator*(const BigInteger& x, const BigInteger& y) {
    BigInteger z;
    z.sign = x.sign * y.sign;
    z.digits.resize(x.digits.size() + y.digits.size());
    fill(z.digits.begin(), z.digits.end(), 0);
    for (int i = 0; i < y.digits.size(); i++)
        for (int j = 0; j < x.digits.size(); j++) {
            z.digits[i + j] += x.digits[j] * y.digits[i];
            z.digits[i + j + 1] += z.digits[i + j] / z.base;
            z.digits[i + j] %= z.base;
        }
    z.zeroJustify();
    return z;
}

BigInteger operator/(const BigInteger& x, const BigInteger& y) {
    BigInteger z, r;
    z.sign = x.sign * y.sign;
    r.sign = POSITIVE;
    z.digits.resize(x.digits.size() - y.digits.size() + 1);
    r.digits.resize(y.digits.size() + 1);
    fill(z.digits.begin(), z.digits.end(), 0);
    fill(r.digits.begin(), r.digits.end(), 0);
    for (int i = x.digits.size() - 1; i >= 0; i--) {
        r.digits.insert(r.digits.begin(), x.digits[i]);
        int low = 0, high = z.base - 1, middle = (high + low + 1) >> 1;
        while (low < high) {
            if ((y * BigInteger(middle)) <= r)
                low = middle;
            else
                high = middle - 1;
            middle = (high + low + 1) >> 1;
        }
        for (int index = 0; index < y.digits.size(); index++) {
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

BigInteger operator%(const BigInteger& x, const BigInteger& y) {
    return (x - (x / y) * y);
}

BigInteger operator^(const BigInteger& x, const unsigned int& y) {
    if (y == 0) return BigInteger(1);
    if (y == 1) return x;
    if (y == 2) return x * x;
    if (y & 1 > 0) return ((x ^ (y / 2)) ^ 2) * x;
    else return ((x ^ (y / 2)) ^ 2);
}

const BigInteger ZERO = BigInteger(0), ONE = BigInteger(1), TWO = BigInteger(2);

BigInteger operator^(const BigInteger& x, const BigInteger& y) {
    if (y == ZERO) return BigInteger(1);
    if (y == ONE) return x;
    if (y == TWO) return x * x;
    if (y.lastDigit() & 1 > 0) return ((x ^ (y / 2)) ^ 2) * x;
    else return ((x ^ (y / 2)) ^ 2);
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    vector<BigInteger> numbers(1001);
    numbers[0] = ONE;
    for (int i = 1; i <= 1000; i++) numbers[i] = numbers[i - 1] * BigInteger(i);
    int n;
    while (cin >> n) {
        cout << n << "!\n";
        cout << numbers[n] << '\n';
    }
    return 0;
}
