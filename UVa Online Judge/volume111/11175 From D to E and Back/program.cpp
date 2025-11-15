// From D to E and Back
// UVa ID: 11175
// Verdict: Accepted
// Submission Date: 2025-11-04
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int m, k;
        cin >> m >> k;
        vector<bitset<300>> adj(m);  // 直接使用bitset存储邻接矩阵
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            adj[x][y] = true;
        }
        bool valid = true;
        // 对于每个目标顶点k
        for (int k = 0; k < m && valid; k++) {
            bitset<300> reference;  // 参考出邻接集合
            bool reference_set = false;
            // 找出所有指向k的顶点
            for (int i = 0; i < m; i++) {
                if (adj[i][k]) {
                    if (!reference_set) {
                        reference = adj[i];  // 设置参考集合
                        reference_set = true;
                    } else {
                        // 直接比较bitset
                        if (adj[i] != reference) {
                            valid = false;
                            break;
                        }
                    }
                }
            }
        }
        cout << "Case #" << caseNum << ": " << (valid ? "Yes" : "No") << "\n";
    }
    return 0;
}
