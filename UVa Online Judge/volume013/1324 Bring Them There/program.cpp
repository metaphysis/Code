// Bring Them There
// UVa ID: 1324
// Verdict: Accepted
// Submission Date: 2026-06-24
// UVa Run Time: 0.050s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, rev, cap;
};

class Dinic {
public:
    int n;
    vector<vector<Edge>> graph;
    vector<int> level, it;

    Dinic(int n = 0) : n(n), graph(n), level(n), it(n) {}

    void addEdge(int from, int to, int cap) {
        Edge f{to, (int)graph[to].size(), cap};
        Edge r{from, (int)graph[from].size(), 0};
        graph[from].push_back(f);
        graph[to].push_back(r);
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (const Edge &e : graph[v])
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
        }
        return level[t] >= 0;
    }

    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = it[v]; i < (int)graph[v].size(); ++i) {
            Edge &e = graph[v][i];
            if (e.cap > 0 && level[e.to] == level[v] + 1) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
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
            int f;
            while ((f = dfs(s, t, INF)) > 0) flow += f;
        }
        return flow;
    }
};

// 构建第 L 天的时间扩展图，返回 Dinic 对象
Dinic buildGraph(int N, int M, int K, int S, int T, const vector<pair<int,int>> &edges, int L) {
    int nodeCnt = (L + 1) * N;          // 0 ~ nodeCnt-1
    int source = nodeCnt;               // 超级源点
    int sink = L * N + T;               // 第 L 层的 T 作为汇点
    Dinic din(nodeCnt + 1);
    const int INF = K;

    // 超级源点连接第 0 层的 S，容量 K
    din.addEdge(source, 0 * N + S, K);

    for (int day = 0; day < L; ++day) {
        // 停留边：同星系相邻层，容量 INF
        for (int i = 0; i < N; ++i)
            din.addEdge(day * N + i, (day + 1) * N + i, INF);
        // 隧道边：双向，每条容量 1
        for (auto &pr : edges) {
            int u = pr.first, v = pr.second;
            din.addEdge(day * N + u, (day + 1) * N + v, 1);
            din.addEdge(day * N + v, (day + 1) * N + u, 1);
        }
    }
    return din;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K, S, T;
    while (cin >> N >> M >> K >> S >> T) {
        --S; --T;
        vector<pair<int,int>> edges;
        for (int i = 0; i < M; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            edges.push_back({u, v});
        }

        int L = 0;
        Dinic dinic;
        while (true) {
            ++L;
            dinic = buildGraph(N, M, K, S, T, edges, L);
            int nodeCnt = (L + 1) * N;
            int source = nodeCnt;
            int sink = L * N + T;
            int flow = dinic.maxFlow(source, sink);
            if (flow >= K) break;
        }

        cout << L << '\n';

        // 每艘飞船当前所在星系（0-based）
        vector<int> shipPos(K, S);
        vector<int> vis(K, 0);           // 当天是否已分配移动

        for (int day = 1; day <= L; ++day) {
            vector<pair<int,int>> moves; // (起点星系, 终点星系)

            // 扫描第 day-1 层所有节点的出边，检测流量为 1 的隧道边
            for (int i = 0; i < N; ++i) {
                int node = (day - 1) * N + i;
                for (const Edge &e : dinic.graph[node]) {
                    int nxt = e.to;
                    int nxtDay = nxt / N;
                    int nxtNode = nxt % N;
                    // 只指向下一层、星系不同、且剩余容量为0（即流量为1）的边
                    if (nxtDay == day && nxtNode != i && e.cap == 0) {
                        moves.push_back({i, nxtNode});
                    }
                }
            }

            // 分配飞船：每个移动对应一艘当前在起点且未分配的飞船
            fill(vis.begin(), vis.end(), 0);
            cout << moves.size();
            for (auto &mv : moves) {
                int from = mv.first, to = mv.second;
                for (int ship = 0; ship < K; ++ship) {
                    if (shipPos[ship] == from && !vis[ship]) {
                        cout << ' ' << ship + 1 << ' ' << to + 1;
                        shipPos[ship] = to;
                        vis[ship] = 1;
                        break;
                    }
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
