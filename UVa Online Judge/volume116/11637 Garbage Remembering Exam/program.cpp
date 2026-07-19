// Garbage Remembering Exam
// UVa ID: 11637
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.280s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
long double logFact[MAXN + 1];

// 计算组合数 C(n, k) 的自然对数，若 k 不合法则返回一个极小的数使得 exp 为 0
long double logComb(int n, int k) {
    if (k < 0 || k > n) return -1e100L;
    return logFact[n] - logFact[k] - logFact[n - k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 预计算阶乘对数
    logFact[0] = 0.0L;
    for (int i = 1; i <= MAXN; ++i) logFact[i] = logFact[i - 1] + log((long double)i);
    int caseNo = 0;
    int N, K;
    while (cin >> N >> K && (N != 0 || K != 0)) {
        ++caseNo;
        // 原环上每个单词的邻居个数
        int t = min(N - 1, 2 * K);
        long double sumNoNeighbor = 0.0L; // 累加所有位置 i 的“没有一个邻居落在邻域内”的概率
        for (int i = 0; i < N; ++i) {
            // 洗牌后线性位置上距离不超过 K 的位置个数（不含自身）
            int m = min(K, i) + min(K, N - 1 - i);
            // 计算从 N-1 个剩余位置中随机放置 t 个邻居，全部落在补集中的概率
            long double noNeighbor;
            if (t > N - 1 - m) {
                // 补集大小不足 t，必然至少有一个邻居落在邻域内
                noNeighbor = 0.0L;
            } else {
                long double logProb = logComb(N - 1 - m, t) - logComb(N - 1, t);
                noNeighbor = exp(logProb);
            }
            sumNoNeighbor += noNeighbor;
        }
        // 期望浪费的单词数 = N - sumNoNeighbor
        long double expected = (long double)N - sumNoNeighbor;
        cout << fixed << setprecision(4) << "Case " << caseNo << ": " << expected << "\n";
    }
    return 0;
}
