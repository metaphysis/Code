// Admiral
// UVa ID: 1658
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

// 流边结构体
struct Edge {
    int to;        // 目标顶点
    int capacity;  // 容量
    int cost;      // 费用
    int rev;       // 反向边索引
};

class MinCostMaxFlow {
private:
    int n;  // 顶点数量
    vector<vector<Edge>> graph;  // 邻接表表示的流网络
    vector<int> dist;    // 最短距离数组
    vector<int> prevv;   // 前驱顶点
    vector<int> preve;   // 前驱边索引
    const int INF = INT_MAX / 2;  // 无穷大值

public:
    // 构造函数，初始化流网络
    MinCostMaxFlow(int n) : n(n), graph(n), dist(n), prevv(n), preve(n) {}

    // 添加边：从from到to，容量为capacity，费用为cost
    void add_edge(int from, int to, int capacity, int cost) {
        graph[from].push_back({to, capacity, cost, (int)graph[to].size()});
        // 添加反向边，初始容量为0，费用为-cost
        graph[to].push_back({from, 0, -cost, (int)graph[from].size() - 1});
    }

    // 最小费用流算法：从s到t，需要required_flow的流量
    int min_cost_flow(int s, int t, int required_flow) {
        int total_flow = 0;   // 总流量
        int total_cost = 0;   // 总费用
        
        while (required_flow > 0) {
            // 初始化距离数组
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            bool updated = true;
            
            // SPFA算法寻找最短路
            while (updated) {
                updated = false;
                for (int v = 0; v < n; ++v) {
                    if (dist[v] == INF) continue;
                    for (int i = 0; i < graph[v].size(); ++i) {
                        Edge& e = graph[v][i];
                        // 如果边有剩余容量且可以松弛
                        if (e.capacity > 0 && dist[e.to] > dist[v] + e.cost) {
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;    // 记录前驱顶点
                            preve[e.to] = i;    // 记录前驱边索引
                            updated = true;
                        }
                    }
                }
            }
            
            // 如果无法到达汇点，返回-1
            if (dist[t] == INF) {
                return -1;
            }
            
            // 计算增广路径上的最小容量
            int flow = required_flow;
            for (int v = t; v != s; v = prevv[v]) {
                flow = min(flow, graph[prevv[v]][preve[v]].capacity);
            }
            
            // 更新流量需求
            required_flow -= flow;
            total_flow += flow;
            
            // 更新残余网络
            for (int v = t; v != s; v = prevv[v]) {
                Edge& e = graph[prevv[v]][preve[v]];
                total_cost += e.cost * flow;  // 累加费用
                e.capacity -= flow;           // 减少正向边容量
                graph[e.to][e.rev].capacity += flow;  // 增加反向边容量
            }
        }
        
        return total_cost;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, e;
    while (cin >> v >> e) {
        // 设置超级源点和超级汇点
        // 顶点编号方案：
        // - 原顶点i的入点编号为i，出点编号为i+v
        // - 超级源点S=0，超级汇点T=2*v+1
        int S = 0, T = 2 * v + 1;
        MinCostMaxFlow mcmf(2 * v + 2);

        // 添加内部拆点边：i->i+v
        // 对于起点和终点，容量为2（允许两艘船经过）
        // 对于其他顶点，容量为1（确保点不交）
        for (int i = 1; i <= v; i++) {
            int cap = (i == 1 || i == v) ? 2 : 1;
            mcmf.add_edge(i, i + v, cap, 0);
        }

        // 添加原图的边：a->b 转化为 a_out->b_in
        // 容量为1确保边不交，费用为炮弹数量
        for (int i = 0; i < e; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            mcmf.add_edge(a + v, b, 1, c);
        }

        // 连接超级源点到起点入点
        mcmf.add_edge(S, 1, 2, 0);
        // 连接终点出点到超级汇点
        mcmf.add_edge(v + v, T, 2, 0);

        // 计算最小费用流，需要2的流量
        int ans = mcmf.min_cost_flow(S, T, 2);
        cout << ans << "\n";
    }

    return 0;
}
