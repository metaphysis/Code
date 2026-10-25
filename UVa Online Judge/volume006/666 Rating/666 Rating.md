## 题目描述

给定两场比赛的结果表，每场比赛按名次从上到下排列，同一行的队伍成绩相同（并列）。每支队伍有一个唯一的整数标识符（范围为 $1$ 到 $100$）。需要根据以下规则生成所有队伍的总排名列表，只输出能够确定总排名的队伍，未确定的队伍不输出。

定义队伍在比赛中的名次 $K$ 为：恰好有 $K-1$ 支队伍在该场比赛中表现优于它。

总排名规则（对于参加了两场比赛的队伍）：
1. 若队伍 $A$ 在两场比赛中均不劣于队伍 $B$，且至少一场严格优于 $B$，则 $A$ 的总排名高于 $B$。
2. 若 $A$ 和 $B$ 各在一场比赛中表现更好（互有胜负），则比较两场比赛名次差的绝对值。绝对值较大的队伍总排名较低（即较差）。若绝对值相等，则两队总排名相同。若两场名次完全相同，也视为总排名相同。

对于只参加了一场比赛的队伍，按以下两条规则尝试确定其总排名：
- **规则 $\texttt{A}$**：若该队伍与某个参加了两场比赛的队伍在同一场比赛中名次相同（即同一行），且所有这样的两赛队伍的总排名相同（位于总列表同一行），则该队伍与该行共享总排名；否则该队伍的总排名无法确定。
- **规则 $\texttt{B}$**：若可以在当前总列表中找到某个位置（开头、末尾或任意两行之间），使得该位置之前的所有队伍在该队伍参加的那场比赛中都优于它，之后的所有队伍都劣于它，则该队伍占据该位置。若多个队伍竞争同一位置，则按它们在该场比赛中的名次升序分组，同名次的队伍放在同一行，名次小的行在前。

## 输入格式

第一行是一个整数 $M$，表示数据集的个数。数据集之间用一个空行分隔。

每个数据集包含两场比赛的描述，两场描述之间用一个空行分隔。每场比赛描述第一行是一个整数 $N$（$1 \le N \le 100$），表示后面有 $N$ 行结果。接下来的 $N$ 行中，每行包含一个或多个队伍标识符（空格分隔），表示该名次上的所有队伍。每支队伍在每场比赛中至多出现一次。

## 输出格式

对于每个数据集，输出若干行，每行包含一个或多个队伍标识符（空格分隔），表示总排名列表。同行队伍的总排名相同，顺序任意。无法确定总排名的队伍不输出。

数据集之间输出一个空行。

## 样例

输入

```
1

6
9
7 1 4
5
15 8
31 18
17

8
3
5
1 10
6
9
19
4 20
21
```

输出

```
3
1 10
5 9
19
4 20
15 8
31 18
17 21
```

## 题目分析

本题的核心是模拟一个基于两场比赛结果的偏序关系，并在此基础上插入仅参加一场比赛的队伍。

首先，对于参加过两场比赛的队伍，它们之间构成了一个偏序集。规则 $\texttt{1}$ 和规则 $\texttt{2}$ 定义了一个明确的比较函数 $\textit{isBetter}(A,B)$，它返回 $A$ 的总排名是否高于 $B$。该比较函数具有传递性，因此我们可以对所有两赛队伍进行排序，并按照规则将相等的队伍（互不比对方高）归为同一行，得到初始总列表。

然后处理只参加一场比赛的队伍。规则 $\texttt{A}$ 优先级高于规则 $\texttt{B}$。规则 $\texttt{A}$ 要求该队伍与某行中的两赛队伍在同一场比赛中同名次，并且所有匹配的两赛队伍都位于同一行，否则该队伍无法确定排名。若满足，则直接将该队伍加入该行。

