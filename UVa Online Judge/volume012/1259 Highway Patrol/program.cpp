// Highway Patrol
// UVa ID: 1259
// Verdict: Accepted
// Submission Date: 2025-10-09
// UVa Run Time: 0.090s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000000;
const int MAXN = 500;
const int MAXM = 5000;

// 边结构体：用于表示网络流中的边
struct Edge {
    int v, f, w, nxt;  // v: 终点, f: 剩余流量, w: 单位费用, nxt: 下一条边索引
    Edge() {}
    Edge(int v, int f, int w, int nxt) : v(v), f(f), w(w), nxt(nxt) {}
};

Edge edges[MAXM];        // 边数组
int head[MAXN], edgeCount; // 邻接表头指针，边计数器
int dist[MAXN], pre[MAXN], preEdge[MAXN]; // SPFA相关数组
bool inQueue[MAXN];      // SPFA队列标记
int src, sink;           // 源点和汇点
int maxflow;             // 最大流量

// 初始化网络流
void initialize() {
    edgeCount = 1;        // 从1开始，方便异或操作获取反向边
    memset(head, 0, sizeof(head));
    maxflow = 0;
}

// 添加边：u->v，容量f，费用w
void addEdge(int u, int v, int f, int w) {
    edges[++edgeCount] = Edge(v, f, w, head[u]);
    head[u] = edgeCount;
    // 添加反向边，容量0，费用-w，用于回流
    edges[++edgeCount] = Edge(u, 0, -w, head[v]);
    head[v] = edgeCount;
}

// SPFA算法寻找增广路
bool spfa() {
    queue<int> q;
    for (int i = 0; i <= sink; i++) {
        dist[i] = INF;      // 初始距离为无穷大
        inQueue[i] = false;
    }
    dist[src] = 0;          // 源点距离为0
    inQueue[src] = true;
    q.push(src);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        
        // 遍历u的所有出边
        for (int i = head[u]; i; i = edges[i].nxt) {
            int v = edges[i].v;
            // 如果边有剩余容量且可以松弛
            if (edges[i].f > 0 && dist[u] + edges[i].w < dist[v]) {
                dist[v] = dist[u] + edges[i].w;
                pre[v] = u;             // 记录前驱节点
                preEdge[v] = i;         // 记录前驱边
                
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return dist[sink] < INF;  // 判断是否找到增广路
}

// 沿增广路增流
int augment() {
    int u = sink, delta = INF;
    
    // 寻找增广路上的最小剩余容量
    while (u != src) {
        if (edges[preEdge[u]].f < delta) 
            delta = edges[preEdge[u]].f;
        u = pre[u];
    }
    
    // 沿增广路更新流量
    u = sink;
    while (u != src) {
        edges[preEdge[u]].f -= delta;      // 正向边减流
        edges[preEdge[u] ^ 1].f += delta;  // 反向边加流
        u = pre[u];
    }
    
    maxflow += delta;  // 更新总流量
    return dist[sink] * delta;  // 返回本次增流的费用
}

// 最小费用最大流主函数
int minCostFlow() {
    int totalCost = 0;
    while (spfa()) totalCost += augment();  // 不断寻找增广路直到找不到为止
    return totalCost;
}

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    int T; cin >> T;
    for (int caseNum = 1; caseNum <= T; caseNum++) {
        int n, m; cin >> n >> m;
        
        // 网络流建模：源点为n+1，汇点为n+2
        src = n + 1, sink = n + 2;
        initialize();
        
        int videoCost = 0;      // 所有边都使用视频监控的总成本
        int baseCost = 0;       // 基础成本（根据选择策略）
        int requiredFlow = 0;   // 需要满足的流量（必须巡逻的边数）
        
        // cycle数组用于存储最小环信息：cycle[u][v] = 巡逻成本 - 视频监控成本
        vector<vector<int>> cycle(n + 1, vector<int>(n + 1, INF));
        
        // 处理每条道路
        for (int i = 0; i < m; i++) {
            int u, v, p, s, x; 
            cin >> u >> v >> p >> s >> x;
            
            // 记录巡逻相对于视频监控的成本差异
            cycle[u][v] = p - s;
            // 累加视频监控总成本（假设所有边都用视频监控）
            videoCost += s;
            
            if (x == 1) {
                // 情况1：必须巡逻的道路
                baseCost += p;           // 直接计入巡逻成本
                requiredFlow++;          // 增加所需流量
                // 流量平衡约束：v节点需要流入，u节点需要流出
                addEdge(src, v, 1, 0);   // 源点向v提供1单位流入
                addEdge(u, sink, 1, 0);  // u向汇点提供1单位流出
            } else {
                if (p >= s) {
                    // 情况2：巡逻成本更高，优先视频监控，但可选择巡逻
                    baseCost += s;       // 基础成本为视频监控成本
                    // 添加可选边：选择巡逻的额外成本为(p-s)
                    addEdge(u, v, 1, p - s);
                } else {
                    // 情况3：巡逻成本更低，强制巡逻
                    baseCost += p;       // 基础成本为巡逻成本
                    requiredFlow++;      // 增加所需流量
                    // 反向边：表示如果选择视频监控可以节省(s-p)
                    addEdge(v, u, 1, s - p);
                    // 流量平衡约束
                    addEdge(src, v, 1, 0);
                    addEdge(u, sink, 1, 0);
                }
            }
        }
        
        // 计算最小费用流
        int flowCost = minCostFlow();
        
        printf("Case %d: ", caseNum);
        
        // 检查流量约束是否满足
        if (maxflow != requiredFlow) {
            printf("impossible\n");
            continue;
        }
        
        int totalCost = baseCost + flowCost;
        
        // 关键优化：如果总成本等于全视频监控成本，说明没有边被巡逻
        // 但题目要求至少有一条边被巡逻，需要找最小巡逻环
        if (totalCost == videoCost) {
            // 使用Floyd算法找最小环
            for (int k = 1; k <= n; k++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        // 松弛操作，注意防止整数溢出
                        if (cycle[i][k] < INF && cycle[k][j] < INF && 
                            cycle[i][j] > cycle[i][k] + cycle[k][j]) {
                            cycle[i][j] = cycle[i][k] + cycle[k][j];
                        }
                    }
                }
            }
            
            // 在所有自环中找最小值（自环表示巡逻环）
            baseCost = INF;
            for (int i = 1; i <= n; i++) 
                baseCost = min(baseCost, cycle[i][i]);
            
            if (baseCost == INF) 
                printf("impossible\n");  // 找不到巡逻环
            else 
                // 最小环成本 + 视频监控基础成本
                printf("%d\n", baseCost + videoCost);
        } else {
            // 正常情况：直接输出计算得到的最小成本
            printf("%d\n", totalCost);
        }
    }
    return 0;
}
