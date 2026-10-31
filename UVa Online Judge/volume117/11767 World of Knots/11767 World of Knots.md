# 题目描述

给定一幅由字符网格表示的开放绳子图。图中包含绳子的线段、交叉点和两个端点，交叉点标记为 `H` 或 `I`，分别表示水平线段或竖直线段从上方通过。判断能否通过反复消去第一类和第二类 Reidemeister 局部结构，将绳子化简为空；若可以，输出 `straightened`，否则输出 `knotted`。

本题按题目评测所采用的约简规则判断，不进行第三类 $\texttt{Reidemeister}$ 移动，也不尝试一般意义上的完整结识别。

# 输入格式

输入包含多组数据。每组数据的第一行包含网格的行数 $R$ 和列数 $C$。随后输入 $R$ 行网格，每行包含 $C$ 个字符。输入以 $R=C=0$ 结束。

# 输出格式

对于每组数据，输出一行，格式为 `Case k: answer`。其中 $k$ 是从 $1$ 开始递增的组号，`answer` 为 `straightened` 或 `knotted`。

# 样例输入

```text
9 15
...............
...+------+....
...|......|....
...|...+--H----
...|...|..|....
---I---H--+....
...|...|.......
...+---+.......
...............
9 15
...............
...+------+....
...|......|....
...|...+--I----
...|...|..|....
---I---H--+....
...|...|.......
...+---+.......
...............
0 0
```

# 样例输出

```text
Case 1: knotted
Case 2: straightened
```

# 题目分析

网格描述的是一条具有两个开放端点的绳子。沿绳子从一个端点走到另一个端点时，每经过一个交叉点，就记录该交叉点的编号、进入和离开交叉点的方向，以及当前经过的绳段是上层还是下层。按走过的先后顺序排列这些记录，得到开放绳子的 $\texttt{Gauss}$ 编码。

第一类消去对应一个小卷曲：同一个交叉点在编码中相邻出现时，可以删除这两次访问。第二类消去对应两个交叉点之间形成的二边形面。仅仅发现两个交叉点之间有两段连接弧还不够；这两段弧必须在平面图中围成同一个面，并且一条弧在两个交叉点处都处于上层，另一条弧在两个交叉点处都处于下层。

开放绳子的两个端点必须始终分开处理。因此，编码首尾不能视为相邻，也不能添加连接两个端点的虚构弧。题目采用不断进行第一类和第二类局部消去的判定过程；当编码变为空时输出 `straightened`，当没有可执行的消去且编码仍非空时输出 `knotted`。

# 解题思路

首先，从网格中寻找度数为 $1$ 的格点作为起点。按线段连通关系沿绳子追踪：在普通线段处继续沿唯一的另一条连接前进，在交叉点处沿进入方向的对向离开。每个交叉点第一次被访问时分配一个编号，并记录该次访问的进入端口、离开端口和上下层信息。追踪到另一个度数为 $1$ 的格点时结束，整个过程生成开放绳子的 $\texttt{Gauss}$ 编码。

接下来重复执行两种局部约简。第一类约简从左到右扫描编码，使用原地栈式处理：如果当前访问与栈顶访问属于同一个交叉点，就删除二者；否则保留当前访问。这样能在线性时间内消去连续出现的卷曲结构。

第二类约简扫描编码中相邻的访问，构造它们之间的弧。每条弧记录两端交叉点编号、交叉点处的端口方向、上下层状态以及在编码中的位置。先按无序交叉点编号对弧分组，再检查同组中的两条弧是否满足以下条件：

- 两条弧在各自两个交叉点处分别保持相同的上下层状态。
- 两条弧的上下层状态相反，一条始终在上层，另一条始终在下层。
- 两条弧的端口方向在两个交叉点处围成同一个二边形面。
- 两次弧出现位置不重叠，并且涉及的交叉点尚未参与本轮消去。

找到的可消二边形会在同一轮中批量删除。代码通过 `used` 标记保证本轮选中的二边形互不冲突，通过 `del` 标记统一删除对应访问。批量删除后重新执行第一类和第二类约简，直到编码为空或第二类约简不再产生删除。

设网格大小为 $R \times C$，交叉点数量为 $K$。建立编码需要 $O(RC)$ 时间和 $O(RC+K)$ 空间。每轮约简需要 $O(K)$ 的编码扫描以及哈希表分组操作；最多发生 $O(K)$ 轮成功消去，因此整体最坏时间复杂度为 $O(RC+K^2)$，空间复杂度为 $O(RC+K)$。

# 代码实现

