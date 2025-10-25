// Square Destroyer
// UVa ID: 1603
// Verdict: Accepted
// Submission Date: 2025-10-25
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 1000;        // 最大数组大小
const int INF_VALUE = 0x3f3f3f3f;  // 无穷大常量

// 表示火柴棒或正方形的结构体
struct Element {
    int x[2];  // x坐标的两个端点
    int y[2];  // y坐标的两个端点
    
    // 检查当前元素是否在另一个元素的边界上
    bool isOnBoundary(Element& boundaryElement) {
        for (int i = 0; i < 2; ++i) {
            // 如果点在边界元素内部（不在边界上），返回 false
            if (x[i] > boundaryElement.x[0] && x[i] < boundaryElement.x[1] && 
                y[i] > boundaryElement.y[0] && y[i] < boundaryElement.y[1]) {
                return 0;
            }
            // 如果点在边界元素外部，返回 false
            if (x[i] < boundaryElement.x[0] || x[i] > boundaryElement.x[1] || 
                y[i] < boundaryElement.y[0] || y[i] > boundaryElement.y[1]) {
                return 0;
            }
        }
        return 1;
    }
};

// 全局变量声明
Element rodArray[MAX_N];        // 存储所有火柴棒
Element squareArray[MAX_N];     // 存储所有正方形
int gridSize;                   // 网格大小 n
int rodCount;                   // 火柴棒总数
int squareCount;                // 正方形总数
int deletedRod[MAX_N];          // 标记被删除的火柴棒
int deletedSquare[MAX_N];       // 标记被删除的正方形
int missingCount;               // 缺失的火柴棒数量

// 舞蹈链算法实现
struct DancingLinks {
    static const int MAX_COLS = 1000;   // 最大列数
    static const int MAX_ROWS = 1000;   // 最大行数
    static const int MAX_NODES = 1000;  // 最大节点数
    
    // 舞蹈链的基本属性
    int colCount;               // 列数
    int nodeCount;              // 节点总数
    int colSize[MAX_COLS];      // 每列的节点数量
    int rowHead[MAX_ROWS];      // 每行的头节点
    int visited[MAX_COLS];      // 用于估价函数的访问标记
    int minAnswer;              // 最小解
    
    // 舞蹈链节点的指针和属性
    int nodeRow[MAX_NODES];     // 节点所在的行
    int nodeCol[MAX_NODES];     // 节点所在的列
    int leftPtr[MAX_NODES];     // 左指针
    int rightPtr[MAX_NODES];    // 右指针
    int upPtr[MAX_NODES];       // 上指针
    int downPtr[MAX_NODES];     // 下指针
    
    // 初始化舞蹈链
    void init(int colNum) {
        colCount = colNum;
        // 初始化列头节点，形成环形双向链表
        for (int i = 0; i <= colCount; ++i) {
            upPtr[i] = downPtr[i] = i;      // 上下指针指向自己
            leftPtr[i] = i - 1;             // 左指针指向前一个
            rightPtr[i] = i + 1;            // 右指针指向后一个
        }
        leftPtr[0] = colCount;              // 首尾相连形成环
        rightPtr[colCount] = 0;
        nodeCount = colCount + 1;           // 节点编号从 colCount + 1 开始
        
        // 初始化辅助数组
        memset(colSize, 0, sizeof(colSize));
        memset(rowHead, -1, sizeof(rowHead));
        memset(visited, 0, sizeof(visited));
        minAnswer = INF_VALUE;
    }
    
    // 添加节点到舞蹈链中
    void addNode(int rowIdx, int colIdx) {
        int newNode = nodeCount++;           // 创建新节点
        colSize[colIdx]++;                   // 该列的节点数加1
        
        // 设置节点属性
        nodeRow[newNode] = rowIdx;
        nodeCol[newNode] = colIdx;
        
        // 连接到列链表
        upPtr[newNode] = upPtr[colIdx];
        downPtr[newNode] = colIdx;
        upPtr[downPtr[newNode]] = downPtr[upPtr[newNode]] = newNode;
        
        // 连接到行链表
        if (!~rowHead[rowIdx]) {
            // 如果这是该行的第一个节点
            rowHead[rowIdx] = leftPtr[newNode] = rightPtr[newNode] = newNode;
        } else {
            // 插入到行链表的头部
            rightPtr[newNode] = rowHead[rowIdx];
            leftPtr[newNode] = leftPtr[rowHead[rowIdx]];
            leftPtr[rightPtr[newNode]] = rightPtr[leftPtr[newNode]] = newNode;
        }
    }
    
    // 移除指定的列（及其相关的行）
    void removeCol(int colIdx) {
        // 遍历该列的所有行，从行链表中移除这些行
        for (int i = downPtr[colIdx]; i != colIdx; i = downPtr[i]) {
            leftPtr[rightPtr[i]] = leftPtr[i];
            rightPtr[leftPtr[i]] = rightPtr[i];
        }
    }
    
    // 恢复被移除的列
    void restoreCol(int colIdx) {
        // 遍历该列的所有行，恢复到行链表中
        for (int i = upPtr[colIdx]; i != colIdx; i = upPtr[i]) {
            leftPtr[rightPtr[i]] = rightPtr[leftPtr[i]] = i;
        }
    }
    
