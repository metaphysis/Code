// Cutting Chains
// UVa ID: 818
// Verdict: Accepted
// Submission Date: 2025-10-23
// UVa Run Time: 0.190s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int n; // 链环数量
bool graph[16][16]; // 邻接矩阵存储图结构
bool opened[16]; // 记录哪些链环被打开
int degree[16]; // 记录每个顶点的度数
bool visited[16]; // DFS 访问标记

// 检查连通分量是否为简单路径，同时统计顶点数和边数
bool isPathComponent(int u, int& vertexCount, int& edgeCount) {
    visited[u] = true;
    vertexCount++; // 顶点数加 1
    edgeCount += degree[u]; // 累加度数（每条边会被计算两次）
    for (int v = 1; v <= n; v++) {
        if (!opened[v] && graph[u][v] && !visited[v]) {
            isPathComponent(v, vertexCount, edgeCount);
        }
    }
    return true;
}

// 检查打开指定链环后，剩余图是否满足条件
bool checkRemainingGraph(int openCount) {
    memset(degree, 0, sizeof(degree));
    memset(visited, false, sizeof(visited));
    
    // 计算剩余图中每个顶点的度数
    for (int i = 1; i <= n; i++) {
        if (opened[i]) continue; // 跳过的打开的链环
        for (int j = i + 1; j <= n; j++) {
            if (!opened[j] && graph[i][j]) {
                degree[i]++;
                degree[j]++;
            }
        }
    }
    
    // 检查度数是否都小于等于 2（路径图的必要条件）
    for (int i = 1; i <= n; i++) {
        if (!opened[i] && degree[i] > 2) return false;
    }
    
    // 检查每个连通分量是否为简单路径
    int compCount = 0; // 连通分量计数
    for (int i = 1; i <= n; i++) {
        if (!opened[i] && !visited[i]) {
            int vCount = 0, eCount = 0;
            isPathComponent(i, vCount, eCount);
            eCount /= 2; // 因为每条边被计算了两次
            // 简单路径的边数 = 顶点数 - 1
            if (eCount != vCount - 1) return false;
            compCount++;
        }
    }
    
    // 连通分量数不能超过打开数 + 1（可以用打开的链环连接各个分量）
    return compCount <= openCount + 1;
}

int main() {
    int caseNum = 1; // 测试用例编号
    while (cin >> n, n) {
        memset(graph, false, sizeof(graph));
        int a, b;
        // 读入连接关系，构建图
        while (cin >> a >> b, a != -1) {
            graph[a][b] = graph[b][a] = true;
        }
        
        int minOpen = n - 1; // 最坏情况需要打开 n - 1 个链环
        // 枚举所有可能的打开方案（位掩码枚举）
        for (int mask = 0; mask < (1 << n); mask++) {
            int openCount = 0; // 当前方案打开的链环数
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) {
                    opened[i + 1] = true; // 标记该链环被打开
                    openCount++;
                } else {
                    opened[i + 1] = false;
                }
            }
            // 检查当前方案是否可行，更新最小值
            if (checkRemainingGraph(openCount)) {
                minOpen = min(minOpen, openCount);
            }
        }
        
        cout << "Set " << caseNum++ << ": Minimum links to open is " << minOpen << endl;
    }
    return 0;
}
