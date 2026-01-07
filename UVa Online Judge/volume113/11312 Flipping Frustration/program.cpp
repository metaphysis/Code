// Flipping Frustration
// UVa ID: 11312
// Verdict: Accepted
// Submission Date: 2026-01-03
// UVa Run Time: 0.070s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 扩展欧几里得算法，返回 (g, x, y) 满足 a*x + b*y = g = gcd(a, b)
tuple<long long, long long, long long> extendedGcd(long long a, long long b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x1, y1] = extendedGcd(b, a % b);
    return {g, y1, x1 - (a / b) * y1};
}

int main() {
    int c;
    cin >> c;
    while (c--) {
        long long n, l, r, t;
        cin >> n >> l >> r >> t;
        
        // 特判：目标页就是起始页
        if (t == 1) {
            cout << 0 << endl;
            continue;
        }
        
        // 判定是否有解
        long long d = __gcd(l, r);
        if ((t - 1) % d != 0) {
            cout << "uh-oh!\n";
            continue;
        }
        
        // 解方程 r*x - l*y = t-1
        // 令 a = r/d, b = l/d, c = (t-1)/d
        long long a = r / d, b = l / d, c = (t - 1) / d;
        
        // 求 a*x0 + b*y0 = 1 的解，注意我们实际需要 a*x0 - b*y0 = 1
        auto [g, x0, y0] = extendedGcd(a, b);
        long long x1 = c * x0, y1 = c * (-y0);  // 调整符号得到 a*x1 - b*y1 = c
        
        // 找最小非负解
        long long kLower = max(ceil((-x1) / (double)b), ceil((-y1) / (double)a));
        long long bestK = kLower;
        long long bestSum = x1 + b * kLower + y1 + a * kLower;
        
        // 检查 kLower 附近的值，确保找到最小 x+y
        for (long long k = kLower - 1; k <= kLower + 1; k++) {
            long long xTry = x1 + b * k, yTry = y1 + a * k;
            if (xTry >= 0 && yTry >= 0) {
                long long sum = xTry + yTry;
                if (sum < bestSum) {
                    bestSum = sum;
                    bestK = k;
                }
            }
        }
        
        // 确定最终解
        long long x = x1 + b * bestK, y = y1 + a * bestK;
        if (x < 0 || y < 0 || r * x - l * y != t - 1) {
            cout << "uh-oh!\n";
            continue;
        }
        
        // 贪心模拟：优先向右翻，使用除法加速
        long long current = 1, rightCnt = x, leftCnt = y, flips = 0;
        bool changed = true;
        while (changed) {
            changed = false;
            
            // 尝试向右翻
            if (rightCnt > 0) {
                long long steps = min(rightCnt, (n - current) / r);
                if (steps > 0) {
                    current += steps * r;
                    flips += steps;
                    rightCnt -= steps;
                    changed = true;
                }
            }
            
            // 尝试向左翻
            if (leftCnt > 0) {
                long long steps = min(leftCnt, (current - 1) / l);
                if (steps > 0) {
                    current -= steps * l;
                    flips += steps;
                    leftCnt -= steps;
                    changed = true;
                }
            }
        }
        
        // 检查是否成功到达目标页
        if (current == t) cout << flips << '\n';
        else cout << "uh-oh!\n";
    }
    return 0;
}
