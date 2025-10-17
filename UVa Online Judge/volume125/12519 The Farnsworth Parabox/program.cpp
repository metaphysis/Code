// The Farnsworth Parabox
// UVa ID: 12519
// Verdict: Accepted
// Submission Date: 2025-10-17
// UVa Run Time: 0.030s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// 定义边结构体
struct Edge {
    int u, v, w;  // 起点u，终点v，权值w
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, B;
    while (cin >> N >> B && (N != 0 || B != 0)) {
        vector<Edge> edges;
        
        // 读取所有盒子信息，构建有向图
        for (int k = 0; k < B; k++) {
            int i, j, t;
            cin >> i >> j >> t;
            // 每个盒子产生两条有向边：
            // 从i到j，权值为+t（直接使用，时间前进）
            edges.push_back({i, j, t});
            // 从j到i，权值为-t（反向使用，时间倒退）
            edges.push_back({j, i, -t});
        }
        
        // 初始化距离数组，dist[i]表示从节点1到节点i的最短距离
        vector<int> dist(N + 1, INT_MAX);
        dist[1] = 0;  // 源点（原始宇宙）距离为0
        
        // Bellman-Ford算法：进行N-1次松弛操作
        for (int i = 1; i <= N - 1; i++) {
            for (const Edge& e : edges) {
                // 如果从u可达，且通过u到v能获得更短路径，则更新
                if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                    dist[e.v] = dist[e.u] + e.w;
                }
            }
        }
        
        // 检测负环：如果第N次松弛还能更新距离，说明存在负环
        bool hasNegativeCycle = false;
        for (const Edge& e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                hasNegativeCycle = true;
                break;
            }
        }
        
        // 输出结果：存在负环输出'Y'，否则输出'N'
        cout << (hasNegativeCycle ? 'Y' : 'N') << '\n';
    }
    
    return 0;
}
