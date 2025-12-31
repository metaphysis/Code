// Signed-digit Numbers
// UVa ID: 10764
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

string toSdNumber(long long n, long long b, long long a) {
    if (n == 0) return "0";
    string result = "";
    while (n != 0) {
        long long r = n % b;  // C++中，余数符号与被除数相同
        if (n > 0) {
            if (r > a) r -= b;
        } else {  // n < 0
            // 确保 r <= 0
            if (r > 0) r -= b;
            if (r < -a) r += b;
        }
        // 此时 r 在 [-a, a] 内，且 (n-r) 能被 b 整除
        n = (n - r) / b;
        if (r < 0) {
            result += char('0' - r);
            result += '\'';
        } else result += char('0' + r);
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    long long n, b, a;
    while (cin >> n >> b >> a && b)
        cout << toSdNumber(n, b, a) << '\n';
    
    return 0;
}
