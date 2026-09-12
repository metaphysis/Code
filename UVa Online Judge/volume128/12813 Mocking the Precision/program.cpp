#include <bits/stdc++.h>
using namespace std;

long long getPow10(int n) {
    long long res = 1;
    while (n--) res *= 10;
    return res;
}

long long getGcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        bool neg = false;
        if (s[0] == '-') {
            neg = true;
            s = s.substr(1);
        }
        size_t dotPos = s.find('.'), leftPos = s.find('('), rightPos = s.find(')');
        string intStr, preStr, repStr;
        if (dotPos == string::npos) intStr = s;
        else {
            intStr = s.substr(0, dotPos);
            if (leftPos == string::npos) preStr = s.substr(dotPos + 1);
            else {
                preStr = s.substr(dotPos + 1, leftPos - dotPos - 1);
                repStr = s.substr(leftPos + 1, rightPos - leftPos - 1);
            }
        }
        long long intPart = intStr.empty() ? 0 : stoll(intStr);
        long long preVal = preStr.empty() ? 0 : stoll(preStr);
        long long repVal = repStr.empty() ? 0 : stoll(repStr);
        long long num, den;
        int preLen = preStr.size(), repLen = repStr.size();
        if (repLen == 0) {
            den = getPow10(preLen);
            num = preVal;
        } else {
            long long base = getPow10(repLen) - 1;
            den = getPow10(preLen) * base;
            num = preVal * base + repVal;
        }
        long long g = getGcd(num, den);
        num /= g;
        den /= g;
        intPart += num / den;
        num %= den;
        if (intPart == 0 && num == 0) {
            cout << 0 << '\n';
            continue;
        }
        if (neg) cout << '-';
        if (intPart > 0) {
            cout << intPart;
            if (num > 0) cout << ' ' << num << '/' << den;
        } else cout << num << '/' << den;
        cout << '\n';
    }
    return 0;
}
