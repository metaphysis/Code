// Lottery
// UVa ID: 12961
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    while (cin >> N >> K) {
        unsigned long long basis[50] = {0}; // K <= 50
        int rankVal = 0;
        for (int i = 0; i < N; ++i) {
            unsigned long long mask = 0;
            for (int j = 0; j < K; ++j) {
                long long val;
                cin >> val;
                if (val & 1) mask |= (1ULL << j); // 按输入顺序放置位
            }
            // 将 mask 插入线性基（高斯消元求秩）
            unsigned long long x = mask;
            for (int j = K - 1; j >= 0; --j) {
                if ((x >> j) & 1ULL) {
                    if (basis[j] == 0) {
                        basis[j] = x;
                        ++rankVal;
                        break;
                    } else x ^= basis[j];
                }
            }
        }
        if (rankVal < K) cout << 'S' << '\n';
        else { // rankVal == K
            if (N == K) cout << 'S' << '\n';
            else cout << 'N' << '\n';
        }
    }
    return 0;
}
