// Black & White
// UVa ID: 10572
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.860s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

#define MAX_STATES 1430  // 预计算的最大合法状态数，对于8列网格，有效状态数约为1430
#define MAX_SIZE 8       // 网格最大行列数，题目约束 M,N ≤ 8

// 完全保持原始变量含义，只重命名
int rowDP[MAX_SIZE][2][MAX_STATES];              // 原d数组，行间DP：rowDP[行号][当前行首颜色][状态索引] = 方案数
int cellDP[MAX_SIZE][MAX_SIZE][2][2][2][MAX_STATES]; // 原e数组，格内DP：cellDP[行][列][上色][左色][预测右色][状态索引] = 方案数
int stateToIndex[1 << (3 * MAX_SIZE - 5)];       // 原p数组，状态编码 -> 状态索引的映射
int solutionGrid[MAX_SIZE][MAX_SIZE];            // 原g数组，存储一个合法解
int stateList[MAX_STATES];                       // 原r数组，状态索引 -> 状态编码的映射
int comp[MAX_SIZE], temp[MAX_SIZE];              // 原a,b数组，comp存储当前状态各列的连通分量编号，temp用于重编号
int rows, cols, stateCount, totalWays, queueHead, queueTail; // 原m,n,c,cc,h,t

// 队列结构（原q数组）
struct QueueNode { 
    int upColor;      // 原a，上一行当前列的颜色（用于2×2约束检查）
    int leftColor;    // 原b，当前行左侧格子的颜色（用于连通性检查）  
    int predColor;    // 原c，预测的右侧格子颜色（用于状态转移）
    int stateIdx;     // 原s，当前状态的索引
} queueNodes[MAX_STATES << 9];  // 队列大小：最大状态数 × 512

// 答案回溯（原ans数组）
struct AnswerNode { 
    int prevIdx;      // 原i，前驱状态在队列中的索引
    int color;        // 原c，当前格子填充的颜色
} answerNodes[MAX_STATES << 9];

bool inQueue[2][2][2][MAX_STATES];               // 原inq数组，队列判重，防止重复添加相同状态
char inputGrid[MAX_SIZE][MAX_SIZE];              // 原s数组，输入网格

// 原decode函数：解码状态编码为连通分量数组
void decodeState(int stateCode) {
    for (int i = cols - 1; i >= 0; --i) {
        comp[i] = stateCode & 7;  // 取最低3位作为当前列的连通分量编号
        stateCode >>= 3;           // 右移3位处理下一列
    }
}

// 原valid函数：检查状态是否合法（连通分量不交叉）
bool isValidState(int stateCode) {
    decodeState(stateCode);
    // 检查是否存在连通分量交叉的情况（类似括号交叉）
    for (int i = 0; i < cols; ++i) {
        for (int j = i + 2; j < cols; ++j) {
            if (comp[i] == comp[j]) {  // 如果第i列和第j列属于同一分量
                // 检查i和j之间是否有其他分量的列
                for (int k = i + 1; k < j; ++k) {
                    if (comp[i] != comp[k]) {  // 找到不同的分量
                        // 检查这个不同的分量是否在j之后再次出现
                        for (int t = j + 1; t < cols; ++t) {
                            if (comp[k] == comp[t]) {
                                return false;  // 发现交叉：分量A在i和j，分量B在k和t，形成交叉
                            }
                        }
                    }
                }
            }
        }
    }
    return true;  // 没有交叉，状态合法
}

// 原rep()函数：重新编号连通分量（最小表示法）
int normalizeState() {
    // 建立旧编号到新编号的映射
    for (int i = 0, newId = 0, k; i < cols; ++i) {
        // 检查当前分量是否已经分配过新编号
        for (k = 0; k < i; ++k) {
            if (comp[k] == comp[i]) break;  // 已经出现过，使用已有编号
        }
        if (k == i) temp[comp[i]] = newId++;  // 新的分量，分配新编号
    }
    // 重新编码状态
    int normalized = 0;
    for (int i = 0; i < cols; ++i) {
        normalized = normalized << 3 | temp[comp[i]];  // 每列占3位
    }
    return normalized;
}

