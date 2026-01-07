// Cyclic Antimonotonic Permutations
// UVa ID: 11630
// Verdict: Accepted
// Submission Date: 2026-01-03
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
int d[MAXN];

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int n;
    while (cin >> n && n) {
        // 前两个固定
        d[1] = 3, d[2] = 1;
        // 中间部分
        for (int i = 3; i < n; ++i) {
            if (i & 1) d[i] = i + 2;  // 奇数位置
            else d[i] = i - 2;        // 偶数位置
        }
        // 最后两个特殊处理
        if (n & 1) d[n] = n - 1;
        else d[n] = n - 2, d[n - 1] = n;
        // 输出
        for (int i = 1; i <= n; ++i) cout << d[i] << " \n"[i == n];
    }
    return 0;
}
