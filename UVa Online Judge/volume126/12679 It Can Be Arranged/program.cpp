// It Can Be Arranged
// UVa ID: 12679
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

struct Dinic {
    struct Edge {
        int to, rev, cap;
    };
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : n(n), g(n), level(n), it(n) {}
    void addEdge(int v, int to, int cap) {
        Edge a{to, (int)g[to].size(), cap};
        Edge b{v, (int)g[v].size(), 0};
        g[v].push_back(a);
        g[to].push_back(b);
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge &e : g[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
        }
        return level[t] >= 0;
    }
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    int maxFlow(int s, int t) {
        int flow = 0;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; ++tc) {
        int N, M;
        scanf("%d %d", &N, &M);
        vector<int> A(N), B(N), S(N);
        for (int i = 0; i < N; ++i) scanf("%d %d %d", &A[i], &B[i], &S[i]);
        vector<vector<int>> clean(N, vector<int>(N));
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) scanf("%d", &clean[i][j]);

        vector<int> k(N);
        int totalNodes = 0;
        for (int i = 0; i < N; ++i) {
            k[i] = (S[i] + M - 1) / M;   // 向上取整
            totalNodes += k[i];
        }

        int SRC = 0, SNK = 2 * N + 1;
        Dinic dinic(SNK + 1);
        // 源点 -> 左部
        for (int i = 0; i < N; ++i) dinic.addEdge(SRC, 1 + i, k[i]);
        // 右部 -> 汇点
        for (int j = 0; j < N; ++j) dinic.addEdge(1 + N + j, SNK, k[j]);
        // 转移边（严格小于）
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                if (i == j) continue;
                if (B[i] + clean[i][j] < A[j])   // 注意严格小于
                    dinic.addEdge(1 + i, 1 + N + j, totalNodes);
            }

        int maxMatch = dinic.maxFlow(SRC, SNK);
        printf("Case %d: %d\n", tc, totalNodes - maxMatch);
    }
    return 0;
}
