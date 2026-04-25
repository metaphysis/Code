// Yell Classico
// UVa ID: 12580
// Verdict: Accepted
// Submission Date: 2026-04-25
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
int N, h[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        scanf("%d", &N);
        for (int i = 1; i <= N; ++i) scanf("%d", &h[i]);
        if (N < 11) {
            printf("Case %d: go home!\n", caseNo);
            continue;
        }
        int current = 1;
        printf("Case %d:", caseNo);
        for (int L = 11; L >= 1; --L) {
            int end = N - L + 1;
            // 找区间 [current, end] 最大值
            int maxVal = -1, best = -1;
            for (int i = current; i <= end; ++i)
                if (h[i] > maxVal) {
                    maxVal = h[i];
                    best = i;
                }
            printf(" %d", maxVal);
            current = best + 1;
        }
        printf("\n");
    }
    return 0;
}
