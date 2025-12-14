// Floor Tiles
// UVa ID: 10644
// Verdict: Accepted
// Submission Date: 2025-12-13
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int l1, l2, w1, w2;
        cin >> l1 >> l2 >> w1 >> w2;
        // 确保范围递增
        if (l1 > l2) swap(l1, l2);
        if (w1 > w2) swap(w1, w2);
        int ans = 0;
        // 遍历所有可能的尺寸
        for (int x = max(l1, 2); x <= l2; x++) {
            for (int y = max(w1, 2); y <= w2; y++) {
                if (x % 6 == 0) ans++;                     // 规则1
                else if (x == 3) ans += (y % 2 == 0);     // 规则2
                else if (x % 3 == 0) ans += (y != 3);     // 规则3
                else if (x % 2 == 0) ans += (y % 3 == 0); // 规则4
                else ans += (y > 3 && y % 3 == 0);        // 规则5
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
