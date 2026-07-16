// Olympic Swimming
// UVa ID: 11546
// Verdict: Accepted
// Submission Date: 2026-07-
// UVa Run Time: s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, K;
    int caseNo = 1;
    while (cin >> L >> K && (L || K)) {
        // 读取每个泳道的栏架位置
        vector<vector<int>> laneHurdles(K);
        for (int i = 0; i < K; ++i) {
            int n;
            cin >> n;
            laneHurdles[i].resize(n);
            for (int j = 0; j < n; ++j) cin >> laneHurdles[i][j];
        }

        // 计算每个泳道的前缀和 S[i][x]：标记 x 之前（<x）的栏架总数
        vector<vector<int>> prefixSum(K, vector<int>(L + 1, 0));
        for (int i = 0; i < K; ++i) {
            vector<int> mark(L, 0);                 // mark[p]=1 表示区间 [p,p+1) 有栏架
            for (int p : laneHurdles[i]) if (p >= 0 && p < L) mark[p] = 1;
            prefixSum[i][0] = 0;
            for (int x = 1; x <= L; ++x)
                prefixSum[i][x] = prefixSum[i][x - 1] + mark[x - 1];
        }

        // 扫描每个标记，记录差异向量首次出现的位置
        map<vector<int>, int> firstPos;   // 差异向量 -> 最早出现标记
        int ans = 0;
        for (int x = 0; x <= L; ++x) {
            vector<int> diff;
            diff.reserve(K - 1);
            for (int i = 1; i < K; ++i)
                diff.push_back(prefixSum[0][x] - prefixSum[i][x]);

            auto it = firstPos.find(diff);
            if (it == firstPos.end()) firstPos[diff] = x;
            else ans = max(ans, x - it->second);
        }

        cout << "Case #" << caseNo << ": " << ans << " meter(s)" << endl;
        ++caseNo;
    }
    return 0;
}
