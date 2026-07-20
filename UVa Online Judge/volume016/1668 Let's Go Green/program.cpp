// Let's Go Green
// UVa ID: 1668
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N;
        cin >> N;
        vector<vector<pair<int, int>>> adj(N + 1);
        for (int i = 0; i < N - 1; ++i) {
            int A, B, C;
            cin >> A >> B >> C;
            adj[A].push_back({B, C});
            adj[B].push_back({A, C});
        }
        long long totalEndpoints = 0;
        for (int u = 1; u <= N; ++u) {
            int S = 0, M = 0;
            for (auto &edge : adj[u]) {
                int w = edge.second;
                S += w;
                if (w > M) M = w;
            }
            int e = max(S % 2, 2 * M - S);
            totalEndpoints += e;
        }
        long long answer = totalEndpoints / 2;
        cout << "Case #" << caseNo << ": " << answer << '\n';
    }
    return 0;
}
