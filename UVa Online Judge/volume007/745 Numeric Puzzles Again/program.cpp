// Numeric Puzzles Again
// UVa ID: 745
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 全局变量
char pattern[32][4][32][32]; // [pieceId][rotation][x][y] 存储所有拼图块的所有旋转形态
char tempOutput[4][32][32], finalOutput[32][32]; // 临时输出和最终输出
int gridSize, pieceCount; // 网格大小和拼图块数量
int maxSum[30]; // 存储最大行和的各位数字

// 更新最终输出：计算四个旋转的行和，选择最大的
void updateFinalOutput() {
    int bestRotation = -1;
    
    // 生成其他三个旋转
    for (int rot = 1; rot < 4; rot++)
        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++)
                tempOutput[rot][i][j] = tempOutput[rot-1][j][gridSize - 1 - i];
    
    // 比较四个旋转的行和
    for (int rot = 0; rot < 4; rot++) {
        int sum[30] = {}; // 存储行和的各位数字
        
        // 计算行和（从右向左处理，便于比较）
        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++) {
                sum[j] += tempOutput[rot][i][gridSize - j - 1] - '0';
            }
        
        // 处理进位
        for (int i = 0; i < 29; i++) {
            sum[i+1] += sum[i] / 10;
            sum[i] %= 10;
        }
        
        // 比较大小
        int compareResult = 0;
        for (int i = 29; i >= 0; i--)
            if (sum[i] != maxSum[i]) {
                compareResult = sum[i] > maxSum[i] ? 1 : -1;
                break;
            }
        
        // 更新最大行和
        if (compareResult == 1) {
            for (int i = 29; i >= 0; i--)
                maxSum[i] = sum[i];
            bestRotation = rot;
        }
    }
    
    // 更新最终输出
    if (bestRotation >= 0)
        for (int i = 0; i < gridSize; i++)
            for (int j = 0; j < gridSize; j++)
                finalOutput[i][j] = tempOutput[bestRotation][i][j];
}

// 舞蹈链（Dancing Links）算法实现，用于精确覆盖问题
class DancingLinks {
public:
    struct Node {
        int left, right, up, down; // 四个方向的指针
        int columnId; // 列ID
        int pieceId, rotation, posX, posY; // 额外数据：拼图块ID、旋转、位置
    } nodes[131072 + 256]; // 节点数组
    
    int columnSize[512], solution[512], head, nodeCount; // 列大小、解、头节点、节点计数
    bool foundSolution; // 是否找到解
    
    // 移除列c及其相关行
    void removeColumn(int col) {
        nodes[nodes[col].right].left = nodes[col].left;
        nodes[nodes[col].left].right = nodes[col].right;
        
        for (int i = nodes[col].down; i != col; i = nodes[i].down)
            for (int j = nodes[i].right; j != i; j = nodes[j].right) {
                nodes[nodes[j].down].up = nodes[j].up;
                nodes[nodes[j].up].down = nodes[j].down;
                columnSize[nodes[j].columnId]--;
            }
    }
    
    // 恢复列c及其相关行
    void restoreColumn(int col) {
        for (int i = nodes[col].down; i != col; i = nodes[i].down)
            for (int j = nodes[i].left; j != i; j = nodes[j].left) {
                nodes[nodes[j].down].up = j;
                nodes[nodes[j].up].down = j;
                columnSize[nodes[j].columnId]++;
            }
        
        nodes[nodes[col].right].left = col;
        nodes[nodes[col].left].right = col;
    }
    
    // 打印解：将解转换为网格输出
    void printSolution(int depth) {
        for (int i = 0; i < depth; i++) {
            int pieceId = nodes[solution[i]].pieceId;
            int rotation = nodes[solution[i]].rotation;
            int posX = nodes[solution[i]].posX;
            int posY = nodes[solution[i]].posY;
            
            // 将拼图块放置到临时输出中
            for (int x = 0; x < gridSize; x++)
                for (int y = 0; y < gridSize; y++)
                    if (pattern[pieceId][rotation][x][y] != ' ')
                        tempOutput[0][posX + x][posY + y] = pattern[pieceId][rotation][x][y];
        }
        updateFinalOutput();
    }
    
    // 舞蹈链搜索
    void search(int depth) {
        if (foundSolution) return;
        
        // 找到解
        if (nodes[head].right == head) {
            printSolution(depth);
            foundSolution = true;
            return;
        }
        
        // 选择列大小最小的列（启发式）
        int minSize = 0x3f3f3f3f, selectedCol = 0;
        for (int i = nodes[head].right; i != head; i = nodes[i].right)
            if (columnSize[i] < minSize) {
                minSize = columnSize[i];
                selectedCol = i;
            }
        
        removeColumn(selectedCol);
        
        // 尝试该列的所有行
        for (int i = nodes[selectedCol].down; i != selectedCol; i = nodes[i].down) {
            solution[depth] = i;
            
            // 移除该行覆盖的其他列
            for (int j = nodes[i].right; j != i; j = nodes[j].right)
                removeColumn(nodes[j].columnId);
            
            search(depth + 1);
            
            // 恢复该行覆盖的其他列
            for (int j = nodes[i].left; j != i; j = nodes[j].left)
                restoreColumn(nodes[j].columnId);
        }
        
        restoreColumn(selectedCol);
    }
    
