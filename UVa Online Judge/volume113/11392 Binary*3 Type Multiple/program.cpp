// Binary*3 Type Multiple
// UVa ID: 11392
// Verdict: Accepted
// Submission Date: 2025-11-12
// UVa Run Time: 0.580s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int k;
    while (cin >> k) {
        int kTemp = k;
        int twoCount = 0, fiveCount = 0;
        
        // 去除因子 2
        while (kTemp % 2 == 0) {
            kTemp /= 2;
            twoCount++;
        }
        // 去除因子 5
        while (kTemp % 5 == 0) {
            kTemp /= 5;
            fiveCount++;
        }
        
        int trailingZeros = max(twoCount, fiveCount);
        
        if (kTemp == 1) {
            // 如果 K' = 1，那么只需要 trailingZeros 个 0 和一个 3
            cout << (1 + trailingZeros) << " " << 1 << " " << trailingZeros << endl;
            continue;
        }
        
        // 寻找最小的 a 使得 a 个 3 能被 kTemp 整除
        int remainder = 0;
        int length = 0;
        while (true) {
            remainder = (remainder * 10 + 3) % kTemp;
            length++;
            if (remainder == 0) {
                break;
            }
        }
        
        // 总长度 = length + trailingZeros
        // 3 的个数 = length
        // 0 的个数 = trailingZeros
        cout << (length + trailingZeros) << " " << length << " " << trailingZeros << endl;
    }
    return 0;
}
