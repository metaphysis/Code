// Looking-Glass House
// UVa ID: 12787
// Verdict: Accepted
// Submission Date: 2026-05-26
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 判断 n 在 b 进制下是否为回文（b <= sqrt(n) 时使用）
bool isPalindrome(int n, int b) {
    int digits[32], len = 0;
    while (n > 0) {
        digits[len++] = n % b;
        n /= b;
    }
    for (int i = 0; i < len / 2; ++i)
        if (digits[i] != digits[len - 1 - i]) return false;
    return true;
}

int smallestBase(int n) {
    if (n == 1) return 2;
    if (n == 2) return 3;
    
    int limit = sqrt(n);
    
    // 第一类：枚举小进制 b <= sqrt(n)
    for (int b = 2; b <= limit; ++b)
        if (isPalindrome(n, b)) return b;
    
    // 第二类：枚举大进制 b > sqrt(n)，此时 n = a*(b+1)
    // b = n/a - 1，需要 b > limit 且 a < b
    for (int a = limit; a >= 1; --a) {
        if (n % a == 0) {
            int b = n / a - 1;
            if (b > limit && a < b) return b;
        }
    }
    
    // 理论上不会到这里，因为 b = n-1 总是解
    return n - 1;
}

int main() {
    int n;
    while (cin >> n) {
        cout << smallestBase(n) << endl;
    }
    return 0;
}
