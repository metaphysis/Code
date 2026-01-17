// The Gossiping System
// UVa ID: 10292
// Verdict: Accepted
// Submission Date: 2026-01-11
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 比较两个大数字符串，a >= b 返回 true
bool greaterOrEqual(const string& a, const string& b) {
    if (a.length() != b.length()) return a.length() > b.length();
    return a >= b;
}

// 大数加法
string addStrings(const string& a, const string& b) {
    string result = "";
    int i = a.length() - 1, j = b.length() - 1, carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
    }
    return result;
}

// 大数减法（保证 a >= b）
string subtractStrings(const string& a, const string& b) {
    string result = "";
    int i = a.length() - 1, j = b.length() - 1, borrow = 0;
    while (i >= 0) {
        int digit = (a[i--] - '0') - borrow;
        if (j >= 0) digit -= (b[j--] - '0');
        if (digit < 0) {
            digit += 10;
            borrow = 1;
        } else borrow = 0;
        result = char(digit + '0') + result;
    }
    size_t pos = result.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return result.substr(pos);
}

// 大数除以2（整除）
string divideByTwo(const string& a) {
    string result = "";
    int remainder = 0;
    for (char digit : a) {
        int current = remainder * 10 + (digit - '0');
        result += char(current / 2 + '0');
        remainder = current % 2;
    }
    size_t pos = result.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return result.substr(pos);
}

// 大数乘以一位数
string multiplyByDigit(const string& a, int digit) {
    if (digit == 0) return "0";
    string result = "";
    int carry = 0;
    for (int i = a.length() - 1; i >= 0; i--) {
        int product = (a[i] - '0') * digit + carry;
        result = char(product % 10 + '0') + result;
        carry = product / 10;
    }
    if (carry > 0) result = char(carry + '0') + result;
    return result;
}

// 大数乘法
string multiplyStrings(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    string result = "0";
    int zeros = 0;
    for (int i = b.length() - 1; i >= 0; i--) {
        string partial = multiplyByDigit(a, b[i] - '0');
        partial += string(zeros, '0');
        result = addStrings(result, partial);
        zeros++;
    }
    return result;
}

// 判断一个数是否为完全平方数，如果是则返回平方根字符串，否则返回"0"
string isPerfectSquare(const string& num) {
    if (num == "0" || num == "1") return num;
    string low = "1", high = num;
    while (greaterOrEqual(high, low)) {
        string mid = divideByTwo(addStrings(low, high));
        string square = multiplyStrings(mid, mid);
        if (square == num) return mid;
        if (greaterOrEqual(square, num)) high = subtractStrings(mid, "1");
        else low = addStrings(mid, "1");
    }
    return "0";
}

// 判断是否存在(n,g,m,2)-gossiping system
bool isGossipSystemPossible(const string& nStr) {
    // 计算 8*n
    string eightN = multiplyByDigit(nStr, 8);
    // 计算 8*n + 1
    string value = addStrings(eightN, "1");
    // 检查是否为完全平方数
    return isPerfectSquare(value) != "0";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        string nStr;
        cin >> nStr;
        if (isGossipSystemPossible(nStr)) cout << "Yes.\n";
        else cout << "No.\n";
    }
    return 0;
}
