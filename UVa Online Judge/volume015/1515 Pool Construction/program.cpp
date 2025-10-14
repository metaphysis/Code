// Pool Construction
// UVa ID: 1515
// Verdict: Accepted
// Submission Date: 2025-10-13
// UVa Run Time: 0.020s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// Dinic最大流算法实现
// 用于求解最小割问题
struct Dinic {
    struct Edge {
        int to;          // 边的终点
        int rev;         // 反向边在邻接表中的索引
        long long cap;   // 边的容量
    };
    vector<vector<Edge>> graph;      // 图的邻接表表示
    vector<int> level;               // BFS层次图
    vector<int> iter;                // DFS当前弧优化
    Dinic(int nodeCount) : graph(nodeCount), level(nodeCount), iter(nodeCount) {}
    // 添加有向边
    void addEdge(int from, int to, long long cap) {
        graph[from].push_back({to, (int)graph[to].size(), cap});
        graph[to].push_back({from, (int)graph[from].size() - 1, 0});
    }
    // BFS构建层次图
    void buildLevelGraph(int source) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int currentNode = q.front(); 
            q.pop();
            for (auto &edge : graph[currentNode]) {
                if (edge.cap > 0 && level[edge.to] < 0) {
                    level[edge.to] = level[currentNode] + 1;
                    q.push(edge.to);
                }
            }
        }
    }
    // DFS寻找增广路
    long long findAugmentingPath(int currentNode, int sink, long long currentFlow) {
        if (currentNode == sink) return currentFlow;
        for (int &i = iter[currentNode]; i < (int)graph[currentNode].size(); i++) {
            Edge &edge = graph[currentNode][i];
            if (edge.cap > 0 && level[currentNode] < level[edge.to]) {
                long long flow = findAugmentingPath(edge.to, sink, min(currentFlow, edge.cap));
                if (flow > 0) {
                    edge.cap -= flow;
                    graph[edge.to][edge.rev].cap += flow;
                    return flow;
                }
            }
        }
        return 0;
    }
    // 计算从源点到汇点的最大流
    long long computeMaxFlow(int source, int sink) {
        long long totalFlow = 0;
        while (true) {
            buildLevelGraph(source);
            if (level[sink] < 0) return totalFlow;
            fill(iter.begin(), iter.end(), 0);
            long long flow;
            while ((flow = findAugmentingPath(source, sink, LLONG_MAX)) > 0) {
                totalFlow += flow;
            }
        }
    }
};

// 四个方向的偏移量：上、下、左、右
int directionX[4] = {-1, 1, 0, 0};
int directionY[4] = {0, 0, -1, 1};

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int testCaseCount;
    cin >> testCaseCount;

    while (testCaseCount--) {
        int width, height, digCost, fillCost, boundaryCost;
        cin >> width >> height >> digCost >> fillCost >> boundaryCost;
        // 读取初始网格
        vector<string> grid(height);
        for (int row = 0; row < height; row++) {
            cin >> grid[row];
        }
        long long totalCost = 0;
        int totalNodes = width * height;
        int sourceNode = totalNodes;      // 源点编号
        int sinkNode = totalNodes + 1;    // 汇点编号
        Dinic flowNetwork(totalNodes + 2);
        // 辅助函数：将二维坐标转换为一维节点编号
        auto getNodeId = [&](int x, int y) { return y * width + x; };
        // 第一步：处理最外圈边界
        // 根据题目要求，最外圈必须是草地
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                // 检查是否在最外圈（第一行、最后一行、第一列、最后一列）
                bool isBorderCell = (row == 0 || row == height - 1 || col == 0 || col == width - 1);
                if (isBorderCell) {
                    // 如果最外圈当前是坑，必须填平，计入填坑费用
                    if (grid[row][col] == '.') {
                        totalCost += fillCost;
                    }
                    // 强制最外圈为草地：从源点连接到该节点，容量为无穷大
                    // 确保该节点始终在源点集合（草地集合）
                    flowNetwork.addEdge(sourceNode, getNodeId(col, row), LLONG_MAX);
                }
            }
        }
        // 第二步：处理内部格子的挖填费用
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                // 跳过最外圈（已在第一步处理）
                bool isBorderCell = (row == 0 || row == height - 1 || col == 0 || col == width - 1);
                if (!isBorderCell) {
                    if (grid[row][col] == '#') {
                        // 当前是草地：从源点连接到该节点，容量为挖坑费用
                        // 如果最终该节点变成坑（在汇点集合），需要割断这条边，产生挖坑费用
                        flowNetwork.addEdge(sourceNode, getNodeId(col, row), digCost);
                    } else {
                        // 当前是坑：从该节点连接到汇点，容量为填坑费用
                        // 如果最终该节点变成草地（在源点集合），需要割断这条边，产生填坑费用
                        flowNetwork.addEdge(getNodeId(col, row), sinkNode, fillCost);
                    }
                }
            }
        }
        // 第三步：处理相邻格子间的边界费用
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                // 遍历四个方向
                for (int direction = 0; direction < 4; direction++) {
                    int neighborX = col + directionX[direction];
                    int neighborY = row + directionY[direction];
                    // 检查邻居是否在网格范围内
                    if (neighborX >= 0 && neighborX < width && neighborY >= 0 && neighborY < height) {
                        // 添加双向边，容量为边界费用
                        // 如果两个相邻格子最终状态不同（一个草地一个坑），需要割断这条边，产生边界费用
                        flowNetwork.addEdge(getNodeId(col, row), getNodeId(neighborX, neighborY), boundaryCost);
                    }
                }
            }
        }
        // 第四步：计算最小割
        // 最小割的值等于所有挖填费用和边界费用的总和
        long long minCutValue = flowNetwork.computeMaxFlow(sourceNode, sinkNode);
        totalCost += minCutValue;

        cout << totalCost << "\n";
    }

    return 0;
}
