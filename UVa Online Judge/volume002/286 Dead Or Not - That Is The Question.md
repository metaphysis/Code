[UVa 286 Dead Or Not - That Is The Question](https://blog.csdn.net/metaphysis/article/details/161361455)

## 题目分析

本题是一道国际象棋中的 **“将死”** 判定问题。给定一个 $8 \times 8$ 的标准棋盘，棋盘上只有一个黑王（用 `K` 表示），其余 $63$ 个格子可以放置任意数量（$0$ 到 $63$）的白色棋子。白色棋子包括：

- 兵（`b`）
- 车（`t`）
- 马（`s`）
- 象（`1`）
- 后（`d`）
- 王（`k`）

题目输入是一个长度为 $64$ 的字符串，按行优先顺序表示棋盘状态（从 `a1` 到 `h8`）。白色棋子向上移动（即从第 $1$ 行向第 $8$ 行推进）。输入包含多组数据，直到 $\texttt{EOF}$ 结束。

需要判断的状态有三种：

1. **$\texttt{checkmate}$**：黑王当前被将军（处于被攻击状态），并且所有可能的移动目标格子也都被攻击，无法逃脱。
2. **$\texttt{draw}$**：黑王当前未被将军，但所有可以移动到的格子都被攻击（无路可走）。
3. **$\texttt{game is not over}$**：黑王当前未被将军，且存在至少一个可以安全移动的格子。

## 解题思路

题目的核心在于 **判断黑王是否处于被攻击状态**，以及 **判断黑王移动到相邻格子后是否会被攻击**。

### 1. 棋盘表示

由于输入是一个长度为 $64$ 的字符串，按行优先存储（第 $1$ 行是 `a1` 到 `h1`，第 $2$ 行是 `a2` 到 `h2`，以此类推）。为了方便处理，将字符串转换为二维数组 `chessboard[8][8]`，其中第一维表示行（$0$ 到 $7$，对应第 $1$ 行到第 $8$ 行），第二维表示列（$0$ 到 $7$，对应 `a` 列到 `h` 列）。

### 2. 攻击判定函数 `check`

函数 `check(blackKingX, blackKingY)` 用于判断在 **当前棋盘布局** 下，位于 `(blackKingX, blackKingY)` 的黑王是否被任意白色棋子攻击。

攻击判定需要分别处理不同类型棋子的攻击方式：

#### （1）水平和垂直方向（车、后、王的攻击）

沿着上、下、左、右四个方向（对应偏移数组的前 $4$ 个方向）逐格检查：

- 遇到空格则继续向前。
- 遇到白色车（`r`）或白色后（`q`）则返回 `true`（被攻击）。
- 遇到白色王（`k`）且距离为 $1$ 格（即相邻）则返回 `true`。
- 遇到其他棋子则停止该方向检查。

#### （2）对角线方向（象、后、兵、王的攻击）

沿着左上、右上、左下、右下四个对角线方向（对应偏移数组的第 $4$ 到第 $7$ 个方向）逐格检查：

- 遇到空格则继续向前。
- 遇到白色象（`b`）或白色后（`q`）则返回 `true`。
- 遇到白色兵（`p`）且距离为 $1$ 格并且兵的位置 **在** 黑王的下方（即兵的 $x$ 坐标小于黑王的 $x$ 坐标，因为白色向上移动）则返回 `true`（兵斜前方吃子）。
- 遇到白色王（`k`）且距离为 $1$ 格则返回 `true`。
- 遇到其他棋子则停止。

#### （3）马（骑士）的攻击

马走“日”字形，共有 $8$ 个可能的攻击位置（对应偏移数组的第 $8$ 到第 $15$ 个方向）。检查这些位置是否存在白色马（`n`），若存在则返回 `true`。

### 3. 将死与逼和判定

#### 步骤一：获取黑王当前位置

遍历棋盘，找到 `K` 的位置 `(blackKingX, blackKingY)`。

#### 步骤二：判断当前是否被将军

调用 `check(blackKingX, blackKingY)`，将结果存入 `checkmate` 变量。注意变量命名：这里的 `checkmate` 实际上是“当前是否被将军”的含义，而非最终输出。

#### 步骤三：判断所有合法移动是否安全

将黑王从当前位置临时移除（棋盘上该位置设为空格），然后尝试向 $8$ 个相邻方向移动（对应偏移数组的前 $8$ 个方向，即上下左右 + 四个对角）：

- 如果目标格子超出棋盘边界则跳过。
- 将黑王移动到目标位置，调用 `check` 判断该位置是否被攻击。
- 若发现任意一个移动目标位置未被攻击，则说明存在安全移动，将标志 `next_checkmate` 设为 `false` 并跳出循环。

注意：移动判定时不需要考虑移动后是否会与己方棋子重叠，因为题目保证黑王是唯一的黑方棋子，且白色棋子不会与黑王初始位置重叠。同时，由于题目说明白王不会与黑王相邻，且移动时实际上是将黑王临时放置到目标格子，可能会与原有白色棋子重叠，但题目保证不会出现这种非法情况（因为相邻关系已保证）。

#### 步骤四：输出结果

根据 `checkmate` 和 `next_checkmate` 的状态组合输出：

| 当前被将军 (`checkmate`) | 存在安全移动 (`next_checkmate` 为 `false`) | 输出 |
| :---: | :---: | :---: |
| `true` | `true`（无安全移动） | `checkmate` |
| `false` | `true`（无安全移动） | `draw` |
| `false` 或 `true` | `false`（有安全移动） | `game is not over` |

更简洁的逻辑：

- 如果当前被将军且所有移动都被攻击 → $\texttt{checkmate}$
- 如果当前未被将军且所有移动都被攻击 → $\texttt{draw}$
- 否则 → $\texttt{game is not over}$

### 4. 注意事项

根据题目补充说明（代码注释中提到）：

- 兵位于第 $8$ 行时，**不需要** 考虑其升变为其他棋子，仍按普通兵处理。
- 输入按行优先顺序：第 $1$ 行为 `a1` 到 `h1`，第 $2$ 行为 `a2` 到 `h2`，以此类推。代码中的索引转换 `i / 8` 为行号，`i % 8` 为列号，符合此约定。

## 代码实现

```cpp
// Dead Or Not - That Is The Question
// UVa ID: 286
// Verdict: Accepted
// Submission Date: 2016-06-04
// UVa Run Time: 0.120s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

// The problem statement is not so clear.
// When a pawn is in the 8th row, do I have to count it as any potentially promoted piece?
// NO, you can assume that potential promotion already took place. so, a pawn in the 8th row is just a pawn.
// The input is given as row by row, first a1 - h1, then a2 - h2, etc.

#include <bits/stdc++.h>

using namespace std;

// 棋盘，8行8列
char chessboard[8][8];

// 移动方向偏移数组
// 前4个：上下左右（车、后、王的直线移动）
// 第4到第7个：四个对角线方向（象、后、兵、王的斜线移动）
// 第8到第15个：马（骑士）的8个日字移动方向
int offset[16][2] = {
    {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {-1, -1}, {1, -1}, {1, 1}, {-1, 1},
    {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}
};

// 判断位于 (blackKingX, blackKingY) 的黑王是否被白色棋子攻击
bool check(int blackKingX, int blackKingY)
{
    // 水平和垂直方向：检查车、后以及相邻的王
    for (int i = 0; i < 4; i++)
    {
        int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
        int step = 0;  // 记录距离步数
        while (x >= 0 && y >= 0 && x < 8 && y < 8)
        {
            step++;
            // 空格则继续向前移动
            if (chessboard[x][y] == ' ')
            {
                x += offset[i][0], y += offset[i][1];
                continue;
            }
            
            // 遇到白色车或白色后，被攻击
            if (chessboard[x][y] == 'r' || chessboard[x][y] == 'q')
                return true;
            
            // 遇到白色王且距离为1（相邻），被攻击
            if (chessboard[x][y] == 'k' && step == 1)
                return true;
                    
            break;  // 遇到其他棋子则停止该方向
        }
    }
    
    // 对角线方向：检查象、后、兵以及相邻的王
    for (int i = 4; i < 8; i++)
    {
        int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
        int step = 0;
        while (x >= 0 && y >= 0 && x < 8 && y < 8)
        {
            step++;
            
            if (chessboard[x][y] == ' ')
            {
                x += offset[i][0], y += offset[i][1];
                continue;
            }
                
            // 遇到白色象或白色后，被攻击
            if (chessboard[x][y] == 'b' || chessboard[x][y] == 'q')
                return true;
            
            // 遇到白色兵，距离为1，且兵的位置在黑王的下方（白色向上移动，兵斜前吃子）
            if (chessboard[x][y] == 'p' && step == 1 && x < blackKingX)
                return true;
                
            // 遇到白色王且距离为1，被攻击
            if (chessboard[x][y] == 'k' && step == 1)
                return true;
                    
            break;
        }
    }
    
    // 马（骑士）的攻击：检查8个日字形位置
    for (int i = 8; i < 16; i++)
    {
        int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
        if (x >= 0 && y >= 0 && x < 8 && y < 8)
        { 
            if (chessboard[x][y] == 'n')
                return true;
        }
    }
    
    return false;  // 所有方向均未被攻击
}

int main(int argc, char *argv[])
{
    string line;
    while (getline(cin, line))
    {
        int blackKingX, blackKingY;
        
        // 将输入字符串转换为棋盘二维数组，并记录黑王位置
        for (int i = 0; i < line.length(); i++)
        {
            chessboard[i / 8][i % 8] = line[i];
            if (line[i] == 'K')
            {
                blackKingX = i / 8;
                blackKingY = i % 8;
            }
        }
        
        // 判断黑王当前位置是否被将军
        bool checkmate = check(blackKingX, blackKingY);
        
        // 判断黑王是否所有合法移动的目标格子都被攻击
        bool next_checkmate = true;  // 初始假设所有移动都不安全
        chessboard[blackKingX][blackKingY] = ' ';  // 临时移除黑王
        
        // 遍历8个相邻方向
        for (int i = 0; i < 8; i++)
        {
            int x = blackKingX + offset[i][0], y = blackKingY + offset[i][1];
            if (x >= 0 && y >= 0 && x < 8 && y < 8)
            {
                next_checkmate = check(x, y);  // 判断该移动目标是否被攻击
                if (!next_checkmate)  // 只要找到一个安全位置，立即停止
                    break;
            }
        }
        
        // 根据状态输出结果
        if (checkmate && next_checkmate)
            cout << "checkmate" << endl;
        else if (!checkmate && next_checkmate)
            cout << "draw" << endl;
        else
            cout << "game is not over" << endl;
    }
    return 0;
}
```
