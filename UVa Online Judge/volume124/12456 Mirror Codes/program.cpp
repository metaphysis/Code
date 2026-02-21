// Mirror Codes
// UVa ID: 12456
// Verdict: Accepted
// Submission Date: 2026-02-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d;
    while (cin >> d && d != 0) {
        vector<int> bases(d);
        for (int i = 0; i < d; i++) cin >> bases[i];

        // 计算总编码数
        long long total = 1;
        for (int b : bases) total *= b;

        // 计算回文编码数
        long long palindrome = 1;
        int half = d / 2;
        for (int i = 0; i < half; i++) palindrome *= bases[i];
        if (d % 2 == 1) palindrome *= bases[half];  // 奇数时中间位

        // 有效游戏数 = 总编码数 - 回文编码数
        long long games = total - palindrome;
        cout << games << '\n';
    }

    return 0;
}
