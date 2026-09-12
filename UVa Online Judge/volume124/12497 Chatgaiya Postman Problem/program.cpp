#include <bits/stdc++.h>
using namespace std;

long long countRoutes(int n, const vector<int>& graph) {
    int allMask = (1 << n) - 1;
    long long answer = 0;
    for (int root = 0; root < n; root++) {
        int rootBit = 1 << root;
        vector<long long> dp((1 << n) * n, 0);
        dp[rootBit * n + root] = 1;
        for (int mask = 0; mask <= allMask; mask++) {
            if ((mask & rootBit) == 0) continue;
            for (int last = 0; last < n; last++) {
                long long way = dp[mask * n + last];
                if (way == 0) continue;
                for (int next = 0; next < n; next++) {
                    if ((mask >> next) & 1) continue;
                    if (((graph[last] >> next) & 1) == 0) continue;
                    dp[(mask | (1 << next)) * n + next] += way;
                }
            }
        }
        int usableMask = allMask ^ rootBit;
        vector<long long> cycle(1 << n, 0);
        for (int mask = 0; mask <= allMask; mask++) {
            if ((mask & rootBit) == 0 || __builtin_popcount(mask) < 3) continue;
            long long ways = 0;
            for (int last = 0; last < n; last++) {
                if (last == root) continue;
                if (((graph[last] >> root) & 1) == 0) continue;
                ways += dp[mask * n + last];
            }
            cycle[mask ^ rootBit] = ways / 2;
        }
        vector<long long> sum = cycle;
        for (int bit = 0; bit < n; bit++) {
            if ((usableMask >> bit) & 1) {
                for (int mask = 0; mask <= usableMask; mask++) {
                    if ((mask >> bit) & 1) sum[mask] += sum[mask ^ (1 << bit)];
                }
            }
        }
        long long ordered = 0;
        for (int mask = 0; mask <= usableMask; mask++) {
            if (cycle[mask] == 0) continue;
            ordered += cycle[mask] * sum[usableMask ^ mask];
        }
        answer += ordered / 2;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int caseId = 1; caseId <= t; caseId++) {
        int n, m;
        cin >> n >> m;
        vector<int> graph(n, 0);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            graph[u] |= 1 << v;
            graph[v] |= 1 << u;
        }
        cout << "Case " << caseId << ": " << countRoutes(n, graph) << '\n';
    }
    return 0;
}
