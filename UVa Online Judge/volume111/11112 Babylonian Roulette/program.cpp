// Babylonian Roulette
// UVa ID: 11112
// Verdict: Accepted
// Submission Date: 2025-11-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long P0, B, Pf;
    while (cin >> P0 >> B >> Pf && (P0 || B || Pf)) {
        // 检查整除条件
        if ((Pf - P0) % B != 0) {
            cout << "No accounting tablet" << endl;
            continue;
        }
        long long T = (Pf - P0) / B;
        // 实际上可以合并到普通情况一起处理
        if (T == 0) {
            // 奖池无变化，可能无人参与
            cout << 0 << endl;
        } else {
            // 使用贪心：尽量用最大步长3或-3
            long long absT = abs(T);
            cout << (absT + 2) / 3 << endl;
        }
    }
    return 0;
}
