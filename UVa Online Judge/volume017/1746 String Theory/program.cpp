// String Theory
// UVa ID: 1746
// Verdict: Accepted
// Submission Date: 2026-07-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        bool found = false;
        int maxK = min(a[0], a[n - 1]);
        // 从大到小尝试可能的嵌套层级 k
        for (int k = maxK; k > 0; --k) {
            vector<int> buf = a;          // 拷贝原始引号块
            int l = 0, r = n - 1, tmp = k;
            // 逐层剥离：每轮从左、右各取 tmp 个引号
            while (l < n && r >= 0 && buf[l] >= tmp && buf[r] >= tmp) {
                buf[l] -= tmp;
                if (buf[l] == 0) ++l;     // 当前块耗尽则右移
                buf[r] -= tmp;
                if (buf[r] == 0) --r;     // 当前块耗尽则左移
                --tmp;                    // 进入下一层（嵌套深度减 1）
                if (tmp == 0) break;      // 所有嵌套层均已剥离
            }
            if (tmp != 0) continue;       // 未能完整剥离所有层，当前 k 不合法
            // 所有嵌套层剥离完毕，剩余引号必须能组成 1‑quotation 序列
            int sum = accumulate(buf.begin(), buf.end(), 0);
            if ((k != 1 && sum % 2 == 0) || (k == 1 && sum == 0)) {
                cout << k << '\n';
                found = true;
                break;
            }
        }
        if (!found) cout << "no quotation\n";
    }
    return 0;
}
