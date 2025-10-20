// Data Mining
// UVa ID: 1591
// Verdict: Accepted
// Submission Date: 2025-10-20
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <climits>

using namespace std;

int main() {
    long long N, SP, SQ;
    while (cin >> N >> SP >> SQ) {
        long long bestK = LLONG_MAX;  // 初始化最佳K为最大值
        int bestA = -1, bestB = -1;   // 初始化最佳A和B
        
        // 枚举所有可能的A和B
        for (int A = 0; A <= 31; A++) {
            for (int B = 0; B <= 31; B++) {
                // 检查是否满足不重叠条件
                if (SP * (1LL + (1LL << A)) >= SQ * (1LL << B)) {
                    // 计算所需内存K
                    long long K = ((N - 1) * SP * (1LL + (1LL << A))) / (1LL << B) + SQ;
                    // 更新最优解
                    if (K < bestK) {
                        bestK = K;
                        bestA = A;
                        bestB = B;
                    } else if (K == bestK) {
                        // K相同时，选择A较小的
                        if (A < bestA) {
                            bestA = A;
                            bestB = B;
                        } else if (A == bestA && B < bestB) {
                            // A相同时，选择B较小的
                            bestB = B;
                        }
                    }
                }
            }
        }
        // 输出结果
        cout << bestK << " " << bestA << " " << bestB << endl;
    }
    return 0;
}
