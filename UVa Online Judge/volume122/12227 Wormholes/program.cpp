// Wormholes
// UVa ID: 12227
// Verdict: Accepted
// Submission Date: 2025-10-19
// UVa Run Time: 0.670s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 三维坐标点
struct Point3D {
    long long x, y, z;
    Point3D(long long a = 0, long long b = 0, long long c = 0):
        x(a), y(b), z(c) {}
    
    // 读取坐标
    void read() {
        scanf("%lld %lld %lld", &x, &y, &z);
    }
    
    // 计算到另一个点的欧几里得距离（向上取整）
    long long distanceTo(const Point3D &other) const {
        return ceil(sqrt((other.x - x) * (other.x - x)
                       + (other.y - y) * (other.y - y)
                       + (other.z - z) * (other.z - z)));
    }
};

// 图的边结构
struct GraphEdge {
    int targetNode;     // 目标节点
    long long createTime; // 虫洞创建时间（普通边设为负无穷）
    long long timeShift;  // 时间偏移量（普通边为飞行时间）
    
    GraphEdge(int target = 0, long long create_time = 0, long long time_shift = 0):
        targetNode(target), createTime(create_time), timeShift(time_shift) {}
};

#define MAX_NODES 128
#define INFINITY_VALUE (1LL << 60)  // 表示无穷大的值

// 全局变量
vector<GraphEdge> graph[MAX_NODES];        // 邻接表存储图
long long minTime[MAX_NODES];              // 到每个节点的最短时间
long long predecessorTime[MAX_NODES];      // 前驱节点对应边的时间约束
int inQueue[MAX_NODES];                    // 节点是否在队列中
int relaxCount[MAX_NODES];                 // 节点松弛次数
int predecessor[MAX_NODES];                // 前驱节点
int inNegativeCycle[MAX_NODES];            // 节点是否在负环中
int visited[MAX_NODES];                    // 访问标记
int visitCounter = 0;                      // 访问计数器

// 处理负环的SPFA算法
void processWithNegativeCycles(int startNode, int nodeCount, deque<int> &nodeQueue, int queueStatus[]) {
    // 初始化计数器和负环标记
    for (int i = 0; i < nodeCount; i++) {
        relaxCount[i] = 0;
        inNegativeCycle[i] = 0;
    }
    
    int currentNode;
    nodeQueue.push_front(startNode);
    
    while (!nodeQueue.empty()) {
        currentNode = nodeQueue.front();
        nodeQueue.pop_front();
        queueStatus[currentNode] = 0;
        
        // 遍历当前节点的所有出边
        for (int i = 0; i < graph[currentNode].size(); i++) {
            GraphEdge currentEdge = graph[currentNode][i];
            long long edgeCost = currentEdge.timeShift;
            
            // 关键步骤：处理虫洞的时间约束
            // 如果到达时间早于虫洞创建时间，需要等待，成本增加
            if (currentEdge.createTime > minTime[currentNode]) {
                edgeCost = currentEdge.timeShift + currentEdge.createTime - minTime[currentNode];
            }
            
            // 松弛操作：如果找到更短的路径
            if (minTime[currentEdge.targetNode] > minTime[currentNode] + edgeCost) {
                minTime[currentEdge.targetNode] = minTime[currentNode] + edgeCost;
                predecessor[currentEdge.targetNode] = currentNode;
                predecessorTime[currentEdge.targetNode] = currentEdge.createTime;
                
                if (!queueStatus[currentEdge.targetNode]) {
                    // 负环检测：如果节点松弛次数过多
                    if (++relaxCount[currentEdge.targetNode] > nodeCount + 1) {
                        visitCounter++;
                        relaxCount[currentEdge.targetNode] = 1;
                        
                        int cycleStart = currentEdge.targetNode;
                        int cycleFound = 0;
                        int bottleneckNode;
                        long long maxCreateTime;
                        
                        // 通过前驱指针回溯找到负环
                        for (int j = predecessor[cycleStart]; j != -1; j = predecessor[j]) {
                            if (visited[j] == visitCounter) {
                                cycleFound = 1;
                                cycleStart = j;
                                break;
                            }
                            visited[j] = visitCounter;
                        }
                        
                        // 找到环中创建时间最大的虫洞（时间瓶颈）
                        maxCreateTime = predecessorTime[cycleStart];
                        bottleneckNode = cycleStart;
                        for (int j = predecessor[cycleStart]; j != -1; j = predecessor[j]) {
                            if (j == cycleStart) {
                                break;
                            }
                            if (predecessorTime[j] > maxCreateTime) {
                                maxCreateTime = predecessorTime[j];
                                bottleneckNode = j;
                            }
                        }
                        
                        // 调整时间：不能无限回到过去，设置到刚好可以使用瓶颈虫洞
                        if (cycleFound) {
                            if (minTime[bottleneckNode] > maxCreateTime) {
                                minTime[bottleneckNode] = maxCreateTime;
                                // 根据时间值决定插入队列的位置（优化）
                                if (nodeQueue.size() && minTime[nodeQueue.front()] > minTime[bottleneckNode])
                                    nodeQueue.push_front(bottleneckNode);
                                else
                                    nodeQueue.push_back(bottleneckNode);
                            }
                        }
                    }
                    
                    if (!queueStatus[currentEdge.targetNode]) {
                        queueStatus[currentEdge.targetNode] = 1;
                        // 根据时间值优化队列插入位置
                        if (nodeQueue.size() && minTime[nodeQueue.front()] > minTime[currentEdge.targetNode])
                            nodeQueue.push_front(currentEdge.targetNode);
                        else
                            nodeQueue.push_back(currentEdge.targetNode);
                    }
                }
            }
        }
    }
}

