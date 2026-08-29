#include <bits/stdc++.h>
using namespace std;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

long double getSum(int n, int a) {
    long double sum = 0;
    for (int j = 0; j <= n; j++) {
        long long den = 8LL * j + a, rem = modPow(16, n - j, den);
        sum += (long double)rem / den;
        sum -= floorl(sum);
    }
    for (int t = 1; t <= 30; t++) {
        long double term = powl(16.0L, -t) / (8.0L * (n + t) + a);
        sum += term;
    }
    return sum;
}

char getDigit(int k) {
    if (k == 1) return '3';
    int n = k - 2, digit;
    long double value = 4.0L * getSum(n, 1) - 2.0L * getSum(n, 4) - getSum(n, 5) - getSum(n, 6);
    value -= floorl(value);
    digit = (int)floorl(value * 16.0L + 1e-12L);
    if (digit >= 16) digit = 15;
    if (digit < 10) return char('0' + digit);
    return char('A' + digit - 10);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    while (cin >> k) cout << getDigit(k) << '\n';
    return 0;
}
