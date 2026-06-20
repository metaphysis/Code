// Piece it Together
// UVa ID: 1514
// Verdict: Accepted
// Submission Date: 2026-06-20
// UVa Run Time: 0.170s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Dinic {
    struct Edge {
        int to, rev, cap;
    };
    int n;
    vector<vector<Edge>> g;
    vector<int> level, it;

    Dinic(int n) : n(n), g(n), level(n), it(n) {}

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
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
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

    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) cin >> grid[i];

        vector<pair<int,int>> bPos, wPos;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 'B') bPos.push_back({i, j});
                else if (grid[i][j] == 'W') wPos.push_back({i, j});
            }

        int B = (int)bPos.size();
        int W = (int)wPos.size();
        if (W != 2 * B) {
            cout << "NO\n";
            continue;
        }

        // 分配节点编号
        int s = 0, t = 1, idx = 2;
        vector<int> bH(B), bV(B);
        for (int i = 0; i < B; ++i) {
            bH[i] = idx++;
            bV[i] = idx++;
        }
        vector<vector<int>> wId(n, vector<int>(m, -1));
        for (int i = 0; i < W; ++i) {
            int r = wPos[i].first, c = wPos[i].second;
            wId[r][c] = idx++;
        }
        int totalNodes = idx;

        Dinic dinic(totalNodes);
        // 源点到每个黑色格子的两个需求
        for (int i = 0; i < B; ++i) {
            dinic.addEdge(s, bH[i], 1);
            dinic.addEdge(s, bV[i], 1);
        }

        // 黑色格子到白色格子的边
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};
        for (int i = 0; i < B; ++i) {
            int r = bPos[i].first, c = bPos[i].second;
            for (int d = 0; d < 4; ++d) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                if (grid[nr][nc] != 'W') continue;
                int wid = wId[nr][nc];
                // 水平方向：左右（d=2,3）对应水平需求；垂直方向：上下（d=0,1）对应垂直需求
                if (d < 2) // 上下为垂直
                    dinic.addEdge(bV[i], wid, 1);
                else       // 左右为水平
                    dinic.addEdge(bH[i], wid, 1);
            }
        }

        // 白色格子到汇点
        for (int i = 0; i < W; ++i) {
            int r = wPos[i].first, c = wPos[i].second;
            dinic.addEdge(wId[r][c], t, 1);
        }

        int flow = dinic.maxFlow(s, t);
        cout << (flow == 2 * B ? "YES" : "NO") << '\n';
    }

    return 0;
}
