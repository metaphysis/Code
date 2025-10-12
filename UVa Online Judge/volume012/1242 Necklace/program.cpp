// Necklace
// UVa ID: 1242
// Verdict: Accepted
// Submission Date: 2025-10-12
// UVa Run Time: 0.090s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 10005;    // 最大顶点数
const int MAXM = 200010;   // 最大边数（无向图需要2倍）
const int INF = 0x3f3f3f3f; // 无穷大

// 边结构体：终点、容量、下一条边
struct Edge {
    int to, cap, next;
} edges[MAXM];

int head[MAXN], tot;       // 邻接表头指针，边计数器
int level[MAXN], cur[MAXN]; // BFS层级，当前弧优化

// 初始化图
void init() {
    memset(head, -1, sizeof(head));
    tot = 0;
}

// 添加无向边
void addEdge(int u, int v, int cap) {
    // 正向边
    edges[tot] = {v, cap, head[u]};
    head[u] = tot++;
    // 反向边（无向图，容量相同）
    edges[tot] = {u, cap, head[v]};
    head[v] = tot++;
}

// BFS构建分层图
bool bfs(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s);
    level[s] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // 遍历u的所有出边
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].to;
            // 如果v未访问且还有剩余容量
            if (level[v] == -1 && edges[i].cap > 0) {
                level[v] = level[u] + 1;
                if (v == t) return true; // 到达汇点
                q.push(v);
            }
        }
    }
    return false; // 无法到达汇点
}

// DFS进行多路增广
int dfs(int u, int t, int flow) {
    if (u == t) return flow; // 到达汇点，返回流量
    
    int ret = 0;
    // 当前弧优化：避免重复检查已经处理完的边
    for (int& i = cur[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        // 满足分层图条件且还有剩余容量
        if (level[v] == level[u] + 1 && edges[i].cap > 0) {
            int f = dfs(v, t, min(flow - ret, edges[i].cap));
            if (f > 0) {
                // 更新正向边和反向边容量
                edges[i].cap -= f;
                edges[i ^ 1].cap += f;
                ret += f;
                if (ret == flow) break; // 已达到可增广上限
            }
        }
    }
    // 如果这个点没有增广出任何流量，标记为无效
    if (ret == 0) level[u] = -1;
    return ret;
}

// Dinic主算法：计算最大流
int dinic(int s, int t) {
    int maxFlow = 0;
    // 不断进行BFS构建分层图，直到无法到达汇点
    while (bfs(s, t)) {
        // 当前弧优化初始化
        memcpy(cur, head, sizeof(head));
        // 多路增广
        maxFlow += dfs(s, t, INF);
    }
    return maxFlow;
}

int main() {
    int n, m, case_num = 1;
    
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        
        init(); // 初始化图
        
        // 读入所有边，构建无向图
        for (int i = 0; i < m; i++) {
            int a, b;
            cin >> a >> b;
            addEdge(a, b, 1); // 无向边，容量为1
        }
        
        int S, T;
        cin >> S >> T;
        
        // 计算S到T的最大流
        int maxFlow = dinic(S, T);
        
        cout << "Case " << case_num++ << ": ";
        // 关键判断：如果最大流>=2，说明存在至少两条边不相交路径
        if (maxFlow >= 2) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
}
