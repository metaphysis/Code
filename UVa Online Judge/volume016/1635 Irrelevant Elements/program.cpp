// Irrelevant Elements
// UVa ID: 1635
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.750s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 质因数分解函数
vector<pair<long long, int>> factorize(long long num) {
    vector<pair<long long, int>> factors;
    // 从2开始试除
    for (long long prime = 2; prime * prime <= num; prime++) {
        if (num % prime == 0) {
            int exponent = 0;
            while (num % prime == 0) {
                num /= prime;
                exponent++;
            }
            factors.emplace_back(prime, exponent);
        }
    }
    // 处理剩余的质因数
    if (num > 1) {
        factors.emplace_back(num, 1);
    }
    return factors;
}

// 计算x!中质因子p的幂次（勒让德公式）
int calculatePrimePower(long long prime, long long num) {
    int powerCount = 0;
    while (num >= prime) {
        powerCount += num / prime;
        num /= prime;
    }
    return powerCount;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    // 处理多个测试用例
    while (cin >> n >> m) {
        // 分解m的质因数
        auto primeFactors = factorize(m);
        vector<int> irrelevantIndices;

        // 检查每个位置i（对应组合数C(n-1, i-1)）
        for (long long index = 0; index < n; index++) {
            bool isIrrelevant = true;
            // 检查所有质因子条件
            for (auto& factor : primeFactors) {
                long long prime = factor.first;
                int requiredExponent = factor.second;
                // 计算组合数中质因子p的幂次：v_p(C(n-1, index))
                int actualExponent = calculatePrimePower(prime, n - 1) 
                                   - calculatePrimePower(prime, index) 
                                   - calculatePrimePower(prime, n - 1 - index);
                // 如果某个质因子的幂次不足，则该位置不是无关的
                if (actualExponent < requiredExponent) {
                    isIrrelevant = false;
                    break;
                }
            }
            // 如果满足所有条件，记录该位置
            if (isIrrelevant) {
                irrelevantIndices.push_back(index + 1);
            }
        }

        // 输出结果
        cout << irrelevantIndices.size() << "\n";
        if (!irrelevantIndices.empty()) {
            for (size_t j = 0; j < irrelevantIndices.size(); j++) {
                if (j > 0) cout << " ";
                cout << irrelevantIndices[j];
            }
            cout << "\n";
        } else {
            cout << "\n";
        }
    }

    return 0;
}
