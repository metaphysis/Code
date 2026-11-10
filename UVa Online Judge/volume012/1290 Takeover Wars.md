
> **摘要**：本文讨论一道双人完全信息博弈题——两家公司轮流通过「友好合并」与「敌意收购」争夺子公司。文章从题目描述、输入输出格式出发，分析出最优策略仅取决于双方最大的两个子公司价值之和，进而给出基于 `multiset` 的贪心模拟算法，时间复杂度为 $O((N+M)\log(N+M))$。

## 题目描述

两家大型公司 $\texttt{Takeover Incorporated}$ 和 $\texttt{Buyout Limited}$ 正在进行一场收购战。每家公司拥有若干子公司，每个子公司具有一个正整数市场价值。双方轮流行动，$\texttt{Takeover Incorporated}$ 先手。每回合，当前公司可以选择以下两种操作之一：

- **友好收购**：将自己名下的两家不同子公司合并为一家，新公司的市场价值等于二者之和。参与合并的子公司规模无限制。
- **敌意收购**：选择自己的一家子公司 $A$，试图收购对方的一家子公司 $B$。若 $A$ 的市场价值大于 $B$ 的市场价值，则 $B$ 被移除，$A$ 的价值不变。规定任意时刻两家不同公司的子公司价值不会相等。

如果某公司无法进行任何合法操作（即无法合并（少于两家子公司）且无法敌意收购（自己的最大价值不大于对方的任意子公司价值）），则该公司只能选择跳过（$\texttt{pass}$）。当一家公司的所有子公司均被敌意收购时，该公司失败。双方均采取最优策略，求最终的获胜者。

## 输入格式

每个测试用例包含三行输入：

- 第一行包含两个整数 $N$ 和 $M$，分别表示 $\texttt{Takeover Incorporated}$ 和 $\texttt{Buyout Limited}$ 的子公司数量，满足 $1 \le N, M \le 10^5$。
- 第二行包含 $N$ 个整数 $a_i$，表示 $\texttt{Takeover Incorporated}$ 各子公司的市场价值，$1 \le a_i \le 10^{12}$。
- 第三行包含 $M$ 个整数 $b_j$，表示 $\texttt{Buyout Limited}$ 各子公司的市场价值，$1 \le b_j \le 10^{12}$。

输入包含多个测试用例，直到文件结束。

## 输出格式

对于每个测试用例，输出一行，格式为 `Case X: Winner`，其中 $X$ 为用例编号（从 $1$ 开始），`Winner` 为 `Takeover Incorporated` 或 `Buyout Limited`，表示最优策略下的获胜方。

## 样例输入

```text
3 2
7 1 1
5 5
4 2
3 3
3 5
5
```

## 样例输出

```text
Case 1: Takeover Incorporated
Case 2: Buyout Limited
```

## 题目分析

本题属于双人完全信息博弈，状态空间为双方子公司的多重集合。由于 $N, M$ 均可达到 $10^5$，无法进行搜索或动态规划，必须挖掘博弈的结构性质。

关键观察在于，每家公司的最优策略仅取决于其子公司价值的分布，特别是最大的几个值。友好合并操作将两个子公司合并为一个，其价值等于二者之和，这相当于用它们的和替换它们，使得集合大小减少 $1$。敌意收购操作移除对方的一个元素，同时不改变己方任何元素。

考虑任何一方的行动，若其当前最大价值能够大于对方的某个子公司，则进行敌意收购是显然不劣的，因为这会削弱对手且不损失己方资源。若不能敌意收购，则唯一可能改变局势的操作是友好合并。因此，双方决策的核心在于决定何时合并以及如何合并。

进一步分析发现，若当前玩家拥有至少两家子公司，并且其最大的两家子公司之和大于对方最大的两家子公司之和，则进行友好合并是强制的优势策略。这是因为合并后产生的新子公司价值 $S$ 大于对方任何可能的友好合并结果（即对方最大的两子之和），同时也大于对方任意单个子公司（因为对方最大单值不大于其两子之和）。此后，该玩家可以始终保持一个价值最大的子公司，并逐步通过敌意收购吃掉对方的所有子公司，从而获胜。反之，若自己的两子之和不大于对方的两子之和，则合并并不能带来绝对优势，此时应优先考虑能否直接用当前最大值收购对方的最大值（若能，则吃掉对方最大子公司），否则只能被迫合并（若有两家以上）或跳过。

该策略是完备的，因为每一步的决策都基于“能否创造不可被超越的最大值”这一核心准则，而其他分支均不会优于该贪心选择。通过模拟双方交替执行这一确定性策略，即可判定最终胜者。

## 解题思路

根据上述分析，我们设计如下模拟算法：

