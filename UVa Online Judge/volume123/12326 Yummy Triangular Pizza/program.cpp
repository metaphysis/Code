// Yummy Triangular Pizza
// UVa ID: 12326
// Verdict: Accepted
// Submission Date: 2026-02-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    // 多联三角形计数结果（允许旋转，不允许翻转），OEIS A006534
    int r[] = {0, 1, 1, 1, 4, 6, 19, 43, 120, 307, 866, 2336, 6588, 18373, 52119, 147700, 422016};
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int N;
        cin >> N;
        cout << "Case #" << t << ": " << r[N] << "\n";
    }
    return 0;
}
