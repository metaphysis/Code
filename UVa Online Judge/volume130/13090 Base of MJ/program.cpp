// Base of MJ
// UVa ID: 13090
// Verdict: Accepted
// Submission Date: 2026-01-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int t;
    cin >> t;
    for (int caseNo = 1; caseNo <= t; ++caseNo) {
        ll bMax, d;
        cin >> bMax >> d;
        ll count = 0;
        if (d == 1) {
            // 若 D=1，所有 B 都满足条件，因为任何数都能被 1 整除
            count = bMax - 1; // B 从 2 到 BMAX
        } else {
            // 计算 B ≡ 1 (mod D) 且 B >= 2 的个数
            // 最小满足条件的 B 是 1，但 B 必须 >=2，所以从 1+D 开始
            ll firstB = d + 1; // 第一个可能的 B（>=2）
            if (firstB <= bMax) count = (bMax - firstB) / d + 1;
            else count = 0;
        }
        cout << "Case " << caseNo << ": " << count << '\n';
    }
    return 0;
}