```cpp
// World of Knots
// UVa ID: 11767
// Verdict: Accepted
// Submission Date: 2026-10-31
// UVa Run Time: 0.130s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Event { int cross, in, out; bool over; };
struct Arc   { int id1, id2, port1, port2, pos; bool over1, over2; };

int R, C;
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};
vector<string> grid;

inline bool inside(int r, int c) { return r >= 0 && r < R && c >= 0 && c < C; }

inline bool linked(int r, int c, int d) {
    int nr = r + dr[d], nc = c + dc[d];
    if (!inside(nr, nc)) return false;
    char a = grid[r][c], b = grid[nr][nc];
    if (a == '.' || b == '.') return false;
    return (d == 0 || d == 2) ? (a != '-' && b != '-') : (a != '|' && b != '|');
}

inline bool isX(char ch) { return ch == 'H' || ch == 'I'; }

inline int dirBetween(int r, int c, int nr, int nc) {
    for (int d = 0; d < 4; d++)
        if (r + dr[d] == nr && c + dc[d] == nc) return d;
    return -1;
}

// 追踪整条开放字符串生成 Gauss code（首尾两个端点不视为相邻）
vector<Event> buildCode() {
    int sr = -1, sc = -1;
    for (int r = 0; r < R && sr < 0; r++)
        for (int c = 0; c < C; c++) {
            if (grid[r][c] == '.') continue;
            int deg = 0;
            for (int d = 0; d < 4; d++) if (linked(r, c, d)) deg++;
            if (deg == 1) { sr = r; sc = c; break; }
        }
    if (sr < 0) return {};

    vector<vector<int>> cid(R, vector<int>(C, 0));
    vector<Event> code;

    int pr = sr, pc = sc, cr = -1, cc = -1;
    for (int d = 0; d < 4; d++)
        if (linked(pr, pc, d)) { cr = pr + dr[d]; cc = pc + dc[d]; break; }

    int nid = 1;
    while (true) {
        int deg = 0;
        for (int d = 0; d < 4; d++) if (linked(cr, cc, d)) deg++;
        if (deg == 1) break;  // 到达另一个端点

        int nr = -1, nc = -1;
        if (isX(grid[cr][cc])) {
            nr = 2 * cr - pr;
            nc = 2 * cc - pc;
        } else {
            for (int d = 0; d < 4; d++) {
                if (!linked(cr, cc, d)) continue;
                int tr = cr + dr[d], tc = cc + dc[d];
                if (tr == pr && tc == pc) continue;
                nr = tr; nc = tc; break;
            }
        }
        if (!inside(nr, nc)) return {};

        if (isX(grid[cr][cc])) {
            if (!cid[cr][cc]) cid[cr][cc] = nid++;
            bool horiz = (pr == cr);
            bool ov = (grid[cr][cc] == 'H') ? horiz : !horiz;
            code.push_back({cid[cr][cc],
                            dirBetween(cr, cc, pr, pc),
                            dirBetween(cr, cc, nr, nc),
                            ov});
        }
        pr = cr; pc = cc; cr = nr; cc = nc;
    }
    return code;
}

// 两条弧是否围出同一个二边形面
bool sameFace(const Arc& A, const Arc& B) {
    int a1, a2, b1, b2;
    if (A.id1 == B.id1 && A.id2 == B.id2) {
        a1 = A.port1; a2 = A.port2;
        b1 = B.port1; b2 = B.port2;
    } else if (A.id1 == B.id2 && A.id2 == B.id1) {
        a1 = A.port1; a2 = A.port2;
        b1 = B.port2; b2 = B.port1;
    } else return false;
    int d1 = (b1 - a1 + 4) & 3;
    int d2 = (a2 - b2 + 4) & 3;
    return (d1 == 1 && d2 == 1) || (d1 == 3 && d2 == 3);
}

// Type I：原地栈消除相邻同 crossing 的小 curl
void reduceI(vector<Event>& code) {
    int sz = 0;
    for (auto& e : code) {
        if (sz > 0 && code[sz - 1].cross == e.cross) sz--;
        else code[sz++] = e;
    }
    code.resize(sz);
}

// 一轮 Type II：一次性找到所有互不重叠的可消二边形并批量删除。
// 返回 true 表示本轮有删除发生。
bool reduceII(vector<Event>& code) {
    int n = code.size();
    if (n < 4) return false;

    int mx = 0;
    for (auto& e : code) mx = max(mx, e.cross);
    vector<char> used(mx + 1, 0);

    unordered_map<uint64_t, vector<Arc>> bucket;
    bucket.reserve(n);

    vector<pair<int,int>> pairs;

    for (int i = 0; i + 1 < n; i++) {
        const Event& e1 = code[i];
        const Event& e2 = code[i + 1];
        if (e1.cross == e2.cross) continue;
        if (used[e1.cross] || used[e2.cross]) continue;

        Arc A{e1.cross, e2.cross, e1.out, e2.in, i, e1.over, e2.over};

        // 一端 over 一端 under 的弧无法构成 Type II，直接丢弃
        if (A.over1 != A.over2) continue;

        int lo = min(e1.cross, e2.cross);
        int hi = max(e1.cross, e2.cross);
        uint64_t key = ((uint64_t)lo << 32) | (uint32_t)hi;

        bool matched = false;
        auto it = bucket.find(key);
        if (it != bucket.end()) {
            for (auto& B : it->second) {
                if (used[B.id1] || used[B.id2]) continue;
                if (B.pos + 1 >= A.pos) continue;
                if (A.over1 == B.over1) continue;
                if (!sameFace(A, B)) continue;
                pairs.push_back({B.pos, A.pos});
                used[A.id1] = used[A.id2] = 1;
                matched = true;
                break;
            }
        }
        if (!matched) bucket[key].push_back(A);
    }

    if (pairs.empty()) return false;

    vector<char> del(n, 0);
    for (auto& p : pairs) {
        del[p.first] = del[p.first + 1] = 1;
        del[p.second] = del[p.second + 1] = 1;
    }
    int w = 0;
    for (int i = 0; i < n; i++) if (!del[i]) code[w++] = code[i];
    code.resize(w);
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc = 0;
    while (cin >> R >> C && (R || C)) {
        grid.resize(R);
        for (auto& row : grid) cin >> row;

        auto code = buildCode();
        while (true) {
            reduceI(code);
            if (code.empty() || !reduceII(code)) break;
        }
        cout << "Case " << ++tc << ": "
             << (code.empty() ? "straightened" : "knotted") << '\n';
    }
    return 0;
}
```

# 总结

本题的关键是把网格图正确转化为开放绳子的 $\texttt{Gauss}$ 编码，并保留交叉点处的端口方向和上下层信息。第一类消去处理相邻的同一交叉点访问；第二类消去需要同时验证上下层关系和二边形面的几何条件。整个判定过程反复进行局部消去，不连接开放端点，也不搜索第三类移动。
