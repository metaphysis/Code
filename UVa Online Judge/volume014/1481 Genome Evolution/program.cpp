// Genome Evolution
// UVa ID: 1481
// Verdict: Accepted
// Submission Date: 2026-02-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n && n != 0) {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        // 记录 b 中每个值的位置
        vector<int> posB(n + 1);
        for (int i = 0; i < n; ++i) posB[b[i]] = i;
        int r = 0;
        for (int i = 0; i < n; ++i) {
            int minPos = n, maxPos = -1;
            for (int j = i; j < n; ++j) {
                int p = posB[a[j]];
                if (p < minPos) minPos = p;
                if (p > maxPos) maxPos = p;
                int length = j - i + 1;
                if (length > 1 && maxPos - minPos + 1 == length) ++r;
            }
        }
        cout << r << '\n';
    }
    return 0;
}

