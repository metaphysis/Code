// Minimum Weight
// UVa ID: 10560
// Verdict: Accepted
// Submission Date: 2025-11-08
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long N;
    int K;
    while (cin >> N >> K && (N || K)) {
        // 计算最少砝码数 m
        int m = 1;
        long long maxW = 1; // (3^1 - 1)/2 = 1
        while (maxW < N) {
            m++;
            maxW = (maxW * 3 + 1); // 递推: maxW(m) = 3 * maxW(m-1) + 1
        }
        
        // 生成砝码
        vector<long long> weights(m);
        long long p = 1;
        for (int i = 0; i < m; i++) {
            weights[i] = p;
            p *= 3;
        }
        
        // 输出砝码
        cout << m;
        for (auto w : weights) cout << " " << w;
        cout << endl;
        
        // 处理每个查询
        for (int k = 0; k < K; k++) {
            long long x;
            cin >> x;
            vector<int> coeff(m, 0);
            long long n = x;
            
            // 正确的平衡三进制转换
            for (int i = 0; i < m; i++) {
                long long remainder = n % 3;
                if (remainder == 2) {
                    coeff[i] = -1;
                    n = n / 3 + 1;  // 进位
                } else if (remainder == 1) {
                    coeff[i] = 1;
                    n = n / 3;
                } else { // remainder == 0
                    coeff[i] = 0;
                    n = n / 3;
                }
            }
            
            // 输出表达式（降序）
            bool first = true;
            for (int i = m - 1; i >= 0; i--) {
                if (coeff[i] != 0) {
                    if (!first) {
                        cout << (coeff[i] > 0 ? "+" : "-");
                    } else {
                        if (coeff[i] < 0) cout << "-";
                        first = false;
                    }
                    cout << weights[i];
                }
            }
            if (first) cout << "0";
            cout << endl;
        }
    }
    return 0;
}
