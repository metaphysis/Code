// Equilateral Triangle in a Grid
// UVa ID: 12630
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    while (cin >> n && n) {
        // 公式：C(n+2, 4) = (n + 2) * (n + 1) * n * (n - 1) / 24
        long long answer = 1LL * (n + 2) * (n + 1) * n * (n - 1) / 24;
        cout << answer << endl;
    }
    return 0;
}
