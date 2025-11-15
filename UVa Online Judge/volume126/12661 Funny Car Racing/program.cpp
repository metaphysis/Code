// Funny Car Racing
// UVa ID: 12661
// Verdict: Accepted
// Submission Date: 2025-11-05
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// 边的数据结构
struct Edge {
    int v, a, b, t;  // 终点、开放时间、关闭时间、通过时间
};

// 优先队列中的状态
struct State {
    int u, time;     // 当前节点、到达该节点的时间
    bool operator<(const State& other) const {
        return time > other.time; // 最小堆，时间小的优先
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, s, t;
    int caseNum = 1;  // 测试用例编号

    // 处理多组测试数据
    while (cin >> n >> m >> s >> t) {
        // 构建邻接表
        vector<vector<Edge>> graph(n + 1);

        // 读入每条道路信息
        for (int i = 0; i < m; i++) {
            int u, v, a, b, tt;
            cin >> u >> v >> a >> b >> tt;
            // 只有通过时间 <= 开放时间才可能使用这条道路
            if (tt <= a) {
                graph[u].push_back({v, a, b, tt});
            }
        }

        // 初始化距离数组
        vector<int> dist(n + 1, INT_MAX);
        dist[s] = 0;

        // 优先队列（Dijkstra算法）
        priority_queue<State> pq;
        pq.push({s, 0});

        while (!pq.empty()) {
            State cur = pq.top();
            pq.pop();

            int u = cur.u;
            int cur_time = cur.time;

            // 如果当前时间不是最优，跳过
            if (cur_time > dist[u]) continue;

            // 如果到达目标节点，提前结束
            if (u == t) break;

            // 遍历所有出边
            for (const Edge& e : graph[u]) {
                int v = e.v;
                int a = e.a;
                int b = e.b;
                int tt = e.t;
                int T = a + b;  // 周期

                // 计算在当前周期中的位置
                int r = cur_time % T;
                int arrival_time;

                if (r < a) {
                    // 当前道路开放
                    if (tt <= a - r) {
                        // 可以在当前开放时段内通过
                        arrival_time = cur_time + tt;
                    } else {
                        // 需要等待到下一周期
                        arrival_time = cur_time + (T - r) + tt;
                    }
                } else {
                    // 当前道路关闭，需要等待到下一周期开放
                    arrival_time = cur_time + (T - r) + tt;
                }

                // 如果找到更早的到达时间，更新
                if (arrival_time < dist[v]) {
                    dist[v] = arrival_time;
                    pq.push({v, arrival_time});
                }
            }
        }

        // 输出结果
        cout << "Case " << caseNum++ << ": " << dist[t] << "\n";
    }

    return 0;
}
