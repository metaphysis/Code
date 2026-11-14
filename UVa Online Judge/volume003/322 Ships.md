[UVa 322 Ships](https://blog.csdn.net/metaphysis/article/details/154292321)

## 题目描述

海战棋是一个经典的双人对战游戏，双方在网格上布置船只，然后轮流猜测对方船只的位置进行攻击。在这个问题中，我们面临的是一个 $7$ 艘特殊船只的布局问题。

### 船只规格
游戏中有 $7$ 种不同的船只，每个船只占据 $4$ 个格子。船只可以旋转但不能镜像。具体的 $7$ 种船型包括：

- $2 \times 2$ 方块型
- 两种 $\texttt{Z}$  型（正 $\texttt{Z}$ 和反 $\texttt{Z}$）
- $\texttt{T}$ 型
- 两种 $\texttt{L}$ 型（互为镜像）
- 直线型（$4$ 格）

### 游戏状态
网格中的每个格子有三种状态：
- `x`：已知有船只覆盖
- `o`：已知没有船只（水）
- `.`：未知状态

### 问题要求
判断是否能够在最多翻到 $1$ 个 `o`（即最多一次"$\texttt{miss}$ "）的情况下，确定所有剩余的 `x` 位置。

## 解题思路

### 核心挑战
这个问题的难点在于需要处理组合爆炸的可能性。$7$ 艘船在 $16 \times 16$ 的网格上可能的布局方式非常多，必须设计高效的搜索和剪枝策略。

### 算法设计

#### 1. 船只表示与旋转处理
我们使用三维数组来表示船只的所有可能旋转状态：
```cpp
char ships[7][4][4][5];
```
其中：
- 第一维：$7$ 种船型
- 第二维：最多 $4$ 种旋转
- 第三、四维：$4 \times 4$ 的网格表示

对于每种船型，我们预计算其所有可能的旋转状态，并进行标准化处理（平移至左上角）。

#### 2. 深度优先搜索（$\texttt{DFS}$）
使用回溯算法尝试所有可能的船只布局：

**搜索策略：**
- 按船只类型顺序进行放置
- 对每个船只尝试所有位置和所有旋转
- 使用字符标记法（`'0' + depth`）来标记已放置的船只

**剪枝优化：**
- 当找到的解数量超过未知格子数量时提前终止
- 只检查能够放置船只的有效位置
- 在找到解时进行去重检查

#### 3. 唯一性判定算法
这是整个问题的核心创新点：

**基本思想：**
如果存在某个未知格子，在所有解中只有一个解该位置是水（`'o'`），那么：
- 如果翻到这个格子是水，就能排除这个唯一解
- 如果翻到这个格子是船，那么所有解在该位置都一致

**逐步消元过程：**
```python
while 存在变化:
    for 每个未知格子:
        统计在所有解中该格子为水的次数
        if 只有一个解中该格子是水:
            移除这个解
           标记存在变化
```

**终止条件：**
- 只剩一个解：可以确定所有船只位置
- 解数量为$0$或超过限制：无法确定
- 无法继续消元：需要多于 $1$ 次 $\texttt{miss}$ 

### 算法正确性证明

**定理：** 上述算法能够正确判断是否能在最多一次 $\texttt{miss}$  的情况下确定所有船只位置。

**证明：**
1. **完备性**：$\texttt{DFS}$ 搜索了所有可能的合法布局
2. **最优性**：逐步消元过程模拟了最优的翻牌策略
3. **正确性**：如果最终解数量$\leq 1$，说明存在翻牌序列能够在最多一次 $\texttt{miss}$ 的情况下确定布局


## 参考代码

```cpp
// Ships
// UVa ID: 322
// Verdict: Accepted
// Submission Date: 2025-11-01
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

char grid[16][17];           // 输入的游戏网格
char solutions[300][16][17]; // 存储所有可能的解
int solutionCount;          // 解的个数

// 每种船型的旋转数量
int rotations[7] = {1, 2, 2, 4, 4, 4, 2};

// 7种船型的定义，每种有最多4种旋转
char ships[7][4][4][5] = {
    // 1. 2x2方块
    {"xx  ", "xx  ", "    ", "    "},
    // 2. Z型1
    {"xx  ", " xx ", "    ", "    ", 
     " x  ", "xx  ", "x   ", "    "},
    // 3. Z型2  
    {" xx ", "xx  ", "    ", "    ",
     "x   ", "xx  ", " x  ", "    "},
    // 4. T型（4种旋转）
    {"x   ", "xxx ", "    ", "    ",
     "xx  ", "x   ", "x   ", "    ", 
     "xxx ", "  x ", "    ", "    ",
     " x  ", " x  ", "xx  ", "    "},
    // 5. L型1（4种旋转）
    {"  x ", "xxx ", "    ", "    ",
     "xx  ", " x  ", " x  ", "    ",
     "xxx ", "x   ", "    ", "    ",
     "x   ", "x   ", "xx  ", "    "},
    // 6. L型2（4种旋转）
    {" x  ", "xxx ", "    ", "    ",
     " x  ", "xx  ", " x  ", "    ",
     "xxx ", " x  ", "    ", "    ",
     "x   ", "xx  ", "x   ", "    "},
    // 7. 直线型（2种旋转）
    {"xxxx", "    ", "    ", "    ",
     "x   ", "x   ", "x   ", "x   "}
};

char backup[7][16][17]; // 用于回溯时保存状态

// 检查船型能否放置在指定位置
bool canPlace(int shipType, int rotation, int row, int col, int height, int width) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            // 只检查船体部分('x')
            if (ships[shipType][rotation][i][j] == 'x') {
                // 检查边界
                if (row + i >= height || col + j >= width) return false;
                // 检查网格是否可放置(只能是'.'或'x')
                if (grid[row + i][col + j] != '.' && grid[row + i][col + j] != 'x') return false;
            }
    return true;
}

// 深度优先搜索放置所有7艘船
void dfs(int depth, int height, int width, int dotCount) {
    // 剪枝：如果解的数量超过未知格子数量，提前返回
    if (solutionCount > dotCount) return;
    // 所有船都已放置完成
    if (depth == 7) {
        // 检查是否所有已知的'x'都被覆盖
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] == 'x') return;
            }
        }
        // 保存当前解：标记为船的位置存为'x'，其他为空格
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j] >= '0' && grid[i][j] <= '9') {
                    solutions[solutionCount][i][j] = 'x'; // 船的位置
                } else {
                    solutions[solutionCount][i][j] = ' '; // 水的位置
                }
            }
        }
        // 去重：检查是否与已有解重复
        for (int k = 0; k < solutionCount; k++) {
            bool isDuplicate = true;
            for (int i = 0; i < height && isDuplicate; i++) {
                for (int j = 0; j < width && isDuplicate; j++) {
                    if (solutions[k][i][j] != solutions[solutionCount][i][j]) {
                        isDuplicate = false;
                    }
                }
            }
            if (isDuplicate) return;
        }
        solutionCount++;
        return;
    }
    
    // 尝试所有可能的位置和旋转
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            // 尝试所有可能的旋转
            for (int rotation = rotations[depth] - 1; rotation >= 0; rotation--) {
                if (canPlace(depth, rotation, row, col, height, width)) {
                    // 保存当前状态并放置船
                    for (int i = 0; i < 4; i++) {
                        for (int j = 0; j < 4; j++) {
                            if (ships[depth][rotation][i][j] == 'x') {
                                backup[depth][row + i][col + j] = grid[row + i][col + j];
                                grid[row + i][col + j] = '0' + depth; // 用数字标记船
                            }
                        }
                    }
                    // 递归放置下一艘船
                    dfs(depth + 1, height, width, dotCount);
                    // 回溯：恢复原始状态
                    for (int i = 0; i < 4; i++)
                        for (int j = 0; j < 4; j++)
                            if (ships[depth][rotation][i][j] == 'x')
                                grid[row + i][col + j] = backup[depth][row + i][col + j];
                }
            }
        }
    }
}

// 检查是否能在最多一次miss的情况下确定所有船的位置
bool canDetermine(int height, int width, int dotCount) {
    solutionCount = 0;
    dfs(0, height, width, dotCount);
    
    // 如果只有一个解，直接可以确定
    if (solutionCount == 1) return true;
    // 如果解太多或没有解，无法确定
    if (solutionCount > dotCount || solutionCount == 0) return false;
    
    // 逐步消元：模拟翻牌过程
    bool changed;
    do {
        changed = false;
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                // 只检查未知格子
                if (grid[row][col] == '.') {
                    int waterCount = 0;    // 该位置为水的解的数量
                    int waterIndex = -1;   // 唯一为水的解的索引
                    
                    // 统计在所有解中该位置为水的次数
                    for (int i = 0; i < solutionCount; i++)
                        if (solutions[i][row][col] == ' ') {
                            waterCount++;
                            waterIndex = i;
                        }
                    
                    // 如果只有一个解中这里是水，翻到这个水就能排除这个解
                    if (waterCount == 1 && solutionCount > 1) {
                        // 移除这个解（用最后一个解覆盖它）
                        for (int i = 0; i < height; i++)
                            for (int j = 0; j < width; j++)
                                solutions[waterIndex][i][j] = solutions[solutionCount - 1][i][j];
                        solutionCount--;
                        changed = true;
                    }
                }
            }
        }
    } while (changed); // 继续直到没有变化
    return solutionCount < 2;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int width, height, testCase = 1;
    while (cin >> width >> height && width != 0) {
        int dotCount = 0;
        // 读取输入并统计未知格子数量
        for (int i = 0; i < height; i++) {
            cin >> grid[i];
            for (int j = 0; j < width; j++)
                if (grid[i][j] == '.') dotCount++;
        }
        cout << "Game #" << testCase++ << endl;
        if (canDetermine(height, width, dotCount)) cout << "yes.";
        else cout << "no.";
        cout << "\n\n";
    }
    return 0;
}
```

## 总结

本题通过巧妙的$\texttt{DFS}$搜索结合逐步消元策略，成功解决了海战棋游戏的布局确定问题。算法的核心创新在于将复杂的推理过程转化为可计算的逐步消元，使得我们能够在合理的时间内判断是否能在有限次尝试内确定所有船只位置。这种方法不仅适用于本题，还可以推广到其他类似的约束满足和推理问题中，展示了组合搜索与逻辑推理相结合的强大能力。