    // 估价函数：使用贪心算法估计最少还需要选择多少行
    int estimate() {
        int estimateVal = 0;
        
        // 第一遍遍历：标记所有剩余的列
        for (int c = rightPtr[0]; c != 0; c = rightPtr[c]) {
            visited[c] = 1;
        }
        
        // 第二遍遍历：贪心选择列
        for (int c = rightPtr[0]; c != 0; c = rightPtr[c]) {
            if (visited[c]) {
                ++estimateVal;               // 选择这一列
                visited[c] = 0;              // 取消标记
                
                // 标记该列覆盖的所有列
                for (int i = downPtr[c]; i != c; i = downPtr[i]) {
                    for (int j = rightPtr[i]; j != i; j = rightPtr[j]) {
                        visited[nodeCol[j]] = 0;
                    }
                }
            }
        }
        return estimateVal;
    }
    
    // 检查并移除空的列
    void checkEmpty() {
        for (int c = 1; c <= colCount; ++c) {
            if (!colSize[c]) {
                // 移除该列的所有行
                for (int i = downPtr[c]; i != c; i = downPtr[i]) {
                    leftPtr[rightPtr[i]] = leftPtr[i];
                    rightPtr[leftPtr[i]] = rightPtr[i];
                }
                // 从列头链表中移除该列
                leftPtr[rightPtr[c]] = leftPtr[c];
                rightPtr[leftPtr[c]] = rightPtr[c];
            }
        }
    }
    
    // 深度优先搜索求解
    void dfs(int depth) {
        // 如果所有列都被覆盖，找到解
        if (rightPtr[0] == 0) {
            minAnswer = depth;
            return;
        }
        
        // 剪枝：当前深度 + 估价函数值 > 当前最优解
        if (depth + estimate() > minAnswer) {
            return;
        }
        
        // 选择节点数最少的列（启发式策略）
        int selectedCol = rightPtr[0];
        for (int i = rightPtr[0]; i != 0; i = rightPtr[i]) {
            if (colSize[i] < colSize[selectedCol]) {
                selectedCol = i;
            }
        }
        
        // 尝试该列的每一行
        for (int i = downPtr[selectedCol]; i != selectedCol; i = downPtr[i]) {
            // 移除当前行
            removeCol(i);
            
            // 移除该行覆盖的所有列
            for (int j = rightPtr[i]; j != i; j = rightPtr[j]) {
                removeCol(j);
            }
            
            // 递归搜索
            dfs(depth + 1);
            
            // 恢复该行覆盖的所有列
            for (int j = leftPtr[i]; j != i; j = leftPtr[j]) {
                restoreCol(j);
            }
            
            // 恢复当前行
            restoreCol(i);
        }
    }
};

DancingLinks dlxSolver;  // 全局舞蹈链求解器实例

int main() {
    int testCases;
    scanf("%d", &testCases);
    
    // 处理每个测试用例
    for (; testCases--;) {
        scanf("%d", &gridSize);
        rodCount = squareCount = 0;
        
        // 生成所有火柴棒
        for (int i = 0; i <= gridSize; ++i) {
            // 生成水平火柴棒
            for (int j = 0; j <= gridSize; ++j) {
                if (j + 1 <= gridSize) {
                    rodArray[rodCount++] = {i, i, j, j + 1};
                }
            }
            // 生成垂直火柴棒
            for (int j = 0; j <= gridSize; ++j) {
                if (i + 1 <= gridSize) {
                    rodArray[rodCount++] = {i, i + 1, j, j};
                }
            }
        }
        
        // 生成所有可能的正方形
        for (int i = 0; i <= gridSize; ++i) {
            for (int j = 0; j <= gridSize; ++j) {
                for (int size = 1; size <= gridSize; ++size) {
                    if (i + size <= gridSize && j + size <= gridSize) {
                        squareArray[squareCount++] = {i, i + size, j, j + size};
                    }
                }
            }
        }
        
        // 初始化标记数组
        memset(deletedRod, 0, sizeof(deletedRod));
        memset(deletedSquare, 0, sizeof(deletedSquare));
        
        // 读取缺失的火柴棒
        scanf("%d", &missingCount);
        while (missingCount--) {
            int idx;
            scanf("%d", &idx);
            deletedRod[idx - 1] = 1;  // 标记该火柴棒被删除
            
            // 标记被这根火柴棒破坏的正方形
            for (int j = 0; j < squareCount; ++j) {
                if (rodArray[idx - 1].isOnBoundary(squareArray[j])) {
                    deletedSquare[j] = 1;
                }
            }
        }
        
        // 初始化舞蹈链
        dlxSolver.init(squareCount);
        
        // 构建精确覆盖矩阵
        for (int i = 0; i < rodCount; ++i) {
            if (!deletedRod[i]) {  // 只考虑可用的火柴棒
                for (int j = 0; j < squareCount; ++j) {
                    if (!deletedSquare[j]) {  // 只考虑未被破坏的正方形
                        if (rodArray[i].isOnBoundary(squareArray[j])) {
                            // 火柴棒在正方形边界上，添加节点
                            dlxSolver.addNode(i + 1, j + 1);
                        }
                    }
                }
            }
        }
        
        // 检查并移除空的列
        dlxSolver.checkEmpty();
        
        // 求解并输出结果
        dlxSolver.dfs(0);
        printf("%d\n", dlxSolver.minAnswer);
    }
    
    return 0;
}
