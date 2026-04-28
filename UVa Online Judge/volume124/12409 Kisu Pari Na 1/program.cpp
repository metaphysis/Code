// Kisu Pari Na 1
// UVa ID: 12409
// Verdict: Accepted
// Submission Date: 2026-04-26
// UVa Run Time: 0.030s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNum = 1; caseNum <= T; ++caseNum) {
        int R, C;
        scanf("%d %d", &R, &C);
        
        long long xorSum = 0;
        
        for (int i = 0; i < R; ++i) {
            for (int j = 0; j < C; ++j) {
                long long coins;
                scanf("%lld", &coins);
                
                // 计算到右下角的曼哈顿距离
                int distToEnd = (R - 1 - i) + (C - 1 - j);
                
                // 只考虑距离为奇数的单元格
                if (distToEnd % 2 == 1) {
                    xorSum ^= coins;
                }
            }
        }
        
        if (xorSum != 0)
            printf("Case %d: win\n", caseNum);
        else
            printf("Case %d: lose\n", caseNum);
    }
    return 0;
}
