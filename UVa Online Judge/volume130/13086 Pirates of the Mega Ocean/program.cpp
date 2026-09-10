// Pirates of the Mega Ocean
// UVa ID: 13086
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.100s

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N, M;
        cin >> N >> M;
        long long P, Q, R, X, Y, Z;
        cin >> P >> Q >> R >> X >> Y >> Z;

        vector<long long> A(N + 1);
        vector<bool> isSmall(N + 1, false);
        long long sumA = 0;

        for (int i = 1; i <= N; ++i) {
            long long val = (P * i * i + Q * i + R) % 1000007LL;
            A[i] = val;
            sumA += val;
        }

        for (int i = 1; i <= M; ++i) {
            long long s = (X * i * i + Y * i + Z) % N + 1;
            isSmall[(int)s] = true;
        }

        long long ans = LLONG_MAX;
        for (int i = 1; i <= N; ++i) {
            if (!isSmall[i]) {
                long long cost = A[i] * (sumA - A[i]);
                if (cost < ans) ans = cost;
            }
        }

        cout << "Case " << tc << ": " << ans << '\n';
    }
    return 0;
}