// SPFA算法主函数
void runSPFA(int startNode, int endNode, int nodeCount) {
    // 初始化前驱数组
    for (int i = 0; i < nodeCount; i++)
        predecessor[i] = -1;
    
    int queueStatus[MAX_NODES];
    // 初始化距离和队列状态
    for (int i = 0; i < nodeCount; i++) {
        minTime[i] = INFINITY_VALUE;
        queueStatus[i] = 0;
    }
    
    deque<int> nodeQueue;
    minTime[startNode] = 0;
    
    // 执行带负环处理的SPFA
    processWithNegativeCycles(startNode, nodeCount, nodeQueue, queueStatus);
    
    printf("%lld\n", minTime[endNode]);
}

int main() {
    int testCases, wormholeCount;
    long long createTime, timeShift;
    Point3D allPoints[MAX_NODES];
    
    scanf("%d", &testCases);
    while (testCases--) {
        // 清空图
        for (int i = 0; i < MAX_NODES; i++)
            graph[i].clear();
        
        // 读取起点和终点
        allPoints[0].read();  // 起点
        allPoints[1].read();  // 终点
        
        scanf("%d", &wormholeCount);
        
        // 处理每个虫洞
        for (int i = 0; i < wormholeCount; i++) {
            // 虫洞入口和出口坐标
            allPoints[(1 + i) * 2].read();     // 虫洞入口
            allPoints[(1 + i) * 2 + 1].read(); // 虫洞出口
            scanf("%lld %lld", &createTime, &timeShift);
            
            // 添加虫洞边：从入口到出口，带有时间约束
            graph[(1 + i) * 2].push_back(GraphEdge((1 + i) * 2 + 1, createTime, timeShift));
        }
        
        // 计算总节点数：起点 + 终点 + 所有虫洞的入口和出口
        int totalNodes = (wormholeCount + 1) * 2;
        
        // 构建完全图：所有节点之间都有普通飞行边
        for (int i = 0; i < totalNodes; i++) {
            for (int j = 0; j < totalNodes; j++) {
                if (i == j) continue;
                // 普通边：创建时间为负无穷，成本为飞行时间
                graph[i].push_back(GraphEdge(j, -INFINITY_VALUE, allPoints[i].distanceTo(allPoints[j])));
            }
        }
        
        // 运行SPFA算法：从起点0到终点1
        runSPFA(0, 1, totalNodes);
    }
    
    return 0;
}

