// Palindrome Numbers
// UVa ID: 12050
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;
string getPalindrome(long long idx) {
    if (idx <= 9) return to_string(idx);
    long long len = 1, count = 9, power = 1;
    while (idx > count) {
        idx -= count;
        len++;
        if (len % 2 == 1) power *= 10;
        count = 9 * power;
    }
    string half = to_string(power + idx - 1);
    string rev = half.substr(0, half.length() - (len % 2));
    reverse(rev.begin(), rev.end());
    return half + rev;
}
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    long long i;
    while (cin >> i && i) cout << getPalindrome(i) << "\n";
    return 0;
}

