## 题目描述

给定多个游戏的计分规则，每个游戏包含若干种得分事件，某些事件必须紧跟在特定前置事件之后才能得分。一个**事件序列**定义为连续发生的、满足前置依赖关系的事件链，其中除第一个事件外，每个事件都必须以前一个事件为前置条件。独立发生的事件（无前置条件）各自构成单独的事件序列。

对于每个游戏和若干目标分数，需要判断该分数是否可达。若可达，还需要给出达到该分数所需**最少事件序列数**的方案，并输出每个事件的使用次数及其贡献分数。

计分规则示例（游戏 “$\texttt{Dunking}$”）：
- `doser`（$2$ 分），无前置条件
- `soaker`（$3$ 分），前置 `doser`
- `spray`（$1$ 分），前置 `soaker`
- `gusher`（$6$ 分），前置 `doser`
- `bucket`（$7$ 分），无前置条件

合法的完整事件序列包括：`doser`、`doser-soaker`、`doser-gusher`、`doser-soaker-spray`、`bucket` 等。注意三个独立的 `doser` 视为三个事件序列，而非一个。

## 输入格式

每个游戏的计分方案以一行整数 $N \le 20$ 开头，表示该游戏的事件数量。接下来 $N$ 行，每行描述一个事件，包含以下字段（以空白分隔）：
- 事件名称（区分大小写，不超过 $16$ 个字符）
- 该事件的得分（整数）
- 可选的前置事件名称（若无前置，则该行只有前两个字段）

之后是一行若干整数，表示需要查询的分数，以 $0$ 结束（$0$ 不作为查询分数）。输入以单独一行 $0$ 结束。

## 输出格式

对于每个游戏/分数对，输出格式如下：
- 标题行：`Case 游戏编号.分数编号 (目标分数):`
- 若分数不可达：在同一行输出 `This score is impossible.`
- 若可达：换行后输出一行，列出所有使用次数大于 $0$ 的事件，格式为 `次数 事件名[s] (该事件贡献总分)`，多个事件间以空格分隔。事件名在次数大于 $1$ 时需要加复数后缀 `s`。
- 每个游戏/分数对之后（除最后一个外）打印一个空行。

## 样例输入

```
5
douser 2
soaker 3 douser
spray 1 soaker
gusher 6 douser
bucket 7
1 2 4 5 6 7 8 9 0
4
foul 0
freshet 1 foul
goal 2
whopper 4
1 2 3 4 5 0
0
```

## 样例输出

```
Case 1.6 (7):
      1 bucket (7)

Case 1.7 (8):
      1 douser (2)
      1 gusher (6)

Case 1.8 (9):
      1 douser (2)
      1 bucket (7)

Case 2.1 (1):
      1 foul (0)
      1 freeshot (1)

Case 2.2 (2):
      1 goal (2)

Case 2.3 (3):
      1 foul (0)
      1 freeshot (1)
      1 goal (2)

Case 2.4 (4):
      1 whopper (4)

Case 2.5 (5):
      1 foul (0)
      1 freeshot (1)
      1 whopper (4)
```

## 题目分析

本题的核心是：给定一组带前置依赖的得分事件，每个事件至多有一个前置事件，因此事件之间的依赖关系形成若干条链（即森林结构）。每个合法的事件序列必须是一条从根（无前置事件）出发，沿着依赖关系向下延伸的完整路径，路径上的所有事件按顺序发生，且每个事件只能在其前置事件之后立即发生。

我们需要在**无限**使用这些事件序列的前提下，用最少的事件序列数凑出给定的目标分数。注意这里的事件序列可以重复使用，且每个序列的总分是固定的，序列内部包含的事件和它们的得分也是固定的。

直接枚举所有可能的序列组合是不现实的，因为目标分数可能较大。但注意到事件数量 $N \le 20$，每个事件最多对应一个以它为结尾的序列，因此序列总数也不超过 $20$。我们可以将每个序列视为一个“物品”，其“重量”为该序列的总分，使用该序列的“代价”为 $1$（即消耗一个事件序列），目标是使用最少的物品数凑出目标分数。这正是典型的**完全背包**问题（每个物品可无限次使用）。

然而，输出方案时要求给出每个独立事件的总使用次数，而不是序列的使用次数。因此需要在背包中记录转移路径，以便回溯每个序列的使用次数，并累加得到各事件的最终计数。

## 解题思路

### 步骤一：构建依赖图并生成所有事件序列

由于每个事件至多有一个前置事件，我们可以将前置关系视为一棵棵有向树（森林），边从父节点指向子节点。根节点是没有前置事件的事件。

