// Factorial Products
// UVa ID: 12765
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 预计算 0~9 的阶乘的质因数分解（2, 3, 5, 7 的指数）
vector<vector<int>> precomputeFactorialFactors() {
    vector<vector<int>> factors(10, vector<int>(4, 0)); // 索引 0~9，每个有 4 个质数指数
    for (int n = 2; n <= 9; ++n) {
        int num = n;
        // 分解 num
        for (int p : {2, 3, 5, 7}) {
            while (num % p == 0) {
                factors[n][p == 2 ? 0 : (p == 3 ? 1 : (p == 5 ? 2 : 3))]++;
                num /= p;
            }
        }
    }
    // 计算 n! 的质因数分解
    for (int n = 2; n <= 9; ++n) {
        for (int i = 0; i < 4; ++i) {
            factors[n][i] += factors[n - 1][i];
        }
    }
    return factors;
}

int main() {
    auto factors = precomputeFactorialFactors();
    int n, m;
    
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        
        vector<int> totalA(4, 0); // 2,3,5,7 的指数
        vector<int> totalB(4, 0);
        
        // 读取第一个乘积
        for (int i = 0; i < n; ++i) {
            int digit;
            cin >> digit;
            if (digit <= 1) continue; // 0! = 1! = 1，不影响
            for (int j = 0; j < 4; ++j) {
                totalA[j] += factors[digit][j];
            }
        }
        
        // 读取第二个乘积
        for (int i = 0; i < m; ++i) {
            int digit;
            cin >> digit;
            if (digit <= 1) continue;
            for (int j = 0; j < 4; ++j) {
                totalB[j] += factors[digit][j];
            }
        }
        
        // 比较质因数指数
        if (totalA == totalB) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
