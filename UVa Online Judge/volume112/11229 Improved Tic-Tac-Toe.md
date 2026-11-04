
> **摘要**：本文讨论一道带概率因素的井字棋博弈题。棋盘固定为 $3 \times 3$，玩家落子前需答题，答对则放置自己的符号、答错则放置对手符号，双方均按最优策略行动。文章用三进制整数编码棋盘状态，定义 $\texttt{dfs}(\textit{state}, \textit{turn})$ 返回先手最终获胜概率，结合记忆化搜索与 $\texttt{minimax}$ 思想处理随机转移，时间复杂度 $\mathcal{O}(9 \cdot 3^9)$。

## 题目描述

迪迪和德德是两个喜欢玩经典井字棋的孩子，但期末考试即将来临。为了既能玩游戏又能学习，他们设计了一个改进版：  
- 棋盘仍是 $3 \times 3$，初始为空，玩家轮流选择空格。  
- 每个格子对应一门学科，玩家选择该格后会被随机问一道该学科的题目。  
  - 若答对，则在该格放置自己的符号（先手为 `O`，后手为 `X`）；  
  - 若答错，则在该格放置对手的符号。  
- 胜利条件与经典版相同：先连成一行、一列或任意一条对角线（主对角线或副对角线）的玩家获胜。若棋盘填满仍未分出胜负，则为平局。  

他们知道对方在每个格子上的答对概率（以百分比给出），且两人都会**最优地**选择落子位置：  
- 先手的目标是**尽量获胜**；  
- 后手的目标是**尽量不输**（即避免先手获胜，平局也可接受）。  

## 输入格式

第一行一个整数 $T$（$1 \le T \le 50$），表示测试用例数。  
每个测试用例先有一个空行（可忽略）。  
接下来给出两个 $3 \times 3$ 的整数矩阵，分别表示先手和后手在每个格子上的答对概率（$0 \sim 100$，含端点）。每个矩阵按行给出，每行三个整数。

## 输出格式

对于每个测试用例，输出一行 `Case #C: X.XX`，其中 $C$ 为用例编号，$X.XX$ 为先手最终获胜的概率（百分比），四舍五入保留两位小数。

## 样例

**输入**

```
5

000 000 000
100 100 100
100 100 100
100 100 100
100 0 0
100 0 0
100 0 0
0 100 100
0 100 100
0 100 100
50 50 50
50 50 50
50 50 50
50 50 50
50 50 50
50 50 50
50 0 0
50 0 0
50 0 0
0 100 100
0 100 100
0 100 100
100 100 100
100 100 100
100 100 100
100 100 100
100 100 100
100 100 100
```

**输出**

```
Case #1: 0.00
Case #2: 100.00
Case #3: 47.46
Case #4: 12.50
Case #5: 0.00
```

## 题目分析

本题是一个带有概率因素的完全信息博弈问题。棋盘大小固定为 $3 \times 3$，状态空间极小（每个格子有三种状态：空、先手符号、后手符号），因此可以直接对整个博弈树进行深度优先搜索，并利用记忆化避免重复计算。

核心难点在于：每个动作的结果不是确定的，而是以一定概率落子成功或失败，因此当前玩家的决策必须基于期望收益。先手希望最大化自己的最终获胜概率，后手则希望最小化先手的获胜概率（即最大化自己不输的概率，等价于最小化对手的胜率）。

由于棋盘最多 $9$ 步走完，且每个状态只有 $9$ 个可选动作，暴力递归完全可行。关键在于正确建模状态转移以及最优决策准则。

## 解题思路

### 状态表示

棋盘状态可以用一个三进制整数编码：  
- 位置 $i$（$0 \le i < 9$）的值：$0$ 表示空，$1$ 表示先手棋子，$2$ 表示后手棋子。  
- 三进制编码：$\textit{state} = \sum_{i=0}^{8} \textit{sym}_i \cdot 3^i$，其中 $\textit{sym}_i \in \{0,1,2\}$。  
- 总状态数为 $3^9 = 19683$，非常小。

### 递归函数定义

定义 $\texttt{dfs}(\textit{state}, \textit{turn})$ 表示在给定棋盘状态 $\textit{state}$ 下，轮到玩家 $\textit{turn}$（$0$ 表示先手，$1$ 表示后手）行动时，**先手最终获胜的概率**（取值 $0 \sim 1$）。

- **终止条件**：  
  - 若当前棋盘已有玩家连成一条线，则直接返回结果（先手赢则 $1$，否则 $0$）。  
  - 若棋盘已满且无人获胜，则平局，返回 $0$。

- **转移过程**：  
  当前玩家 $\textit{turn}$ 枚举所有空格 $pos$。对于每个空格：  
  - 当前玩家答对该格的概率为 $p$（若 $\textit{turn}=0$ 则使用先手概率数组，否则使用后手概率数组）。  
  - 若答对，则该格放置当前玩家的符号（$\textit{playerSym} = \textit{turn}+1$），生成新状态 $\textit{ns}_\text{correct}$。  
  - 若答错，则该格放置对手的符号（$\textit{otherSym} = 3 - \textit{playerSym}$），生成新状态 $\textit{ns}_\text{wrong}$。  
  - 对两种新状态，若已分出胜负则直接取对应的 $0$ 或 $1$，否则递归调用 $\texttt{dfs}(\textit{newState}, 1-\textit{turn})$。  
  - 该动作的期望胜率：$E = p \cdot V_{\text{correct}} + (1-p) \cdot V_{\text{wrong}}$。

