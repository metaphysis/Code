
> **摘要**：本题要求在若干关于「人员—物品」颜色线索的约束下，推断每位客人每件物品的确定颜色。核心做法是：由于所有线索都限定在单一物品上，各物品相互独立，可分别处理；对每个物品用并查集把「相同颜色」的人员合并为等价类，再用整数位掩码维护每个等价类的候选颜色集合，「颜色为 $Y$」做交集、「颜色不为 $Y$」做差集；若某等价类候选集合为空则输出 `Contradiction`，否则候选集合仅剩一种颜色时即为确定颜色，多于一种则输出 `?`。整体时间复杂度约 $O(i \cdot m + u \cdot \alpha(m))$，空间复杂度 $O(i \cdot m)$。

## 题目描述

聚会中有多位客人，其中三位（唐娜·安娜、唐娜·埃尔维拉和唐·奥塔维奥）戴着面具，意欲与唐·乔瓦尼对质。作为普通客人，你希望避开他们，但你无法直接辨认出他们的身份。你从其他客人处收集到若干关于衣着物品颜色的线索，需要根据这些线索确定每一位客人每一件物品的颜色。

每个客人有 $i$ 件物品（例如鞋子、面具、衣服等），每件物品都可以染上 $c$ 种颜色之一（颜色编号为 $0$ 到 $c-1$）。线索共有三种类型：

- **相同颜色**：对于物品 $X$，所列人员具有相同的颜色。
- **颜色为** $Y$：对于物品 $X$，所列人员的颜色就是 $Y$。
- **颜色不为** $Y$：对于物品 $X$，所列人员的颜色不是 $Y$。

如果所有线索能够同时满足，则输出每位客人（按字母顺序）每件物品的确定颜色；若某件物品的颜色无法由线索唯一确定，则输出 `?`。若线索集合本身矛盾（即不存在任何颜色赋值满足所有线索），则输出 `Contradiction`。

---

## 输入格式

输入第一行为一个正整数，表示测试用例的个数。  
每个测试用例以一行四个正整数 $n$、$i$、$c$、$u$ 开头，分别表示：

- $n$：线索所涉及的总人数（最多 $26$ 人，用大写字母 A–Z 表示）；
- $i$：物品总数（最多 $10$ 件，编号 $0$ 到 $i-1$）；
- $c$：颜色总数（最多 $10$ 种，编号 $0$ 到 $c-1$）；
- $u$：线索条数。

接下来 $u$ 行，每行描述一条线索。线索行的格式为：

- `Same colour of item X = <list>`，其中 `<list>` 是按字母顺序排列的若干大写字母；
- `Colour Y for item X = <list>`；
- `Not colour Y for item X = <list>`。

所有单词、字母、数字之间均由单个空格分隔。  
两个连续测试用例的输入之间有一个空行（但处理时可忽略空白行）。

---

## 输出格式

对于每个测试用例：

- 若线索不一致，则输出一行 `Contradiction`；
- 否则输出 $n$ 行，每行对应一个人物（按字母序），格式为 `P C0 C1 ... C_{i-1}`，其中 $P$ 是该人物的大写字母，$C_j$ 是物品 $j$ 的确定颜色编号，若无法确定则输出 `?`。

两个测试用例的输出之间用一个空行隔开。

---

## 样例

**输入**
```text
2

4 2 3 6
Same colour of item 0 = A B D
Colour 2 for item 0 = B
Not colour 2 for item 1 = C
Not colour 1 for item 1 = C
Same colour of item 1 = C D
Same colour of item 1 = A D

4 2 3 7
Same colour of item 0 = A B D
Colour 2 for item 0 = B
Not colour 2 for item 1 = C
Not colour 1 for item 1 = C
Same colour of item 1 = C D
Same colour of item 1 = A D
Colour 1 for item 0 = D
```

**输出**
```text
A 2 0
B 2 ?
C ? 0
D 2 0

Contradiction
```

---

## 题目分析

本题的约束对象是“（人员，物品）”二元组。记人员集合为 $\mathcal{P}$，物品集合为 $\mathcal{I}$，颜色集合为 $\mathcal{C}$。每个二元组 $(p, x)$ 的取值域为 $\mathcal{C}$（$0$ 到 $c-1$）。

三种线索分别等价于：

- **相同颜色**：对于固定物品 $x$，所有出现在列表中的人员 $p_1, p_2, \dots, p_k$ 的 $(p, x)$ 变量取值相等。
- **颜色为 $Y$**：对于固定物品 $x$，列表中每个人员 $p$ 的 $(p, x)$ 变量只能取颜色 $Y$。
- **颜色不为 $Y$**：对于固定物品 $x$，列表中每个人员 $p$ 的 $(p, x)$ 变量不能取颜色 $Y$。

