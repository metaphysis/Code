// Light Bulbs
// UVa ID: 1019
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
// https://blog.csdn.net/metaphysis/article/details/163173589

#include <bits/stdc++.h>
using namespace std;

// 将十进制字符串转为二进制字符串（无前导零，"0" -> "0"）
string decToBin(string s) {
    if (s == "0") return "0";
    string bin;
    while (s != "0") {
        int rem = (s.back() - '0') & 1;
        bin.push_back(char('0' + rem));
        string q;
        int carry = 0;
        for (char c : s) {
            int cur = carry * 10 + (c - '0');
            int digit = cur / 2;
            carry = cur % 2;
            if (!q.empty() || digit != 0) q.push_back(char('0' + digit));
        }
        s = q.empty() ? "0" : q;
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

// 比较两个解，返回 a 是否优于 b（代价小优先，代价相同则数值小优先）
bool isBetter(const vector<int>& a, const vector<int>& b, int n) {
    int cntA = 0, cntB = 0;
    for (int i = 1; i <= n; ++i) {
        cntA += a[i];
        cntB += b[i];
    }
    if (cntA != cntB) return cntA < cntB;
    for (int i = 1; i <= n; ++i) {
        if (a[i] != b[i]) return a[i] < b[i];
    }
    return false;
}

// 将开关向量（x[1]为最高位）转为十进制字符串
string xToDec(const vector<int>& x, int n) {
    vector<int> digits(1, 0);       // 低位在前
    for (int i = 1; i <= n; ++i) {
        int carry = x[i];
        for (size_t j = 0; j < digits.size(); ++j) {
            int temp = digits[j] * 2 + carry;
            digits[j] = temp % 10;
            carry = temp / 10;
        }
        while (carry > 0) {
            digits.push_back(carry % 10);
            carry /= 10;
        }
    }
    string res;
    for (int i = (int)digits.size() - 1; i >= 0; --i)
        res.push_back(char('0' + digits[i]));
    return res.empty() ? "0" : res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string aStr, bStr;
    int caseNo = 1;
    bool firstCase = true;
    while (cin >> aStr >> bStr) {
        if (aStr == "0" && bStr == "0") break;
        if (!firstCase) cout << "\n";
        firstCase = false;
        string aBin = decToBin(aStr);
        string bBin = decToBin(bStr);
        int n = max(aBin.size(), bBin.size());
        // 补零至 n 位，高位对应灯泡 1
        string aPad = string(n - aBin.size(), '0') + aBin;
        string bPad = string(n - bBin.size(), '0') + bBin;
        vector<int> diff(n + 1, 0);   // diff[1..n]
        for (int i = 1; i <= n; ++i)
            diff[i] = (aPad[i - 1] != bPad[i - 1]) ? 1 : 0;
        vector<int> bestX(n + 1, 0);
        bool found = false;
        // 枚举 x[1]（唯一自由变量）
        for (int guess = 0; guess <= 1; ++guess) {
            vector<int> x(n + 2, 0);   // x[0] 和 x[n+1] 默认为 0
            if (n == 1) {
                x[1] = guess;
                if (diff[1] == x[1]) {
                    if (!found || isBetter(x, bestX, n)) {
                        bestX = x;
                        found = true;
                    }
                }
                continue;
            }
            x[1] = guess;
            x[2] = diff[1] ^ x[1];                     // 灯泡 1 的方程
            for (int i = 2; i <= n - 1; ++i)            // 中间灯泡
                x[i + 1] = diff[i] ^ x[i - 1] ^ x[i];
            // 检查最后一个灯泡的方程
            if ((x[n - 1] ^ x[n]) == diff[n]) {
                if (!found || isBetter(x, bestX, n)) {
                    bestX = x;
                    found = true;
                }
            }
        }
        cout << "Case Number " << caseNo << ": ";
        if (!found) cout << "impossible";
        else cout << xToDec(bestX, n);
        cout << '\n';
        ++caseNo;
    }
    return 0;
}
