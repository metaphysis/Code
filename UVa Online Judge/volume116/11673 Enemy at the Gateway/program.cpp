// Enemy at the Gateway
// UVa ID: 11673
// Verdict: Accepted
// Submission Date: 2026-07-28
// UVa Run Time: 6.240s

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int P;
        scanf("%d", &P);
        vector<int> pattern(P);
        for (int i = 0; i < P; ++i) scanf("%d", &pattern[i]);

        int N;
        long long p0, q0, A, B, C, D, E, F, M;
        scanf("%d%lld%lld%lld%lld%lld%lld%lld%lld%lld",
              &N, &p0, &q0, &A, &B, &C, &D, &E, &F, &M);

        vector<ull> mask(N);
        long long pPrev = p0, qPrev = q0;
        for (int i = 0; i < N; ++i) {
            long long p_i = (A * pPrev + B * qPrev + C) % M;
            long long q_i = (D * pPrev + E * qPrev + F) % M;
            if (q_i < p_i) swap(p_i, q_i);
            pPrev = p_i;
            qPrev = q_i;

            ull cur = 0;
            for (int j = 0; j < P; ++j) {
                if (p_i <= pattern[j] && pattern[j] <= q_i)
                    cur |= (1ULL << j);
            }
            mask[i] = cur;
        }

        int ans = 0;
        int limit = N - P;
        for (int s = 0; s <= limit; ++s) {
            bool ok = true;
            for (int j = 0; j < P; ++j) {
                if (((mask[s + j] >> j) & 1ULL) == 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) ++ans;
        }
        printf("Case %d: %d\n", tc, ans);
    }
    return 0;
}