// 原rep(int x)函数：重新编号给定状态编码
int normalizeState(int stateCode) {
    decodeState(stateCode);
    memset(temp, 0, sizeof(temp));  // 清空映射表
    return normalizeState();
}

// 原fr函数：处理第一行，从颜色掩码生成初始状态
int getFirstRowState(int colorMask) {
    // 解码颜色掩码到comp数组（这里comp临时存储颜色）
    for (int i = cols - 1; i >= 0; --i) {
        comp[i] = colorMask & 1;  // 取最低位作为颜色（0:黑, 1:白）
        colorMask >>= 1;
    }
    // 检查是否与输入中的固定颜色冲突
    for (int i = 0; i < cols; ++i) {
        if ((comp[i] && inputGrid[0][i] == '#') || (!comp[i] && inputGrid[0][i] == 'o')) {
            return -1;  // 颜色冲突
        }
    }
    // 根据颜色分配连通分量编号（相同颜色的相邻格子属于同一分量）
    int state = 0;
    for (int i = 0, compId = 0; i < cols; ++i) {
        // 如果当前列颜色与前一列不同，开始新的连通分量
        state = state << 3 | (i > 0 && comp[i] != comp[i - 1] ? ++compId : compId);
    }
    return stateToIndex[state];  // 返回状态索引
}

// 原fc函数：从连通分量推断当前列的上方实际颜色
int getActualUpColor(int col, int upColor) {
    int color = upColor;  // 以上一行的颜色为起点
    // 遍历从第1列到第col列，检查连通分量变化
    for (int j = 1; j <= col; ++j) {
        if (comp[j] != comp[j - 1]) {  // 连通分量变化
            color ^= 1;  // 颜色翻转：0变1，1变0
        }
    }
    return color;  // 返回推断出的实际颜色
}

// 原upd函数（第一个版本）：更新格内DP，用于行内转移
void updateCellState(int upColor, int leftColor, int predColor, int stateIdx, int delta, int &target) {
    if (inQueue[upColor][leftColor][predColor][stateIdx]) {
        target += delta;  // 状态已在队列中，只增加方案数
    } else {
        target = delta;  // 新状态，设置方案数
        queueNodes[queueTail] = {upColor, leftColor, predColor, stateIdx};  // 加入队列
        queueTail++;
        inQueue[upColor][leftColor][predColor][stateIdx] = true;  // 标记已入队
    }
}

// 原upd函数（第二个版本）：更新行间DP，用于行末转移
void updateRowState(int upColor, int stateIdx, int delta, int &target) {
    if (!target) {  // 如果这是第一次到达这个状态
        queueNodes[queueTail] = {upColor, -1, -1, stateIdx};  // 加入队列（-1表示无效）
        queueTail++;
    }
    target += delta;  // 增加方案数
}

// 原dfs函数：回溯构造一个合法解
void backtrack(int row, int col, int nodeIdx) {
    if (row) {  // 不是第一行
        solutionGrid[row][col] = answerNodes[nodeIdx].color;  // 填充当前格子
        // 递归回溯：如果col>0则继续当前行，否则换到上一行最后一列
        backtrack(col ? row : row - 1, col ? col - 1 : cols - 1, answerNodes[nodeIdx].prevIdx);
    } else {  // 第一行，特殊处理
        int firstColor = queueNodes[nodeIdx].upColor;  // 第一行第一个格子的颜色
        solutionGrid[0][0] = firstColor;
        decodeState(stateList[queueNodes[nodeIdx].stateIdx]);  // 解码第一行的状态
        
        // 根据连通分量变化推断第一行其他格子的颜色
        int currentColor = firstColor;
        for (int i = 1; i < cols; ++i) {
            if (comp[i] != comp[i - 1]) {  // 连通分量变化
                currentColor ^= 1;  // 颜色翻转
            }
            solutionGrid[0][i] = currentColor;  // 填充第一行
        }
    }
}

// 原gen函数：生成一个合法解（在找到第一个合法方案时调用）
void generateSolution(int col, int nodeIdx, int color) {
    if (totalWays == 0) {  // 只在找到第一个解时构造
        // 处理最后一行的特殊情况
        if (col + 1 < cols) solutionGrid[rows - 1][cols - 1] = color;
        solutionGrid[rows - 1][col] = color;
        // 开始回溯构造完整解
        backtrack(col ? rows - 1 : rows - 2, col ? col - 1 : cols - 1, nodeIdx);
    }
}

