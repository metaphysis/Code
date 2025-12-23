// Smooth Factor
// UVa ID: 12788
// Verdict: Accepted
// Submission Date: 2025-12-15
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        int left = 0, maxLen = 1; // 至少长度为1
        int dropCount = 0; // 窗口中下降的次数

        for (int right = 1; right < n; ++right) {
            // 判断 right 是否为下降点
            if (a[right - 1] > a[right]) dropCount++;

            // 如果下降次数超过1，移动左边界直到满足条件
            while (dropCount > 1) {
                // 如果 left 是下降点，移出窗口时减少计数
                if (a[left] > a[left + 1]) dropCount--;
                left++;
            }

            // 更新最大长度
            maxLen = max(maxLen, right - left + 1);
        }

        cout << maxLen << "\n";
    }

    return 0;
}
