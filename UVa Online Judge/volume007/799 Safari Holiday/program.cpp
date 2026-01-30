// Safari Holiday
// UVa ID: 799
// Verdict: Accepted
// Submission Date: 2026-01-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n, kmax;
    while (cin >> n >> kmax) {
        long long bestK = -1;
        // 如果允许所有人一组
        if (n <= kmax) bestK = n;
        else {
            // 从大到小搜索第一个满足整除条件的 k
            for (long long k = kmax; k >= 2; --k)
                if (n % k == 0 && (n - 1) % (k - 1) == 0) {
                    bestK = k;
                    break;
                }
        }
        // 处理 n=1 的特殊情况
        if (n == 1 && kmax >= 1) bestK = 1;
        
        if (bestK == -1) cout << "No solution\n";
        else {
            long long days;
            if (bestK == n || bestK == 1) days = 1;
            else days = (n - 1) / (bestK - 1);
            cout << bestK << " persons/group, " << days << " day";
            if (days > 1) cout << 's';
            cout << '\n';
        }
    }
    return 0;
}
