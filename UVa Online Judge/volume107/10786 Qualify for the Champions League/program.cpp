// 10786 Qualify for the Champions League
// UVa ID: 10786
// Verdict: Accepted
// Submission Date: 2026-07-18
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N, V, Q;
        scanf("%d%d%d", &N, &V, &Q);
        int ans;
        if (Q == N) answer = 0;
        else if (Q == 1) answer = (N - 1) * V + 2;
        else answer = V * (N - Q) + 1;
        printf("League %d: %d\n", tc, answer);
    }
    return 0;
}
