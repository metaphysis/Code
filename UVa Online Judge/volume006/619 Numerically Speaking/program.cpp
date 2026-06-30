// Numerically Speaking
// UVa ID: 619
// Verdict: Accepted
// Submission Date: 2016-08-28
// UVa Run Time: 0.000s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 十进制下的四则运算。
const int BASE = 10;

// 移除计算结果的前导0。
void zeroJustify(string &number) {
    while (number.front() == '0' && number.length() > 1)
        number.erase(number.begin());
}

// 将两个字符串形式表示的非负整数进行相加操作，返回字符串表示的结果。
string add(string number1, string number2) {
    if (number1.length() < number2.length())
        number1.swap(number2);
    number1.insert(number1.begin(), '0');
    int carry = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--) {
        int sum = number1[i] - '0' + (j >= 0 ? (number2[j] - '0') : 0) + carry;
        number1[i] = sum % BASE + '0';
        carry = sum / BASE;
    }
    zeroJustify(number1);
    return number1;
}

// 判断第一个数是否不小于第二个数。
bool greaterOrEqual(string &number1, string &number2) {
    if (number1.length() != number2.length())
        return number1.length() > number2.length();
    for (int i = 0; i < number1.length(); i++)
        if (number1[i] != number2[i])
            return number1[i] > number2[i];
    return true;
}

// 两个非负整数的减法。
string subtract(string number1, string number2) {
    int sign = 1;
    if (!greaterOrEqual(number1, number2)) {
        sign = -1;
        number1.swap(number2);
        number1.insert(number1.begin(), '0');
    }
    int borrow = 0, i = number1.length() - 1, j = number2.length() - 1;
    for (; i >= 0; i--, j--) {
        int diff = number1[i] - '0' - (j >= 0 ? (number2[j] - '0') : 0) - borrow;
        borrow = 0;
        if (diff < 0) {
            diff += BASE;
            borrow = 1;
        }
        number1[i] = diff + '0';
    }
    zeroJustify(number1);
    if (sign == -1)
        number1.insert(number1.begin(), '-');
    return number1;
}

// 两个非负整数的乘法。
string multiplicate(string number1, string number2) {
    string number3(number1.length() + number2.length(), 0);
    int length1 = number1.length() - 1, length2 = number2.length() - 1;
    for (int i = length1; i >= 0; i--)
        for (int j = length2; j >= 0; j--) {
            int k = number3.length() - 1 - (length1 - i + length2 - j);
            number3[k] += (number2[j] - '0') * (number1[i] - '0');
            number3[k - 1] += number3[k] / BASE;
            number3[k] %= BASE;
        }
    for (int i = 0; i < number3.length(); i++)
        number3[i] += '0';
    zeroJustify(number3);
    return number3;
}

// 非负整数的除法。
pair<string, string> divide(string number1, string number2) {
    string row, quotient, remainder;
    for (int i = 0; i < number1.length(); i++) {
        row.push_back(number1[i]);
        quotient.push_back('0');
        zeroJustify(row);
        while (greaterOrEqual(row, number2)) {
            quotient.back() += 1;
            row = subtract(row, number2);
        }
    }
    remainder = row;
    zeroJustify(quotient);
    zeroJustify(remainder);
    return make_pair(quotient, remainder);
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    string line, word, number;
    while (getline(cin, line), line != "*") {
        if (isdigit(line.front())) {
            number = line;
            word.clear();
            while (line != "0") {
                pair<string, string> result = divide(line, "26");
                line = result.first;
                if (result.second == "0") {
                    result.second = "26";
                    line = subtract(result.first, "1");
                }
                word.insert(word.begin(), (char)('a' + stoi(result.second) - 1));
            }
        } else {
            word = line;
            number = "0";
            for (int i = 0; i < line.length(); i++) {
                string digits = to_string(line[i] - 'a' + 1);
                number = add(multiplicate(number, "26"), digits);
            }
        }
        cout << word;
        cout << string(22 - word.length(), ' ');
        int start = number.length() % 3;
        if (start == 0) start = 3;
        cout << number.substr(0, start);
        for (int i = start; i < number.length(); i += 3)
            cout << ',' << number[i] << number[i + 1] << number[i + 2];
        cout << '\n';
    }
    return 0;
}
