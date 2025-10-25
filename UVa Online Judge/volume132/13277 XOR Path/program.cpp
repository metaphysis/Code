// XOR Path
// UVa ID: 13277
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.280s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// 常量定义
const int MAX_NODE_COUNT = 100000;  // 最大节点数
const int MAX_VALUE_RANGE = 1 << 16;  // 值域范围 2^16

// 全局变量声明
vector<pair<int, int>> treeAdjacency[MAX_NODE_COUNT + 5];  // 树的邻接表存储
int xorDistance[MAX_NODE_COUNT + 5];  // 存储每个节点到根节点的异或距离
long long frequency[MAX_VALUE_RANGE];  // 频数数组，记录每个异或值的出现次数
long long convolutionResult[MAX_VALUE_RANGE];  // 卷积结果数组

/**
 * 深度优先搜索函数，计算每个节点到根节点的异或和
 * @param currentNode 当前处理的节点
 * @param parentNode 父节点，用于避免重复访问
 * @param currentXor 当前路径的异或累积值
 */
void performDFS(int currentNode, int parentNode, int currentXor) {
    xorDistance[currentNode] = currentXor;  // 记录当前节点到根节点的异或和
    // 遍历当前节点的所有邻居
    for (auto& edge : treeAdjacency[currentNode]) {
        int neighborNode = edge.first;      // 邻居节点
        int edgeWeight = edge.second;       // 边权值
        // 避免回溯到父节点
        if (neighborNode != parentNode) {
            // 递归计算子节点的异或和
            performDFS(neighborNode, currentNode, currentXor ^ edgeWeight);
        }
    }
}

/**
 * 快速沃尔什-哈达玛变换，用于计算异或卷积
 * @param array 输入数组，同时也会被修改为变换结果
 * @param arraySize 数组大小，必须是2的幂次
 * @param invertTransform 是否为逆变换
 */
void fastWalshHadamardTransform(long long array[], int arraySize, bool invertTransform) {
    // 分治进行变换
    for (int segmentLength = 1; 2 * segmentLength <= arraySize; segmentLength <<= 1) {
        for (int startIndex = 0; startIndex < arraySize; startIndex += 2 * segmentLength) {
            for (int offset = 0; offset < segmentLength; offset++) {
                // 获取当前分段的两个值
                long long firstValue = array[startIndex + offset];
                long long secondValue = array[startIndex + offset + segmentLength];
                // 正变换：和与差
                array[startIndex + offset] = firstValue + secondValue;
                array[startIndex + offset + segmentLength] = firstValue - secondValue;
            }
        }
    }
    // 如果是逆变换，需要除以数组大小进行归一化
    if (invertTransform) {
        for (int i = 0; i < arraySize; i++) {
            array[i] /= arraySize;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int testCaseCount;  // 测试用例数量
    cin >> testCaseCount;
    
    // 处理每个测试用例
    for (int caseNumber = 1; caseNumber <= testCaseCount; caseNumber++) {
        int nodeCount;  // 当前测试用例的节点数
        cin >> nodeCount;

        // 初始化邻接表
        for (int i = 1; i <= nodeCount; i++) {
            treeAdjacency[i].clear();
        }

        // 读入树的边信息
        for (int i = 0; i < nodeCount - 1; i++) {
            int firstNode, secondNode, weight;
            cin >> firstNode >> secondNode >> weight;
            // 构建无向图
            treeAdjacency[firstNode].emplace_back(secondNode, weight);
            treeAdjacency[secondNode].emplace_back(firstNode, weight);
        }

        // 从节点 1 开始 DFS 计算所有节点到根节点的异或和
        performDFS(1, -1, 0);

        // 初始化频数数组
        memset(frequency, 0, sizeof(frequency));
        // 统计每个异或值的出现次数
        for (int i = 1; i <= nodeCount; i++) {
            frequency[xorDistance[i]]++;
        }

        // 将频数数组复制到卷积结果数组进行变换
        memcpy(convolutionResult, frequency, sizeof(frequency));
        // 执行正变换
        fastWalshHadamardTransform(convolutionResult, MAX_VALUE_RANGE, false);
        // 点乘：计算频数数组的平方（在变换域中）
        for (int i = 0; i < MAX_VALUE_RANGE; i++) {
            convolutionResult[i] *= convolutionResult[i];
        }
        // 执行逆变换，得到卷积结果
        fastWalshHadamardTransform(convolutionResult, MAX_VALUE_RANGE, true);

        // 输出结果
        cout << "Case " << caseNumber << ":\n";
        for (int x = 0; x < MAX_VALUE_RANGE; x++) {
            long long pathCount;
            if (x == 0) {
                // 对于 x=0，需要减去 i=j 的情况（n个），然后除以 2 得到无序对
                pathCount = (convolutionResult[x] - nodeCount) / 2;
            } else {
                // 对于 x≠0，直接除以 2 得到无序对
                pathCount = convolutionResult[x] / 2;
            }
            cout << pathCount << "\n";
        }
    }

    return 0;
}
