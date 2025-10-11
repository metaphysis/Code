// The Islands
// UVa ID: 1096
// Verdict: Accepted
// Submission Date: 2025-10-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 定义常量和宏
#define TOLERANCE 1e-12          // 浮点数容差
#define MAX_N 128                // 最大岛屿数量
#define SHIFT_BITS 7             // 用于编码的位移位数
#define BIT(k) (1ULL << (k))     // 生成指定位的掩码
#define MASK(k) (BIT(k) - 1ULL)  // 生成低位掩码
// 编码路径类型信息：类型(type) + 岛屿i(x) + 岛屿j(y)
#define ENCODE_PATH_TYPE(type, x, y) ((x) | ((y) << SHIFT_BITS) | ((type) << (SHIFT_BITS + SHIFT_BITS)))
#define SQUARE(x) ((x) * (x))    // 计算平方
#define INFINITY_VALUE (1 << 29) // 表示无穷大的值

typedef long long int64;         // 定义64位整数类型

// 返回两个double中的较小值
double minDouble(double x, double y) { return x < y ? x : y; }

// 全局变量定义
int islandCount;                 // 岛屿总数
int specialIsland1;              // 第一个特殊岛屿
int specialIsland2;              // 第二个特殊岛屿  
int caseNumber;                  // 测试用例编号
int pathRecord[MAX_N][MAX_N];    // 记录路径选择决策
int *outputPtr;                  // 输出路径指针
int outputPath[MAX_N * MAX_N];   // 存储输出路径
double distanceMatrix[MAX_N][MAX_N]; // 岛屿间距离矩阵
double dpState[MAX_N][MAX_N];    // DP状态数组
int64 coordX[MAX_N];             // 岛屿x坐标
int64 coordY[MAX_N];             // 岛屿y坐标

/**
 * 计算从状态(i,j)出发的最小路径长度
 * 状态定义：一条路径在岛屿i，另一条在岛屿j，且所有小于max(i,j)的岛屿都已被访问
 * 返回值：从当前状态到终点的最小路径长度
 */
double calculateDPState(int i, int j) {
    // 计算下一个要访问的岛屿编号
    int nextIsland = (i < j ? j + 1 : i + 1);
    
    // 如果已经计算过，直接返回结果（记忆化搜索）
    if (dpState[i][j] < INFINITY_VALUE)
        return dpState[i][j];
    
    // 如果下一个岛屿是特殊岛屿1，必须加入第一条路径
    if (nextIsland == specialIsland1) {
        // 记录决策：类型0表示加入第一条路径，nextIsland成为新的i，j保持不变
        pathRecord[i][j] = ENCODE_PATH_TYPE(0, nextIsland, j);
        // 递归计算并更新DP状态
        return dpState[i][j] = calculateDPState(nextIsland, j) + distanceMatrix[i][nextIsland];
    }
    // 如果下一个岛屿是特殊岛屿2，必须加入第二条路径
    else if (nextIsland == specialIsland2) {
        // 记录决策：类型1表示加入第二条路径，i保持不变，nextIsland成为新的j
        pathRecord[i][j] = ENCODE_PATH_TYPE(1, i, nextIsland);
        // 递归计算并更新DP状态
        return dpState[i][j] = calculateDPState(i, nextIsland) + distanceMatrix[j][nextIsland];
    }
    // 如果到达最后一个岛屿，计算到终点的距离
    else if (nextIsland == islandCount) {
        // 两条路径分别连接到终点岛屿n-1
        return dpState[i][j] = distanceMatrix[i][islandCount - 1] + distanceMatrix[j][islandCount - 1];
    }
    // 普通情况：尝试将下一个岛屿加入两条路径中的任意一条
    else {
        // 选项1：将nextIsland加入第二条路径（j->nextIsland）
        double option1 = calculateDPState(i, nextIsland) + distanceMatrix[j][nextIsland];
        // 选项2：将nextIsland加入第一条路径（i->nextIsland）  
        double option2 = calculateDPState(nextIsland, j) + distanceMatrix[i][nextIsland];
        
        // 选择较小的路径并记录决策
        if ((dpState[i][j] = minDouble(option1, option2)) == option1) {
            // 记录选择加入第二条路径
            pathRecord[i][j] = ENCODE_PATH_TYPE(1, i, nextIsland);
        } else {
            // 记录选择加入第一条路径
            pathRecord[i][j] = ENCODE_PATH_TYPE(0, nextIsland, j);
        }
        return dpState[i][j];
    }
}

/**
 * 回溯重建完整路径
 * 根据pathRecord数组从起点(0,0)开始重建访问顺序
 */
void reconstructPath(int i, int j) {
    int islandA, islandB, pathType;
    
    // 递归终止条件：到达终点
    if (i == islandCount - 1 || j == islandCount - 1)
        return;
    
    // 解码路径记录
    int record = pathRecord[i][j];
    islandA = (record & MASK(SHIFT_BITS));                    // 提取新的i值
    islandB = (record >> SHIFT_BITS) & MASK(SHIFT_BITS);      // 提取新的j值
    pathType = record >> (SHIFT_BITS + SHIFT_BITS);           // 提取路径类型
    
    // 记录路径选择：将类型和岛屿编号编码为一个整数
    // pathType | (岛屿编号 << 1)，这样可以通过最低位判断路径类型
    *outputPtr++ = pathType | ((pathType ? islandB : islandA) << 1);
    
    // 继续回溯
    reconstructPath(islandA, islandB);
}

