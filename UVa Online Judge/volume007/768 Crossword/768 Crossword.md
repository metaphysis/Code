## 题目描述

给定一个单词列表，列表中的单词按字典序排列且不重复。构造一个长度为 $L$ 的字符串（只包含小写字母），使得该字符串存在两种不同的拆词方式，每种拆词方式将字符串切分为若干个单词，这些单词均来自给定的列表，且满足以下约束：

- 两种拆词方式所使用的单词集合互不相交（即同一个单词不能同时出现在两种拆法中）。
- 在任意一种拆法中，同一个单词不能重复出现。
- 两种拆法的所有切割点（即每个单词的结束位置）除字符串末尾外，不能有任何重合。
- 允许其中一种拆法只包含一个单词。

要求输出所有满足条件的字符串中字典序最小的一个，若无解则输出 `NO SOLUTION`。

## 输入格式

输入包含多个测试用例。每个测试用例第一行为整数 $L$（$4 \le L \le 50$），表示目标字符串长度。第二行为整数 $N$（$1 \le N \le 1000$），表示单词数量。接下来 $N$ 行，每行一个字符串，长度在 $2$ 到 $20$ 之间，由小写字母组成，列表按字典序排列且无重复。

输入以文件结束符 `EOF` 结束。

## 输出格式

对于每个测试用例，输出一行：若存在合法字符串，则输出字典序最小的那个；否则输出 `NO SOLUTION`。

## 样例

输入

```
17
19
all
an
and
area
as
ask
at
data
do
for
last
of
or
ort
read
real
task
to
tor
```

输出

```
andatareadofortor
```

## 题目分析

本题要求构造一个长度为 $L$ 的字符串，同时具备两种合法的单词拆分方式。两种拆分方式之间共享同一个字符串，但使用的单词不能重复，且切割点不能重叠（末端除外）。这等价于在单词列表上寻找两条从位置 $0$ 到位置 $L$ 的路径，路径上的边（即单词）长度之和恰好为 $L$，两条路径的内部顶点（即切割点）互不相同，且两条路径上的边互不相同。同时，两条路径所覆盖的字符序列必须完全一致，即它们共同定义同一个字符串。

直接枚举所有可能的拆分方式组合，复杂度是指数级的，不可接受。必须设计高效的搜索算法，同时构造两条拆分路径，并在搜索过程中利用剪枝减少状态空间。

## 解题思路

### 双指针并行搜索

用两个指针 $\textit{last}$ 和 $\textit{now}$ 分别表示两种拆法当前已经填充到的位置。初始时 $\textit{last} = 0$，$\textit{now} = 0$。每次总是推进较小的指针（若相等则推进 $\textit{last}$），这样可以保证字符串从左到右逐步确定，便于字典序比较和剪枝。

当从位置 $\textit{last}$ 尝试一个单词 $w$（长度为 $\textit{step}$）时，新位置为 $\textit{newP} = \textit{last} + \textit{step}$。为了保证两种拆法的切割点不重合，需要满足：
- 若 $\textit{newP} \ne L$，则 $\textit{newP}$ 不能等于另一个指针 $\textit{now}$（即不能在非末尾处同时切割）。
- 由于总是推进较小的指针，且切割点不能重叠，实际上这个条件已经足够保证所有历史切割点互不重合（因为较小指针和较大指针之间不存在切割点，推进过程不会遇到历史切割点）。

同时，单词不能重复使用，因此用一个布尔数组 $\textit{used}$ 标记已使用的单词。

### 字符一致性约束

两种拆法最终得到同一个字符串，因此当尝试填充单词时，需要检查与当前位置上已由另一种拆法填充的字符是否冲突。若冲突则跳过该单词。

### 字典序最小保证

由于单词列表已按字典序排列，搜索时按顺序尝试单词，但仅仅“找到第一个解就返回”并不能保证全局字典序最小，因为同一个位置可能选择不同长度的单词，后续字符会影响整体字典序。例如，选择较短的单词可能使后续字符变大，而选择较长的单词可能使后续字符更小。

因此，必须采用“全局最优解 + 前缀剪枝”的策略：