对于未通过规则 $\texttt{A}$ 的队伍，尝试规则 $\texttt{B}$。规则 $\texttt{B}$ 需要枚举所有可能的插入位置（行间或两端），并检查该位置是否满足“前面所有队伍均优于它，后面所有队伍均劣于它”的条件。由于总列表会因规则 $\texttt{A}$ 加入的单赛队伍而发生变化，因此规则 $\texttt{B}$ 的检查必须基于当前已经包含所有规则 $\texttt{A}$ 插入的完整列表。同时，因为总列表中可能混有只参加一场比赛的队伍，在比较名次时必须只考虑与当前队伍参加同一场比赛的队伍，另一场比赛的成绩不存在，应跳过比较。

规则 $\texttt{B}$ 允许多支队伍竞争同一位置，此时需要按它们在该场比赛中的名次分组，同名次的队伍在同一行，按名次升序依次插入。从后往前插入可避免插入位置索引的变动。

最终输出所有行。

## 解题思路

### 数据结构的选择

本题队伍标识符范围为 $1$ 到 $100$，因此可以使用两个大小为 $110$ 的整型数组 `place1` 和 `place2` 存储每支队伍在两场比赛中的名次，未参赛则值为 $0$。使用数组访问快速且实现简洁。

### 比较函数的实现

对于两支参加过两场比赛的队伍 $A$ 和 $B$，设其名次分别为 $(a_1, a_2)$ 和 $(b_1, b_2)$。比较函数按如下规则实现：

1. 若 $a_1 \le b_1$ 且 $a_2 \le b_2$ 且至少一个严格小于，则 $A$ 优于 $B$。
2. 若 $b_1 \le a_1$ 且 $b_2 \le a_2$ 且至少一个严格小于，则 $B$ 优于 $A$。
3. 若互有胜负，令 $\textit{diff1} = b_1 - a_1$，$\textit{diff2} = b_2 - a_2$（此时两者符号相反）。由于 $A$ 优于 $B$ 当且仅当 $\lvert \textit{diff1} \rvert > \lvert \textit{diff2} \rvert$，而符号相反时 $\lvert \textit{diff1} \rvert > \lvert \textit{diff2} \rvert$ 等价于 $\textit{diff1} + \textit{diff2} > 0$。因此比较函数可直接返回 $\textit{diff1} + \textit{diff2} > 0$。
4. 若名次完全相同，则两者相等，互不比对方高。

该比较函数具有传递性，可安全用于 `std::sort`。

### 初始总列表的生成

收集所有 `place1` 和 `place2` 均非零的队伍，按比较函数排序。然后扫描排序后的数组，将互相相等的队伍（即 `!isBetter(a,b) && !isBetter(b,a)`）归并到同一行，形成初始 `rows` 向量。

### 处理单赛队伍

遍历 $1$ 到 $100$ 的所有队伍，跳过两赛队伍。

#### 规则 $\texttt{A}$ 的处理

对于当前队伍 `id`，确定其参加的比赛 `c`（1 或 2）和名次 `p`。在 `twoTeams` 中查找所有在同一场比赛 `c` 中名次也为 `p` 的队伍，收集到 `matched` 向量。然后检查这些队伍是否全部位于 `rows` 的同一行。若存在某一队伍不在任何行中（理论上不会发生，因为 `twoTeams` 均已排序归入行），或它们所在行索引不一致，则规则 $\texttt{A}$ 失败。若成功，则将该队伍插入到该行末尾。

一旦规则 $\texttt{A}$ 匹配成功（无论成功或失败），都跳过规则 $\texttt{B}$，因为规则 $\texttt{A}$ 的判定具有优先性，且失败即表示无法确定排名。

#### 规则 $\texttt{B}$ 的处理

