// Hooligan
// UVa ID: 12193
// Verdict: Accepted
// Submission Date: 2026-07-30
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

class Dinic {
public:
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : g(n), level(n), it(n) {}

    void addEdge(int fr, int to, int cap) {
        Edge a{to, (int)g[to].size(), cap};
        Edge b{fr, (int)g[fr].size(), 0};
        g[fr].push_back(a);
        g[to].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto &e : g[v]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] >= 0;
    }

    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)g[v].size(); ++i) {
            Edge &e = g[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                int ret = dfs(e.to, t, min(f, e.cap));
                if (ret > 0) {
                    e.cap -= ret;
                    g[e.to][e.rev].cap += ret;
                    return ret;
                }
            }
        }
        return 0;
    }

    int maxFlow(int s, int t) {
        int flow = 0;
        const int INF = 1e9;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, G;
    while (cin >> N >> M >> G && (N || M || G)) {
        vector<int> cur(N, 0);
        int played[45][45] = {};

        for (int k = 0; k < G; ++k) {
            int I, J;
            char C;
            cin >> I >> C >> J;
            if (C == '=') {
                cur[I] += 1;
                cur[J] += 1;
            } else { // 'c' 或 '<' 均表示 I 输给 J
                cur[J] += 2;
            }
            played[I][J]++;
            played[J][I]++;
        }

        // 0号剩余比赛场数
        int k0 = 0;
        for (int j = 1; j < N; ++j)
            k0 += M - played[0][j];

        int S0 = cur[0] + 2 * k0;
        bool possible = true;
        vector<int> limit(N, 0);

        for (int i = 1; i < N; ++i) {
            limit[i] = S0 - 1 - cur[i];
            if (limit[i] < 0) possible = false;
        }

        if (!possible) {
            cout << "N\n";
            continue;
        }

        // 收集非0球队之间的未赛比赛
        struct Match { int a, b; };
        vector<Match> matches;
        for (int i = 1; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                int rem = M - played[i][j];
                for (int t = 0; t < rem; ++t)
                    matches.push_back({i, j});
            }
        }

        int R = (int)matches.size();
        if (R == 0) {
            cout << "Y\n";
            continue;
        }

        int source = 0;
        int matchStart = 1;
        int teamStart = matchStart + R;
        int totalNodes = teamStart + (N - 1) + 1;
        int sink = totalNodes - 1;
        Dinic dinic(totalNodes);

        auto teamNode = [&](int i) -> int {
            return teamStart + (i - 1);
        };

        for (int idx = 0; idx < R; ++idx) {
            int matchNode = matchStart + idx;
            dinic.addEdge(source, matchNode, 2);
            int a = matches[idx].a, b = matches[idx].b;
            dinic.addEdge(matchNode, teamNode(a), 2);
            dinic.addEdge(matchNode, teamNode(b), 2);
        }

        for (int i = 1; i < N; ++i)
            dinic.addEdge(teamNode(i), sink, limit[i]);

        int flow = dinic.maxFlow(source, sink);
        cout << (flow == 2 * R ? "Y\n" : "N\n");
    }

    return 0;
}
