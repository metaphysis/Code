// Disjoint Paths
// UVa ID: 1236
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_NODES = 65;

using ll = long long;

int nodeCount, maxPaths;
vector<pair<int, int>> graph[MAX_NODES];
int dp[MAX_NODES][MAX_NODES][3];  // dp[u][i][state]: 以u为根的子树中选择i条路径，节点u状态为state时的最大权重和
int temp[MAX_NODES][3];           // 临时数组，用于状态转移
int visited[MAX_NODES];           // 访问标记数组

/**
 * 深度优先搜索进行树形动态规划
 * @param currentNode 当前处理的节点
 * 
 * 状态说明：
 * state = 0: 当前节点未被任何路径使用
 * state = 1: 当前节点是某条路径的端点
 * state = 2: 当前节点是某条路径的中间点
 */
void depthFirstSearch(int currentNode) {
    visited[currentNode] = 1;
    // 初始化：不选任何路径时权重和为0
    dp[currentNode][0][0] = 0;
    // 遍历当前节点的所有邻接边
    for (auto edge : graph[currentNode]) {
        int neighborNode = edge.first;
        int edgeWeight = edge.second;
        if (!visited[neighborNode]) {
            depthFirstSearch(neighborNode);
            memset(temp, -1, sizeof(temp));
            // 从大到小遍历当前节点已选择的路径数
            for (int currentPaths = maxPaths; currentPaths >= 0; currentPaths--) {
                for (int currentState = 0; currentState <= 2; currentState++) {
                    if (dp[currentNode][currentPaths][currentState] == -1) continue;
                    // 遍历子节点可能选择的路径数
                    for (int childPaths = 0; childPaths <= maxPaths - currentPaths + 1; childPaths++) {
                        for (int childState = 0; childState < 3; childState++) {
                            if (dp[neighborNode][childPaths][childState] == -1) continue;
                            
                            int totalPaths = currentPaths + childPaths;
                            int totalWeight = dp[currentNode][currentPaths][currentState] + 
                                            dp[neighborNode][childPaths][childState];
                            // 情况1：不使用当前边连接两个节点
                            if (totalPaths <= maxPaths) {
                                temp[totalPaths][currentState] = max(temp[totalPaths][currentState], totalWeight);
                            }
                            // 情况2：使用当前边连接两个节点，分三种子情况
                            // 子情况2.1：两个端点连接（形成一条更长的路径）
                            if (currentState == 1 && childState == 1) {
                                if (currentPaths > 0 && childPaths > 0 && totalPaths - 1 >= 0) {
                                    temp[totalPaths - 1][2] = max(temp[totalPaths - 1][2], 
                                                                totalWeight + edgeWeight);
                                }
                            }
                            // 子情况2.2：两个空闲节点连接（创建一条新路径）
                            else if (currentState == 0 && childState == 0) {
                                if (totalPaths + 1 <= maxPaths) {
                                    temp[totalPaths + 1][1] = max(temp[totalPaths + 1][1], 
                                                                totalWeight + edgeWeight);
                                }
                            }
                            // 子情况2.3：一端一空闲连接（扩展现有路径）
                            else if (currentState <= 1 && childState <= 1) {
                                if (totalPaths <= maxPaths) {
                                    int newState = currentState + 1;  // 状态升级：0->1 或 1->2
                                    temp[totalPaths][newState] = max(temp[totalPaths][newState], 
                                                                    totalWeight + edgeWeight);
                                }
                            }
                        }  
                    }
                }
            }
            // 将临时数组的结果更新到dp数组中
            for (int paths = 0; paths <= maxPaths; paths++) {
                for (int state = 0; state <= 2; state++) {
                    dp[currentNode][paths][state] = temp[paths][state];
                }
            }
        }
    }
}

/**
 * 处理单个测试用例
 */
void solveTestCase() {
    // 初始化数组
    memset(visited, 0, sizeof(visited));
    memset(dp, -1, sizeof(dp));
    // 清空图结构
    for (int i = 1; i <= MAX_NODES; i++) {
        graph[i].clear();
    }
    // 读取输入
    cin >> nodeCount >> maxPaths;
    for (int i = 1; i < nodeCount; i++) {
        int nodeA, nodeB, weight;
        cin >> nodeA >> nodeB >> weight;
        graph[nodeA].push_back({nodeB, weight});
        graph[nodeB].push_back({nodeA, weight});
    }
    // 从节点1开始深度优先搜索
    depthFirstSearch(1);
    // 寻找最大答案：在根节点的所有状态中找最大值
    int maxWeightSum = 0;
    for (int paths = 0; paths <= maxPaths; paths++) {
        for (int state = 0; state < 3; state++) {
            if (dp[1][paths][state] > maxWeightSum) {
                maxWeightSum = dp[1][paths][state];
            }
        }
    }
    cout << maxWeightSum << "\n";
}

int main(int argc, char* argv[]) {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int testCaseCount;
    cin >> testCaseCount;
    while (testCaseCount-- > 0) {
        solveTestCase();
    }
    return 0;
}
