// Coco Monkey
// UVa ID: 10726
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.650s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; caseNo++) {
        int S, M, low, high;
        cin >> S >> M >> low >> high;
        int cnt = 0;
        // 枚举最后的剩余椰子数：k * S
        for (int k = 1; ; k++) {
            long long C = k * S; // 最后剩余椰子数
            bool valid = true;
            // 逆向回推 S 步
            for (int i = 0; i < S; i++) {
                // 回推公式：C_prev = S * C / (S-1) + M，且必须整除
                if (C % (S - 1) != 0) {
                    valid = false;
                    break;
                }
                C = C / (S - 1) * S + M;
                // 提前退出：如果已经超过 high，再回推只会更大
                if (C > high) break;
            }
            if (valid && C >= low && C <= high) cnt++;
            // 如果回推后的 C 已经大于 high，再增大 k 只会更大，可以停止
            if (C > high) break;
        }
        cout << "Case " << caseNo << ": " << cnt << endl;
    }
    return 0;
}
