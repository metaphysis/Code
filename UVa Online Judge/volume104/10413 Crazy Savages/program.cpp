// Crazy Savages
// UVa ID: 10413
// Verdict: Accepted
// Submission Date: 2025-11-15
// UVa Run Time: 0.430s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int n;
int c[20], p[20], l[20];

// 扩展欧几里得算法，求解 ax + by = gcd(a,b)
int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

// 检查m是否满足条件
bool check(int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int A = p[i] - p[j];
            int B = c[j] - c[i];
            int maxDay = min(l[i], l[j]);
            
            int d = __gcd(A, m);
            if (B % d != 0) continue;
            
            int new_m = m / d;
            int new_A = A / d;
            int new_B = B / d;
            
            // 处理负数情况
            if (new_A < 0) {
                new_A = -new_A;
                new_B = -new_B;
            }
            new_B = (new_B % new_m + new_m) % new_m;
            
            int x, y;
            exgcd(new_A, new_m, x, y);
            x = (x % new_m + new_m) % new_m;
            
            int k0 = (long long)x * new_B % new_m;
            
            if (k0 <= maxDay) return false;
        }
    }
    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        int maxC = 0;
        for (int i = 0; i < n; ++i) {
            cin >> c[i] >> p[i] >> l[i];
            maxC = max(maxC, c[i]);
            c[i]--; // 转换为0-based，方便模运算
        }
        
        // 从maxC开始枚举m
        for (int m = maxC; m <= 1000000; m++) {
            if (check(m)) {
                cout << m << endl;
                break;
            }
        }
    }
    return 0;
}
