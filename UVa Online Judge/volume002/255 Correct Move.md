[UVa 255 Correct Move](https://blog.csdn.net/metaphysis/article/details/161282912)

## 题目分析

这是一道关于国际象棋棋盘上王和后移动规则的模拟问题。题目描述了一个 $8 \times 8$ 的棋盘，格子编号从 $0$ 到 $63$，编号方式为逐行排列（第 $0$ 行：$0 \sim 7$，第 $1$ 行：$8 \sim 15$，依此类推）。

棋盘上有两个棋子：一个王（$\texttt{King}$）和一个后（$\texttt{Queen}$）。**状态** 定义为王的位置和后的位置组成的二元组 $(king, queen)$。当两个棋子不在同一格时，状态是 **合法的**。

### 移动规则

1. **王的移动**：可以上下左右移动 **恰好 $1$ 格**，但不能移动到后所在的位置。
2. **后的移动**：可以上下左右移动 **任意多格**（至少 $1$ 格），但不能越过王的位置（即路径上不能有王）。

### 额外限制（允许移动）

一个移动被称为 **允许的**，当且仅当：
- 移动本身是合法的；
- 移动的目标位置不是对方可以移动到的位置。

换句话说：王不能移动到后能走到的格子，后也不能移动到王能走到的格子。

### 问题要求

对于每组输入（包含三个整数：$king$, $queen$, $new\_queen$），需要依次判断：

1. 给定的状态是否合法（$king \neq queen$）？
2. 后的移动是否合法（后能否从当前位置合法地移动到 $new\_queen$）？
3. 后的移动是否允许（移动目标是否不在王的可移动范围内）？
4. 如果以上都满足，更新后的位置，判断在 **新状态** 下王是否被锁死（即王没有任何允许的移动）。

### 输出对应关系

| 条件 | 输出 |
|------|------|
| 状态不合法（$king = queen$） | $\texttt{Illegal state}$ |
| 状态合法，但后的移动不合法 | $\texttt{Illegal move}$ |
| 状态合法，后的移动合法，但不允许 | $\texttt{Move not allowed}$ |
| 状态合法，后的移动合法且允许，且新状态下王有允许的移动 | $\texttt{Continue}$ |
| 状态合法，后的移动合法且允许，但新状态下王无允许的移动 | $\texttt{Stop}$ |

---

## 解题思路

题目的核心在于正确实现三个判定函数：

1. **$\texttt{isLegalMove}$**：判断后的移动是否合法。
2. **$\texttt{isAllowedMove}$**：判断后的移动是否允许（即目标位置是否在王的一步可达位置内）。
3. **$\texttt{isStop}$**：判断在新状态下王是否被锁死。

### 棋盘坐标与编号转换

棋盘编号从 $0$ 到 $63$，第 $r$ 行第 $c$ 列的编号为 $r \times 8 + c$。

常用转换：
- 行号：$row = pos / 8$
- 列号：$col = pos \% 8$
- 同一行的格子范围：$[row \times 8, (row+1) \times 8 - 1]$
- 同一列的格子：$pos, pos \pm 8, pos \pm 16, \dots$

### 1. 判断后的合法移动（$\texttt{isLegalMove}$）

后的移动是 **直线** 的，分为四个方向：上、下、左、右。在每个方向上，后可以移动任意多格，但不能越过王的位置。

实现方法：
- 向上（列不变，行递减）：从 $queen - 8$ 开始，每次减 $8$，直到遇到王或超出棋盘边界。
- 向下（列不变，行递增）：从 $queen + 8$ 开始，每次加 $8$。
- 向左（行不变，列递减）：从 $queen - 1$ 开始，每次减 $1$，但不能跨行（即左边界为当前行的最左列）。
- 向右（行不变，列递增）：从 $queen + 1$ 开始，每次加 $1$，但不能跨行（即右边界为当前行的最右列）。

在这些方向上收集所有可以到达的格子（不包括被王阻挡之后的格子），然后检查 $move$ 是否在集合中。

**注意**：由于王可能位于后的移动路径上，需要提前终止该方向的搜索。

### 2. 判断后的移动是否允许（$\texttt{isAllowedMove}$）

后的移动 **允许** 当且仅当目标位置 $move$ 不是王的一步可达位置。

王的一步可达位置（曼哈顿距离为 $1$ 且在同一行或同一列）：
- 上：$king - 8$（如果 $king - 8 \ge 0$）
- 下：$king + 8$（如果 $king + 8 < 64$）
- 左：$king - 1$（如果 $king$ 不在最左列，即 $king \% 8 \neq 0$）
- 右：$king + 1$（如果 $king$ 不在最右列，即 $(king \% 8) \neq 7$）

如果 $move$ 等于上述任一位置，则后的移动不允许；否则允许。

### 3. 判断王是否被锁死（$\texttt{isStop}$）

在新的状态（王位置不变，后位置变为 $move$）下，判断王是否有任何允许的移动。

首先，确定王的所有合法移动位置（上下左右各一步，且不能与后位置重合）。

然后，需要排除 **后能走到的格子**。注意：这里“后能走到的格子”是指在 **新状态** 下，后从新位置出发可以走到的所有格子（包括新位置本身？注意题目描述：后不能移动到王的位置，但王也不能移动到后能走到的位置。实际上，后移动时不能“遇到”王，但后占据的位置本身，王是不能进入的。因此，在判断王的允许移动时，需要排除：
- 后的新位置本身（因为两个棋子不能在同一格）
- 后从新位置出发，沿四个方向直线可以到达的所有格子（同样，遇到王时停止，因为王的阻挡会使后不能到达更远的格子）

实现方法：
- 收集后的“势力范围”：向上、向下、向左、向右直线延伸，遇到王则停止（不包括王本身，因为王在格子上，后不能越过）。
- 然后检查王的四个可能移动位置，如果任何一个位置 **不在** 后的势力范围内，并且该位置在棋盘内，且不是后本身，则王有允许的移动，返回 $\texttt{false}$（不是 Stop）。
- 否则返回 $\texttt{true}$（王被锁死，是 Stop）。

---

## 代码实现

```cpp
// Correct Move
// UVa ID: 255
// Verdict: Accepted
// Submission Date: 2016-05-12
// UVa Run Time: 0.110s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 判断后的移动是否合法
bool isLegalMove(int king, int queen, int move) {
    set<int> next;  // 存储后可以合法移动到的所有位置
    
    // 向上移动（列不变，行递减）
    for (int i = queen - 8; i >= 0; i -= 8) {
        if (i == king)      // 遇到王，不能越过，停止
            break;
        next.insert(i);
    }
    
    // 向下移动（列不变，行递增）
    for (int i = queen + 8; i < 64; i += 8) {
        if (i == king)      // 遇到王，停止
            break;
        next.insert(i);
    }
    
    // 向左移动（行不变，列递减，不能跨行）
    for (int i = queen - 1; i >= (queen / 8) * 8; i--) {
        if (i == king)      // 遇到王，停止
            break;
        next.insert(i);
    }
    
    // 向右移动（行不变，列递增，不能跨行）
    for (int i = queen + 1; i < (queen / 8 + 1) * 8; i++) {
        if (i == king)      // 遇到王，停止
            break;
        next.insert(i);
    }
    
    // 检查目标位置是否在合法移动集合中
    return next.count(move) > 0;
}

// 判断后的移动是否允许（即目标位置不能是王一步能到的位置）
bool isAllowedMove(int king, int move) {
    // 检查王的上方
    if ((king - 8) >= 0 && (king - 8) == move) return false;
    
    // 检查王的下方
    if ((king + 8) < 64 && (king + 8) == move) return false;
    
    // 检查王的左方（注意不能跨行）
    if ((king - 1) >= (king / 8 * 8) && (king - 1) == move) return false;
    
    // 检查王的右方
    if ((king + 1) < ((king / 8 + 1) * 8) && (king + 1) == move) return false;
    
    return true;
}

// 判断在新状态下王是否被锁死（没有任何允许的移动）
bool isStop(int king, int queen) {
    set<int> disallowed;  // 存储后能走到的所有格子（包括后本身）
    
    // 向上收集后的势力范围
    for (int i = queen; i >= 0; i -= 8)
        disallowed.insert(i);
    
    // 向下收集后的势力范围
    for (int i = queen; i < 64; i += 8)
        disallowed.insert(i);
    
    // 向左收集后的势力范围
    for (int i = (queen / 8) * 8; i < (queen / 8 + 1) * 8; i++)
        disallowed.insert(i);
    
    // 检查王的上方是否可走
    if ((king - 8) >= 0 && disallowed.count((king - 8)) == 0)
        return false;
    
    // 检查王的下方是否可走
    if ((king + 8) < 64 && disallowed.count((king + 8)) == 0)
        return false;
    
    // 检查王的左方是否可走
    if ((king - 1) >= (king / 8 * 8) && disallowed.count((king - 1)) == 0)
        return false;
    
    // 检查王的右方是否可走
    if ((king + 1) < ((king / 8 + 1) * 8) && disallowed.count((king + 1)) == 0)
        return false;
    
    // 四个方向都不可走，则王被锁死
    return true;
}

int main() {
    cin.tie(0);
    cout.sync_with_stdio(false);
    
    int king, queen, move;
    while (cin >> king >> queen >> move) {
        // 1. 检查状态是否合法
        if (king == queen) {
            cout << "Illegal state\n";
            continue;
        }
        
        // 2. 检查后的移动是否合法
        if (isLegalMove(king, queen, move) == false) {
            cout << "Illegal move\n";
            continue;
        }
        
        // 3. 检查后的移动是否允许
        if (isAllowedMove(king, move) == false) {
            cout << "Move not allowed\n";
            continue;
        }
        
        // 4. 更新后的位置，判断王是否被锁死
        queen = move;
        
        if (isStop(king, queen)) cout << "Stop\n";
        else cout << "Continue\n";
    }
    
    return 0;
}
```

---

## 总结

本题的关键在于准确理解三种判定逻辑：

- **合法移动**：后的直线路径不被王阻挡。
- **允许移动**：后的目标位置不与王的可移动位置冲突。
- **锁死判定**：在新状态下，王的所有可能移动位置都在后的攻击范围内。

代码实现时注意边界条件（棋盘边缘、行边界）以及王作为障碍物对后移动的影响。使用 $\texttt{set}$ 来存储后的可达位置可以简化判断逻辑。