// 原mx函数：获取状态中最大的连通分量编号
int getMaxComponent(int stateCode) {
    int maxComp = 0;
    for (int i = cols - 1; i >= 0; --i) {
        maxComp = max(maxComp, stateCode & 7);  // 取最低3位
        stateCode >>= 3;  // 右移3位处理下一列
    }
    return maxComp;  // 返回最大分量编号
}

// 原check函数：检查格子颜色是否与输入中的固定颜色兼容
bool isColorCompatible(char cellChar, int color) {
    int cellColor = cellChar == '.' ? -1 : (cellChar == 'o');  // 转换：'#'->0, 'o'->1, '.'->-1
    return cellColor < 0 || cellColor == color;  // 兼容：要么未固定，要么颜色匹配
}

// 原solve函数：解决单个测试用例的主函数
void solve() {
    // 读取输入
    cin >> rows >> cols;
    queueHead = queueTail = totalWays = 0;  // 初始化队列和方案数
    memset(rowDP, 0, sizeof(rowDP));  // 清零行间DP数组
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> inputGrid[i][j];  // 读入网格
        }
    }
    
    // ========== 第一步：预处理所有合法状态 ==========
    stateCount = 0;
    int maxStateCode = 1 << (3 * cols - 5);  // 状态编码的最大值（3*n-5位）
    for (int code = 0; code < maxStateCode; ++code) {
        if (isValidState(code) && normalizeState(code) == code) {
            // 只存储最小表示的状态，避免重复
            stateList[stateToIndex[code] = stateCount++] = code;
        }
    }
    
    // ========== 第二步：第一行初始化 ==========
    int maxMask = 1 << cols;  // 第一行所有可能的颜色模式
    for (int mask = 0; mask < maxMask; ++mask) {
        int stateIdx = getFirstRowState(mask);
        if (stateIdx >= 0) {  // 状态有效（不与固定颜色冲突）
            rowDP[0][comp[0]][stateIdx] = 1;  // 设置方案数为1
            queueNodes[queueTail++] = {comp[0], -1, -1, stateIdx};  // 加入队列
        }
    }
    
    // ========== 第三步：主DP循环，逐行逐格处理 ==========
    for (int i = 1, lastRow = rows - 1; i < rows; ++i) {  // 从第二行开始
        for (int j = 0; j < cols; ++j) {  // 遍历每列
            // 快速检查：如果当前格子和它的左上、上、左三个格子都是固定颜色且相同，则违反2×2约束
            if (j > 0 && inputGrid[i][j] != '.' && 
                inputGrid[i][j] == inputGrid[i][j-1] && 
                inputGrid[i][j] == inputGrid[i-1][j] && 
                inputGrid[i][j] == inputGrid[i-1][j-1]) {
                cout << 0 << endl << endl;  // 输出0并返回
                return;
            }
            
            int queueStart = queueTail;  // 记录当前列开始处理时的队列位置
            int fixedColor = inputGrid[i][j] == '.' ? -1 : (inputGrid[i][j] == 'o');  // 当前格子固定颜色
            memset(inQueue, 0, sizeof(inQueue));  // 清空判重数组，准备处理新列
            
            // 处理当前列的所有待扩展状态
            while (queueHead < queueStart) {
                int upColor = queueNodes[queueHead].upColor;
                int leftColor = queueNodes[queueHead].leftColor;
                int predColor = queueNodes[queueHead].predColor;
                int stateIdx = queueNodes[queueHead].stateIdx;
                
                // 获取到达当前状态的方案数
                int ways = j ? cellDP[i][j-1][upColor][leftColor][predColor][stateIdx] : 
                              rowDP[i-1][upColor][stateIdx];
                queueHead++;  // 出队
                
                decodeState(stateList[stateIdx]);  // 解码当前状态到comp数组
                int actualUpColor = getActualUpColor(j-1, upColor);  // 推断上方实际颜色
                
                // ========== 情况1：最后一列（需要换行） ==========
                if (j == cols - 1) {
                    // 检查是否需要合并连通分量（三个颜色不完全相同）
                    if (actualUpColor != leftColor || actualUpColor != predColor || leftColor != predColor) {
                        // 如果当前颜色与上方相同但与左侧不同，需要合并连通分量
                        if (actualUpColor == predColor && comp[j-1] != comp[j]) {
                            int oldComp = comp[j];
                            for (int k = 0; k < cols; ++k) {
                                if (comp[k] == oldComp) comp[k] = comp[j-1];  // 合并分量
                            }
                        }
                        
                        // 尝试填充predColor颜色
                        if (fixedColor < 0 || fixedColor == predColor) {
                            int newState = stateToIndex[normalizeState()];  // 获取新状态索引
                            answerNodes[queueTail] = {queueHead-1, predColor};  // 记录答案路径
                            updateRowState(upColor, newState, ways, rowDP[i][upColor][newState]);  // 更新行间DP
                            
                            // 如果是最后一行且只有一个连通分量，记录合法方案
                            if (i == lastRow && getMaxComponent(stateList[newState]) == 1) {
                                generateSolution(j, queueHead-1, predColor);
                                totalWays += ways;  // 累加方案数
                            }
                        }
                        
                        // 尝试另一种颜色（1^predColor表示颜色翻转）
                        decodeState(stateList[stateIdx]);  // 恢复原始状态
                        int sameCompCount = 0;  // 统计与当前格子同分量的格子数
                        for (int k = 0; k < cols && sameCompCount < 2; ++k) {
                            if (comp[k] == comp[j]) ++sameCompCount;
                        }
                        
                        if (fixedColor != predColor) {  // 固定颜色要求另一种颜色
                            if (sameCompCount > 1) {  // 当前分量有多个格子，可以改变颜色
                                if (i == lastRow && actualUpColor != predColor && 
                                    getMaxComponent(stateList[stateIdx]) == 1) {
                                    totalWays += ways;
                                    generateSolution(j, queueHead-1, 1 ^ predColor);
                                }
                                // 更新分量编号并尝试另一种颜色
                                comp[j] = (actualUpColor == predColor) ? cols - 1 : comp[j-1];
                                int newState = stateToIndex[normalizeState()];
                                answerNodes[queueTail] = {queueHead-1, 1 ^ predColor};
                                updateRowState(upColor, newState, ways, rowDP[i][upColor][newState]);
                            } else if (i == lastRow && actualUpColor != predColor && 
                                      isColorCompatible(inputGrid[lastRow][j], actualUpColor)) {
                                // 特殊情况：最后一行，当前分量只有一个格子
                                comp[j] = comp[j-1];
                                if (normalizeState() == 0) {  // 有效状态
                                    generateSolution(j, queueHead-1, 1 ^ predColor);
                                    totalWays += ways;
                                }
                            }
                        }
                    } else if (fixedColor != actualUpColor) {  // 三个颜色相同但固定颜色不同
                        if (i == lastRow && stateList[stateIdx] == 0) {
                            generateSolution(j, queueHead-1, 1 ^ predColor);
                            totalWays += ways;
                        }
                        comp[j] = cols - 1;  // 分配新的分量编号
                        int newState = stateToIndex[normalizeState()];
                        answerNodes[queueTail] = {queueHead-1, 1 ^ predColor};
                        updateRowState(upColor, newState, ways, rowDP[i][upColor][newState]);
                    }
                }
                // ========== 情况2：行内非首列（非第一列且非最后一列） ==========
                else if (j > 0) {
                    int nextColor = comp[j+1] == comp[j] ? predColor : 1 ^ predColor;  // 预测下一列颜色
                    
                    if (actualUpColor != leftColor || actualUpColor != predColor || leftColor != predColor) {
                        if (actualUpColor == predColor && comp[j-1] != comp[j]) {
                            int oldComp = comp[j];
                            for (int k = 0; k < cols; ++k) {
                                if (comp[k] == oldComp) comp[k] = comp[j-1];  // 合并分量
                            }
                        }
                        
                        if (fixedColor < 0 || fixedColor == predColor) {
                            int newState = stateToIndex[normalizeState()];
                            answerNodes[queueTail] = {queueHead-1, predColor};
                            updateCellState(upColor, predColor, nextColor, newState, ways, 
                                         cellDP[i][j][upColor][predColor][nextColor][newState]);  // 更新格内DP
                        }
                        
                        decodeState(stateList[stateIdx]);  // 恢复原始状态
                        int sameCompCount = 0;
                        for (int k = 0; k < cols && sameCompCount < 2; ++k) {
                            if (comp[k] == comp[j]) ++sameCompCount;
                        }
                        
                        if (fixedColor != predColor) {
                            if (sameCompCount > 1) {
                                comp[j] = (actualUpColor == predColor) ? cols - 1 : comp[j-1];
                                int newState = stateToIndex[normalizeState()];
                                answerNodes[queueTail] = {queueHead-1, 1 ^ predColor};
                                updateCellState(upColor, predColor, nextColor, newState, ways, 
                                             cellDP[i][j][upColor][predColor][nextColor][newState]);
                            } else if (i == lastRow && predColor != nextColor && 
                                      predColor != actualUpColor && j + 2 == cols && 
                                      isColorCompatible(inputGrid[lastRow][cols-1], actualUpColor)) {
                                // 特殊情况：处理最后一行倒数第二列
                                comp[j] = comp[j+1] = comp[j-1];  // 合并三个格子到同一分量
                                if (normalizeState() == 0) {
                                    generateSolution(j, queueHead-1, 1 ^ predColor);
                                    totalWays += ways;
                                }
                            }
                        }
                    } else if (fixedColor != actualUpColor) {
                        comp[j] = cols - 1;
                        int newState = stateToIndex[normalizeState()];
                        answerNodes[queueTail] = {queueHead-1, 1 ^ predColor};
                        updateCellState(upColor, predColor, nextColor, newState, ways, 
                                     cellDP[i][j][upColor][predColor][nextColor][newState]);
                    }
                }
                // ========== 情况3：行首列（第一列） ==========
                else {
                    predColor = comp[1] == comp[0] ? actualUpColor : 1 ^ actualUpColor;  // 预测颜色
                    int sameCompCount = 1;  // 统计与第0列同分量的格子数
                    for (int k = 1; k < cols; ++k) {
                        if (comp[k] == comp[0]) ++sameCompCount;
                    }
                    
                    if (fixedColor < 0 || fixedColor == actualUpColor) {
                        answerNodes[queueTail] = {queueHead-1, actualUpColor};
                        updateCellState(actualUpColor, actualUpColor, predColor, stateIdx, ways, 
                                     cellDP[i][j][actualUpColor][actualUpColor][predColor][stateIdx]);
                    }
                    
                    if (fixedColor != actualUpColor) {
                        if (sameCompCount > 1) {  // 当前分量有多个格子
                            comp[0] = cols - 1;  // 给新分量一个大编号
                            int newColor = 1 ^ actualUpColor;
                            int newState = stateToIndex[normalizeState()];
                            answerNodes[queueTail] = {queueHead-1, newColor};
                            updateCellState(newColor, actualUpColor, predColor, newState, ways, 
                                         cellDP[i][j][newColor][actualUpColor][predColor][newState]);
                        } else if (i == lastRow && actualUpColor != predColor && 
                                  cols == 2 && isColorCompatible(inputGrid[lastRow][1], predColor)) {
                            // 特殊情况：2列网格的最后一行
                            generateSolution(j, queueHead-1, 1 ^ actualUpColor);
                            totalWays += ways;
                        }
                    }
                }
            }
        }
    }
    
    // ========== 第四步：输出结果 ==========
    cout << totalWays << endl;  // 输出方案总数
    if (totalWays) {  // 如果有合法方案，输出其中一个
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // 将内部颜色表示转换为字符输出：0->'#', 1->'o'
                cout << (solutionGrid[i][j] ? 'o' : '#');
            }
            cout << endl;
        }
    }
    cout << endl;  // 每个测试用例后输出空行
}

int main() {
    int testCases;
    cin >> testCases;
    while (testCases--) {
        solve();  // 处理每个测试用例
    }
    return 0;
}
