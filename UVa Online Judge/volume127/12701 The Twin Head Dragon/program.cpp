// The Twin Head Dragon
// UVa ID: 12701
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.040s

#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, idx, w; };
struct PathInfo { int mask; int sum; int cnt; };

void dfs(int u, int parent, int mask, int sum, int cnt,
         const vector<vector<Edge>>& adj,
         vector<PathInfo>& paths, unordered_set<int>& seen) {
    for (const Edge& e : adj[u]) {
        int v = e.to;
        if (v == parent) continue;
        int newMask = mask | (1 << e.idx);
        int newSum = sum + e.w;
        int newCnt = cnt + 1;
        if (seen.find(newMask) == seen.end()) {
            seen.insert(newMask);
            paths.push_back({newMask, newSum, newCnt});
        }
        dfs(v, u, newMask, newSum, newCnt, adj, paths, seen);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    while (cin >> N && N) {
        int M = N - 1;
        vector<vector<Edge>> adj(N);
        for (int i = 0; i < M; ++i) {
            int A, B, C;
            cin >> A >> B >> C;
            adj[A].push_back({B, i, C});
            adj[B].push_back({A, i, C});
        }
        vector<PathInfo> paths;
        unordered_set<int> seen;
        for (int s = 0; s < N; ++s)
            dfs(s, -1, 0, 0, 0, adj, paths, seen);
        int totalMask = (1 << M) - 1;
        const double INF = 1e100;
        vector<double> dp(totalMask + 1, INF);
        dp[0] = 0.0;
        for (int mask = 0; mask <= totalMask; ++mask) {
            if (dp[mask] >= INF / 2) continue;
            for (const PathInfo& p : paths) {
                if ((p.mask & mask) == 0) {
                    int newMask = mask | p.mask;
                    double cost = (double)p.sum / p.cnt;
                    dp[newMask] = min(dp[newMask], dp[mask] + cost);
                }
            }
        }
        cout << fixed << setprecision(4) << dp[totalMask] << "\n";
    }
    return 0;
}
