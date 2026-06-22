// Blood Groups
// UVa ID: 13005
// Verdict: Accepted
// Submission Date: 2026-06-22
// UVa Run Time: 0.340s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev, cap; };
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : g(n), level(n), it(n) {}
    void addEdge(int v, int to, int cap) {
        if (cap <= 0) return;
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
            for (auto &e : g[v])
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
        int flow = 0, INF = 1e9;
        while (bfs(s, t)) {
            fill(it.begin(), it.end(), 0);
            while (true) {
                int f = dfs(s, t, INF);
                if (!f) break;
                flow += f;
            }
        }
        return flow;
    }
};

bool feasibleForQuery(const vector<set<int>>& parents, const vector<int>& query) {
    int N = parents.size();
    int B = query.size();

    // 查询为空（O型）：所有父母必须能贡献O（即血型大小<N）
    if (B == 0) {
        for (int i = 0; i < N; ++i)
            if ((int)parents[i].size() == N) return false;
        return true;
    }

    // 收集父母侧所有抗原（去重）
    set<int> parentSet;
    for (int i = 0; i < N; ++i)
        for (int x : parents[i]) parentSet.insert(x);
    vector<int> parentAntigens(parentSet.begin(), parentSet.end());
    int PA = parentAntigens.size();

    // 节点编号
    int S = 0;
    int parentStart = 1;
    int parentAntigenStart = parentStart + N;
    int childAntigenStart = parentAntigenStart + PA;
    int T = childAntigenStart + B;
    int V = T + 1;
    Dinic din(V);

    // 源点 -> 每位父母，容量1
    for (int i = 0; i < N; ++i)
        din.addEdge(S, parentStart + i, 1);

    // 父母 -> 父母侧抗原（若父母拥有该抗原）
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < PA; ++j)
            if (parents[i].count(parentAntigens[j]))
                din.addEdge(parentStart + i, parentAntigenStart + j, 1);

    // 父母侧抗原 -> 子代侧抗原（相同抗原）
    for (int j = 0; j < PA; ++j)
        for (int k = 0; k < B; ++k)
            if (parentAntigens[j] == query[k])
                din.addEdge(parentAntigenStart + j, childAntigenStart + k, 1);

    // 子代侧抗原 -> 汇点，容量1（每个抗原只需被覆盖一次）
    for (int k = 0; k < B; ++k)
        din.addEdge(childAntigenStart + k, T, 1);

    int flow = din.maxFlow(S, T);
    return flow == B;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    while (cin >> N >> Q) {
        vector<set<int>> parents(N);
        for (int i = 0; i < N; ++i) {
            int B;
            cin >> B;
            for (int j = 0; j < B; ++j) {
                int c;
                cin >> c;
                parents[i].insert(c);
            }
        }
        for (int q = 0; q < Q; ++q) {
            int B;
            cin >> B;
            vector<int> query(B);
            for (int i = 0; i < B; ++i) cin >> query[i];
            cout << (feasibleForQuery(parents, query) ? 'Y' : 'N') << '\n';
        }
    }
    return 0;
}
