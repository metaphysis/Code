## 题目描述

$\texttt{Domino}$ 游戏采用 $28$ 张多米诺骨牌，每张牌的两面分别标有数字 $0$ 到 $6$。两面数字相同的牌称为双块。游戏由两名玩家（$\texttt{Red}$ 和 $\texttt{Green}$）进行，双方各获得 $n$ 张牌，且牌堆不重复。

游戏开始时，拥有最大数字双块的玩家先手，将该双块放置在桌面中央，形成一条链，链的两端称为“极端”。此后双方轮流行动，每次行动时，当前玩家必须从自己剩余的牌中选出一张，将其放置在链的某一端，使得该牌与极端相邻的那一面的数字与极端数字相同。放置后，牌的另一面成为新的极端。若当前玩家没有任何牌能与任一极端匹配，则必须跳过该回合。

胜利条件：率先将自己手中所有牌全部放完的玩家获胜。

给定双方的初始牌组，需要判断：
- 只有 $\texttt{Red}$ 可能获胜；
- 只有 $\texttt{Green}$ 可能获胜；
- 双方均可能获胜；
- 双方均不可能获胜。

本题并非寻找必胜策略，而是判断每位玩家是否存在至少一条合法的出牌路径，使其最终获胜。

## 输入格式

输入包含多个测试用例，每个测试用例占一行，格式为：

```
n r11 r12 r21 r22 ... rn1 rn2 g11 g12 ... gn1 gn2
```

其中：
- $n$（$1 \le n \le 14$）表示 $\texttt{Red}$ 和 $\texttt{Green}$ 各自获得的牌数；
- $r_{i1} \, r_{i2}$ 表示 $\texttt{Red}$ 的第 $i$ 张牌的两个数字；
- $g_{i1} \, g_{i2}$ 表示 $\texttt{Green}$ 的第 $i$ 张牌的两个数字；
- 所有牌均不重复；
- 至少有一名玩家拥有一张双块；
- 每个数字均为 $0$ 到 $6$ 的整数。

数字之间可由任意数量的空白字符分隔。相邻测试用例之间无空行。输入以一行 $n = 0$ 结束。

## 输出格式

对于每个测试用例，输出一行，内容为以下四种消息之一：

- `Only player Red can win`
- `Only player Green can win`
- `Both players can win`
- `No players can win`

两个连续测试用例的输出之间用一个空行隔开。

## 样例

输入

```
1 6 6 0 0
2 5 5 3 4 1 5 3 5
2 1 1 2 2 3 3 4 4
1 4 5 4 4
0
```

输出

```
Only player Red can win

Both players can win

No players can win

Only player Green can win
```

## 题目分析

游戏的状态由以下要素决定：
- 当前链的两个极端数字（左端和右端）；
- 当前轮到哪名玩家行动；
- $\texttt{Red}$ 和 $\texttt{Green}$ 各自剩余的牌（用位掩码表示，共 $28$ 张牌）。

由于 $n \le 14$，双方总牌数为 $2n \le 28$，恰好等于全部牌的数量，因此每个玩家的剩余牌集合可以表示为一个 $28$ 位的二进制掩码。

游戏过程是一个确定性的状态转移过程：每个状态下，当前玩家从自己的剩余牌中枚举所有能与左端或右端匹配的牌，放置后产生新状态；若没有可用的牌，则跳过回合。游戏终止于某玩家手中的牌数为 $0$。

我们需要判断的是：从初始状态出发，是否存在一条状态转移路径，使得 $\texttt{Red}$ 最终出完所有牌；以及是否存在一条路径，使得 $\texttt{Green}$ 最终出完所有牌。这两者可以独立判断。

由于状态空间有限（虽然 $2^{28}$ 理论上很大，但实际可达状态数受牌数和链形态限制，在 $n \le 14$ 时完全可枚举），可以使用广度优先搜索（$\texttt{BFS}$）遍历所有可达状态，分别检查是否能够到达红方或绿方获胜的终止状态。

## 解题思路

### 状态表示

将 $28$ 张牌分别编号为 $0$ 到 $27$，并建立数字对到编号的映射。每张牌记录其两个数字（无序）。

定义结构体 $\textit{State}$ 包含：
- `left`、`right`：当前链两端的数字；
- `turn`：当前行动玩家（$0$ 表示 $\texttt{Red}$，$1$ 表示 $\texttt{Green}$）；
- `maskR`、`maskG`：各自剩余牌的位掩码（$28$ 位，某位为 $1$ 表示该牌仍在手中）。

### 初始状态