对于每个事件节点，从该事件所在的树的根节点出发，沿依赖路径走到该事件，即可得到以该事件结尾的唯一合法序列。因此，总共有 $N$ 个事件序列（每个事件对应一个），每个序列的总分就是路径上所有事件的得分之和，同时记录该序列包含哪些事件及其出现次数。

例如，对于样例中的 “$\texttt{Dunking}$” 游戏：
- 事件 `doser`（根）对应的序列为 `[doser]`，总分 $2$
- 事件 `soaker`（前置 `doser`）对应的序列为 `[doser, soaker]`，总分 $5$
- 事件 `spray`（前置 `soaker`）对应的序列为 `[doser, soaker, spray]`，总分 $6$
- 事件 `gusher`（前置 `doser`）对应的序列为 `[doser, gusher]`，总分 $8$
- 事件 `bucket`（根）对应的序列为 `[bucket]`，总分 $7$

需要注意，如果一个序列的总分为 $0$，使用它不会增加分数，但会增加事件序列数量，因此不可能出现在最优解中，可以忽略。

### 步骤二：完全背包求最小序列数

设查询分数中的最大值为 $M$。对于当前游戏，我们得到若干物品（事件序列），每个物品 $i$ 具有总分 $w_i$（正整数）和计数向量 $\mathbf{c}_i$（长度为 $N$，表示该序列中各事件的出现次数）。

定义动态规划状态：
- $\textit{dp}[j]$：表示凑出分数 $j$ 所需的最少事件序列数。
- $\textit{pre}[j]$：表示在最优方案中，达到分数 $j$ 时最后一个使用的物品编号（用于回溯）。

初始化 $\textit{dp}[0] = 0$，其余 $\textit{dp}[j] = \infty$。转移方程为：

$$
\textit{dp}[j] = \min_{i: w_i \le j} \{ \textit{dp}[j - w_i] + 1 \}
$$

由于每个物品可以无限次使用，我们采用**完全背包**的正向遍历方式：

```cpp
for (int i = 0; i < itemCount; ++i)
    for (int j = w_i; j <= M; ++j)
        if (dp[j - w_i] + 1 < dp[j]) {
            dp[j] = dp[j - w_i] + 1;
            pre[j] = i;
        }
```

### 步骤三：回溯方案并统计事件次数

对于每个查询分数 $S$，若 $\textit{dp}[S] = \infty$，则该分数不可达。否则，从 $S$ 开始，反复使用 $\textit{pre}$ 指针回溯：

```cpp
int cur = S;
while (cur > 0) {
    int idx = pre[cur];
    累加 items[idx].counts 到总计数;
    cur -= items[idx].totalScore;
}
```

最终得到每个事件的总使用次数，按输入顺序输出次数大于 $0$ 的事件，格式需注意单复数。

### 复杂度分析

- 序列生成：通过 $\texttt{DFS}$ 遍历森林，每个节点访问一次，时间复杂度 $O(N)$。
- 完全背包：物品数 $\le N \le 20$，目标最大分数 $M$ 取决于输入查询分数。由于题目未明确 $M$ 的上限，但查询分数通常不会过大（根据样例推断），且 $N$ 较小，完全背包时间复杂度为 $O(N \cdot M)$，在 $M$ 可接受范围内可行。
- 空间复杂度：$O(N + M)$，用于存储 $\textit{dp}$ 和 $\textit{pre}$ 数组。

实际实现中，若 $M$ 可能较大，也可考虑使用 $\texttt{BFS}$ 或 $\texttt{Dijkstra}$ 等最短路算法，但此处完全背包已足够。

## 代码实现

