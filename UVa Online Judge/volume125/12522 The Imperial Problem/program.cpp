// The Imperial Problem
// UVa ID: 12522
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 获取罗马字符数值
int toValue(char ch) {
    switch (ch) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

// 整数转标准罗马数字
string toRoman(int num) {
    string thousands[] = {"", "M", "MM", "MMM"};
    string hundreds[]  = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string tens[]      = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string ones[]      = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
    return thousands[num / 1000] +
           hundreds[(num % 1000) / 100] +
           tens[(num % 100) / 10] +
           ones[num % 10];
}

// 计算最大匹配数（补空格+滑动窗口）
int maxMatch(const string& s, const string& t) {
    int n = s.size(), m = t.size();
    // 原串左右补 m 个空格，使所有偏移对齐都覆盖
    string padded = string(m, ' ') + s + string(m, ' ');
    int totalLen = padded.size();
    int best = 0;
    // 滑动窗口，长度为 m，比较与 t 的相同字符数
    for (int d = 0; d <= totalLen - m; ++d) {
        int match = 0;
        for (int i = 0; i < m; ++i)
            if (padded[d + i] == t[i]) ++match;
        if (match > best) best = match;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string s;
    while (cin >> s) {
        if (s == "*") break;
        int value = 0;
        for (char ch : s) value += toValue(ch);
        string target = toRoman(value);
        int match = maxMatch(s, target);
        int e = s.size() - match;
        int c = target.size() - match;
        cout << e << " " << c << "\n";
    }
    return 0;
}
