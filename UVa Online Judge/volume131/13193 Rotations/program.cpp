// Rotations
// UVa ID: 13193
// Verdict: Accepted
// Submission Date: 2026-02-27
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 判断 32 位无符号整数 n 能否通过连续 5 位生成 0~31 的所有数
string solve(uint32_t n) {
    bool seen[32] = {false};               // 标记每个数是否出现过
    for (int i = 0; i < 32; ++i) {
        // 循环左移 i 位，取低 5 位
        uint32_t rotated = (n << i) | (n >> (32 - i));
        uint32_t val = rotated & 0x1F;      // 取低 5 位
        seen[val] = true;
    }
    for (int i = 0; i < 32; ++i)
        if (!seen[i]) return "no";
    return "yes";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        uint32_t n;
        cin >> n;
        cout << solve(n) << '\n';
    }
    return 0;
}
