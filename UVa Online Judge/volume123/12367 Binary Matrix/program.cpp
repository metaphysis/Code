// Binary Matrix
// UVa ID: 12367
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

long long minRingCost(const vector<int>& a, int L, int target) {
    vector<long long> pref(L);
    pref[0] = 0;
    for (int i = 1; i < L; ++i)
        pref[i] = pref[i - 1] + (a[i - 1] - target);
    sort(pref.begin(), pref.end());
    long long median = pref[L / 2];
    long long ans = 0;
    for (long long x : pref)
        ans += llabs(x - median);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int M, N;
        cin >> M >> N;
        vector<int> rowSum(M, 0), colSum(N, 0);
        int total = 0;
        string s;
        for (int i = 0; i < M; ++i) {
            cin >> s;
            for (int j = 0; j < N; ++j)
                if (s[j] == '1') {
                    ++rowSum[i];
                    ++colSum[j];
                    ++total;
                }
        }

        bool both = (total % M == 0 && total % N == 0);
        bool rowOk = (total % M == 0);
        bool colOk = (total % N == 0);

        if (both) {
            int R = total / M;
            int C = total / N;
            long long costRow = minRingCost(rowSum, M, R);
            long long costCol = minRingCost(colSum, N, C);
            cout << "Case " << tc << ": both " << (costRow + costCol) << '\n';
        } else if (rowOk) {
            int R = total / M;
            cout << "Case " << tc << ": row " << minRingCost(rowSum, M, R) << '\n';
        } else if (colOk) {
            int C = total / N;
            cout << "Case " << tc << ": column " << minRingCost(colSum, N, C) << '\n';
        } else {
            cout << "Case " << tc << ": impossible\n";
        }
    }
    return 0;
}
