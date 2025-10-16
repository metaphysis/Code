// The Counting Problem
// UVa ID: 1640
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// 计算从1到n中数字d出现的次数
ll countDigit(ll n, int d) {
    if (n < 1) return 0;  // 处理边界情况
    ll ans = 0, base = 1; // base表示当前位的权值
    while (base <= n) {
        ll cur = (n / base) % 10;   // 当前位的数字
        ll high = n / (base * 10);  // 高位部分
        ll low = n % base;          // 低位部分
        
        if (d != 0) {  // 处理非零数字
            if (cur < d) {
                ans += high * base;
            } else if (cur == d) {
                ans += high * base + low + 1;
            } else {
                ans += (high + 1) * base;
            }
        } else {  // 处理数字0，需要特殊处理前导零
            if (high != 0) {  // 确保不是最高位
                if (cur == 0) {
                    ans += (high - 1) * base + low + 1;
                } else {
                    ans += high * base;
                }
            }
        }
        base *= 10;  // 移动到下一位
    }
    return ans;
}

int main() {
    ll a, b;
    while (cin >> a >> b && (a || b)) {  // 读取直到遇到0 0
        if (a > b) swap(a, b);  // 确保a <= b
        // 输出每个数字的出现次数
        for (int d = 0; d < 10; d++) {
            if (d > 0) cout << " ";
            cout << countDigit(b, d) - countDigit(a - 1, d);
        }
        cout << endl;
    }
    return 0;
}