- 使用两个多重集合（或优先队列）分别维护两家公司的子公司价值，支持插入、删除最大值、获取最大值和次大值。
- 每轮由当前玩家行动，行动规则如下：

  规则 $\texttt{1}$. 计算当前玩家子公司集合的最大值 $mx$ 和次大值 $sec$（若存在），以及对手的最大值 $omx$ 和次大值 $osec$（若存在）。  
  规则 $\texttt{2}$. 若当前玩家至少有两家子公司且 $mx + sec > omx + osec$，则执行友好合并，将最大值和次大值取出，插入它们的和。  
  规则 $\texttt{3}$. 否则，若 $mx > omx$，则执行敌意收购，移除对手的最大值。  
  规则 $\texttt{4}$. 否则，若当前玩家至少有两家子公司，则无奈合并（将最大值和次大值合并），因为无法收购也无法取得优势，但必须行动（若不能行动则跳过）。  
  规则 $\texttt{5}$. 若以上均不满足（即只有一家子公司且无法敌意收购），则当前玩家跳过。

- 切换玩家，重复上述过程，直到某一方的集合为空。此时另一方获胜。

该策略的正确性基于如下论证：  
- 若当前玩家能合并出一个大于对手最大两子之和的新子公司，那么此后该玩家可以一直用这个巨型子公司进行敌意收购，对手无法通过合并产生更大的值，也无法通过已有的单个值反收购，因此该玩家必胜。  
- 若当前玩家最大值大于对手最大值，则敌意收购对手最大子公司是最优的，因为吃掉对手最强棋子不会降低己方实力，且能削弱对手。  
- 若上述两种情况均不成立，说明当前玩家处于劣势，无法取得优势，此时合并（若可能）是唯一的行动选择，即使不能立刻改变劣势，也比跳过更好（因为跳过等于浪费回合，对手可继续进攻）。

由于每次操作（合并或敌意收购）都会使总子公司数量减少 $1$，总操作次数不超过 $N+M-1$，因此模拟可以在线性对数时间内完成。

## 代码实现

使用 `multiset<long long>` 维护子公司价值，每次操作获取最大值（`rbegin()`）和次大值（`prev(rbegin())`）均可在对数时间内完成。注意当集合大小不足 $2$ 时次大值不存在。代码中按上述规则循环，直至一方为空。

复杂度分析：  
- 时间复杂度：$O((N+M)\log(N+M))$。  
- 空间复杂度：$O(N+M)$。

```cpp
// Takeover Wars
// UVa ID: 1290
// Verdict: Accepted
// Submission Date: 2026-07-16
// UVa Run Time: 0.730s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M;
    int caseNumber = 1;
    while (cin >> N >> M) {
        multiset<long long> takeoverHeap, buyoutHeap;
        long long val;
        for (int i = 0; i < N; ++i) { cin >> val; takeoverHeap.insert(val); }
        for (int i = 0; i < M; ++i) { cin >> val; buyoutHeap.insert(val); }
        bool turn = true; // true 表示 Takeover 行动
        while (!takeoverHeap.empty() && !buyoutHeap.empty()) {
            multiset<long long>& cur = turn ? takeoverHeap : buyoutHeap;
            multiset<long long>& opp = turn ? buyoutHeap : takeoverHeap;
            long long curMax = *cur.rbegin();
            long long curSum = curMax;
            if (cur.size() >= 2) {
                auto itMax = prev(cur.end());
                long long second = *prev(itMax);
                curSum = curMax + second;
            }
            long long oppMax = *opp.rbegin();
            long long oppSum = oppMax;
            if (opp.size() >= 2) {
                auto itMax = prev(opp.end());
                long long second = *prev(itMax);
                oppSum = oppMax + second;
            }
            if (cur.size() >= 2 && curSum > oppSum) {
                auto itMax = prev(cur.end());
                long long a = *itMax;
                cur.erase(itMax);
                auto itSecond = prev(cur.end());
                long long b = *itSecond;
                cur.erase(itSecond);
                cur.insert(a + b);
            } else if (curMax > oppMax) {
                opp.erase(prev(opp.end()));
            } else if (cur.size() >= 2) {
                auto itMax = prev(cur.end());
                long long a = *itMax;
                cur.erase(itMax);
                auto itSecond = prev(cur.end());
                long long b = *itSecond;
                cur.erase(itSecond);
                cur.insert(a + b);
            }
            turn = !turn;
        }
        cout << "Case " << caseNumber++ << ": ";
        if (takeoverHeap.empty()) cout << "Buyout Limited\n";
        else cout << "Takeover Incorporated\n";
    }
    return 0;
}
```

## 总结

本题的核心在于发现博弈的最优策略可由双方最大的两个子公司之和的比较来驱动。通过贪心模拟，每次选择当前最有利的行动，即可确定最终胜者。该思路避免了复杂的博弈树搜索，将问题转化为简单的集合操作，适用于大规模数据。  
关键技巧包括：
- 使用 `multiset` 或优先队列高效维护最大值和次大值。
- 理解友好合并的本质是“创造新的最大值”，其价值取决于最大的两个元素。
- 敌意收购只针对对方最大值，因为吃掉最大值总是最优的。
- 当无法取得优势时，合并是唯一的积极行动，否则跳过。

该解法对任意 $N, M \le 10^5$ 均能快速运行，且代码简洁，易于实现。
