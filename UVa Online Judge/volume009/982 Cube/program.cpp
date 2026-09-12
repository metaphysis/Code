// Cube 
// UVa ID: 982
// Verdict: Accepted
// Submission Date: 2026-08-06
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

int gcdNum(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

string formatFrac(int num, int den) {
    if (num == 0) return "0";
    int g = gcdNum(num, den);
    num /= g;
    den /= g;
    if (den == 1) return to_string(num);
    return to_string(num) + "/" + to_string(den);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        int len = s.size(), evenCnt = 0, primeCnt = 0, oddCnt = 0;
        for (char c : s) {
            int d = c - '0';
            if (d % 2 == 0) evenCnt++;
            if (d == 2 || d == 3 || d == 5 || d == 7) primeCnt++;
            if (d == 1 || d == 3) oddCnt++;
        }
        int xNum = evenCnt, yNum = primeCnt, zNum = oddCnt;
        int xDen = len, yDen = len, zDen = len;
        int gx = gcdNum(xNum, xDen), gy = gcdNum(yNum, yDen), gz = gcdNum(zNum, zDen);
        xNum /= gx;
        xDen /= gx;
        yNum /= gy;
        yDen /= gy;
        zNum /= gz;
        zDen /= gz;
        cout << formatFrac(xNum, xDen) << " ";
        cout << formatFrac(yNum, yDen) << " ";
        cout << formatFrac(zNum, zDen) << "\n";
        int a = s[0] - '0', b = s[1 % len] - '0';
        int c = s[2 % len] - '0', d = s[3 % len] - '0';
        int e = s[4 % len] - '0', f = s[5 % len] - '0';
        long long num = 0, den = 1;
        if (xNum != 0) {
            num = 1LL * a * xNum;
            den = 1LL * b * xDen;
        }
        if (yNum != 0) {
            long long addNum = 1LL * c * yNum;
            long long addDen = 1LL * d * yDen;
            num = num * addDen + addNum * den;
            den *= addDen;
        }
        if (zNum != 0) {
            long long addNum = 1LL * e * zNum;
            long long addDen = 1LL * f * zDen;
            num = num * addDen + addNum * den;
            den *= addDen;
        }
        long long g = gcd(num, den);
        num /= g;
        den /= g;
        if (num > 1 && !isPrime((int)num)) cout << "SAFE\n";
        else cout << "FATAL\n";
    }
    return 0;
}