    // 创建新节点
    int createNode(int up, int down, int left, int right) {
        nodes[nodeCount].up = up;
        nodes[nodeCount].down = down;
        nodes[nodeCount].left = left;
        nodes[nodeCount].right = right;
        
        // 更新相邻节点的指针
        nodes[up].down = nodes[down].up = nodes[left].right = nodes[right].left = nodeCount;

        return nodeCount++;
    }
    
    // 添加新行
    void addRow(int columns[], int colCount, int pieceId, int rotation, int posX, int posY) {
        int firstNode = 0, currentNode;
        
        for (int i = 0; i < colCount; i++) {
            nodes[nodeCount].columnId = columns[i];
            columnSize[columns[i]]++;
            
            // 设置额外数据
            nodes[nodeCount].pieceId = pieceId;
            nodes[nodeCount].rotation = rotation;
            nodes[nodeCount].posX = posX;
            nodes[nodeCount].posY = posY;
            
            if (i == 0)
                firstNode = createNode(nodes[nodes[columns[i]].columnId].up, 
                                      nodes[columns[i]].columnId, 
                                      nodeCount, nodeCount);
            else
                currentNode = createNode(nodes[nodes[columns[i]].columnId].up, 
                                        nodes[columns[i]].columnId, 
                                        nodes[firstNode].left, firstNode);
        }
    }
    
    // 初始化舞蹈链
    void initialize(int totalColumns) {
        nodeCount = 0;
        head = createNode(0, 0, 0, 0); // 创建头节点
        
        // 创建列头节点
        for (int i = 1; i <= totalColumns; i++) {
            createNode(i, i, nodes[head].left, head);
            nodes[i].columnId = i;
            columnSize[i] = 0;
        }
    }
} dlx;

// 检查位置是否有效
bool isValidPosition(int x, int y) {
    return x >= 0 && x < gridSize && y >= 0 && y < gridSize;
}

string inputBuffer[32767];

int main() {
    while (cin >> gridSize) {
        if (gridSize == 0) break;
        cin >> pieceCount;
        cin.ignore(1024, '\n');  // 清除换行符
        
        // 初始化舞蹈链：列数 = 网格单元格数 + 拼图块数
        dlx.initialize(gridSize * gridSize + pieceCount);
        
        // 读取输入
        int inputLineCount = 0;
        while (getline(cin, inputBuffer[inputLineCount])) {
            if (inputBuffer[inputLineCount].front() == '#') break;
            inputLineCount++;
        }
        
        memset(pattern, ' ', sizeof(pattern)); // 初始化模式数组
        
        int totalCells = 0;
        for (int pieceIdx = 0, inputIdx = 0; pieceIdx < pieceCount; pieceIdx++) {
            int rows = 0, cols = 0;
            char pieceChar = -1;
            
            // 读取拼图块字符
            for (int j = 0; j < inputBuffer[inputIdx].size(); j++)
                if (inputBuffer[inputIdx][j] >= '0' && inputBuffer[inputIdx][j] <= '9')
                    pieceChar = inputBuffer[inputIdx][j];
            
            // 读取拼图块形状
            for (rows = 0; ; rows++) {
                int hasPieceChar = 0;
                for (int j = 0; j < inputBuffer[inputIdx].size(); j++)
                    if (inputBuffer[inputIdx][j] == pieceChar)
                        hasPieceChar = 1;

                if (!hasPieceChar) break;
                
                for (int j = 0; j < inputBuffer[inputIdx].size(); j++)
                    if (inputBuffer[inputIdx][j] == pieceChar) {
                        pattern[pieceIdx][0][rows][j] = inputBuffer[inputIdx][j];
                        cols = max(cols, j + 1);
                        totalCells++;
                    }
                inputIdx++;
            }
            
            // 确保形状是正方形（便于旋转）
            rows = cols = max(rows, cols);
            
            // 生成旋转形态
            for (int rot = 1; rot < 4; rot++)
                for (int x = 0; x < rows; x++)
                    for (int y = 0; y < cols; y++)
                        pattern[pieceIdx][rot][x][y] = pattern[pieceIdx][rot-1][y][rows - 1 - x];
            
            // 为原始旋转（0°）生成所有可能的放置位置
            for (int rot = 0; rot < 1; rot++) {
                for (int posX = -20; posX <= gridSize; posX++) {
                    for (int posY = -20; posY <= gridSize; posY++) {
                        int valid = 1;
                        int columns[512], colCount = 0;
                        
                        // 检查该位置是否可以放置拼图块
                        for (int x = 0; x < rows && valid; x++) {
                            for (int y = 0; y < cols && valid; y++) {
                                if (pattern[pieceIdx][rot][x][y] != ' ') {
                                    valid &= isValidPosition(x + posX, y + posY);
                                    columns[colCount++] = (x + posX) * gridSize + (y + posY) + 1;
                                }
                            }
                        }
                        
                        // 如果可以放置，添加到舞蹈链
                        if (valid) {
                            columns[colCount++] = gridSize * gridSize + pieceIdx + 1;
                            dlx.addRow(columns, colCount, pieceIdx, rot, posX, posY);
                        }
                    }
                }
            }
        }
        
        // 搜索解
        memset(maxSum, 0, sizeof(maxSum));
        dlx.foundSolution = false;
        dlx.search(0);
        
        // 输出结果
        if (dlx.foundSolution)
            for (int i = 0; i < gridSize; i++) {
                for (int j = 0; j < gridSize; j++)
                    putchar(finalOutput[i][j]);
                cout << '\n';
            }
        cout << '\n';
    }
    return 0;
}
