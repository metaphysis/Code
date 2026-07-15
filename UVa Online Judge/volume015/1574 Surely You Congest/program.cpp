// Surely You Congest
// UVa ID: 1574
// Verdict: Accepted
// Submission Date: 2026-07-13
// UVa Run Time: 0.710s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// Dinic最大流，用于每组距离相同的通勤者
class Dinic {
public:
    struct Edge {
        int to, rev, cap;
    };
    vector<vector<Edge>> g;
    vector<int> level, it;
    Dinic(int n) : g(n), level(n), it(n) {}
    void addEdge(int fr, int to, int cap) {
        Edge f{to, (int)g[to].size(), cap};
        Edge r{fr, (int)g[fr].size(), 0};
        g[fr].push_back(f);
        g[to].push_back(r);
    }
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
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

    int n, m, c;
    while (cin >> n >> m >> c) {
        // 存储无向边
        vector<pair<pair<int,int>, int>> roads; // ((u,v), t)
        vector<vector<pair<int,int>>> adj(n + 1);
        for (int i = 0; i < m; ++i) {
            int x, y, t;
            cin >> x >> y >> t;
            roads.push_back({{x, y}, t});
            adj[x].push_back({y, t});
            adj[y].push_back({x, t});
        }

        // 读取所有通勤者的起点
        vector<int> starts(c);
        for (int i = 0; i < c; ++i) cin >> starts[i];

        // Dijkstra 求所有点到 1 的最短距离（无向图，从1出发）
        const long long INF = 4e18;
        vector<long long> dist(n + 1, INF);
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
        dist[1] = 0;
        pq.push({0, 1});
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d != dist[u]) continue;
            for (auto &[v, t] : adj[u]) {
                if (dist[v] > d + t) {
                    dist[v] = d + t;
                    pq.push({dist[v], v});
                }
            }
        }

        // 构建最短路径 DAG 的有向边（方向从高距离指向低距离）
        vector<pair<int,int>> dagEdges;
        for (auto &road : roads) {
            int u = road.first.first, v = road.first.second, t = road.second;
            if (dist[u] == dist[v] + t) dagEdges.push_back({u, v});
            if (dist[v] == dist[u] + t) dagEdges.push_back({v, u});
        }

        // 统计每个起点出现的次数
        vector<int> startCnt(n + 1, 0);
        for (int s : starts) startCnt[s]++;

        // 按距离分组，每组记录起点及数量
        map<long long, vector<pair<int,int>>> groups;
        for (int i = 1; i <= n; ++i) {
            if (startCnt[i] > 0) {
                groups[dist[i]].push_back({i, startCnt[i]});
            }
        }

        long long answer = 0; // 答案最大不超过 c，int 足够
        for (auto &kv : groups) {
            auto &vec = kv.second;
            // 特判：如果所有起点就在市中心（距离0），直接全部计入
            // 但统一走最大流也可，此处不特判，保持通用
            Dinic din(n + 1); // 节点编号 0..n，0 为超级源，1 为汇
            // 添加所有 DAG 边，容量 1（同距离组内不可共享）
            for (auto &e : dagEdges) {
                din.addEdge(e.first, e.second, 1);
            }
            // 超级源连接到该组每个起点，容量为该起点通勤者数
            for (auto &p : vec) {
                din.addEdge(0, p.first, p.second);
            }
            // 求从超级源到节点 1 的最大流
            answer += din.maxFlow(0, 1);
        }

        cout << answer << '\n';
    }

    return 0;
}
