#include <bits/stdc++.h>
using namespace std;

long long getLenSum(long long n) {
    if (n <= 0) return 0;
    long long ans = 0, base = 1, len = 1;
    while (base <= n) {
        long long last = min(n, base * 10 - 1);
        ans += (last - base + 1) * len;
        base *= 10;
        len++;
    }
    return ans;
}

long long getTotalLen(long long n) {
    if (n <= 0) return 0;
    return getLenSum(n) + n - n / 4;
}

char getDigit(long long n, long long pos) {
    string str = to_string(n);
    if (pos <= (long long)str.size()) return str[pos - 1];
    if (n % 2 == 1) return '2';
    return '0';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long k;
    while (cin >> k && k) {
        long long left = 1, right = k;
        while (left < right) {
            long long mid = left + (right - left) / 2;
            if (getTotalLen(mid) >= k) right = mid;
            else left = mid + 1;
        }
        long long n = left;
        long long pos = k - getTotalLen(n - 1);
        cout << getDigit(n, pos) << '\n';
    }
    return 0;
}
