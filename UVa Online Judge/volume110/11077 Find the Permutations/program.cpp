// Find the Permutations
// UVa ID: 11077
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
int main() {
    const int maxN = 21;
    // 斯特林数表，stirlingTable[n][k] 表示 n 个元素恰好 k 个循环的排列数
    vector<vector<ull>> stirlingTable(maxN + 1, vector<ull>(maxN + 1, 0));
    // 初始化：0 个元素 0 个循环只有 1 种情况（空排列）
    stirlingTable[0][0] = 1;
    // 递推计算斯特林数
    for (int n = 1; n <= maxN; n++) {
        for (int k = 1; k <= n; k++) {
            // 新元素单独成循环，或者插入到已有的 n-1 个元素的某个循环中
            stirlingTable[n][k] = stirlingTable[n - 1][k - 1] + (n - 1) * stirlingTable[n - 1][k];
        }
    }
    int n, k;
    while (cin >> n >> k) {
        if (n == 0 && k == 0) break;
        // 最少交换次数 = n - 循环数 = k → 循环数 = n - k
        cout << stirlingTable[n][n - k] << endl;
    }
    return 0;
}