首先从双方的牌中找出数字最大的双块。由于题目保证至少有一名玩家拥有双块，因此可以唯一确定拥有该双块的玩家（若最大双块数字相同，则只可能有一张，因为牌不重复）。该玩家作为先手，必须首先放置此双块。

放置后，链的两端数字均为该双块上的数字，且该牌从先手玩家的掩码中移除。当前行动玩家切换为对方。

### 广度优先搜索（$\texttt{BFS}$）

分别对 $\texttt{Red}$ 和 $\texttt{Green}$ 作为目标玩家执行一次 $\texttt{BFS}$，判断是否存在获胜路径。

$\texttt{BFS}$ 从初始状态开始，用队列扩展所有可达状态。使用哈希集合记录已访问状态，避免重复扩展。

对于每个出队状态：
1. 若 `maskR == 0`，则 $\texttt{Red}$ 已出完所有牌，此时若目标为 $\texttt{Red}$ 则返回 `true`，否则继续（但若目标为 $\texttt{Green}$，则此状态不是 $\texttt{Green}$ 的获胜状态，因为 $\texttt{Red}$ 先获胜了）。
2. 若 `maskG == 0`，同理判断目标是否为 $\texttt{Green}$。
3. 否则，根据 `turn` 确定当前玩家，枚举其手中所有牌（遍历 $28$ 位掩码）。对于每张牌，尝试将其放置在左端或右端（若匹配），生成新状态：
   - 新链两端数字相应更新；
   - 该牌从当前玩家的掩码中移除；
   - 行动玩家切换为对方。
   若新状态尚未访问，则入队。
4. 若当前玩家没有任何一张牌能与任一极端匹配，则只能跳过回合，生成一个 `turn` 取反、其余不变的状态（若未访问则入队）。

$\texttt{BFS}$ 结束后仍未到达目标玩家的获胜状态，则返回 `false`。

### 状态数估计

虽然掩码有 $28$ 位，但实际可达状态远小于 $2^{28}$，因为：
- 双方总牌数固定为 $2n$；
- 链两端的数字受已放置的牌限制；
- 状态转移有向且无环（牌数持续减少，跳过回合不减少牌数但会切换玩家，可能形成循环，需用哈希去重）。

对于 $n \le 14$，实际状态数在可接受范围内，$\texttt{BFS}$ 能够快速完成。

### 复杂度分析

- 每个状态转移枚举当前玩家的剩余牌，最多 $28$ 张，每张尝试左右两个方向，常数小。
- 状态数 $S$ 不超过所有可能的掩码组合与链端组合，最坏情况下在 $n=14$ 时约为 $O(2^{28})$ 但实际远小于此，完全可行。
- 总时间复杂度 $O(S \cdot 28)$，空间复杂度 $O(S)$。

## 代码实现