- **决策准则**：  
  - 先手（$\textit{turn}=0$）会选择使 $E$ **最大**的空格。  
  - 后手（$\textit{turn}=1$）会选择使 $E$ **最小**的空格（因为 $E$ 是先手的胜率，后手希望它最小）。

### 记忆化

由于同一个状态可能通过不同路径到达，使用二维数组 $\textit{memo}[\textit{state}][\textit{turn}]$ 存储已计算结果，并用 $\textit{visited}$ 标记是否计算过，避免重复递归。

### 复杂度分析

- 状态数：$2 \times 3^9 = 39366$。  
- 每个状态最多枚举 $9$ 个空格，每个动作计算常数次递归，总时间复杂度 $\mathcal{O}(9 \cdot 3^9)$，空间复杂度 $\mathcal{O}(3^9)$。  
- 完全满足 $T \le 50$ 的要求。

## 代码实现

```cpp
// Improved Tic-Tac-Toe
// UVa ID: 11229
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.520s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAX_STATE = 19683;   // 3^9

int pow3[9];
double prob1[9], prob2[9];
double memo[MAX_STATE][2];
bool visited[MAX_STATE][2];

// 获取 state 中位置 pos 的符号 (0空,1先手,2后手)
inline int getSym(int state, int pos) {
    return (state / pow3[pos]) % 3;
}

// 在 state 的 pos 位置放置符号 sym (1或2)，要求原位置为空
inline int setSym(int state, int pos, int sym) {
    return state + sym * pow3[pos];
}

// 检查棋盘是否已满
inline bool isFull(int state) {
    for (int i = 0; i < 9; ++i)
        if (getSym(state, i) == 0) return false;
    return true;
}

// 检查胜利者，返回 0 无胜者，1 先手胜，2 后手胜
int checkWin(int state) {
    const int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},  // 行
        {0,3,6}, {1,4,7}, {2,5,8},  // 列
        {0,4,8}, {2,4,6}            // 对角线
    };
    for (int i = 0; i < 8; ++i) {
        int a = getSym(state, lines[i][0]);
        int b = getSym(state, lines[i][1]);
        int c = getSym(state, lines[i][2]);
        if (a != 0 && a == b && b == c) return a;
    }
    return 0;
}

// dfs 返回当前状态下先手胜率 (0~1)
double dfs(int state, int turn) {
    int win = checkWin(state);
    if (win != 0) return (win == 1 ? 1.0 : 0.0);
    if (isFull(state)) return 0.0;
    if (visited[state][turn]) return memo[state][turn];
    visited[state][turn] = true;
    int playerSym = turn + 1;       // 1 或 2
    int otherSym = 3 - playerSym;
    double best = (turn == 0 ? 0.0 : 1.0);   // 先手最大化，后手最小化
    for (int pos = 0; pos < 9; ++pos) {
        if (getSym(state, pos) != 0) continue;
        // 答对分支：放置当前玩家符号
        int nsCorrect = setSym(state, pos, playerSym);
        int winC = checkWin(nsCorrect);
        double valC;
        if (winC != 0) valC = (winC == 1 ? 1.0 : 0.0);
        else valC = dfs(nsCorrect, 1 - turn);
        // 答错分支：放置对手符号
        int nsWrong = setSym(state, pos, otherSym);
        int winW = checkWin(nsWrong);
        double valW;
        if (winW != 0) valW = (winW == 1 ? 1.0 : 0.0);
        else valW = dfs(nsWrong, 1 - turn);
        double prob = (turn == 0 ? prob1[pos] : prob2[pos]);   // 答对概率
        double expected = prob * valC + (1.0 - prob) * valW;
        if (turn == 0) {
            if (expected > best) best = expected;
        } else {
            if (expected < best) best = expected;
        }
    }

    memo[state][turn] = best;
    return best;
}

int main() {
    // 预计算 3 的幂
    pow3[0] = 1;
    for (int i = 1; i < 9; ++i) pow3[i] = pow3[i-1] * 3;
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        // 读取先手概率网格（9个整数）
        for (int i = 0; i < 9; ++i) { cin >> prob1[i]; prob1[i] /= 100.0; }
        // 读取后手概率网格
        for (int i = 0; i < 9; ++i) { cin >> prob2[i]; prob2[i] /= 100.0; }
        // 清空记忆化标记
        for (int s = 0; s < MAX_STATE; ++s)
            for (int t = 0; t < 2; ++t)
                visited[s][t] = false;
        double ans = dfs(0, 0) * 100.0;   // 转换成百分比
        cout << "Case #" << tc << ": " << fixed << setprecision(2) << ans << "\n";
    }
    return 0;
}
```

## 总结

本题的核心技巧在于将有限状态博弈转化为带记忆化的递归搜索，并正确处理概率转移与最优决策。主要收获包括：

- 三进制编码能够紧凑表示有限棋盘状态，便于存储和记忆化。  
- 在存在随机性的博弈中，采用期望收益作为评价标准，先手最大化、后手最小化，符合零和博弈的 $\texttt{minimax}$ 思想。  
- 小状态空间下直接搜索是可行且高效的，避免了复杂的策略推导。  
- 注意概率读入为整数百分比，计算前需转换为 $[0,1]$ 的小数。  

本题也体现了 “状态压缩 + 搜索” 在解决组合博弈问题中的通用性。
