// Transportation
// UVa ID: 1486
// Verdict: Accepted
// Submission Date: 2026-01-20
// UVa Run Time: 0.320s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXN = 105;
const int MAXM = 50005;

struct Edge {
    int to, next, cap, cost;
} edge[MAXM];
int head[MAXN], tot;
int pre[MAXN], dist[MAXN];
bool vis[MAXN];

// 添加有向边
void addEdge(int u, int v, int cap, int cost) {
    edge[tot].to = v; edge[tot].cap = cap; edge[tot].cost = cost; edge[tot].next = head[u]; head[u] = tot++;
    edge[tot].to = u; edge[tot].cap = 0; edge[tot].cost = -cost; edge[tot].next = head[v]; head[v] = tot++;
}

// SPFA 寻找最短增广路
bool spfa(int s, int t) {
    memset(dist, 0x3f, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    queue<int> q;
    dist[s] = 0; vis[s] = true; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for (int i = head[u]; i != -1; i = edge[i].next) {
            int v = edge[i].to;
            if (edge[i].cap > 0 && dist[v] > dist[u] + edge[i].cost) {
                dist[v] = dist[u] + edge[i].cost;
                pre[v] = i;
                if (!vis[v]) vis[v] = true, q.push(v);
            }
        }
    }
    return pre[t] != -1;
}

// 最小费用流，限制流量为 needFlow
int minCostFlow(int s, int t, int needFlow) {
    int cost = 0, flow = 0;
    while (spfa(s, t) && flow < needFlow) {
        int minFlow = INF;
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) 
            minFlow = min(minFlow, edge[i].cap);
        minFlow = min(minFlow, needFlow - flow);  // 限制不超过需要的流量
        for (int i = pre[t]; i != -1; i = pre[edge[i ^ 1].to]) {
            edge[i].cap -= minFlow;
            edge[i ^ 1].cap += minFlow;
            cost += edge[i].cost * minFlow;
        }
        flow += minFlow;
    }
    if (flow < needFlow) return -1;  // 无法达到需要的流量
    return cost;
}

int main() {
    int n, m, k;
    while (scanf("%d %d %d", &n, &m, &k) == 3) {
        memset(head, -1, sizeof(head));
        tot = 0;
        int src = 1, sink = n;
        
        // 读取当前测试用例的所有道路
        for (int i = 0; i < m; ++i) {
            int u, v, a, c;
            scanf("%d %d %d %d", &u, &v, &a, &c);
            // 将边拆分为 c 条容量为 1，费用为 a*(2*j-1) 的边
            for (int j = 1; j <= c; ++j) 
                addEdge(u, v, 1, a * (2 * j - 1));
        }
        
        int cost = minCostFlow(src, sink, k);
        printf("%d\n", cost);
    }
    return 0;
}
