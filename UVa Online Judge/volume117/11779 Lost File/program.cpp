// Lost File
// UVa ID: 11779
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.120s
// https://blog.csdn.net/metaphysis/article/details/163173948

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N, K;
        cin >> N >> K;

        // P[u][v] = 从 u 到 v 的路径总数
        vector<vector<ll>> P(N, vector<ll>(N, 0));
        for (int i = 0; i < K; ++i) {
            int u, v;
            ll w;
            cin >> u >> v >> w;
            P[u][v] = w;
        }

        // 拓扑排序（依据路径偏序）
        vector<int> indeg(N, 0);
        for (int u = 0; u < N; ++u)
            for (int v = 0; v < N; ++v)
                if (P[u][v] > 0)
                    ++indeg[v];

        queue<int> q;
        for (int i = 0; i < N; ++i)
            if (indeg[i] == 0) q.push(i);

        vector<int> order;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (int v = 0; v < N; ++v)
                if (P[u][v] > 0) {
                    --indeg[v];
                    if (indeg[v] == 0) q.push(v);
                }
        }

        // 构建上三角矩阵 U（按拓扑序）
        vector<vector<ll>> U(N, vector<ll>(N, 0));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (i == j) U[i][j] = 1;
                else U[i][j] = P[order[i]][order[j]];
            }
        }

        // 回代求逆 V = U^{-1}
        vector<vector<ll>> V(N, vector<ll>(N, 0));
        for (int i = N - 1; i >= 0; --i) {
            // 非对角元
            for (int j = N - 1; j > i; --j) {
                ll sum = 0;
                for (int k = i + 1; k < N; ++k)
                    sum += U[i][k] * V[k][j];
                V[i][j] = -sum;
            }
            // 对角元
            ll sum = 0;
            for (int k = i + 1; k < N; ++k)
                sum += U[i][k] * V[k][i];
            V[i][i] = 1 - sum;
        }

        // 还原邻接表（原节点编号）
        vector<vector<int>> adj(N);
        for (int i = 0; i < N; ++i)
            for (int j = i + 1; j < N; ++j)
                if (V[i][j] == -1) {
                    int u = order[i];
                    int v = order[j];
                    adj[u].push_back(v);
                }

        // 排序并统计边数
        int E = 0;
        for (int u = 0; u < N; ++u) {
            sort(adj[u].begin(), adj[u].end());
            E += (int)adj[u].size();
        }

        cout << "Case " << caseNo << ": " << N << " " << E << "\n";
        for (int u = 0; u < N; ++u) {
            cout << adj[u].size();
            for (int v : adj[u]) cout << " " << v;
            cout << "\n";
        }
    }

    return 0;
}
