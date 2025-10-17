// GCD XOR
// UVa ID: 12716
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.690s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include<stdio.h>
int sum[30000005];
void precompute() {
    for (int i = 3; i <= 30000000; i++)
        if ((i ^ (i - 1)) == 1) {
            sum[i]++;
            for (int j = i << 1, k = 2; j <= 30000000; j += i, k++)
                if (k == (j ^ (j - k))) sum[j]++;
        }
    for (int i = 1; i <= 30000000; i++) sum[i] += sum[i - 1];
}
int main() {
    precompute();
    int T, n;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        scanf("%d", &n);
        printf("Case %d: %d\n", t, sum[n]);
    }
    return 0;
}
