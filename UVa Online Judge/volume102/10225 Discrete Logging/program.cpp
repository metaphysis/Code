// Discrete Logging
// UVa ID: 10225
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;

typedef long long ll;

// 快速幂取模 (base^exponent mod modulus)
ll fastPowMod(ll base, ll exponent, ll modulus) {
    ll result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exponent >>= 1;
    }
    return result;
}

// 使用大步小步算法求解离散对数
ll solveDiscreteLog(ll prime, ll base, ll target) {
    // 特殊情况：目标值为 1 时，对数为 0
    if (target == 1) {
        return 0;
    }
    
    // 计算步长 m = ceil(sqrt(P-1))
    ll stepSize = ceil(sqrt(prime - 1));
    unordered_map<ll, ll> valueToIndex;
    
    // 小步：预计算 base^j 对于 j = 0 到 m-1
    ll currentValue = 1;
    for (ll j = 0; j < stepSize; j++) {
        if (valueToIndex.find(currentValue) == valueToIndex.end()) {
            valueToIndex[currentValue] = j;
        }
        currentValue = (currentValue * base) % prime;
    }
    
    // 计算 base^{-m} mod prime
    ll inverseStep = fastPowMod(base, prime - 1 - stepSize, prime);
    currentValue = target;
    
    // 大步：检查 target * (base^{-m})^i 是否在预计算的表中
    for (ll i = 0; i < stepSize; i++) {
        if (valueToIndex.find(currentValue) != valueToIndex.end()) {
            return i * stepSize + valueToIndex[currentValue];
        }
        currentValue = (currentValue * inverseStep) % prime;
    }
    
    return -1; // 无解
}

int main() {
    ll prime, base, target;
    while (cin >> prime >> base >> target) {
        ll result = solveDiscreteLog(prime, base, target);
        if (result == -1) {
            cout << "no solution" << endl;
        } else {
            cout << result << endl;
        }
    }
    return 0;
}