/**
 * 四舍五入到百分位
 * 用于输出格式要求，保留两位小数
 */
double roundToHundredth(double x) {
    return ((int)(100 * (x + 0.005))) / 100.00;
}

/**
 * 主求解函数：计算最短路径并重建访问顺序
 * 参数outputArray：输出路径数组
 * 返回值：最短路径长度
 */
double solveProblem(int *outputArray) {
    int i, j;
    int *leftPath, *rightPath;
    int leftIslands[MAX_N], rightIslands[MAX_N];  // 存储左右路径的岛屿
    double result;
    
    // 初始化DP状态为无穷大
    for (i = 0; i < islandCount; ++i)
        for (j = 0; j < islandCount; ++j)
            dpState[i][j] = INFINITY_VALUE;
    
    // 设置终点状态：两条路径都到达最后一个岛屿，距离为0
    dpState[islandCount - 1][islandCount - 1] = 0;
    
    // 从起点(0,0)开始计算最短路径
    result = calculateDPState(0, 0);
    
    // 重建路径：从起点开始回溯
    outputPtr = outputPath;
    reconstructPath(0, 0);
    
    // 分离左右路径（去程和回程）
    leftPath = leftIslands;   // 左路径（去程）
    rightPath = rightIslands; // 右路径（回程）
    
    // 处理输出路径：类型0的加入左路径，类型1的加入右路径
    for (i = 0; i < outputPtr - outputPath; ++i)
        if (!(outputPath[i] & 1))  // 类型0：第一条路径（去程）
            *leftPath++ = outputPath[i] >> 1;  // 右移1位获取岛屿编号
    
    // 右路径需要逆序处理（因为回溯时是反向的）
    for (j = outputPtr - outputPath - 1; j >= 0; --j)
        if (outputPath[j] & 1)  // 类型1：第二条路径（回程）
            *rightPath++ = outputPath[j] >> 1;  // 右移1位获取岛屿编号
    
    // 构建最终输出序列：0 + 左路径 + 右路径 + 0
    outputPtr = outputArray;
    *outputPtr++ = 0;  // 起点0
    // 添加左路径（去程）
    for (i = 0; i < leftPath - leftIslands; *outputPtr++ = leftIslands[i++]);
    // 添加右路径（回程）  
    for (i = 0; i < rightPath - rightIslands; *outputPtr++ = rightIslands[i++]);
    *outputPtr++ = 0;  // 终点0
    *outputPtr = MAX_N;  // 结束标记
    
    return result;
}

/**
 * 主函数：处理输入输出，协调整个求解过程
 */
int main(int argc, char* argv[]) {
    int i, j, temp;
    int pathA[MAX_N + MAX_N], pathB[MAX_N + MAX_N];  // 两种方案的路径
    double resultA, resultB;                         // 两种方案的结果
    int *outputPathPtr;                              // 最终输出路径指针
    
    // 处理每个测试用例，直到输入为0 0 0
    while (3 == scanf("%d %d %d", &islandCount, &specialIsland1, &specialIsland2) && 
           (islandCount || specialIsland1 || specialIsland2)) {
        
        // 读入所有岛屿的坐标
        for (i = 0; i < islandCount; ++i)
            scanf("%lld %lld", &coordX[i], &coordY[i]);
        
        // 计算岛屿间距离矩阵（欧几里得距离）
        for (i = 0; i < islandCount; ++i)
            for (j = i + 1; j < islandCount; ++j)
                distanceMatrix[i][j] = distanceMatrix[j][i] = 
                    sqrt(SQUARE(coordX[i] - coordX[j]) + SQUARE(coordY[i] - coordY[j]));
        
        // 第一次求解：使用原始的特殊岛屿分配
        resultA = solveProblem(pathA);
        
        // 交换特殊岛屿，第二次求解（处理对称性）
        temp = specialIsland1;
        specialIsland1 = specialIsland2;
        specialIsland2 = temp;
        resultB = solveProblem(pathB);
        
        // 选择更优的解输出
        // 优先选择路径第二个岛屿是1的方案，或者结果更小的方案
        if ((pathA[1] == 1 && pathB[1] != 0) || (pathA[1] == 1 && pathB[1] == 1 && resultA < resultB)) {
            printf("Case %d: %.2lf\n", ++caseNumber, roundToHundredth(resultA) + TOLERANCE);
            outputPathPtr = pathA;
        } else {
            printf("Case %d: %.2lf\n", ++caseNumber, roundToHundredth(resultB) + TOLERANCE);
            outputPathPtr = pathB;
        }
        
        // 输出路径
        for (i = 0; ; ++i) {
            printf("%d", outputPathPtr[i]);
            if (outputPathPtr[i + 1] != MAX_N)  // 不是最后一个元素
                putchar(' ');
            else  // 到达结束标记
                break;
        }
        putchar('\n');
    }
    
    return 0;
}
