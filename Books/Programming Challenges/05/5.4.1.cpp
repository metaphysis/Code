#include <bits/stdc++.h>
using namespace std;

map<char, int> charToInt = {
    {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
    {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
    {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14},
};

string intToChar = "0123456789ABCDE";

// 将R进制数转换为十进制数，假设转换得到的数值均在整数数据类型表示的范围内。
int convertRToDecimal(string textOfNumber, int base) {
    // 处理符号位。
    int sign = 1;
    if (textOfNumber.front() == '+' || textOfNumber.front() == '-') {
        sign = textOfNumber.front() == '+' ? 1 : -1;
        textOfNumber.erase(textOfNumber.begin());
    }
    // 将字符串表示的数字从左至右进行转换。
    int number = 0;
    for (auto digit : textOfNumber) {
        digit = toupper(digit);
        number = number * base + charToInt[digit];
    }
    // 返回的数值需要乘以符号位。
    return sign * number;
}

// 将十进制数转换为R进制数。
string convertDecimalToR(int number, int base) {
    // 处理符号位。
    int sign = number >= 0 ? 1 : -1;
    // 取绝对值，使用求余数法进行转换。
    string textOfNumber;
    number = abs(number);
    while (number) {
        textOfNumber.insert(textOfNumber.begin(), intToChar[number % base]);
        number /= base;
    }
    // 当为负数时添加符号位。
    if (sign < 0) textOfNumber.insert(textOfNumber.begin(), '-');
    return textOfNumber;
}

int main(int argc, char *argv[]) {
    string line;
    int startBase, endBase;
    while (cin >> line >> startBase >> endBase) {
        int decimal = convertRToDecimal(line, startBase);
        cout << line << "(" << startBase << " Based) = ";;
        cout << decimal << "(10 Based) = ";
        cout << convertDecimalToR(decimal, endBase) << "(" << endBase << " Based)" << endl;
    }
    return 0;
}