- 维护一个全局最优字符串 $\textit{best}$，初始时所有位置设为最大字符（如 $\texttt{ASCII}$ $128$）。
- 在每次递归入口，比较当前已填充的 $\textit{line}$ 与 $\textit{best}$ 的已确定前缀：若 $\textit{line}$ 已经大于 $\textit{best}$，则剪枝返回。
- 当找到一个完整解（$\textit{last} = \textit{now} = L$）时，用 $\textit{line}$ 更新 $\textit{best}$。
- 搜索结束后，$\textit{best}$ 即为字典序最小的合法字符串。

该剪枝是安全的，因为字符串比较具有前缀决定性：一旦某个位置分出大小，后续字符不再影响结果。

### 辅助剪枝

- **最短单词剪枝**：若某个指针剩余长度小于最短单词长度，则不可能完成，直接返回。
- **重叠检查**：仅当 $\textit{now} > 0$ 时检查重叠部分字符是否一致。
- **首字母索引**：当 $\textit{last} > 0$ 且 $\textit{line}[\textit{last}]$ 已被填充时，利用首字母索引只尝试以该字符开头的单词，减少循环次数。

### 复杂度分析

搜索空间理论上可能很大，但由于剪枝（前缀剪枝、最短长度剪枝、重叠检查、切割点限制）非常有效，实际运行时间远低于时限。每个测试用例中，单词数量 $N$ 最多 $1000$，长度 $L$ 最多 $50$，搜索深度不超过 $L / \min\textit{len}$。最坏情况下，若单词长度均为 $2$，最大深度为 $25$，分支数受剪枝大幅削减。实际运行时间约 $150$ 毫秒，满足要求。

## 代码实现

```cpp
// Crossword
// UVa ID: 768
// Verdict: Accepted
// Submission Date: 2026-07-11
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int L, N, minL, head[32], used[1024];
int line[64], best[64];
string words[1024];

void dfs(int last, int now) {
    int better = 1;
    for (int i = 0; i < L; i++) {
        if (line[i] < best[i]) break;
        if (line[i] > best[i]) { better = 0; break; }
    }
    if (!better) return;
    if (now < L && L - now < minL) return;
    if (last == L && now == L) {
        for (int i = 0; i < L; ++i) best[i] = line[i];
        return;
    }
    int start = 0, end = N;
    if (last) {
        int c = line[last] - 'a';
        start = head[c];
        end = (c == 25 ? N : head[c + 1]);
    }
    for (int id = start; id < end; id++) {
        if (used[id]) continue;
        string& w = words[id];
        int step = w.size();
        if (last + step > L) continue;
        if (last + step == now && now != L) continue;
        int ok = 1;
        for (int i = 0; i < min(step, now - last); i++)
            if (line[last + i] != w[i]) { ok = 0; break; }
        if (!ok) continue;
        for (int i = 0; i < step; i++) line[last + i] = w[i];
        used[id] = 1;
        dfs(min(last + step, now), max(last + step, now));
        used[id] = 0;
        for (int i = now; i < last + step; i++) line[i] = 0;
    }
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    while (cin >> L) {
        cin >> N;
        minL = 32;
        for (int i = 0; i < N; ++i) {
            cin >> words[i];
            minL = min(minL, (int)words[i].size());
        }
        for (int i = 0; i < 26; ++i) {
            string s(1, char('a' + i));
            head[i] = lower_bound(words, words + N, s) - words;
        }
        memset(line, 0, sizeof(line));
        memset(used, 0, sizeof(used));
        for (int i = 0; i < 64; ++i) best[i] = 128;
        dfs(0, 0);
        if (best[0] == 128) cout << "NO SOLUTION\n";
        else {
            for (int i = 0; i < L; ++i) cout << (char)best[i];
            cout << '\n';
        }
    }
    return 0;
}
```

## 总结

本题的关键点在于：

- **并行双指针搜索**，同时构建两种拆分方式，确保切割点不重叠。
- **全局最优 + 前缀剪枝**，而非贪心选取第一个解，从而保证字典序最小。
- **首字母索引和最短长度剪枝**，有效减少搜索分支。

通过合理的剪枝策略，该算法能够在给定约束下快速找到字典序最小的合法字符串，通过了所有测试数据。
