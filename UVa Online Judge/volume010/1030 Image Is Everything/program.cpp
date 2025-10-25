// Image Is Everything
// UVa ID: 1030
// Verdict: Accepted
// Submission Date: 2025-10-24
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const int MAX_CUBE_SIZE = 15;  // 最大立方体尺寸

class CubeReconstructor {
private:
    int cubeSize;                          // 立方体的尺寸 N
    char viewData[6][MAX_CUBE_SIZE][MAX_CUBE_SIZE];  // 存储6个方向的视图数据
    char cubeState[MAX_CUBE_SIZE][MAX_CUBE_SIZE][MAX_CUBE_SIZE];  // 三维立方体状态
    
    /**
     * 读取有效字符，跳过空格等无效字符
     * @return 有效的颜色字符（大写字母）或 '.' 表示透明
     */
    char readValidCharacter() {
        char currentChar;
        while (true) {
            currentChar = getchar();
            // 只接受大写字母（颜色）或 '.'（透明）
            if ((currentChar >= 'A' && currentChar <= 'Z') || currentChar == '.') {
                return currentChar;
            }
        }
    }
    
    /**
     * 将视图坐标转换为三维立方体坐标
     * @param viewId 视图编号（0-5分别对应前、左、后、右、顶、底视图）
     * @param viewRow 视图中的行坐标
     * @param viewCol 视图中的列坐标
     * @param depth 视线深度（从近到远）
     * @param cubeX 输出的立方体X坐标
     * @param cubeY 输出的立方体Y坐标
     * @param cubeZ 输出的立方体Z坐标
     */
    void convertViewToCubeCoordinates(int viewId, int viewRow, int viewCol, int depth, 
                                     int& cubeX, int& cubeY, int& cubeZ) {
        switch(viewId) {
            case 0:  // 前视图 (front): 从 -Z 方向观察
                cubeX = viewRow;
                cubeY = viewCol;
                cubeZ = depth;
                break;
            case 1:  // 左视图 (left): 从 -X 方向观察
                cubeX = viewRow;
                cubeY = depth;
                cubeZ = cubeSize - viewCol - 1;
                break;
            case 2:  // 后视图 (back): 从 +Z 方向观察
                cubeX = viewRow;
                cubeY = cubeSize - viewCol - 1;
                cubeZ = cubeSize - depth - 1;
                break;
            case 3:  // 右视图 (right): 从 +X 方向观察
                cubeX = viewRow;
                cubeY = cubeSize - depth - 1;
                cubeZ = viewCol;
                break;
            case 4:  // 顶视图 (top): 从 +Y 方向观察
                cubeX = depth;
                cubeY = viewCol;
                cubeZ = cubeSize - viewRow - 1;
                break;
            case 5:  // 底视图 (bottom): 从 -Y 方向观察
                cubeX = cubeSize - depth - 1;
                cubeY = viewCol;
                cubeZ = viewRow;
                break;
        }
    }

public:
    /**
     * 初始化重构器，读取输入数据
     * @param size 立方体的尺寸 N
     */
    void initialize(int size) {
        cubeSize = size;
        
        // 读取6个方向的视图数据
        // 输入顺序：对于每一行，依次读取前、左、后、右、顶、底视图的对应行
        for (int row = 0; row < cubeSize; row++) {
            for (int viewId = 0; viewId < 6; viewId++) {
                for (int col = 0; col < cubeSize; col++) {
                    viewData[viewId][row][col] = readValidCharacter();
                }
            }
        }
        
        // 初始化立方体状态：'#' 表示立方体可能存在（初始状态）
        for (int x = 0; x < cubeSize; x++) {
            for (int y = 0; y < cubeSize; y++) {
                for (int z = 0; z < cubeSize; z++) {
                    cubeState[x][y][z] = '#';
                }
            }
        }
    }
    
    /**
     * 计算物体的最大可能重量
     * @return 最大重量（即存在的立方体数量）
     */
    int calculateMaximumWeight() {
        int cubeX, cubeY, cubeZ;  // 立方体坐标

        // 第一步：处理透明视图约束
        // 对于每个视图中标记为 '.' 的位置，移除整条视线上的所有立方体
        for (int viewId = 0; viewId < 6; viewId++) {
            for (int viewRow = 0; viewRow < cubeSize; viewRow++) {
                for (int viewCol = 0; viewCol < cubeSize; viewCol++) {
                    if (viewData[viewId][viewRow][viewCol] == '.') {
                        // 沿着视线方向，将所有立方体标记为不存在
                        for (int depth = 0; depth < cubeSize; depth++) {
                            convertViewToCubeCoordinates(viewId, viewRow, viewCol, depth, 
                                                        cubeX, cubeY, cubeZ);
                            cubeState[cubeX][cubeY][cubeZ] = '.';  // 标记为不存在
                        }
                    }
                }
            }
        }

        // 第二步：迭代处理颜色约束
        bool hasChanges;  // 标记本轮迭代是否有状态变化
        do {
            hasChanges = false;  // 初始假设没有变化
            
            // 遍历所有视图的所有颜色位置
            for (int viewId = 0; viewId < 6; viewId++) {
                for (int viewRow = 0; viewRow < cubeSize; viewRow++) {
                    for (int viewCol = 0; viewCol < cubeSize; viewCol++) {
                        char expectedColor = viewData[viewId][viewRow][viewCol];
                        // 只处理颜色位置，跳过透明位置
                        if (expectedColor != '.') {
                            // 沿着视线方向寻找第一个存在的立方体
                            for (int depth = 0; depth < cubeSize; depth++) {
                                convertViewToCubeCoordinates(viewId, viewRow, viewCol, depth,
                                                            cubeX, cubeY, cubeZ);
                                
                                // 如果当前立方体已确定不存在，继续检查下一个
                                if (cubeState[cubeX][cubeY][cubeZ] == '.') {
                                    continue;
                                }
                                
                                // 如果立方体颜色未确定，设置为期望颜色
                                if (cubeState[cubeX][cubeY][cubeZ] == '#') {
                                    cubeState[cubeX][cubeY][cubeZ] = expectedColor;
                                }
                                
                                // 如果颜色匹配，这个视图位置处理完成
                                if (cubeState[cubeX][cubeY][cubeZ] == expectedColor) {
                                    break;
                                }
                                
                                // 颜色冲突：立方体颜色与视图要求不符，必须移除
                                cubeState[cubeX][cubeY][cubeZ] = '.';
                                hasChanges = true;  // 标记有状态变化，需要继续迭代
                            }
                        }
                    }
                }
            }
        } while (hasChanges);  // 继续迭代直到没有状态变化

        // 统计最终存在的立方体数量
        int existingCubeCount = 0;
        for (int x = 0; x < cubeSize; x++) {
            for (int y = 0; y < cubeSize; y++) {
                for (int z = 0; z < cubeSize; z++) {
                    if (cubeState[x][y][z] != '.') {
                        existingCubeCount++;
                    }
                }
            }
        }
        
        return existingCubeCount;  // 每个立方体重1克，所以数量即为重量
    }
};

int main() {
    int cubeSize;
    CubeReconstructor reconstructor;
    
    // 处理多个测试用例，直到输入0为止
    while (scanf("%d", &cubeSize) == 1 && cubeSize != 0) {
        reconstructor.initialize(cubeSize);
        int maxWeight = reconstructor.calculateMaximumWeight();
        printf("Maximum weight: %d gram(s)\n", maxWeight);
    }
    
    return 0;
}
