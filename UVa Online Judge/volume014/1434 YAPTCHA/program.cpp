// YAPTCHA
// UVa ID: 1434
// Verdict: Accepted
// Submission Date: 2025-11-03
// UVa Run Time: 0.120s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_K = 1000000;                    // k 的最大值
const int MAX_M = 3 * MAX_K + 10;             // m = 3k+7 的最大值

vector<bool> isPrime;                         // 标记是否为质数
vector<int> prefixSum;                        // 前缀和数组

// 埃拉托斯特尼筛法预处理质数
void sieve() {
    isPrime.assign(MAX_M + 1, true);          // 初始化为全是质数
    isPrime[0] = isPrime[1] = false;          // 0 和 1 不是质数
    for (int i = 2; i * i <= MAX_M; i++) {
        if (isPrime[i]) {                     // 如果 i 是质数
            for (int j = i * i; j <= MAX_M; j += i) {
                isPrime[j] = false;           // 标记 i 的倍数为非质数
            }
        }
    }
}

// 预处理前缀和数组
void precompute() {
    sieve();                                  // 先筛出质数
    prefixSum.resize(MAX_K + 1, 0);           // 初始化前缀和数组
    for (int k = 1; k <= MAX_K; k++) {
        int m = 3 * k + 7;                    // 计算 m = 3k+7
        // 如果 m 是质数，当前项为 1，否则为 0
        prefixSum[k] = prefixSum[k - 1] + (isPrime[m] ? 1 : 0);
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    precompute();
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << prefixSum[n] << "\n";
    }
    return 0;
}
