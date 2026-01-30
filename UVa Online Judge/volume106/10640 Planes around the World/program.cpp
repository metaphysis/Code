// Planes around the World
// UVa ID: 10640
// Verdict: Accepted
// Submission Date: 2026-01-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        int a, b;
        scanf("%d %d", &a, &b);
        if (a == 0) {
            printf("Case %d: -1\n", caseNo);
            continue;
        }
        if (a >= b) {
            printf("Case %d: 1\n", caseNo);
            continue;
        }
        double r = (double)a / b;
        int needed = 10001;
        // 枚举前半程辅助飞机数i
        for (int i = 1; i < needed; i++) {
            // 计算前半程结束时环球飞机能飞的距离
            double s = (2.0 * i * a) / ((i + 1.0) * b);
            // 如果前半程飞不完，继续尝试更大的i
            if (s <= 1.0 - r + 1e-9) continue;
            int cnt = 1;  // 已经使用的飞机数（环球飞机）
            while (s < 1.0 - 1e-9) {
                // 如果已经超过当前最优解，提前结束
                if (i + cnt - 1 >= needed) break;
                // 添加一架辅助飞机
                s += (r - (1.0 - s)) / (cnt + 1.0);
                cnt++;
            }
            // 更新答案：前半程i架辅助飞机，后半程(cnt-1)架辅助飞机
            if (s >= 1.0 - 1e-9) needed = min(needed, i + cnt - 1);
        }
        if (needed > 10000) printf("Case %d: -1\n", caseNo);
        else printf("Case %d: %d\n", caseNo, needed);
    }
    return 0;
}
