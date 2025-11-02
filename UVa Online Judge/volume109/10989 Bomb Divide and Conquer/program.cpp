// Bomb Divide and Conquer
// UVa ID: 10989
// Verdict: Accepted
// Submission Date: 2025-11-02
// UVa Run Time: 0.160s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

/**
 * Dinic 最大流算法类
 * 用于计算无向图的最小割
 */
struct DinicMaxFlow {
    // 边结构体
    struct FlowEdge {
        int targetNode;          // 目标节点
        int reverseEdgeIndex;    // 反向边在邻接表中的索引
        int capacity;            // 边容量
        int currentFlow;         // 当前流量
    };

    int totalNodes;                      // 总节点数
    vector<vector<FlowEdge>> graph;      // 图的邻接表表示
    vector<int> nodeLevel;               // 节点的层级（用于分层图）
    vector<int> currentEdgePointer;      // 当前弧指针（用于优化）

    // 构造函数
    DinicMaxFlow(int nodeCount) : totalNodes(nodeCount), 
                                 graph(nodeCount), 
                                 nodeLevel(nodeCount), 
                                 currentEdgePointer(nodeCount) {}

    /**
     * 添加无向边
     * @param from 起始节点
     * @param to 目标节点  
     * @param cap 边的容量
     */
    void addUndirectedEdge(int from, int to, int cap) {
        // 添加正向边
        graph[from].push_back({to, (int)graph[to].size(), cap, 0});
        // 添加反向边（无向图，容量相同）
        graph[to].push_back({from, (int)graph[from].size() - 1, cap, 0});
    }

    /**
     * 使用 BFS 构建分层图
     * @param source 源点
     * @param sink 汇点
     * @return 如果汇点可达返回 true，否则 false
     */
    bool buildLevelGraph(int source, int sink) {
        fill(nodeLevel.begin(), nodeLevel.end(), -1);
        nodeLevel[source] = 0;
        queue<int> bfsQueue;
        bfsQueue.push(source);
        
        while (!bfsQueue.empty()) {
            int currentNode = bfsQueue.front();
            bfsQueue.pop();
            
            for (const FlowEdge& edge : graph[currentNode]) {
                if (nodeLevel[edge.targetNode] == -1 && edge.currentFlow < edge.capacity) {
                    nodeLevel[edge.targetNode] = nodeLevel[currentNode] + 1;
                    bfsQueue.push(edge.targetNode);
                }
            }
        }
        return nodeLevel[sink] != -1;
    }

    /**
     * 使用 DFS 在分层图中寻找阻塞流
     * @param currentNode 当前节点
     * @param sink 汇点
     * @param minCapacity 路径上的最小容量
     * @return 实际推送的流量
     */
    int findBlockingFlow(int currentNode, int sink, int minCapacity) {
        if (currentNode == sink) return minCapacity;
        
        for (int& edgeIndex = currentEdgePointer[currentNode]; 
             edgeIndex < (int)graph[currentNode].size(); 
             edgeIndex++) {
            
            FlowEdge& edge = graph[currentNode][edgeIndex];
            
            if (nodeLevel[edge.targetNode] == nodeLevel[currentNode] + 1 && 
                edge.currentFlow < edge.capacity) {
                
                int pushedFlow = findBlockingFlow(edge.targetNode, sink, 
                                                 min(minCapacity, edge.capacity - edge.currentFlow));
                
                if (pushedFlow > 0) {
                    edge.currentFlow += pushedFlow;
                    graph[edge.targetNode][edge.reverseEdgeIndex].currentFlow -= pushedFlow;
                    return pushedFlow;
                }
            }
        }
        return 0;
    }

    /**
     * 计算从 source 到 sink 的最大流
     * @param source 源点
     * @param sink 汇点
     * @return 最大流值（即最小割值）
     */
    int computeMaxFlow(int source, int sink) {
        int totalFlow = 0;
        
        // 反复构建分层图并寻找阻塞流
        while (buildLevelGraph(source, sink)) {
            fill(currentEdgePointer.begin(), currentEdgePointer.end(), 0);
            
            while (int pushedFlow = findBlockingFlow(source, sink, INT_MAX)) {
                totalFlow += pushedFlow;
            }
        }
        
        // 重置所有边的流量，为下一次计算做准备
        resetFlow();
        return totalFlow;
    }

private:
    /**
     * 重置图中所有边的流量为 0
     */
    void resetFlow() {
        for (int i = 0; i < totalNodes; i++) {
            for (FlowEdge& edge : graph[i]) {
                edge.currentFlow = 0;
            }
        }
    }
};

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int T;
    cin >> T;
    
    for (int cs= 1; cs <= T; cs++) {
        int cityCount, roadCount;
        cin >> cityCount >> roadCount;
        
        // 初始化 Dinic 算法实例
        DinicMaxFlow flowSolver(cityCount);
        
        // 读取道路信息并构建图
        for (int i = 0; i < roadCount; i++) {
            int cityA, cityB, destroyCost;
            cin >> cityA >> cityB >> destroyCost;
            cityA--; cityB--;  // 转换为 0-based 索引
            flowSolver.addUndirectedEdge(cityA, cityB, destroyCost);
        }

        // 计算全局最小割
        int minCutValue = INT_MAX;
        int sourceNode = 0;  // 固定源点为第一个城市
        
        // 枚举所有其他城市作为汇点
        for (int sinkNode = 1; sinkNode < cityCount; sinkNode++) {
            minCutValue = min(minCutValue, flowSolver.computeMaxFlow(sourceNode, sinkNode));
        }
        
        // 处理图原本不连通的情况
        if (minCutValue == INT_MAX) minCutValue = 0;
        
        cout << "Case #" << caseNumber << ": " << minCutValue << '\n';
    }

    return 0;
}