注意到不同物品之间没有交叉约束（因为所有线索都限定在单一物品 $X$ 上），因此每个物品的约束可以独立处理。但由于同一个人在不同物品上的颜色是分开的，我们只需为每个物品独立维护其等价类和候选颜色集合。

约束的“相同颜色”本质上是将同一物品下的若干变量强制相等，这可以用并查集将变量合并为等价类。合并后，每个等价类具有统一的候选颜色集合。后续的“颜色为”和“颜色不为”操作则是对该集合进行交集或差集（排除）运算。若某个等价类的候选集合为空，则矛盾。

因为 $n \le 26$、$i \le 10$、$c \le 10$，变量总数最多 $260$，颜色种类数不超过 $10$，可以用一个整数位掩码（$0$ 到 $2^c-1$）表示候选颜色集合，位操作非常高效。

---

## 解题思路

### 步骤 $\texttt{1}$：读取并解析输入

每个测试用例先读入 $n$、$i$、$c$、$u$，然后读取 $u$ 行线索。在处理线索之前，需要确定所有出现过的人员字母，并按照字母序排序，建立字母到索引的映射。这是因为输出要求按字母序排列，且并查集的大小需要等于实际出现的人数（可能小于 $26$）。注意题目保证 $n$ 与线索中出现的人数一致，但为了安全我们以实际出现集合为准。

### 步骤 $\texttt{2}$：为每个物品建立独立的并查集

对每个物品 $x$（$0 \le x < i$），创建一个大小为 $m$（$m$ 为实际人数）的并查集，$m$ 个节点分别对应按字母序排列的 $m$ 个人。

同时，为每个物品 $x$ 和每个人 $p$ 维护一个整数掩码 $\textit{mask}[x][p]$，初始值为 $(1 \ll c) - 1$，表示所有颜色都可选。注意该掩码只在并查集的根节点上有效。

### 步骤 $\texttt{3}$：处理相同颜色线索（合并等价类）

遍历所有线索，若第一条单词为 `Same`，则解析出物品编号 $X$ 和人员列表。将列表中第一个人与其余每个人在物品 $X$ 的并查集上执行合并操作。这样，所有被声明为相同颜色的人员在对应物品上成为同一等价类。

### 步骤 $\texttt{4}$：处理颜色确定与排除线索（更新掩码）

再次遍历所有线索，若第一条单词为 `Colour` 或 `Not`，则分别解析出颜色 $Y$、物品 $X$ 和人员列表。对于列表中的每一个人 $p$：

- 找到该人员在物品 $X$ 并查集中的根节点 $r$；
- 若为 `Colour Y`，则令 $\textit{mask}[X][r] \gets \textit{mask}[X][r] \;\&\; (1 \ll Y)$；
- 若为 `Not Y`，则令 $\textit{mask}[X][r] \gets \textit{mask}[X][r] \;\&\; \sim (1 \ll Y)$。

这里使用按位与运算缩小候选集合。注意掩码为 `int` 类型，$c \le 10$，故安全。

### 步骤 $\texttt{5}$：检查矛盾

对于每个物品 $x$ 和每个人 $p$，找到根节点 $r$，若 $\textit{mask}[x][r] = 0$，则说明该等价类没有任何可选颜色，线索矛盾，输出 `Contradiction`。

### 步骤 $\texttt{6}$：输出结果

若未矛盾，则按字母序输出每个人 $p$。对于每个物品 $x$，找到根节点 $r$，若 $\textit{mask}[x][r]$ 为 $2$ 的幂（即只有一位为 $1$），则该位对应的颜色编号即为确定的颜色；否则输出 `?`。判断方法为 `(mask & (mask - 1)) == 0`。

两个测试用例的输出之间用空行分隔。

---

## 复杂度分析

- 设实际人数为 $m$（$m \le 26$），物品数为 $i$（$i \le 10$），颜色数为 $c$（$c \le 10$），线索数为 $u$（$u$ 无明确上限，但总输入规模有限）。
- 并查集操作近似 $O(\alpha(m))$，其中 $\alpha$ 为反阿克曼函数。
- 每条线索只需解析一次，且所有操作均在常数时间内完成。
- 时间复杂度为 $O(i \cdot m + u \cdot \alpha(m))$，实际上非常小。
- 空间复杂度为 $O(i \cdot m)$，用于存储掩码和并查集。