```cpp
// Cheapest Scores
// UVa ID: 351
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Event {
    string name;
    int score;
    string prereqName;
    int parent;
    vector<int> children;
};

struct Sequence {
    int totalScore;
    vector<int> counts;   // 长度为事件数
};

struct Game {
    vector<Event> events;
    vector<int> queries;
};

// 生成每个事件的序列（从根到该事件的路径）
void buildSequences(const vector<Event>& events, vector<Sequence>& seqs) {
    int n = events.size();
    seqs.assign(n, Sequence{0, vector<int>(n, 0)});
    vector<int> roots;
    for (int i = 0; i < n; ++i)
        if (events[i].parent == -1) roots.push_back(i);

    function<void(int, vector<int>&)> dfs = [&](int u, vector<int>& path) {
        path.push_back(u);
        // 生成当前节点的序列
        int total = 0;
        vector<int> cnt(n, 0);
        for (int idx : path) {
            total += events[idx].score;
            cnt[idx]++;
        }
        seqs[u] = {total, cnt};
        // 递归子节点
        for (int v : events[u].children)
            dfs(v, path);
        path.pop_back();
    };

    for (int r : roots) {
        vector<int> path;
        dfs(r, path);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Game> games;
    int N;
    while (cin >> N && N != 0) {
        cin.ignore(); // 忽略 N 后的换行
        Game game;
        game.events.resize(N);
        for (int i = 0; i < N; ++i) {
            string line;
            getline(cin, line);
            istringstream iss(line);
            string name, prereq;
            int score;
            iss >> name >> score;
            game.events[i].name = name;
            game.events[i].score = score;
            if (iss >> prereq)
                game.events[i].prereqName = prereq;
            else
                game.events[i].prereqName = "";
        }
        int x;
        while (cin >> x && x != 0)
            game.queries.push_back(x);
        games.push_back(game);
    }

    int totalCases = 0;
    for (const auto& g : games)
        totalCases += g.queries.size();

    int caseIdx = 0;
    for (int gNum = 1; gNum <= (int)games.size(); ++gNum) {
        Game& game = games[gNum - 1];
        int n = game.events.size();

        // 建立名称到索引的映射
        unordered_map<string, int> nameToIdx;
        for (int i = 0; i < n; ++i)
            nameToIdx[game.events[i].name] = i;

        // 确定父节点并构建孩子列表
        for (int i = 0; i < n; ++i) {
            if (game.events[i].prereqName.empty())
                game.events[i].parent = -1;
            else
                game.events[i].parent = nameToIdx[game.events[i].prereqName];
            game.events[i].children.clear();
        }
        for (int i = 0; i < n; ++i) {
            int p = game.events[i].parent;
            if (p != -1)
                game.events[p].children.push_back(i);
        }

        // 生成所有序列（每个事件对应一个）
        vector<Sequence> seqs;
        buildSequences(game.events, seqs);

        // 收集可用物品（总分 > 0）
        vector<Sequence> items;
        int maxScore = 0;
        for (int s : game.queries)
            maxScore = max(maxScore, s);

        for (int i = 0; i < n; ++i) {
            if (seqs[i].totalScore > 0 && seqs[i].totalScore <= maxScore)
                items.push_back(seqs[i]);
        }

        // 完全背包：dp[j] = 最小序列数，pre[j] = 最后使用的物品编号
        const int INF = 1e9;
        vector<int> dp(maxScore + 1, INF);
        vector<int> pre(maxScore + 1, -1);
        dp[0] = 0;

        for (int i = 0; i < (int)items.size(); ++i) {
            int w = items[i].totalScore;
            for (int j = w; j <= maxScore; ++j) {
                if (dp[j - w] != INF && dp[j - w] + 1 < dp[j]) {
                    dp[j] = dp[j - w] + 1;
                    pre[j] = i;
                }
            }
        }

        // 处理每个查询
        for (int qIdx = 1; qIdx <= (int)game.queries.size(); ++qIdx) {
            int score = game.queries[qIdx - 1];
            ++caseIdx;

            if (dp[score] == INF) {
                cout << "Case " << gNum << "." << qIdx << " (" << score << "):\n      This score is impossible.\n";
            } else {
                // 回溯得到每种事件的总次数
                vector<int> totalCnt(n, 0);
                int cur = score;
                while (cur > 0) {
                    int itemIdx = pre[cur];
                    for (int i = 0; i < n; ++i)
                        totalCnt[i] += items[itemIdx].counts[i];
                    cur -= items[itemIdx].totalScore;
                }

                cout << "Case " << gNum << "." << qIdx << " (" << score << "):\n";
                string line;
                for (int i = 0; i < n; ++i) {
                    if (totalCnt[i] == 0) continue;
                    if (!line.empty()) line += "\n";
                    line += "      " + to_string(totalCnt[i]) + " " + game.events[i].name;
                    if (totalCnt[i] > 1) line += "s";
                    line += " (" + to_string(game.events[i].score * totalCnt[i]) + ")";
                }
                cout << line << "\n";
            }

            // 除最后一个 case 外，输出空行
            if (caseIdx < totalCases)
                cout << "\n";
        }
    }

    return 0;
}
```

## 总结

本题将复杂的依赖型事件序列问题转化为经典的完全背包问题，关键在于：
1. 识别出每个事件唯一对应一个从根到该事件的路径序列，因此序列总数等于事件数。
2. 利用完全背包求解最小序列数，并通过回溯 $\textit{pre}$ 数组还原具体方案。
3. 注意输出格式的细节，包括复数 `s` 的添加、空行的处理等。

本题的难点在于建模转换，而非背包本身。通过将依赖链映射为背包物品，我们成功将看似复杂的问题简化。同时，利用 $N \le 20$ 的较小规模，完全背包在时间复杂度上也是可行的。这一思路可以推广到其他类似的“组合依赖 + 最小数量”问题中。
