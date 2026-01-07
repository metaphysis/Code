// Twin Apparent Primes
// UVa ID: 12349
// Verdict: Accepted
// Submission Date: 2026-01-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

vector<int> digits; // 低位在前
static const int BASE = 10000;  // 万进制

// 乘以一个小整数
void multiply(int x) {
    int carry = 0;
    for (size_t i = 0; i < digits.size(); i++) {
        int product = digits[i] * x + carry;
        digits[i] = product % BASE;
        carry = product / BASE;
    }
    if (carry) digits.push_back(carry);
}

// 转换为十进制字符串
string toString() {
    if (digits.empty()) return "0";
    stringstream ss;
    ss << digits.back();
    for (int i = (int)digits.size() - 2; i >= 0; i--)
        ss << setw(4) << setfill('0') << digits[i];
    return ss.str();
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    digits.push_back(1);
    int flag[8010] = {0};
    for (int i = 2; i <= 8000; i++)
        if (!flag[i]) {
            multiply(i);
            for (int j = i * i; j <= 8000; j += i) flag[j] = 1;
        }
    string M = toString(), a = "8009";
    int n, t;
    while (cin >> n >> t && n)
        cout << M << string(n - M.length() - 4, '0') << a << '\n';
    return 0;
}
