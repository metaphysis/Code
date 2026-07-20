// Very Funny Mr. Feynman
// UVa ID: 11120
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 将 int 转为小端序 vector<int>（个位在 [0]）
vector<int> intToBigInt(int n) {
    if (n == 0) return vector<int>{0};
    vector<int> res;
    while (n > 0) { res.push_back(n % 10); n /= 10; }
    return res;
}

// 去除前导零，保留至少一位
void trim(vector<int>& a) {
    while (a.size() > 1 && a.back() == 0) a.pop_back();
}

// 比较两个大整数，返回 -1 / 0 / 1
int compareBig(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
    }
    return 0;
}

// 原地乘以小整数 b
void multiplyByInt(vector<int>& a, int b) {
    if (b == 0) { a = vector<int>{0}; return; }
    int carry = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        long long cur = (long long)a[i] * b + carry;
        a[i] = cur % 10;
        carry = (int)(cur / 10);
    }
    while (carry > 0) {
        a.push_back(carry % 10);
        carry /= 10;
    }
    trim(a);
}

// 原地加上小整数 b
void addInt(vector<int>& a, int b) {
    if (b == 0) return;
    int carry = b;
    for (size_t i = 0; i < a.size(); ++i) {
        int sum = a[i] + carry;
        a[i] = sum % 10;
        carry = sum / 10;
        if (carry == 0) break;
    }
    while (carry > 0) {
        a.push_back(carry % 10);
        carry /= 10;
    }
    trim(a);
}

// 原地减去另一个大整数（保证 a >= b）
void subtractBig(vector<int>& a, const vector<int>& b) {
    int borrow = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        int sub = (i < b.size() ? b[i] : 0) + borrow;
        int val = a[i] - sub;
        if (val < 0) { val += 10; borrow = 1; }
        else { borrow = 0; }
        a[i] = val;
    }
    trim(a);
}

// 复制并乘以小整数
vector<int> multiplyByIntCopy(const vector<int>& a, int b) {
    vector<int> res = a;
    multiplyByInt(res, b);
    return res;
}

// 复制并加上小整数
vector<int> addIntCopy(const vector<int>& a, int b) {
    vector<int> res = a;
    addInt(res, b);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p;
    while (cin >> p && p != 0) {
        // 求整数部分 n = floor(sqrt(p))
        int n = (int)sqrt(p);
        while ((long long)(n + 1) * (n + 1) <= p) ++n;
        while ((long long)n * n > p) --n;

        // 将整数部分转为数字序列（高位在前）
        vector<int> intDigits;
        if (n == 0) intDigits.push_back(0);
        else {
            int tmp = n;
            while (tmp > 0) { intDigits.push_back(tmp % 10); tmp /= 10; }
            reverse(intDigits.begin(), intDigits.end());
        }

        // 检查整数部分是否已存在三连
        bool found = false;
        for (size_t i = 0; i + 2 < intDigits.size(); ++i) {
            if (intDigits[i] == intDigits[i+1] && intDigits[i+1] == intDigits[i+2]) {
                cout << p << " " << i << " " << intDigits[i] << "\n";
                found = true;
                break;
            }
        }
        if (found) continue;

        // 初始化 x = n, r = p - n²
        vector<int> x = intToBigInt(n);
        int rem = p - n * n;
        vector<int> r = intToBigInt(rem);

        // 当前所有数字序列（从整数部分开始）
        vector<int> digits = intDigits;

        // 逐位生成小数部分
        while (true) {
            multiplyByInt(r, 100);                      // r *= 100
            vector<int> t = multiplyByIntCopy(x, 20);   // t = 20 * x

            int chosenD = 0;
            vector<int> prod;
            for (int d = 9; d >= 0; --d) {
                vector<int> temp = addIntCopy(t, d);    // t + d
                prod = multiplyByIntCopy(temp, d);      // (t + d) * d
                if (compareBig(prod, r) <= 0) {
                    chosenD = d;
                    break;
                }
            }

            digits.push_back(chosenD);                  // 记录该位

            multiplyByInt(x, 10);                       // x *= 10
            addInt(x, chosenD);                         // x += d
            subtractBig(r, prod);                       // r -= prod

            size_t sz = digits.size();
            if (sz >= 3 && digits[sz-3] == digits[sz-2] && digits[sz-2] == digits[sz-1]) {
                int prefix = (int)sz - 3;
                cout << p << " " << prefix << " " << digits[sz-1] << "\n";
                break;
            }
        }
    }
    return 0;
}