若规则 $\texttt{A}$ 未能应用（即 `matched` 为空），则枚举所有可能的插入位置 `k`（$0$ 到 $R$，其中 $R$ 为当前行数）。对于每个位置 $k$，检查：
- 前 $k$ 行中的所有队伍，若它们也参加了比赛 `c`，则其名次必须严格小于 `p`（即优于当前队伍）；
- 后 $R - k$ 行中的所有队伍，若参加了比赛 `c`，则其名次必须严格大于 `p`（即劣于当前队伍）。

注意：在检查时，`rows` 中可能包含已经通过规则 A 插入的单赛队伍。这些队伍可能没有参加比赛 `c`，此时应跳过它们（名次值为 $0$ 时视为不存在，不参与比较）。

若只有一个合法的 `k`，则将该队伍记录到 `posTeams[k]` 中，等待后续插入。若有多个或零个合法位置，则该队伍排名无法确定，不输出。

### 插入规则 $\texttt{B}$ 产生的队伍

对于 `posTeams` 中的每个位置，收集所有竞争该位置的队伍。先按它们在该场比赛中的名次升序排序，再按名次分组（同名次一组）。为了保持插入后原有行顺序不变，从位置最大的键开始，从后往前插入。具体为：对每个组（已按名次升序），将其作为一个新行插入到 `rows.begin() + pos` 位置。由于是从后往前插入，先插入名次大的组（实际上从后往前保证了最终顺序为名次升序）。

### 输出

按行输出 `rows` 中所有队伍，同行空格分隔。数据集间输出空行。

## 代码实现

