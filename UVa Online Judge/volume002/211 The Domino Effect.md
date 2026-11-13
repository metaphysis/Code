[UVa 211 The Domino Effect](https://blog.csdn.net/metaphysis/article/details/161045135)

## 题目分析

本题使用一套标准的“双六”多米诺骨牌，共有 $28$ 张骨牌，每张骨牌上有两个数字（$0$ 到 $6$），所有组合唯一。题目给定一个 $7 \times 8$ 的点阵（每个格子是 $0$ 到 $6$ 的数字），这个点阵是由全部 $28$ 张骨牌不重叠、不遗漏地摆放而成的。需要找出所有可能的骨牌摆放方案，并输出对应的骨牌编号地图（每张骨牌有一个唯一的编号 $1$ 到 $28$）。

例如，标准骨牌列表中：
- 骨牌 $1$ 为 $(0,0)$，骨牌 $2$ 为 $(0,1)$，……，骨牌 $28$ 为 $(6,6)$。

输入包含多个测试用例，每个用例是一个 $7 \times 8$ 的点阵。输出每个用例的布局、所有可能的骨牌编号地图，以及方案总数。

## 解题思路

### 1. 骨牌列表预处理

根据题目描述，$28$ 张骨牌的组合是固定的：
- $(0,0), (0,1), (0,2), \dots, (0,6)$
- $(1,1), (1,2), \dots, (1,6)$
- ……
- $(6,6)$

可以预先计算出每个骨牌编号对应的两个数字，存到 `bone[28][2]` 中（注意骨牌编号从 $1$ 开始，但代码中使用 $0$ 索引方便，实际输出时加 $1$）。

### 2. 搜索策略

由于网格大小为 $7 \times 8 = 56$，恰好放置 $28$ 张骨牌，每张骨牌覆盖两个相邻格子（水平或竖直相邻）。需要找出所有合法摆放方式。

使用 **回溯法（$\texttt{DFS}$）**：
- 按骨牌编号顺序放置（从 $1$ 到 $28$）。
- 每次寻找第一个未被覆盖的格子 `(i, j)`，尝试将其与右边的格子或下边的格子配对，使得这两个格子上的数字与当前骨牌的数字匹配（顺序可颠倒）。
- 如果匹配成功，则在该位置标记当前骨牌编号，继续放置下一张骨牌。
- 如果放置完 $28$ 张骨牌，则找到一组解，输出骨牌编号地图。

### 3. 关键细节

- **方向数组**：只考虑向右 `(0,1)` 和向下 `(1,0)` 两个方向，因为按顺序遍历格子时，左侧和上方的格子已经被填充，避免了重复。
- **骨牌数字匹配**：骨牌的两个数字是无序的，因此只要 `(grid[i][j], grid[ii][jj])` 与 `(bone[matched][0], bone[matched][1])` 相等或顺序相反即可。
- **输出格式**：每个数字宽度为 $4$，使用 `setw(4)` 对齐。不同测试用例之间空三行，同一用例内的布局和地图之间空一行。

### 4. 复杂度分析

最坏情况下搜索空间较大，但由于骨牌数量固定且约束强，实际运行很快。本题在 UVa 上的运行时间约 $0.100$ 秒。

---

## 代码实现（带注释）

```cpp
// The Domino Effect
// UVa ID: 211
// Verdict: Accepted
// Submission Date: 2016-04-28
// UVa Run Time: 0.100s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

int grid[7][8];          // 存储输入的点阵数字
int board[7][8];         // 存储骨牌编号地图（0 表示未放置）
int bone[28][2];         // 骨牌列表，bone[i][0] 和 bone[i][1] 表示第 i+1 张骨牌的两个数字
int solutions;           // 当前布局的解的数量
int cases = 0;           // 布局编号

// 两个方向：右、下
int location[2][2] = { {0, 1}, {1, 0} };

// 回溯搜索，matched 表示已经成功放置的骨牌数量（即下一张要放的骨牌索引，从 0 开始）
void backtrack(int matched) {
    // 如果已经放完 28 张骨牌，输出一个解
    if (matched == 28) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 8; j++)
                cout << setw(4) << board[i][j];
            cout << "\n";
        }
        cout << "\n";

        solutions++;
        return;
    }

    // 按行优先顺序寻找第一个未被覆盖的格子
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j] == 0 &&  (grid[i][j] == bone[matched][0] || grid[i][j] == bone[matched][1])) {
                // 尝试向右或向下放置
                for (int m = 0; m < 2; m++) {
                    int ii = i + location[m][0];
                    int jj = j + location[m][1];

                    if (ii < 0 || jj < 0 || ii > 6 || jj > 7)
                        continue;

                    if (board[ii][jj] == 0 &&
                        ((grid[i][j] == bone[matched][0] && grid[ii][jj] == bone[matched][1]) ||
                         (grid[i][j] == bone[matched][1] && grid[ii][jj] == bone[matched][0]))) {
                        // 放置当前骨牌（编号为 matched+1）
                        board[i][j] = matched + 1;
                        board[ii][jj] = matched + 1;
                        backtrack(matched + 1);
                        // 回溯，撤销放置
                        board[i][j] = 0;
                        board[ii][jj] = 0;
                    }
                }
                // 注意：这里找到第一个未覆盖格子后，必须直接返回，因为按顺序摆放骨牌时，当前格子必须被这一张骨牌覆盖
                return;
            }
}

int main() {
    cin.tie(0);
    cin.sync_with_stdio(false);

    // 预处理骨牌列表，骨牌编号从 1 到 28
    // 生成规则：先固定较小数字，避免重复组合
    for (int i = 7, x = 0, y = 0, index = 0; i >= 1; i--, x++, y++)
        for (int j = y; j <= 6; j++, index++) {
            bone[index][0] = x;
            bone[index][1] = j;
        }

    int number, counter = 0;
    while (cin >> number) {
        grid[counter / 8][counter % 8] = number;
        counter++;

        // 当读满 56 个数字（一个完整布局）时进行处理
        if (counter == 56) {
            if (cases > 0)
                cout << "\n\n\n";   // 不同用例之间空三行

            cases++;
            cout << "Layout #" << cases << ":\n";
            cout << "\n";

            // 输出原始布局
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 8; j++)
                    cout << setw(4) << grid[i][j];
                cout << "\n";
            }
            cout << "\n";

            cout << "Maps resulting from layout #" << cases << " are:\n";
            cout << "\n";

            solutions = 0;
            memset(board, 0, sizeof(board));
            backtrack(0);

            cout << "There are " << solutions << " solution(s) for layout #" << cases << ".\n";
            counter = 0;
        }
    }

    return 0;
}
```

## 总结

本题的核心是**回溯法**与**状态标记**。通过预处理骨牌组合，按顺序寻找未覆盖格子并尝试两个方向放置，可以高效地枚举所有合法摆放方案。输出格式需要严格按照题目要求，包括对齐和空行间隔。
