// Series of Powers
// UVa ID: 11190
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int l, h, k, caseNo = 0;
    while (scanf("%d %d %d", &l, &h, &k) == 3) {
        if (l == -1 && h == -1 && k == -1) break;
        ++caseNo;

        // 存储每项的尾数和指数（科学计数法）
        vector<pair<double, int>> terms;
        int maxExp = -1e9;
        bool allZero = true;

        for (int i = l; i <= h; ++i) {
            if (i == 0) {
                // 0^k = 0，当 k > 0 时
                terms.push_back({0.0, 0});
                if (0 > maxExp) maxExp = 0;
                continue;
            }
            allZero = false;
            double logVal = k * log10(i);
            int expPart = floor(logVal);
            double mantissa = pow(10, logVal - expPart);
            // mantissa 在 [1, 10)
            if (mantissa >= 10.0) {
                mantissa /= 10.0;
                expPart++;
            }
            terms.push_back({mantissa, expPart});
            if (expPart > maxExp) maxExp = expPart;
        }

        // 如果所有项都是 0（即 l = h = 0）
        if (allZero && l == 0 && h == 0) {
            printf("Case %04d: 0.000000e0000000001\n", caseNo);
            continue;
        }

        // 对齐到 maxExp 并求和
        double sumMantissa = 0.0;
        for (auto& term : terms) {
            if (term.first == 0.0) continue;
            int expDiff = maxExp - term.second;
            sumMantissa += term.first * pow(10, -expDiff);
        }

        // 如果和为 0
        if (fabs(sumMantissa) < 1e-12) {
            printf("Case %04d: 0.000000e0000000001\n", caseNo);
            continue;
        }

        // 归一化尾数到 [0.1, 1)
        int finalExp = maxExp;
        while (sumMantissa >= 1.0) {
            sumMantissa /= 10.0;
            finalExp++;
        }
        while (sumMantissa > 0 && sumMantissa < 0.1) {
            sumMantissa *= 10.0;
            finalExp--;
        }

        // 输出，尾数保留6位小数
        printf("Case %04d: 0.%06de%010d\n", caseNo, (int)round(sumMantissa * 1e6), finalExp);
    }
    return 0;
}
