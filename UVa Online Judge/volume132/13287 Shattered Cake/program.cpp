// Shattered Cake
// UVa ID: 13287
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <cstdio>

int main() {
    int W, N, w, l;
    while (scanf("%d", &W) == 1) {
        scanf("%d", &N);
        long long sum = 0;
        for (int i = 0; i < N; i++) {
            scanf("%d %d", &w, &l);
            sum += (long long)w * l;
        }
        printf("%lld\n", sum / W);
    }
    return 0;
}
