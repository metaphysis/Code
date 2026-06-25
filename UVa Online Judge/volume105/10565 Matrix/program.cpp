// Matrix
// UVa ID: 10565
// Verdict: Accepted
// Submission Date: 2026-06-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int m;
        cin >> m;
        vector<int> k(m);
        for (int i = 0; i < m; ++i) cin >> k[i];

        if (m == 1) {
            if (k[0] == 0) {
                cout << -1 << "\n";
            } else {
                cout << 1 << "\n";
                cout << -k[0] << "\n";
            }
        } else {
            // 取第一个非零的 k_i，若 k[0] 为 0 则取 k[1]（因为互异，k[1] 必非零）
            int val = (k[0] != 0) ? -k[0] : -k[1];
            cout << 2 << "\n";
            cout << val << " 0\n";
            cout << "0 " << val << "\n";
        }
    }
    return 0;
}
