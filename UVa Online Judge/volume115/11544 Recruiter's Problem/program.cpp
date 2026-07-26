// Recruiter's Problem
// UVa ID: 11544
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.310s
// https://blog.csdn.net/metaphysis/article/details/163173800

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge { int to, rev, cap; };
    vector<vector<Edge>> g;
    vector<int> level, iter;

    Dinic(int n) : g(n), level(n), iter(n) {}

    void addEdge(int from, int to, int cap) {
        Edge f{to, (int)g[to].size(), cap};
        Edge r{from, (int)g[from].size(), 0};
        g[from].push_back(f);
        g[to].push_back(r);
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
        for (int &i = iter[v]; i < (int)g[v].size(); ++i) {
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
        const int INF = 1e9;
        while (bfs(s, t)) {
            fill(iter.begin(), iter.end(), 0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        int N, M;
        cin >> N >> M;
        vector<int> r(M + 1);
        for (int i = 1; i <= M; ++i) cin >> r[i];

        vector<vector<int>> pref(N + 1);
        for (int i = 1; i <= N; ++i) {
            int K;
            cin >> K;
            pref[i].resize(K);
            for (int j = 0; j < K; ++j) cin >> pref[i][j];
        }

        // 节点编号：源点 0，候选人 1..N，项目 N+1..N+M，汇点 N+M+1
        int S = 0, Tnode = N + M + 1;
        Dinic initDinic(Tnode + 1);

        for (int i = 1; i <= N; ++i) initDinic.addEdge(S, i, 1);
        for (int i = 1; i <= N; ++i)
            for (int p : pref[i])
                initDinic.addEdge(i, N + p, 1);
        for (int p = 1; p <= M; ++p)
            if (r[p] > 0) initDinic.addEdge(N + p, Tnode, r[p]);

        int L = initDinic.maxFlow(S, Tnode);

        vector<int> assign(N + 1, 0);
        vector<int> used(M + 1, 0);

        auto checkFeasible = [&]() -> bool {
            int cnt = 0;
            for (int i = 1; i <= N; ++i) if (assign[i] != 0) ++cnt;
            int need = L - cnt;
            if (need < 0) return false;
            if (need == 0) return true;

            Dinic dinic(Tnode + 1);
            for (int i = 1; i <= N; ++i) {
                if (assign[i] == 0) {
                    dinic.addEdge(S, i, 1);
                    for (int p : pref[i])
                        if (used[p] < r[p])
                            dinic.addEdge(i, N + p, 1);
                }
            }
            for (int p = 1; p <= M; ++p) {
                int cap = r[p] - used[p];
                if (cap > 0) dinic.addEdge(N + p, Tnode, cap);
            }
            return dinic.maxFlow(S, Tnode) == need;
        };

        for (int i = 1; i <= N; ++i) {
            bool assigned = false;
            for (int p : pref[i]) {
                if (used[p] < r[p]) {
                    assign[i] = p;
                    used[p]++;

                    if (checkFeasible()) {
                        assigned = true;
                        break;
                    } else {
                        assign[i] = 0;
                        used[p]--;
                    }
                }
            }
        }

        cout << "Case #" << caseNo << ":\n";
        cout << L << " applicant(s) can be hired.\n";
        for (int i = 1; i <= N; ++i)
            if (assign[i] != 0)
                cout << i << " " << assign[i] << "\n";
    }

    return 0;
}
