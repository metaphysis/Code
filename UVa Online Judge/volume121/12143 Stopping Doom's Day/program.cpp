// Stopping Doom's Day
// UVa ID: 12143
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MOD = 10007;  // 题目要求的模数

/**
 * 使用扩展欧几里得算法计算模逆元
 * @param a 需要求逆元的数
 * @param m 模数
 * @return a 在模 m 下的逆元
 */
int modularInverse(int a, int m) {
    int originalMod = m;
    int y = 0, x = 1;
    
    if (m == 1) return 0;
    
    while (a > 1) {
        int quotient = a / m;
        int temp = m;
        m = a % m;
        a = temp;
        temp = y;
        y = x - quotient * y;
        x = temp;
    }
    
    if (x < 0) x += originalMod;
    return x;
}

/**
 * 拉格朗日插值法计算多项式在给定点的值
 * @param knownValues 已知的函数值点 (n=1到11对应的T(n)值)
 * @param x 需要计算的点 (对应 n-1)
 * @param mod 模数
 * @return 插值结果，即 T(n) mod 10007
 */
int lagrangeInterpolation(const vector<int>& knownValues, int x, int mod) {
    int pointCount = knownValues.size();  // 已知点数量 (11个点)
    
    // 如果 x 在已知点范围内，直接返回对应的已知值
    if (x < pointCount) {
        return knownValues[x] % mod;
    }
    
    int result = 0;
    
    // 拉格朗日插值主循环
    for (int i = 0; i < pointCount; i++) {
        int numerator = 1;   // 分子
        int denominator = 1; // 分母
        
        // 计算拉格朗日基函数
        for (int j = 0; j < pointCount; j++) {
            if (i == j) continue;
            
            // 计算分子: ∏(x - x_j)
            numerator = (long long)numerator * (x - j + mod) % mod;
            
            // 计算分母: ∏(x_i - x_j)  
            denominator = (long long)denominator * (i - j + mod) % mod;
        }
        
        // 累加每一项: y_i * [∏(x - x_j)] / [∏(x_i - x_j)]
        result = (result + (long long)knownValues[i] * numerator % mod * 
                 modularInverse(denominator, mod)) % mod;
    }
    
    return result;
}

int main() {
    // 已知的 n=1 到 11 的正确输出值（模 10007）
    // 这些值通过小规模暴力计算或题目已知结果得到
    vector<int> knownValues = {
        0,      // n = 1
        0,      // n = 2  
        120,    // n = 3
        3200,   // n = 4
        5139,   // n = 5
        6959,   // n = 6
        3988,   // n = 7
        8968,   // n = 8
        4108,   // n = 9
        9728,   // n = 10
        444     // n = 11
    };
    
    int inputN;
    while (cin >> inputN && inputN != 0) {
        if (inputN <= 11) {
            // 对于 n <= 11，直接输出已知值
            cout << knownValues[inputN - 1] << "\n";
        } else {
            // 对于 n > 11，使用拉格朗日插值计算
            // 注意：knownValues 的索引对应关系：索引 0 -> n=1, 索引 1 -> n=2, ..., 索引 10 -> n=11
            // 所以对于输入 n，对应的插值点 x = n - 1
            int interpolationPoint = inputN - 1;
            cout << lagrangeInterpolation(knownValues, interpolationPoint, MOD) << "\n";
        }
    }
    
    return 0;
}