```cpp
// Domino Game
// UVa ID: 742
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 28张多米诺牌，每张牌两个数字，编号0~27
int domino[28][2];
int idxMap[7][7];

// 游戏状态
struct State {
    int left, right;          // 当前链两端数字
    int turn;                 // 0: Red, 1: Green
    uint32_t maskR, maskG;    // 各自剩余牌的位掩码（28位）

    bool operator==(const State& other) const {
        return left == other.left && right == other.right &&
               turn == other.turn && maskR == other.maskR && maskG == other.maskG;
    }
};

// 哈希函数，用于unordered_set
struct StateHash {
    size_t operator()(const State& s) const {
        uint64_t h1 = (uint64_t)s.left << 60 | (uint64_t)s.right << 54 |
                      (uint64_t)s.turn << 53 | (uint64_t)s.maskR << 25 |
                      (uint64_t)s.maskG;
        return (size_t)h1;
    }
};

// 判断目标玩家（target = 0 表示 Red，1 表示 Green）是否有获胜路径
bool canWin(int target, const State& init) {
    queue<State> q;
    unordered_set<State, StateHash> visited;
    q.push(init);
    visited.insert(init);

    while (!q.empty()) {
        State cur = q.front(); q.pop();

        // 检查是否有人获胜
        if (cur.maskR == 0) return target == 0;   // Red 出完
        if (cur.maskG == 0) return target == 1;   // Green 出完

        uint32_t mask = (cur.turn == 0) ? cur.maskR : cur.maskG;
        bool hasMove = false;

        // 枚举当前玩家的每张牌
        for (int id = 0; id < 28; ++id) {
            if (!(mask & (1u << id))) continue;
            int a = domino[id][0], b = domino[id][1];

            // 尝试匹配左端
            if (a == cur.left || b == cur.left) {
                hasMove = true;
                int newLeft = (a == cur.left) ? b : a;
                int newRight = cur.right;
                uint32_t newMaskR = cur.maskR, newMaskG = cur.maskG;
                if (cur.turn == 0) newMaskR &= ~(1u << id);
                else newMaskG &= ~(1u << id);
                State nxt{newLeft, newRight, 1 - cur.turn, newMaskR, newMaskG};
                if (!visited.count(nxt)) {
                    if (nxt.maskR == 0 && target == 0) return true;
                    if (nxt.maskG == 0 && target == 1) return true;
                    visited.insert(nxt);
                    q.push(nxt);
                }
            }

            // 尝试匹配右端
            if (a == cur.right || b == cur.right) {
                hasMove = true;
                int newRight = (a == cur.right) ? b : a;
                int newLeft = cur.left;
                uint32_t newMaskR = cur.maskR, newMaskG = cur.maskG;
                if (cur.turn == 0) newMaskR &= ~(1u << id);
                else newMaskG &= ~(1u << id);
                State nxt{newLeft, newRight, 1 - cur.turn, newMaskR, newMaskG};
                if (!visited.count(nxt)) {
                    if (nxt.maskR == 0 && target == 0) return true;
                    if (nxt.maskG == 0 && target == 1) return true;
                    visited.insert(nxt);
                    q.push(nxt);
                }
            }
        }

        // 当前玩家无牌可出，跳过回合
        if (!hasMove) {
            State nxt{cur.left, cur.right, 1 - cur.turn, cur.maskR, cur.maskG};
            if (!visited.count(nxt)) {
                if (nxt.maskR == 0 && target == 0) return true;
                if (nxt.maskG == 0 && target == 1) return true;
                visited.insert(nxt);
                q.push(nxt);
            }
        }
    }
    return false;
}

int main() {
    // 初始化所有牌（编号0~27）
    int cnt = 0;
    for (int a = 0; a <= 6; ++a)
        for (int b = a; b <= 6; ++b) {
            domino[cnt][0] = a;
            domino[cnt][1] = b;
            idxMap[a][b] = cnt;
            ++cnt;
        }

    bool needBlank = false;
    int n;
    while (cin >> n && n != 0) {
        uint32_t maskR = 0, maskG = 0;

        // 读取 Red 的 n 张牌
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            int id = idxMap[x][y];
            maskR |= (1u << id);
        }

        // 读取 Green 的 n 张牌
        for (int i = 0; i < n; ++i) {
            int x, y;
            cin >> x >> y;
            if (x > y) swap(x, y);
            int id = idxMap[x][y];
            maskG |= (1u << id);
        }

        // 找出最大双块的持有者
        int maxDoubleVal = -1, maxDoublePlayer = -1, maxDoubleId = -1;
        for (int id = 0; id < 28; ++id) {
            if (domino[id][0] == domino[id][1]) {
                int val = domino[id][0];
                if (maskR & (1u << id) || maskG & (1u << id)) {
                    if (val > maxDoubleVal) {
                        maxDoubleVal = val;
                        maxDoublePlayer = (maskR & (1u << id)) ? 0 : 1;
                        maxDoubleId = id;
                    }
                }
            }
        }

        // 初始状态：最大双块已由先手放下
        State init;
        init.left = init.right = maxDoubleVal;
        init.maskR = maskR;
        init.maskG = maskG;
        if (maxDoublePlayer == 0) init.maskR &= ~(1u << maxDoubleId);
        else init.maskG &= ~(1u << maxDoubleId);
        init.turn = 1 - maxDoublePlayer;   // 轮到对方

        bool redWin  = canWin(0, init);
        bool greenWin = canWin(1, init);

        if (needBlank) cout << endl;
        needBlank = true;

        if (redWin && greenWin) cout << "Both players can win\n";
        else if (redWin && !greenWin) cout << "Only player Red can win\n";
        else if (!redWin && greenWin) cout << "Only player Green can win\n";
        else cout << "No players can win\n";
    }

    return 0;
}
```

## 总结

本题是一道典型的状态空间搜索问题，关键点在于：
- 将游戏状态精确定义为链两端、当前玩家和双方剩余牌的掩码；
- 利用广度优先搜索（$\texttt{BFS}$）枚举所有可达状态，分别判断两位玩家各自是否存在获胜路径；
- 使用哈希集合去重，避免状态无限循环；
- 位掩码表示牌集合，高效进行集合操作。

该解法直接且可靠，对于 $n \le 14$ 的限制完全满足时间和空间要求。通过分别对两位玩家调用搜索函数，可以清晰得到四种可能的结果。