---

## 代码实现

```cpp
// The Party Part II
// UVa ID: 10960
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    vector<int> parent, rank;
    UnionFind(int n) { parent.resize(n); rank.assign(n, 0); for (int i = 0; i < n; ++i) parent[i] = i; }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (rank[ra] < rank[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rank[ra] == rank[rb]) ++rank[ra];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int n, i, c, u;
        cin >> n >> i >> c >> u;
        cin.ignore();
        vector<string> lines(u);
        set<char> peopleSet;
        for (int k = 0; k < u; ++k) {
            getline(cin, lines[k]);
            size_t eqPos = lines[k].find('=');
            if (eqPos != string::npos) {
                string rest = lines[k].substr(eqPos + 1);
                for (char ch : rest)
                    if (ch >= 'A' && ch <= 'Z') peopleSet.insert(ch);
            }
        }
        vector<char> persons(peopleSet.begin(), peopleSet.end());
        unordered_map<char, int> idx;
        for (int p = 0; p < (int)persons.size(); ++p) idx[persons[p]] = p;
        vector<UnionFind> uf;
        for (int x = 0; x < i; ++x) uf.emplace_back(persons.size());
        vector<vector<int>> mask(i, vector<int>(persons.size(), (1 << c) - 1));
        // 第一遍：处理 Same 合并
        for (const string& line : lines) {
            istringstream iss(line);
            string first;
            iss >> first;
            if (first == "Same") {
                string tmp; iss >> tmp; // colour
                iss >> tmp; // of
                iss >> tmp; // item
                int X; iss >> X;
                iss >> tmp; // =
                vector<char> people;
                char p;
                while (iss >> p) people.push_back(p);
                if (people.size() > 1) {
                    int firstIdx = idx[people[0]];
                    for (int q = 1; q < (int)people.size(); ++q) {
                        int otherIdx = idx[people[q]];
                        uf[X].unite(firstIdx, otherIdx);
                    }
                }
            }
        }
        // 第二遍：处理 Colour 和 Not
        for (const string& line : lines) {
            istringstream iss(line);
            string first;
            iss >> first;
            if (first == "Colour") {
                int Y; iss >> Y;
                string tmp; iss >> tmp; // for
                iss >> tmp; // item
                int X; iss >> X;
                iss >> tmp; // =
                vector<char> people;
                char p;
                while (iss >> p) people.push_back(p);
                for (char person : people) {
                    int id = idx[person];
                    int root = uf[X].find(id);
                    mask[X][root] &= (1 << Y);
                }
            } else if (first == "Not") {
                string tmp; iss >> tmp; // colour
                int Y; iss >> Y;
                iss >> tmp; // for
                iss >> tmp; // item
                int X; iss >> X;
                iss >> tmp; // =
                vector<char> people;
                char p;
                while (iss >> p) people.push_back(p);
                for (char person : people) {
                    int id = idx[person];
                    int root = uf[X].find(id);
                    mask[X][root] &= ~(1 << Y);
                }
            }
        }
        bool contradiction = false;
        for (int x = 0; x < i && !contradiction; ++x)
            for (int id = 0; id < (int)persons.size(); ++id) {
                int root = uf[x].find(id);
                if (mask[x][root] == 0) { contradiction = true; break; }
            }
        if (contradiction) cout << "Contradiction\n";
        else {
            for (char person : persons) {
                cout << person;
                for (int x = 0; x < i; ++x) {
                    int root = uf[x].find(idx[person]);
                    int m = mask[x][root];
                    cout << ' ';
                    if ((m & (m - 1)) == 0) { // 只有一位
                        int color = __builtin_ctz((unsigned)m);
                        cout << color;
                    } else {
                        cout << '?';
                    }
                }
                cout << '\n';
            }
        }
        if (tc != T) cout << '\n'; // 用例间空行
    }
    return 0;
}
```

---

## 总结

本题的核心思想是 **等价类合并 + 候选集合位运算**。

- 利用并查集处理“相同颜色”的等价关系，将约束简化到每个等价类上。
- 利用位掩码表示颜色集合，可以高效地进行交集和差集运算。
- 由于物品之间独立，可以分别处理每个物品，降低问题规模。
- 最终判断矛盾的条件是某个等价类的候选颜色集合为空；否则，若集合大小为 $1$ 则确定颜色，否则为 `?`。

这种模式在处理“相等关系 + 取值范围约束”类问题时十分常见，适合使用并查集搭配位运算或集合差分来处理。本题规模很小，但算法具有通用性，也可扩展至更大型的数据。
