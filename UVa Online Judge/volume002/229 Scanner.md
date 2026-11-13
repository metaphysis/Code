[UVa 229 Scanner](https://blog.csdn.net/metaphysis/article/details/153005875)

## 题目描述

本题要求模拟一个身体扫描仪的工作过程。扫描仪通过扫描物体的一系列水平切片来构建三维模型。每个切片是一个 $10 \times 15$ 的二维网格。

扫描仪由四个传感器阵列组成：
- **阵列1**：$10$ 个向右扫描的传感器
- **阵列2**：$24$ 个向右上对角线扫描的传感器  
- **阵列3**：$15$ 个向上扫描的传感器
- **阵列4**：$24$ 个向左上对角线扫描的传感器

每个传感器记录其视线方向上物体部分的"厚度"（即物体占据的格子数量）。一次完整的扫描包含 $73$ 个读数。

## 输入格式

输入以整数开始，表示图像切片的数量。对于每个切片，有四行数据分别对应四个传感器阵列的读数：
- 第一行：$10$ 个整数（阵列1）
- 第二行：$24$ 个整数（阵列2）  
- 第三行：$15$ 个整数（阵列3）
- 第四行：$24$ 个整数（阵列4）

## 输出格式

对于每个切片，输出 $10$ 行，每行 $15$ 个字符：
- `#` 表示该格子是物体的一部分
- `.` 表示该格子不是物体的一部分

如果扫描结果存在歧义，输出全为 `.` 的空白图像。切片之间用空行分隔。

## 解题思路

### 核心思想

这是一个**约束满足问题**，我们需要根据四个方向的传感器读数来确定每个格子的状态。关键在于利用已知信息进行逻辑推导，逐步确定未知格子的状态。

### 算法设计

#### 1. 数据结构
- `gridColor[10][15]`：存储每个格子的状态（$0$=空，$1$=物体）
- `cellDetermined[10][15]`：标记格子状态是否已确定
- `sensorReadings[4][32]`：存储四个传感器阵列的读数
- `sensorVerified[4][32]`：标记传感器约束是否已验证

#### 2. 迭代推导过程

算法采用**迭代推导**的方法，不断应用以下逻辑规则，直到无法再推导出新的信息：

对于每个传感器视线方向上的格子序列：

设：
- `totalCells` = 该方向上的总格子数
- `blackCount` = 已确定的物体格子数  
- `whiteCount` = 已确定的空格子数
- `unknownCount` = 未确定的格子数
- `reading` = 传感器读数

**推导规则：**
1. 如果 `blackCount + unknownCount == reading`：
   - 所有未知格子**必须**是物体（`#`）
2. 如果 `whiteCount + unknownCount == totalCells - reading`：
   - 所有未知格子**必须**是空的（`.`）

#### 3. 传感器扫描方向处理

**阵列1（向右）**：
- $10$ 个传感器，每个对应一行
- 扫描方向：从左到右，`(row, 0) → (row, 14)`

**阵列2（右上）**：
- $24$ 个传感器，扫描方向：`(-1, +1)`
- 前 $10$ 个：从左边开始 `(0,0), (1,0), ..., (9,0)`
- 后 $14$ 个：从底部开始 `(9,1), (9,2), ..., (9,14)`

**阵列3（向上）**：
- $15$ 个传感器，每个对应一列
- 扫描方向：从下到上，`(0,col) → (9,col)`

**阵列4（左上）**：
- $24$ 个传感器，扫描方向：`(-1, -1)`
- 前 $14$ 个：从底部开始 `(9,0), (9,1), ..., (9,13)`
- 后 $10$ 个：从右边开始 `(8,14), (7,14), ..., (0,14)`

#### 4. 终止条件

- 当一轮迭代中没有任何格子状态更新时，算法终止
- 最终检查所有传感器约束是否都满足：
  - 如果全部满足，输出推导出的网格
  - 如果有任何约束未满足，输出全空网格

### 复杂度分析

- 空间复杂度：$O(1)$，固定大小的网格和传感器数组
- 时间复杂度：$O(k \times n)$，其中 $k$ 是迭代次数，$n$ 是格子总数（$150$）

### 示例分析

以样例输入为例，算法会：
1. 读取四个传感器阵列的数据
2. 通过迭代推导逐步确定格子状态
3. 验证所有传感器读数是否与最终网格匹配
4. 输出结果网格或空白图像

## AC代码

```cpp
// Scanner
// UVa ID: 229
// Verdict: Accepted
// Submission Date: 2025-10-10
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

#define MAX_ROWS 10
#define MAX_COLS 15

// 传感器数量配置：Array1(10), Array2(24), Array3(15), Array4(24)
int sensorCounts[] = {10, 24, 15, 24};
int sensorReadings[4][32];    // 存储4组传感器的读数
int sensorVerified[4][32];    // 标记传感器约束是否已验证通过
int gridColor[MAX_ROWS][MAX_COLS] = {};      // 网格颜色状态：0=空(.), 1=物体(#)
int cellDetermined[MAX_ROWS][MAX_COLS] = {}; // 标记格子状态是否已确定

/**
 * 检查坐标是否在网格范围内
 */
int isInBound(int x, int y) {
    return x >= 0 && y >= 0 && x < MAX_ROWS && y < MAX_COLS;
}

/**
 * 沿指定方向填充格子颜色
 * @param startX, startY 起始坐标
 * @param deltaX, deltaY 方向向量
 * @param colorValue 要填充的颜色值 (0=空, 1=物体)
 */
void fillGridColor(int startX, int startY, int deltaX, int deltaY, int colorValue) {
    for (int x = startX, y = startY; isInBound(x, y); x += deltaX, y += deltaY) {
        if (!cellDetermined[x][y]) {
            cellDetermined[x][y] = 1;        // 标记格子状态已确定
            gridColor[x][y] = colorValue;    // 设置格子颜色
        }
    }
}

int main() {
    int testCaseCount;
    scanf("%d", &testCaseCount);
    
    while (testCaseCount--) {
        int totalConstraints = 0, satisfiedConstraints = 0;
        
        // ========== 读取传感器数据 ==========
        for (int sensorArray = 0; sensorArray < 4; sensorArray++) {
            for (int sensorIndex = 0; sensorIndex < sensorCounts[sensorArray]; sensorIndex++) {
                scanf("%d", &sensorReadings[sensorArray][sensorIndex]);
            }
            totalConstraints += sensorCounts[sensorArray];  // 累计总约束数
        }
        
        // ========== 初始化网格和标记数组 ==========
        memset(gridColor, 0, sizeof(gridColor));
        memset(cellDetermined, 0, sizeof(cellDetermined));
        memset(sensorVerified, 0, sizeof(sensorVerified));
        
        int hasUpdate;  // 标记是否在本轮迭代中有更新
        
        // ========== 迭代推导：不断应用约束直到收敛 ==========
        do {
            hasUpdate = 0;  // 每轮迭代开始时重置更新标记
            
            // ========== 处理 Array 1: 向右扫描的传感器 ==========
            // 10个传感器，每个对应一行，从左侧向右水平扫描
            for (int row = 0; row < sensorCounts[0]; row++) {
                int totalCells = 0, blackCount = 0, whiteCount = 0;
                int reading = sensorReadings[0][row];  // 当前传感器的读数
                
                // 统计该行所有格子的状态
                for (int col = 0; col < MAX_COLS; col++) {
                    if (cellDetermined[row][col]) {
                        // 格子状态已确定
                        if (gridColor[row][col] == 0) whiteCount++;  // 空格子
                        else blackCount++;                          // 物体格子
                    }
                    totalCells++;  // 总格子数
                }
                
                // 检查该传感器约束是否已完全满足
                // 条件：所有格子状态已确定 且 物体格子数等于传感器读数
                if (whiteCount + blackCount == totalCells && reading == blackCount) {
                    sensorVerified[0][row] = 1;  // 标记该传感器已验证通过
                }
                
                // 如果还有未确定的格子，尝试进行逻辑推导
                if (whiteCount + blackCount != totalCells) {
                    int unknownCount = totalCells - whiteCount - blackCount;
                    
                    // 情况1：如果 "当前物体数 + 未知格子数 = 传感器读数"
                    // 说明所有未知格子都必须是物体
                    if (reading == blackCount + unknownCount) {
                        fillGridColor(row, 0, 0, 1, 1);  // 向右填充物体
                        hasUpdate = 1;  // 标记有更新，需要继续迭代
                    }
                    
                    // 情况2：如果 "当前空位数 + 未知格子数 = 总格子数 - 传感器读数"  
                    // 说明所有未知格子都必须是空的
                    if (totalCells - reading == whiteCount + unknownCount) {
                        fillGridColor(row, 0, 0, 1, 0);  // 向右填充空位
                        hasUpdate = 1;  // 标记有更新，需要继续迭代
                    }
                }
            }
            
            // ========== 处理 Array 2: 右上扫描的传感器 ==========
            // 24个传感器，沿右上对角线方向扫描 (dx=-1, dy=+1)
            for (int sensorIndex = 0; sensorIndex < sensorCounts[1]; sensorIndex++) {
                int totalCells = 0, blackCount = 0, whiteCount = 0;
                int reading = sensorReadings[1][sensorIndex];
                int startX, startY, currentX, currentY;
                
                // 确定扫描线的起点坐标
                if (sensorIndex < 10) {
                    // 前10个传感器：左边界从上到下 (0,0), (1,0), ..., (9,0)
                    startX = sensorIndex;
                    startY = 0;
                } else {
                    // 后14个传感器：下边界从左到右 (9,1), (9,2), ..., (9,14)
                    startX = MAX_ROWS - 1;
                    startY = sensorIndex - MAX_ROWS + 1;
                }
                
                // 统计该对角线上的格子状态
                for (currentX = startX, currentY = startY; 
                     isInBound(currentX, currentY); 
                     currentX--, currentY++) {
                    if (cellDetermined[currentX][currentY]) {
                        if (gridColor[currentX][currentY] == 0) whiteCount++;
                        else blackCount++;
                    }
                    totalCells++;
                }
                
                // 检查传感器约束是否满足
                if (whiteCount + blackCount == totalCells && reading == blackCount) {
                    sensorVerified[1][sensorIndex] = 1;
                }
                
                // 推导未知格子
                if (whiteCount + blackCount != totalCells) {
                    int unknownCount = totalCells - whiteCount - blackCount;
                    
                    if (reading == blackCount + unknownCount) {
                        fillGridColor(startX, startY, -1, 1, 1);  // 右上方向填充物体
                        hasUpdate = 1;
                    }
                    
                    if (totalCells - reading == whiteCount + unknownCount) {
                        fillGridColor(startX, startY, -1, 1, 0);  // 右上方向填充空位
                        hasUpdate = 1;
                    }
                }
            }
            
            // ========== 处理 Array 3: 向上扫描的传感器 ==========
            // 15个传感器，每个对应一列，从底部向上垂直扫描
            for (int col = 0; col < sensorCounts[2]; col++) {
                int totalCells = 0, blackCount = 0, whiteCount = 0;
                int reading = sensorReadings[2][col];
                
                // 统计该列所有格子的状态（从下到上）
                for (int row = 0; row < MAX_ROWS; row++) {
                    if (cellDetermined[row][col]) {
                        if (gridColor[row][col] == 0) whiteCount++;
                        else blackCount++;
                    }
                    totalCells++;
                }
                
                // 检查传感器约束是否满足
                if (whiteCount + blackCount == totalCells && reading == blackCount) {
                    sensorVerified[2][col] = 1;
                }
                
                // 推导未知格子
                if (whiteCount + blackCount != totalCells) {
                    int unknownCount = totalCells - whiteCount - blackCount;
                    
                    if (reading == blackCount + unknownCount) {
                        fillGridColor(0, col, 1, 0, 1);  // 向下填充物体（从顶部开始）
                        hasUpdate = 1;
                    }
                    
                    if (totalCells - reading == whiteCount + unknownCount) {
                        fillGridColor(0, col, 1, 0, 0);  // 向下填充空位（从顶部开始）
                        hasUpdate = 1;
                    }
                }
            }
            
            // ========== 处理 Array 4: 左上扫描的传感器 ==========
            // 24个传感器，沿左上对角线方向扫描 (dx=-1, dy=-1)
            for (int sensorIndex = 0; sensorIndex < sensorCounts[3]; sensorIndex++) {
                int totalCells = 0, blackCount = 0, whiteCount = 0;
                int reading = sensorReadings[3][sensorIndex];
                int startX, startY, currentX, currentY;
                
                // 确定扫描线的起点坐标
                if (sensorIndex < 14) {
                    // 前14个传感器：下边界从左到右 (9,0), (9,1), ..., (9,13)
                    startX = MAX_ROWS - 1;
                    startY = sensorIndex;
                } else {
                    // 后10个传感器：右边界从下到上 (8,14), (7,14), ..., (0,14)
                    startX = MAX_ROWS - (sensorIndex - 14) - 1;
                    startY = MAX_COLS - 1;
                }
                
                // 统计该对角线上的格子状态
                for (currentX = startX, currentY = startY; 
                     isInBound(currentX, currentY); 
                     currentX--, currentY--) {
                    if (cellDetermined[currentX][currentY]) {
                        if (gridColor[currentX][currentY] == 0) whiteCount++;
                        else blackCount++;
                    }
                    totalCells++;
                }
                
                // 检查传感器约束是否满足
                if (whiteCount + blackCount == totalCells && reading == blackCount) {
                    sensorVerified[3][sensorIndex] = 1;
                }
                
                // 推导未知格子
                if (whiteCount + blackCount != totalCells) {
                    int unknownCount = totalCells - whiteCount - blackCount;
                    
                    if (reading == blackCount + unknownCount) {
                        fillGridColor(startX, startY, -1, -1, 1);  // 左上方向填充物体
                        hasUpdate = 1;
                    }
                    
                    if (totalCells - reading == whiteCount + unknownCount) {
                        fillGridColor(startX, startY, -1, -1, 0);  // 左上方向填充空位
                        hasUpdate = 1;
                    }
                }
            }
        } while (hasUpdate);  // 继续迭代直到没有新的更新

        // ========== 统计满足的约束数量 ==========
        for (int sensorArray = 0; sensorArray < 4; sensorArray++) {
            for (int sensorIndex = 0; sensorIndex < sensorCounts[sensorArray]; sensorIndex++) {
                satisfiedConstraints += sensorVerified[sensorArray][sensorIndex];
            }
        }

        // ========== 输出最终结果 ==========
        if (totalConstraints == satisfiedConstraints) {
            // 所有传感器约束都满足，输出推导出的网格
            for (int row = 0; row < MAX_ROWS; row++, puts("")) {
                for (int col = 0; col < MAX_COLS; col++) {
                    printf("%c", gridColor[row][col] ? '#' : '.');
                }
            }
        } else {
            // 有约束未满足或存在歧义，输出全空网格
            for (int row = 0; row < MAX_ROWS; row++, puts("")) {
                for (int col = 0; col < MAX_COLS; col++) {
                    printf(".");
                }
            }
        }

        // 测试用例之间输出空行（最后一个除外）
        if (testCaseCount) puts("");
    }

    return 0;
}
```

这个解法通过迭代应用约束推导，能够高效地解决这个多方向约束满足问题，并在存在歧义时正确输出空白图像。
