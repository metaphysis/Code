// Next Palindromic Numbers
// UVa ID: 12940
// Verdict: Accepted
// Submission Date: 2026-01-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 将左半部分反转复制到右半部分构造回文数
string makePalindrome(const string &left, int len) {
    string result = left;
    string right = left;
    reverse(right.begin(), right.end());
    if (len % 2 == 1) {
        // 奇数长度，去掉中间字符
        right = right.substr(1);
    }
    result += right;
    return result;
}

// 获取下一个回文数
string nextPalindrome(const string &s) {
    int len = s.length();
    
    // 特殊情况：全是9的数字，如 999 -> 1001
    bool allNine = true;
    for (char c : s) {
        if (c != '9') {
            allNine = false;
            break;
        }
    }
    if (allNine) {
        string result(len + 1, '0');
        result[0] = '1';
        result[len] = '1';
        return result;
    }
    
    // 取左半部分（包含中间字符）
    string left = s.substr(0, (len + 1) / 2);
    
    // 先构造回文数
    string candidate = makePalindrome(left, len);
    
    // 如果构造的数小于等于原数，左半部分加1
    if (candidate <= s) {
        // 左半部分加1
        int carry = 1;
        for (int i = left.length() - 1; i >= 0 && carry; i--) {
            int digit = (left[i] - '0') + carry;
            left[i] = (digit % 10) + '0';
            carry = digit / 10;
        }
        // 如果有进位（如 999 -> 1000），需要特殊处理
        if (carry) {
            // 这种情况应该已经被allNine检测到了，但为了安全还是处理
            left = "1" + string(left.length() - 1, '0');
        }
        // 重新构造
        candidate = makePalindrome(left, len);
    }
    
    return candidate;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string d;
    while (cin >> n >> d) {
        string current = d;
        for (int i = 0; i < n; i++) {
            current = nextPalindrome(current);
            cout << current << "\n";
        }
    }
    return 0;
}