```cpp
// Rating
// UVa ID: 666
// Verdict: Accepted
// Submission Date: 2026-07-03
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

int place1[110], place2[110];

bool isBetter(int a, int b) {
    int a1 = place1[a], a2 = place2[a];
    int b1 = place1[b], b2 = place2[b];
    if (a1 <= b1 && a2 <= b2 && (a1 < b1 || a2 < b2)) return true;
    if (b1 <= a1 && b2 <= a2 && (b1 < a1 || b2 < a2)) return false;
    int diff1 = b1 - a1, diff2 = b2 - a2;
    return diff1 + diff2 > 0;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    int M;
    cin >> M;
    for (int ds = 0; ds < M; ++ds) {
        memset(place1, 0, sizeof place1);
        memset(place2, 0, sizeof place2);
        int N1; cin >> N1; cin.ignore(128, '\n');
        int total = 0;
        for (int i = 0; i < N1; ++i) {
            string line; getline(cin, line);
            stringstream ss(line);
            int id;
            int p = total + 1;
            while (ss >> id) { place1[id] = p; ++total; }
        }
        int N2; cin >> N2; cin.ignore(128, '\n');
        total = 0;
        for (int i = 0; i < N2; ++i) {
            string line; getline(cin, line);
            stringstream ss(line);
            int id;
            int p = total + 1;
            while (ss >> id) { place2[id] = p; ++total; }
        }
        vector<int> twoTeams;
        for (int id = 1; id <= 100; id++)
            if (place1[id] && place2[id])
                twoTeams.push_back(id);
        sort(twoTeams.begin(), twoTeams.end(), isBetter);
        vector<vector<int>> rows;
        for (int i = 0; i < (int)twoTeams.size();) {
            vector<int> row;
            row.push_back(twoTeams[i]);
            int j = i + 1;
            while (j < (int)twoTeams.size() &&
                   !isBetter(twoTeams[i], twoTeams[j]) &&
                   !isBetter(twoTeams[j], twoTeams[i])) {
                row.push_back(twoTeams[j]);
                ++j;
            }
            rows.push_back(row);
            i = j;
        }
        map<int, vector<int>> posTeams; // 位置 -> 待插入队伍
        for (int id = 1; id <= 100; id++) {
            if (place1[id] && place2[id]) continue;
            if (!place1[id] && !place2[id]) continue;
            int c = (place1[id] ? 1 : 2);
            int p = (c == 1 ? place1[id] : place2[id]);
            // 规则 A
            vector<int> matched;
            for (int t : twoTeams) {
                if (c == 1 && place1[t] == p) matched.push_back(t);
                else if (c == 2 && place2[t] == p) matched.push_back(t);
            }
            if (!matched.empty()) {
                int rowIdx = -1;
                bool ok = true;
                for (int t : matched) {
                    int idx = -1;
                    for (int i = 0; i < (int)rows.size(); ++i) {
                        if (find(rows[i].begin(), rows[i].end(), t) != rows[i].end()) {
                            idx = i; break;
                        }
                    }
                    if (idx == -1) { ok = false; break; }
                    if (rowIdx == -1) rowIdx = idx;
                    else if (rowIdx != idx) { ok = false; break; }
                }
                // 能唯一确定则添加
                if (ok) rows[rowIdx].push_back(id);
                // 不能唯一确定则不列出
                continue;
            }
            // 规则 B
            int R = rows.size();
            vector<int> validPos;
            for (int k = 0; k <= R; ++k) {
                bool valid = true;
                for (int i = 0; i < k; ++i) {
                    for (int t : rows[i]) {
                        int pt = (c == 1 ? place1[t] : place2[t]);
                        if (pt && pt >= p) { valid = false; break; }
                    }
                    if (!valid) break;
                }
                if (!valid) continue;
                for (int i = k; i < R; ++i) {
                    for (int t : rows[i]) {
                        int pt = (c == 1 ? place1[t] : place2[t]);
                        if (pt && pt <= p) { valid = false; break; }
                    }
                    if (!valid) break;
                }
                if (valid) validPos.push_back(k);
            }
            if (validPos.size() == 1) posTeams[validPos[0]].push_back(id);
        }
        // 插入规则 B 产生的行
        vector<int> keys;
        for (auto &kv : posTeams) keys.push_back(kv.first);
        sort(keys.begin(), keys.end(), greater<int>());
        for (int pos : keys) {
            vector<int> &v = posTeams[pos];
            sort(v.begin(), v.end(), [&](int a, int b) {
                int pa = (place1[a] ? place1[a] : place2[a]);
                int pb = (place1[b] ? place1[b] : place2[b]);
                return pa < pb;
            });
            vector<vector<int>> groups;
            for (int i = 0; i < (int)v.size();) {
                int j = i + 1;
                int pa = (place1[v[i]] ? place1[v[i]] : place2[v[i]]);
                while (j < (int)v.size() &&
                       (place1[v[j]] ? place1[v[j]] : place2[v[j]]) == pa) ++j;
                vector<int> group(v.begin() + i, v.begin() + j);
                groups.push_back(group);
                i = j;
            }
            for (int g = (int)groups.size() - 1; g >= 0; --g)
                rows.insert(rows.begin() + pos, groups[g]);
        }
        // 输出
        for (int i = 0; i < rows.size(); ++i) {
            for (int j = 0; j < rows[i].size(); ++j) {
                if (j) cout << ' ';
                cout << rows[i][j];
            }
            cout << '\n';
        }
        if (ds != M - 1) cout << '\n';
    }
    return 0;
}
```

## 总结

本题的关键在于准确实现比较函数，并正确处理规则 $\texttt{A}$ 和规则 $\texttt{B}$ 的优先级与插入逻辑。需要注意以下几点：

- 比较函数在互有胜负时的简化需保证正确性，利用差分和的正负来判断绝对值大小。
- 规则 $\texttt{A}$ 失败后不能再尝试规则 $\texttt{B}$，因为规则 $\texttt{A}$ 的判定结果已经决定了该队伍排名是否可确定。
- 规则 $\texttt{B}$ 的位置检查必须考虑 `rows` 中可能已存在的单赛队伍，这些队伍可能缺少当前比较所需的比赛名次，应跳过。
- 插入多支竞争同一位置的队伍时，需要按名次分组，并从后往前插入以保持相对顺序。

使用固定数组存储名次，结合 `std::sort`，代码简洁且高效，足以通过本题。
