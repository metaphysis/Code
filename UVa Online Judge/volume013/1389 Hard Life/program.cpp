// Hard Life
// UVa ID: 1389
// Verdict: Accepted
// Submission Date: 2025-10-16
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

const int MAXN = 105;
const int MAXM = 1005;
const int MAXV = MAXN + 2;
const double INF = 1e9;
const double EPS = 1e-7;

// 网络流边结构
struct Edge {
    int to, rev;      // 目标顶点，反向边索引
    double cap;       // 容量
};

vector<Edge> g[MAXV]; // 流网络邻接表
int level[MAXV], iter[MAXV]; // Dinic算法层级图和当前弧
int n, m;             // 顶点数，边数
int edges[MAXM][2];   // 存储输入的边
int degree[MAXN];     // 每个顶点的度数

// 添加流网络边
void add_edge(int from, int to, double cap) {
    g[from].push_back({to, (int)g[to].size(), cap});
    g[to].push_back({from, (int)g[from].size() - 1, 0.0});
}

// BFS构建层级图
void bfs(int s) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (auto &e : g[v]) {
            if (e.cap > EPS && level[e.to] < 0) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
    }
}

// DFS寻找增广路
double dfs(int v, int t, double f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < (int)g[v].size(); i++) {
        Edge &e = g[v][i];
        if (e.cap > EPS && level[v] < level[e.to]) {
            double d = dfs(e.to, t, min(f, e.cap));
            if (d > EPS) {
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

// Dinic算法计算最大流
double max_flow(int s, int t) {
    double flow = 0;
    while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        memset(iter, 0, sizeof(iter));
        double f;
        while ((f = dfs(s, t, INF)) > EPS) {
            flow += f;
        }
    }
}

bool vis[MAXV];
// 从源点DFS寻找最小割S集合（最大密度子图）
void find_vertices(int v, vector<int> &res) {
    if (v < n) res.push_back(v + 1); // 转换回1-based编号
    vis[v] = true;
    for (auto &e : g[v]) {
        if (e.cap > EPS && !vis[e.to]) {
            find_vertices(e.to, res);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    bool first_case = true;
    while (cin >> n >> m) {
        if (!first_case) cout << "\n";
        first_case = false;

        // 处理无边特殊情况
        if (m == 0) {
            cout << "1\n1\n";
            continue;
        }

        memset(degree, 0, sizeof(degree));
        // 读入边并计算度数
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            edges[i][0] = a;
            edges[i][1] = b;
            degree[a]++;
            degree[b]++;
        }

        double low = 0.0, high = m;
        vector<int> best_team;
        
        // 二分查找最优密度g
        while (high - low > 1e-7) {
            double mid = (low + high) / 2;
            // 构建流网络
            int s = n, t = n + 1;
            for (int i = 0; i < n + 2; i++) g[i].clear();
            // s到每个顶点容量m
            for (int i = 0; i < n; i++) {
                add_edge(s, i, m);
                add_edge(i, t, m + 2 * mid - degree[i]);
            }
            // 顶点间双向边容量1
            for (int i = 0; i < m; i++) {
                int a = edges[i][0], b = edges[i][1];
                add_edge(a, b, 1.0);
                add_edge(b, a, 1.0);
            }
            double mincut = max_flow(s, t);
            double value = (m * n - mincut) / 2.0;
            
            if (value > EPS) {
                low = mid;
                // 记录当前最优团队
                memset(vis, 0, sizeof(vis));
                vector<int> team;
                find_vertices(s, team);
                if (!team.empty()) best_team = team;
            } else {
                high = mid;
            }
        }

        // 确保至少有一个顶点
        if (best_team.empty()) best_team.push_back(1);
        sort(best_team.begin(), best_team.end());
        cout << best_team.size() << "\n";
        for (int v : best_team) {
            cout << v << "\n";
        }
    }

    return 0;
}
