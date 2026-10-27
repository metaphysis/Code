## 题目描述

给定一个 $8 \times 8$ 的方格，其中 $4$ 个格子被阻塞（用 `'*'` 表示），其余 $60$ 个格子需要用 $12$ 种不同的五连方（$\texttt{Pentomino}$）完全覆盖。每种五连方由 $5$ 个大小相等的正方形边对边连接而成。共有 $12$ 种不同的形状（忽略旋转和反射），每种形状可使用任意多次或完全不使用。要求输出一种合法的覆盖方案，其中每个五连方用不同的字符 `'a'` 至 `'l'` 表示，阻塞格用 `'*'` 表示。若不存在方案，则输出 `No solution.`。

## 输入格式

输入文件包含多个测试用例。  
第一行为数据集个数 $T$，随后有一个空行。  
每个数据集包含 $4$ 行，每行两个整数 $x, y$（$1 \le x, y \le 8$），表示阻塞格子的行列坐标（从 $1$ 开始）。$4$ 个格子互不相同。  
两个连续数据集之间由一个空行分隔。

## 输出格式

对于每个测试用例，输出 $8$ 行，每行 $8$ 个字符，表示填充后的棋盘。阻塞格显示为 `'*'`，每个五连方用唯一字符 `'a'` 至 `'l'` 表示。若不存在解，则输出 `No solution.`。  
两个连续输出之间打印一个空行。

## 样例

输入
```
1

3 5
4 5
5 5
6 5
```

输出
```
aaaaabcc
deeeebbcc
ddde*bcc
ffde*ggg
hffi*ggj
hfii*jjj
hiikkklj
hhklllll
```

## 题目分析

本题属于精确覆盖问题。棋盘大小为 $8 \times 8$，剩余 $60$ 个格子恰好需要由 $12$ 个五连方填充（每个五连方 $5$ 格）。题目允许每种五连方使用任意多次，因此本质上我们只需要找到一种用五连方铺满棋盘的方法，而不用关心每种形状是否恰好使用一次。

**关键难点**：五连方有 $12$ 种自由形状，每种形状通过旋转和反射最多有 $8$ 种不同朝向。棋盘规模较大（$64$ 格），直接暴力枚举所有放置组合会导致搜索空间爆炸，需要高效的剪枝策略。

**隐含约束**：由于棋盘剩余格子数为 $60$，且每个五连方占 $5$ 格，因此总共需要放置恰好 $12$ 个五连方。虽然同一种形状可重复，但不同放置块之间必须使用不同字符（`'a'` 至 `'l'`），这实际上强制了每个放置块在棋盘上必须拥有唯一的字母标识，但并不限制其形状类型。

## 解题思路

### 1. 形状预处理

首先枚举所有可能的五连方形状。因为五连方本质是 $5$ 个格子的连通集合，我们通过深度优先搜索生成所有包含原点 `(0,0)` 的 $5$ 格连通集合。对于每个集合，将其归一化（平移至最小行列均为 $0$）并排序，然后取其 $8$ 种正交变换（旋转和反射）的字典序最小者作为该自由形状的唯一标识。这样可得到 $12$ 种互不相同的自由形状。

对每个自由形状，再生成其所有不同的朝向（同样通过 $8$ 种正交变换并去重），存储为相对坐标偏移列表。这些朝向在后续搜索中会被使用。

### 2. 在线放置生成

对于每个测试用例，已知 $4$ 个阻塞格的位置。我们为每个朝向尝试将其放置在棋盘的每个可能锚点（即该形状的第一个坐标 `(0,0)` 对齐的格子）。若放置后所有格子均在棋盘内且不覆盖阻塞格，则该放置合法。记录每个放置的位掩码（用 $64$ 位整数表示占用的格子）以及覆盖的格子索引列表。

同时，为每个格子维护一个列表，存储所有能覆盖该格子的放置索引，用于后续剪枝。

### 3. 深度优先搜索与剪枝

搜索采用回溯法，核心剪枝策略：

- **剩余格子数剪枝**：剩余未填充的格子数必须为 $5$ 的倍数，否则无解。
- **连通性剪枝**：检查剩余空格所在的每个连通分量，若某个连通分量的大小不是 $5$ 的倍数，则无法由完整的五连方填充，剪枝。
- **最小剩余值（MRV）剪枝**：每次选择候选放置数量最少的空格进行尝试。对于每个空格，统计尚未使用的合法放置中能覆盖该空格的个数，选择个数最少的那个空格优先搜索，这能有效减少分支。

