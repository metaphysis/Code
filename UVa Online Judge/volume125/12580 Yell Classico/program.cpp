// Yell Classico
// UVa ID: 12580
// Verdict: Accepted
// Submission Date: 2026-04-25
// UVa Run Time: 0.840s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
int N;
int h[MAXN];
int dp[MAXN][12]; // dp[i][k]：从 i 开始选 k 个的最优起始位置（-1 表示不可行）

// 返回 true 表示方案 A 比方案 B 字典序更大
bool isBetter(int posA, int kA, int posB, int kB) {
    if (kA == 0) return false;
    if (kB == 0) return true;
    if (h[posA] != h[posB]) return h[posA] > h[posB];
    // 第一个相等，比较剩余部分
    return isBetter(dp[posA + 1][kA - 1], kA - 1, dp[posB + 1][kB - 1], kB - 1);
}

void solve() {
    // 边界：k = 0 无法表示，用 pos = N+1 表示空
    for (int i = 1; i <= N + 2; ++i) 
        dp[i][0] = N + 1; // 虚拟空位置
    
    for (int k = 1; k <= 11; ++k) {
        for (int i = N - k + 1; i >= 1; --i) {
            int end = N - k + 1;
            // 找到区间 [i, end] 中的最大值
            int maxVal = -1;
            for (int j = i; j <= end; ++j) 
                if (h[j] > maxVal) maxVal = h[j];
            
            int bestPos = -1;
            // 遍历所有等于 maxVal 的位置
            for (int j = i; j <= end; ++j) {
                if (h[j] == maxVal) {
                    if (bestPos == -1) bestPos = j;
                    else {
                        // 比较 (j 作为第一个) 和 (bestPos 作为第一个) 哪个更好
                        if (isBetter(dp[j + 1][k - 1], k - 1, dp[bestPos + 1][k - 1], k - 1))
                            bestPos = j;
                    }
                }
            }
            dp[i][k] = bestPos;
        }
    }
}

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

        solve();
        
        // 输出结果
        int cur = dp[1][11];
        printf("Case %d:", caseNo);
        for (int k = 11; k >= 1; --k) {
            printf(" %d", h[cur]);
            if (k == 1) break;
            cur = dp[cur + 1][k - 1];
        }
        printf("\n");
    }
    return 0;
}
