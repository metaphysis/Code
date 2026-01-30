// Spiral
// UVa ID: 12954
// Verdict: Accepted
// Submission Date: 2026-01-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, b;
    while (cin >> n >> b) {
        // 找到层数 k
        long long L = 0, R = (n - 1) / 2, k = 0;
        while (L <= R) {
            long long mid = (L + R) / 2;
            long long s = n - 2 * mid;
            long long before = n * n - s * s; // mid 层之前的总数
            if (b > before) {
                k = mid;
                L = mid + 1;
            } else {
                R = mid - 1;
            }
        }
        
        long long s = n - 2 * k;
        long long before = n * n - s * s;
        long long off = b - before - 1;
        long long sr = k + 1, sc = k + 1;
        long long r = sr, c = sc;
        
        if (s == 1) {
            // 中心点
            cout << r << " " << c << endl;
            continue;
        }
        
        if (off < s - 1) c += off;
        else if (off < 2 * s - 2) { r += off - (s - 1); c += s - 1; }
        else if (off < 3 * s - 3) { r += s - 1; c += s - 1 - (off - (2 * s - 2)); }
        else { r += s - 1 - (off - (3 * s - 3)); c = sc; }
        
        cout << r << " " << c << endl;
    }
    return 0;
}
