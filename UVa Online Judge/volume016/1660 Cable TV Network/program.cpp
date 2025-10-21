// Cable TV Network
// UVa ID: 1660
// Verdict: Accepted
// Submission Date: 2025-10-21
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105; // 拆点后最多 2*50=100
const int INF = 1e9;

int n, m;
int capacity[MAXN][MAXN]; // 容量矩阵
vector<int> graph[MAXN];  // 残量图的邻接表
int parent[MAXN];         // BFS 路径记录

// 原图的邻接表
vector<int> origGraph[55];

// 检查原图是否连通
bool isConnected() {
    if (n <= 1) return true;
    bool visited[55] = {false};
    queue<int> q;
    q.push(0);
    visited[0] = true;
    int count = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : origGraph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                count++;
                q.push(v);
            }
        }
    }
    return count == n;
}

// BFS 寻找增广路
bool bfs(int s, int t) {
    memset(parent, -1, sizeof(parent));
    queue<int> q;
    q.push(s);
    parent[s] = -2;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : graph[u]) {
            if (parent[v] == -1 && capacity[u][v] > 0) {
                parent[v] = u;
                if (v == t) return true;
                q.push(v);
            }
        }
    }
    return false;
}

// Edmonds-Karp 最大流算法
int maxFlow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int pathFlow = INF;
        // 计算增广路上的最小容量
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, capacity[u][v]);
        }
        // 更新残量网络
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            capacity[u][v] -= pathFlow;
            capacity[v][u] += pathFlow;
        }
        flow += pathFlow;
    }
    return flow;
}

// 主求解函数
int solve() {
    if (n <= 1) return n; // 特殊情况：空网络或单节点
    if (!isConnected()) return 0; // 原图不连通
    
    int ans = n; // 初始化为最大可能值
    // 枚举所有源汇点对
    for (int s = 0; s < n; s++) {
        for (int t = s + 1; t < n; t++) {
            // 初始化容量和邻接表
            memset(capacity, 0, sizeof(capacity));
            for (int i = 0; i < 2 * n; i++) graph[i].clear();
            
            // 拆点建图
            for (int i = 0; i < n; i++) {
                int in = i, out = i + n;
                if (i == s || i == t) {
                    capacity[in][out] = INF; // 源汇点不可删除
                } else {
                    capacity[in][out] = 1; // 普通节点容量为1
                }
                graph[in].push_back(out);
                graph[out].push_back(in);
            }
            
            // 添加原图的边
            for (int u = 0; u < n; u++) {
                for (int v : origGraph[u]) {
                    capacity[u + n][v] = INF; // u_out -> v_in
                    capacity[v + n][u] = INF; // v_out -> u_in
                    graph[u + n].push_back(v);
                    graph[v].push_back(u + n);
                    graph[v + n].push_back(u);
                    graph[u].push_back(v + n);
                }
            }
            
            // 计算 s 到 t 的最大流
            int flow = maxFlow(s, t + n);
            ans = min(ans, flow);
        }
    }
    return ans;
}

int main() {
    while (cin >> n >> m) {
        // 初始化原图
        for (int i = 0; i < n; i++) origGraph[i].clear();
        // 读入边
        for (int i = 0; i < m; i++) {
            char ch;
            int u, v;
            cin >> ch >> u >> ch >> v >> ch;
            origGraph[u].push_back(v);
            origGraph[v].push_back(u);
        }
        cout << solve() << endl;
    }
    return 0;
}
