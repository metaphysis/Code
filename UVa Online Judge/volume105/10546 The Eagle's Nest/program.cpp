// The Eagle's Nest
// UVa ID: 10546
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int caseNumber = 1;  // 测试用例编号
    int N;  // 任务数量
    while (cin >> N && N != 0) {
        // 读取任务，名称和难度
        vector<pair<string, int>> missions(N);
        for (int i = 0; i < N; i++) cin >> missions[i].first >> missions[i].second;
        
        // 提取难度值
        vector<int> v(N);
        for (int i = 0; i < N; i++) v[i] = missions[i].second;
        
        // 第一步：计算最长严格递增子序列(LIS)的长度K，并记录每个任务的层级d[i]
        vector<int> d(N, 1);  // d[i]表示以任务i结尾的LIS长度
        int maxLen = 1;       // 即K值
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (v[j] < v[i] && d[j] + 1 > d[i]) {
                    d[i] = d[j] + 1;
                }
            }
            maxLen = max(maxLen, d[i]);
        }
        
        // 第二步：构建网络流图求解最大不相交路径数
        // 节点编号：0-源点，1~N为任务入点，N+1~2N为任务出点，2N+1为汇点
        int source = 0, sink = 2 * N + 1;
        vector<vector<int>> cap(2 * N + 2, vector<int>(2 * N + 2, 0));
        
        // 任务拆点：每个任务入点到出点容量为1，保证每个任务只被用一次
        for (int i = 0; i < N; i++) {
            cap[i + 1][i + 1 + N] = 1;
        }
        
        // 源点连接所有第一层任务（d[i]==1）
        for (int i = 0; i < N; i++) {
            if (d[i] == 1) {
                cap[source][i + 1] = 1;
            }
        }
        
        // 所有最后一层任务（d[i]==K）连接汇点
        for (int i = 0; i < N; i++) {
            if (d[i] == maxLen) {
                cap[i + 1 + N][sink] = 1;
            }
        }
        
        // 根据层级关系连接任务：如果v[i] < v[j] 且 d[j] == d[i] + 1，则连边
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if (v[i] < v[j] && d[j] == d[i] + 1) {
                    // 从i的出点连接到j的入点
                    cap[i + 1 + N][j + 1] = 1;
                }
            }
        }
        
        // Dinic 最大流算法
        auto bfs = [&](vector<int>& level) -> bool {
            fill(level.begin(), level.end(), -1);
            queue<int> q;
            q.push(source);
            level[source] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v = 0; v <= sink; v++) {
                    if (level[v] == -1 && cap[u][v] > 0) {
                        level[v] = level[u] + 1;
                        q.push(v);
                    }
                }
            }
            return level[sink] != -1;
        };
        
        function<int(int, int, vector<int>&)> dfs = [&](int u, int flow, vector<int>& level) -> int {
            if (u == sink) return flow;
            for (int v = 0; v <= sink; v++) {
                if (level[v] == level[u] + 1 && cap[u][v] > 0) {
                    int pushed = dfs(v, min(flow, cap[u][v]), level);
                    if (pushed > 0) {
                        cap[u][v] -= pushed;
                        cap[v][u] += pushed;
                        return pushed;
                    }
                }
            }
            return 0;
        };
        
        int maxFlow = 0;
        vector<int> level(sink + 1);
        while (bfs(level)) {
            while (int pushed = dfs(source, INT_MAX, level)) {
                maxFlow += pushed;
            }
        }
        
        // 第三步：计算最终答案 = K * 最大不相交路径数
        int result = maxLen * maxFlow;
        cout << "Case #" << caseNumber++ << ": " << result << endl;
    }
    return 0;
}
