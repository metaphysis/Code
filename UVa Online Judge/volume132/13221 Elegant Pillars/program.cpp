// Elegant Pillars
// UVa ID: 13221
// Verdict: Accepted
// Submission Date: 2026-05-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 计算 N 根柱子最多能放置的球数
// 公式：ans = floor((N^2 + 2N - 1) / 2)
long long maxBalls(long long n) {
    return (n * n + 2 * n - 1) / 2;
}

int main() {
    long long n;
    while (cin >> n)
        cout << maxBalls(n) << endl;
    return 0;
}
