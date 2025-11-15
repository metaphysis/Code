// Abundance and Perfect Numbers
// UVa ID: 10914
// Verdict: Accepted
// Submission Date: 2025-11-10
// UVa Run Time: 0.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_N = 10000000;

vector<long long> precomputeAbunPrefixSum() {
    // 筛法标记素数
    vector<bool> isPrime(MAX_N + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= MAX_N; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= MAX_N; j += i) {
                isPrime[j] = false;
            }
        }
    }

    vector<long long> prefixSum(MAX_N + 1, 0);

    // 遍历所有奇素数 p
    for (int p = 2; p <= MAX_N; p++) {
        if (!isPrime[p] || p == 2) continue; // 跳过偶素数 2
        long long powerOfTwo = 2;
        for (int k = 1; ; k++) {
            long long num = powerOfTwo * p;
            if (num > MAX_N) break;
            // 计算 abunVal = 2^(k+1) - p - 1
            long long abunVal = (powerOfTwo * 2) - p - 1;
            prefixSum[num] += abunVal;
            powerOfTwo *= 2;
            if (powerOfTwo > MAX_N) break;
        }
    }

    // 构建前缀和
    for (int i = 1; i <= MAX_N; i++) {
        prefixSum[i] += prefixSum[i - 1];
    }

    return prefixSum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<long long> prefixSum = precomputeAbunPrefixSum();

    int n;
    while (cin >> n && n != 0) {
        cout << n << " " << prefixSum[n] << "\n";
    }

    return 0;
}
