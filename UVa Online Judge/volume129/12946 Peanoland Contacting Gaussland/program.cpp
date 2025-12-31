// Peanoland Contacting Gaussland
// UVa ID: 12946
// Verdict: Accepted
// Submission Date: 2025-12-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long p;
    while (cin >> p) {
        long long aTotal = 0, bTotal = 0; // 总和 a + bi
        long long ak = 1, bk = 0;         // (i-1)^k 的实部和虚部系数

        while (p > 0) {
            if (p & 1) { // 当前二进制位为1
                aTotal += ak;
                bTotal += bk;
            }
            // 更新 (i-1)^(k+1) = (i-1)^k * (i-1)
            long long aNext = -ak - bk;
            long long bNext = ak - bk;
            ak = aNext;
            bk = bNext;

            p >>= 1; // 移到下一位
        }

        cout << aTotal << " " << bTotal << "\n";
    }

    return 0;
}