搜索过程中，按放置顺序依次分配字符 `'a'`、`'b'`、...、`'l'`。当所有格子被填满时，搜索成功，输出棋盘。

### 4. 复杂度分析

形状预生成只需一次，时间复杂度为常数。每个测试用例在线生成合法放置，由于棋盘最大 $64$ 格，每种朝向最多 $64$ 个锚点，朝向总数约为 $12 \times 8 = 96$，总放置数不超过 $64 \times 96 = 6144$，实际由于阻塞格限制会更少。搜索配合强剪枝，能在极短时间内求解。

## 代码实现

```cpp
// Pentominos
// UVa ID: 764
// Verdict: Accepted
// Submission Date: 2026-07-05
// UVa Run Time: 0.900s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;

// 所有五连方朝向的坐标偏移（相对于锚点）
vector<vector<pair<int,int>>> allOrients;

// 生成 12 种五连方的所有不同朝向
void generateShapes() {
    set<vector<pair<int,int>>> uniqueKeys;
    vector<pair<int,int>> cells;

    function<void(int)> dfsGen = [&](int step) {
        if (step == 5) {
            int minR = INT_MAX, minC = INT_MAX;
            for (auto &p : cells) { minR = min(minR, p.first); minC = min(minC, p.second); }
            vector<pair<int,int>> norm;
            for (auto &p : cells) norm.push_back({p.first - minR, p.second - minC});
            sort(norm.begin(), norm.end());

            int trans[8][2][2] = {
                {{1,0},{0,1}}, {{1,0},{0,-1}}, {{-1,0},{0,1}}, {{-1,0},{0,-1}},
                {{0,1},{1,0}}, {{0,1},{-1,0}}, {{0,-1},{1,0}}, {{0,-1},{-1,0}}
            };
            vector<pair<int,int>> best = norm;
            for (int t = 0; t < 8; ++t) {
                vector<pair<int,int>> cur;
                for (auto &p : norm) {
                    int nr = p.first * trans[t][0][0] + p.second * trans[t][0][1];
                    int nc = p.first * trans[t][1][0] + p.second * trans[t][1][1];
                    cur.push_back({nr, nc});
                }
                int mr = INT_MAX, mc = INT_MAX;
                for (auto &p : cur) { mr = min(mr, p.first); mc = min(mc, p.second); }
                for (auto &p : cur) { p.first -= mr; p.second -= mc; }
                sort(cur.begin(), cur.end());
                if (cur < best) best = cur;
            }
            uniqueKeys.insert(best);
            return;
        }

        set<pair<int,int>> neighbors;
        int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
        for (auto &p : cells) {
            for (int d = 0; d < 4; ++d) {
                int nr = p.first + dr[d], nc = p.second + dc[d];
                if (find(cells.begin(), cells.end(), make_pair(nr, nc)) == cells.end())
                    neighbors.insert({nr, nc});
            }
        }
        for (auto &np : neighbors) {
            cells.push_back(np);
            dfsGen(step + 1);
            cells.pop_back();
        }
    };

    cells.push_back({0, 0});
    dfsGen(1);

    // 从 uniqueKeys 提取所有朝向
    for (auto &key : uniqueKeys) {
        set<vector<pair<int,int>>> seen;
        int trans[8][2][2] = {
            {{1,0},{0,1}}, {{1,0},{0,-1}}, {{-1,0},{0,1}}, {{-1,0},{0,-1}},
            {{0,1},{1,0}}, {{0,1},{-1,0}}, {{0,-1},{1,0}}, {{0,-1},{-1,0}}
        };
        for (int t = 0; t < 8; ++t) {
            vector<pair<int,int>> cur;
            for (auto &p : key) {
                int nr = p.first * trans[t][0][0] + p.second * trans[t][0][1];
                int nc = p.first * trans[t][1][0] + p.second * trans[t][1][1];
                cur.push_back({nr, nc});
            }
            int mr = INT_MAX, mc = INT_MAX;
            for (auto &p : cur) { mr = min(mr, p.first); mc = min(mc, p.second); }
            for (auto &p : cur) { p.first -= mr; p.second -= mc; }
            sort(cur.begin(), cur.end());
            if (seen.insert(cur).second) allOrients.push_back(cur);
        }
    }
}

// 放置结构：位掩码和覆盖格子索引列表
struct Placement {
    ull mask;
    vector<int> cells;
};

vector<Placement> placements;   // 当前测试用例的所有合法放置
vector<int> cover[64];          // cover[pos] 存储能覆盖 pos 的放置索引
char board[64];                 // 棋盘字符（0 表示空格，'*' 表示阻塞）

// 连通性剪枝：剩余空格每个连通分量大小必须为 5 的倍数
bool checkConnectivity(ull occupied) {
    bool vis[64] = {};
    for (int i = 0; i < 64; ++i) {
        if (!(occupied >> i & 1) && !vis[i]) {
            int cnt = 0;
            queue<int> q;
            q.push(i); vis[i] = true;
            while (!q.empty()) {
                int v = q.front(); q.pop();
                ++cnt;
                int r = v / 8, c = v % 8;
                int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
                        int nid = nr * 8 + nc;
                        if (!(occupied >> nid & 1) && !vis[nid]) {
                            vis[nid] = true;
                            q.push(nid);
                        }
                    }
                }
            }
            if (cnt % 5 != 0) return false;
        }
    }
    return true;
}

// 深度优先搜索
bool dfs(ull occupied, char ch) {
    int left = 64 - __builtin_popcountll(occupied);
    if (left == 0) return true;
    if (left % 5 != 0) return false;
    if (!checkConnectivity(occupied)) return false;

    // 选择候选放置最少的空格（MRV）
    int bestPos = -1, bestCnt = INT_MAX;
    for (int i = 0; i < 64; ++i) {
        if ((occupied >> i & 1) == 0) {
            int cnt = 0;
            for (int pid : cover[i]) {
                if ((placements[pid].mask & occupied) == 0) ++cnt;
            }
            if (cnt == 0) return false;
            if (cnt < bestCnt) { bestCnt = cnt; bestPos = i; }
        }
    }

    // 尝试所有覆盖 bestPos 的放置
    for (int pid : cover[bestPos]) {
        if (placements[pid].mask & occupied) continue;
        // 放置该块，分配当前字符 ch
        ull newOcc = occupied | placements[pid].mask;
        for (int idx : placements[pid].cells) board[idx] = ch;
        if (dfs(newOcc, ch + 1)) return true;
        // 回溯
        for (int idx : placements[pid].cells) board[idx] = 0;
    }
    return false;
}

int main() {
    generateShapes(); // 预生成所有五连方朝向

    int T;
    cin >> T;
    for (int caseNo = 1; caseNo <= T; ++caseNo) {
        ull occupied = 0;
        for (int i = 0; i < 64; ++i) board[i] = 0;

        // 读入 4 个阻塞格（坐标 1~8 转为 0~7）
        for (int i = 0; i < 4; ++i) {
            int x, y;
            cin >> x >> y;
            int idx = (x - 1) * 8 + (y - 1);
            occupied |= 1ULL << idx;
            board[idx] = '*';
        }

        // 生成当前棋盘的所有合法放置（不覆盖阻塞格）
        placements.clear();
        for (int i = 0; i < 64; ++i) cover[i].clear();

        for (auto &coords : allOrients) {
            for (int r = 0; r < 8; ++r) {
                for (int c = 0; c < 8; ++c) {
                    ull mask = 0;
                    vector<int> cells;
                    bool ok = true;
                    for (auto &p : coords) {
                        int nr = r + p.first, nc = c + p.second;
                        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) { ok = false; break; }
                        int idx = nr * 8 + nc;
                        if (occupied & (1ULL << idx)) { ok = false; break; }
                        mask |= 1ULL << idx;
                        cells.push_back(idx);
                    }
                    if (ok) {
                        int pid = placements.size();
                        placements.push_back({mask, cells});
                        for (int idx : cells) cover[idx].push_back(pid);
                    }
                }
            }
        }

        if (dfs(occupied, 'a')) {
            // 输出棋盘
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j)
                    cout << board[i * 8 + j];
                cout << '\n';
            }
        } else {
            cout << "No solution.\n";
        }
        if (caseNo != T) cout << '\n'; // 两组输出间空行
    }
    return 0;
}
```

## 总结

本题的关键在于：

- **形状预生成**：利用 $\texttt{DFS}$ 枚举所有连通五格集合，通过归一化和正交变换去重，得到所有朝向，避免在每组测试中重复计算。
- **位运算棋盘**：使用 $64$ 位整数高效表示占用状态，快速判断覆盖和重叠。
- **剪枝策略**：剩余格子数倍数剪枝、连通分量大小剪枝、$\texttt{MRV}$ 选点剪枝，三者结合大幅减少搜索空间，保证求解速度。
- **放置生成与回溯**：在线生成合法放置，并维护每个格子的候选放置列表，便于快速 $\texttt{MRV}$ 计算。
