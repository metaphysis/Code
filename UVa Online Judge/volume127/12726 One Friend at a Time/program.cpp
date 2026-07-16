// One Friend at a Time
// UVa ID: 12726
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int N, M, K;
        cin >> N >> M >> K;

        vector<vector<bool>> adj(N + 1, vector<bool>(N + 1, false));
        for (int i = 0; i < M; ++i) {
            int A, B;
            cin >> A >> B;
            adj[A][B] = adj[B][A] = true;
        }

        // 如果已经是好友
        if (adj[1][N]) {
            cout << "Case #" << tc << ": 0\n";
            continue;
        }

        // 预处理每个节点的邻居掩码（位 i-1 表示节点 i）
        vector<int> neighborMask(N + 1, 0);
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                if (adj[i][j])
                    neighborMask[i] |= (1 << (j - 1));

        // 初始状态：$\texttt{Bob}$ 已有的朋友（不含 Alice）
        int startMask = 0;
        for (int v = 2; v <= N - 1; ++v)
            if (adj[1][v])
                startMask |= (1 << (v - 1));

        // 检查初始状态是否能直接添加 Alice
        auto canAdd$\texttt{Alice}$ = [&](int mask) -> bool {
            int common = __builtin_popcount(mask & neighborMask[N]);
            return common >= K;
        };

        if (canAdd$\texttt{Alice}$(startMask)) {
            cout << "Case #" << tc << ": 0\n";
            continue;
        }

        // BFS
        int totalStates = 1 << N; // N <= 20，1<<20 可接受
        vector<bool> visited(totalStates, false);
        queue<pair<int, int>> q; // {mask, steps}
        visited[startMask] = true;
        q.push({startMask, 0});

        int answer = -1;
        while (!q.empty()) {
            auto [mask, steps] = q.front();
            q.pop();

            // 尝试添加一个非 Alice 的新朋友
            for (int v = 2; v <= N - 1; ++v) {
                int bit = 1 << (v - 1);
                if (mask & bit) continue; // 已经是朋友

                int common = __builtin_popcount(mask & neighborMask[v]);
                if (common < K) continue;

                int newMask = mask | bit;
                if (visited[newMask]) continue;
                visited[newMask] = true;

                // 检查添加 v 后是否能添加 Alice
                if (canAdd$\texttt{Alice}$(newMask)) {
                    answer = steps + 1; // 只额外添加了 v（Alice 不计）
                    goto found;
                }

                q.push({newMask, steps + 1});
            }
        }

        found:
        cout << "Case #" << tc << ": " << answer << "\n";
    }

    return 0;
}
