## 题目描述

在一条长度为 $n$（$n \le 60$）的一维棋盘上有若干空位与两方棋子。字符 $\texttt{1}$ 表示玩家一的棋子，字符 $\texttt{2}$ 表示玩家二的棋子，双方棋子数相同，且棋盘上至少有两个空位。一名玩家可以把自己的一枚棋子移动到棋盘上任意一个空位，但棋子不能落在其它棋子上，也不能跳过其它棋子。双方轮流走棋，玩家一先手，目标是让对手在其回合没有任何合法走法。要求判断玩家一是否必胜、必败或只能平局，并在必胜时给出字典序最小的必胜走法。

## 输入格式

每行一个棋盘字符串，字符 $\texttt{0}$ 表示空位，$\texttt{1}$ 表示玩家一，$\texttt{2}$ 表示玩家二，字符串长度不超过 $60$。输入以单独一行 $\texttt{0}$ 结束。

## 输出格式

对每个棋盘输出一行：若玩家一必胜，输出 $1$ 以及必胜走法的起点孔号和终点孔号（孔号从 $1$ 开始，取起点孔号最小、再取终点孔号最小的走法）；若玩家一必败，输出 $2$；否则输出 $0$。

## 样例输入

```
000200100000
000100200102
000010201002
000010200102
001020020001100002000
0
```

## 样例输出

```
1 7 5
1 4 5
1 5 4
2
1 13 15
```

## 题目分析

棋子不能跳过其它棋子，因此全部棋子的相对顺序从始至终都不会改变，一步移动只是把某枚棋子在其左右相邻棋子围成的区间内挪动，其效果等价于改变相邻棋子之间的空位数。于是整个局面可以看成若干由空位组成的间隙：当双方棋子能够两两配成相邻异色对时，每个配对之间的空位数就是一个 $\texttt{Nim}$ 石堆，胜负由这些空位数的异或和决定；当某一方存在能无限移动的结构时，这一方就拥有了不会输的能力，博弈的性质随之改变。因此求解的关键是把局面分成纯 $\texttt{Nim}$ 部分与无限移动结构部分，并按优先级进行判定。无限移动结构简记为 $\texttt{IMS}$，它指的是某方能够无限走子、永远不会被完全限制住的结构。

## 解题思路

先给出三条可以直接判定的可靠规则。规则 $\texttt{1}$ 是卡死：若玩家一初始没有任何合法走法，则玩家一必败，输出 $2$。规则 $\texttt{2}$ 是一步制胜：若玩家一存在一步走法使玩家二无合法走法，则玩家一必胜，输出 $1$。规则 $\texttt{3}$ 是可配对 $\texttt{Nim}$：若全部棋子从左到右能相邻两两配对且每对异色，则对每对棋子计算其间隔的空位数，再把这些空位数异或起来，异或和为 $0$ 时玩家一必败，输出 $2$，非 $0$ 时玩家一必胜，输出 $1$。

对不属于上述三种情况的局面，需要判断双方是否拥有 $\texttt{IMS}$ 或是否能一步形成 $\texttt{IMS}$。$\texttt{IMS}$ 分为三类。第一类内部振荡器，指一段不含对方棋子的连续区间内己方棋子数至少 $3$ 且存在己方棋子—空位—己方棋子构成的空隙。第二类端部振荡器，指棋盘最左或最右的两枚棋子都是己方，且该侧端点处存在空位。第三类夹子（含扩展夹子），指己方棋子在两侧夹住对方棋子，棋子颜色模式为 $c^{L}(dc)^{k}dc^{R}$，其中 $c$ 为己方棋子，$d$ 为对方棋子，$k \ge 0$，中间部分为 $d$、$c$、$d$、$c$、$\ldots$、$d$ 的交替，贴边一侧的 $c$ 个数可以少一枚，且段内必须存在空位。

记 $\texttt{can\_create}$ 为某方是否存在一步走法在新局面中形成 $\texttt{IMS}$，记 $\texttt{can\_prevent}(a,b)$ 为 $a$ 方是否存在一步走法使 $b$ 方在新局面中无法形成 $\texttt{IMS}$。对双方都无 $\texttt{IMS}$ 且都无法创建的有限局面，其 $\texttt{Nim}$ 值由贪心消去求得：从左到右扫描全部棋子并维护一个当前未配对棋子，新棋子与当前棋子异色时配对并把两者间隔的空位数异或进答案、同时清空当前棋子，同色时用新棋子替换当前棋子，最后异或和为 $0$ 表示先手必败、非 $0$ 表示先手必胜。

完整的分类流程按以下优先级进行。第一步处理规则 $\texttt{1}$ 卡死，输出 $2$。第二步处理规则 $\texttt{2}$ 一步制胜，输出 $1$。第三步处理规则 $\texttt{3}$ 可配对 $\texttt{Nim}$。第四步处理有限局面，用贪心消去得到的异或和判定胜负。第五步，若双方都已有 $\texttt{IMS}$，则谁也无法逼死对方，输出 $0$。第六步，若玩家二有 $\texttt{IMS}$ 而玩家一没有，则玩家一能一步形成 $\texttt{IMS}$ 时输出 $0$，否则输出 $2$。第七步，若玩家一有 $\texttt{IMS}$ 而玩家二没有，则玩家二不能形成 $\texttt{IMS}$ 时输出 $1$，否则玩家一能阻止玩家二时输出 $1$、不能阻止时输出 $0$。第八步处理双方都无 $\texttt{IMS}$ 的情形，此时若仅玩家一能形成 $\texttt{IMS}$ 则输出 $1$，若仅玩家二能形成 $\texttt{IMS}$ 则由玩家一阻止后的有限局面异或和判定：异或和为 $0$ 时玩家二走棋必败故输出 $1$，非 $0$ 时输出 $2$。若双方都能形成 $\texttt{IMS}$，则先看 $\texttt{can\_prevent}$ 的不对称性，玩家一能阻止而玩家二不能阻止时输出 $1$，玩家一不能阻止时输出 $0$；当双方都能阻止时，若玩家一存在一步既形成己方 $\texttt{IMS}$ 又阻止玩家二的走法则输出 $1$，否则模拟玩家一先阻止、玩家二再阻止得到的有限局面，其异或和非 $0$ 时输出 $1$，为 $0$ 时输出 $0$。必胜走法则枚举玩家一的全部合法走法并按起点、终点升序排列，找到第一个使新局面对玩家二而言必败的走法即可。

时间复杂度为 $O(n^{3}m^{3})$，其中 $n \le 60$ 为孔数，$m \le 58$ 为棋子数；由于 $\texttt{IMS}$ 与 $\texttt{can\_create}$ 都做了记忆化，且搜索会提前返回，实际运行远低于上界。空间复杂度为 $O(n^{3})$，用于记忆化表存储局面字符串。

## 代码实现

```cpp
// Board Game
// UVa ID: 896
// Verdict: Accepted
// Submission Date: 2026-10-29
// UVa Run Time: 0.080s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

using Board = string;

// ---------- 记忆化（每个查询内共享，跨查询清空） ----------
static unordered_map<string, pair<char, char>> ims_memo;  // board -> (ims1, ims2)
static unordered_map<string, pair<char, char>> cc_memo;   // board -> (cc1, cc2)

// ---------- 基础 ----------

static vector<pair<int,int>> legal_moves(const Board &b, char c) {
    int n = (int)b.size();
    vector<pair<int,int>> mv;
    for (int i = 0; i < n; ++i) {
        if (b[i] != c) continue;
        for (int j = i - 1; j >= 0 && b[j] == '0'; --j) mv.push_back({i, j});
        for (int j = i + 1; j < n && b[j] == '0'; ++j) mv.push_back({i, j});
    }
    return mv;
}

static Board apply(const Board &b, int from, int to) {
    Board r = b;
    r[to] = r[from];
    r[from] = '0';
    return r;
}

static bool all_stuck(const Board &b, char c) {
    return legal_moves(b, c).empty();
}

static bool has_winning_move(const Board &b) {
    for (auto [f, t] : legal_moves(b, '1'))
        if (all_stuck(apply(b, f, t), '2')) return true;
    return false;
}

static Board swap_colors(const Board &b) {
    Board r = b;
    for (char &ch : r) {
        if (ch == '1') ch = '2';
        else if (ch == '2') ch = '1';
    }
    return r;
}

// ---------- Nim ----------

static pair<bool,int> nim_pairing(const Board &b) {
    vector<pair<int,char>> ps;
    for (int i = 0; i < (int)b.size(); ++i) if (b[i] != '0') ps.push_back({i, b[i]});
    if (ps.size() % 2 != 0) return {false, 0};
    for (int k = 0; k < (int)ps.size(); k += 2)
        if (ps[k].second == ps[k+1].second) return {false, 0};
    int x = 0;
    for (int k = 0; k < (int)ps.size(); k += 2)
        x ^= (ps[k+1].first - ps[k].first - 1);
    return {true, x};
}

static int nim_xor(const Board &b) {
    vector<int> ps;
    for (int i = 0; i < (int)b.size(); ++i) if (b[i] != '0') ps.push_back(i);
    int x = 0;
    int cur = -1; char curc = 0;
    for (int p : ps) {
        if (cur == -1) { cur = p; curc = b[p]; }
        else if (curc == b[p]) cur = p;
        else { x ^= (p - cur - 1); cur = -1; }
    }
    return x;
}

// ---------- IMS（原始判定，不带记忆化） ----------

static bool has_ims_raw(const Board &b, char c) {
    int n = (int)b.size();
    char d = (c == '1') ? '2' : '1';
    vector<pair<int,char>> pieces;
    for (int i = 0; i < n; ++i) if (b[i] != '0') pieces.push_back({i, b[i]});
    vector<int> pos;
    for (auto [p, ch] : pieces) if (ch == c) pos.push_back(p);
    if (pos.size() < 2) return false;
    // T1
    for (int i = 0; i < n; ) {
        if (b[i] == d) { ++i; continue; }
        int j = i;
        vector<int> cpos;
        int cnt0 = 0;
        while (j < n && b[j] != d) {
            if (b[j] == c) cpos.push_back(j);
            else cnt0++;
            ++j;
        }
        if ((int)cpos.size() >= 3 && cnt0 >= 1)
            for (int k = 0; k + 1 < (int)cpos.size(); ++k)
                if (cpos[k+1] - cpos[k] >= 2) return true;
        i = j;
    }
    // T2
    int m = (int)pieces.size();
    if (m >= 2) {
        if (pieces[0].second == c && pieces[1].second == c)
            for (int k = 0; k <= pieces[1].first; ++k) if (b[k] == '0') return true;
        if (pieces[m-2].second == c && pieces[m-1].second == c)
            for (int k = pieces[m-2].first; k < n; ++k) if (b[k] == '0') return true;
    }
    // T3/D9 夹子
    auto all_zero = [&](int a, int e) {
        for (int k = a; k < e; ++k) if (b[k] != '0') return false;
        return true;
    };
    for (int i = 0; i < m; ++i) {
        if (pieces[i].second != c) continue;
        for (int j = i + 2; j < m; ++j) {
            if (pieces[j].second != c) continue;
            int len = j - i + 1;
            bool left_edge = all_zero(0, pieces[i].first);
            bool right_edge = all_zero(pieces[j].first + 1, n);
            int L = 0;
            while (L < len && pieces[i + L].second == c) ++L;
            int R = 0;
            while (R < len && pieces[j - R].second == c) ++R;
            int needL = left_edge ? 1 : 2;
            int needR = right_edge ? 1 : 2;
            if (L < needL || R < needR) continue;
            if (L + R >= len) continue;
            bool ok = true;
            for (int k = L; k < len - R; ++k) {
                char want = ((k - L) % 2 == 0) ? d : c;
                if (pieces[i + k].second != want) { ok = false; break; }
            }
            if (!ok) continue;
            int lo = left_edge ? 0 : pieces[i].first;
            int hi = right_edge ? (n - 1) : pieces[j].first;
            for (int k = lo; k <= hi; ++k) if (b[k] == '0') return true;
        }
    }
    return false;
}

static pair<bool,bool> get_ims(const Board &b) {
    auto it = ims_memo.find(b);
    if (it != ims_memo.end()) return {it->second.first, it->second.second};
    bool i1 = has_ims_raw(b, '1');
    bool i2 = has_ims_raw(b, '2');
    ims_memo[b] = {i1, i2};
    return {i1, i2};
}

static bool can_create_raw(const Board &b, char c) {
    for (auto [f, t] : legal_moves(b, c)) {
        auto ims = get_ims(apply(b, f, t));
        if (c == '1' ? ims.first : ims.second) return true;
    }
    return false;
}

static pair<bool,bool> get_cc(const Board &b) {
    auto it = cc_memo.find(b);
    if (it != cc_memo.end()) return {it->second.first, it->second.second};
    bool c1 = can_create_raw(b, '1');
    bool c2 = can_create_raw(b, '2');
    cc_memo[b] = {c1, c2};
    return {c1, c2};
}

// ---------- 有界搜索谓词 ----------

static bool can_prevent(const Board &b, char a, char bb) {
    for (auto [f, t] : legal_moves(b, a)) {
        auto cc = get_cc(apply(b, f, t));
        if (!(bb == '1' ? cc.first : cc.second)) return true;
    }
    return false;
}

static bool can_create_and_prevent(const Board &b, char a, char bb) {
    for (auto [f, t] : legal_moves(b, a)) {
        Board nb = apply(b, f, t);
        auto ims = get_ims(nb);
        auto cc = get_cc(nb);
        bool has_a = (a == '1') ? ims.first : ims.second;
        bool can_bb = (bb == '1') ? cc.first : cc.second;
        if (has_a && !can_bb) return true;
    }
    return false;
}

static int mutual_block_nim(const Board &b) {
    for (auto [f1, t1] : legal_moves(b, '1')) {
        Board b1 = apply(b, f1, t1);
        if (get_cc(b1).second) continue;         // 玩家二仍能造 IMS
        for (auto [f2, t2] : legal_moves(b1, '2')) {
            Board b2 = apply(b1, f2, t2);
            if (get_cc(b2).first) continue;      // 玩家一仍能造 IMS
            auto ims = get_ims(b2);
            if (ims.first || ims.second) continue;
            auto cc = get_cc(b2);
            if (cc.first || cc.second) continue;
            return nim_xor(b2);
        }
    }
    return -1;
}

static bool block_nims_has_zero(const Board &b) {
    for (auto [f, t] : legal_moves(b, '1')) {
        Board b1 = apply(b, f, t);
        if (get_cc(b1).second) continue;
        auto ims = get_ims(b1);
        if (ims.first || ims.second) continue;
        auto cc = get_cc(b1);
        if (cc.first || cc.second) continue;
        if (nim_xor(b1) == 0) return true;
    }
    return false;
}

// ---------- 分类 ----------

static int classify(const Board &b) {
    if (all_stuck(b, '1')) return 2;             // R1
    if (has_winning_move(b)) return 1;           // R2
    auto [pairable, x] = nim_pairing(b);         // R3
    if (pairable) return (x != 0) ? 1 : 2;
    auto ims = get_ims(b);
    auto cc = get_cc(b);
    bool ims1 = ims.first, ims2 = ims.second;
    bool cc1 = cc.first, cc2 = cc.second;
    if (!ims1 && !ims2) {
        if (!cc1 && !cc2) {
            int v = nim_xor(b);                   // finite
            return (v != 0) ? 1 : 2;
        }
        if (cc1 && !cc2) return 1;                // W1
        if (!cc1 && cc2)                          // W8 / L6
            return block_nims_has_zero(b) ? 1 : 2;
        bool p12 = can_prevent(b, '1', '2');
        bool p21 = can_prevent(b, '2', '1');
        if (p12 && !p21) return 1;                // W9
        if (!p12) return 0;                       // D6/D7
        if (can_create_and_prevent(b, '1', '2')) return 1;  // W10
        int mn = mutual_block_nim(b);
        if (mn != -1 && mn != 0) return 1;        // W10b
        return 0;                                 // D7D8
    } else {
        if (ims1 && ims2) return 0;               // D1
        if (ims2 && !ims1) {
            if (cc1) return 0;                    // D2
            return 2;                             // L2/L5
        }
        if (!cc2) return 1;                       // M2/M5
        if (can_prevent(b, '1', '2')) return 1;   // W4/W8
        return 0;                                 // D5
    }
}

// ---------- 必胜走法 ----------

static pair<int,int> find_winning_move(const Board &b) {
    auto mv = legal_moves(b, '1');
    sort(mv.begin(), mv.end());
    for (auto [f, t] : mv)
        if (classify(swap_colors(apply(b, f, t))) == 2) return {f, t};
    return {-1, -1};
}

// ---------- 主程序 ----------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    while (cin >> s) {
        if (s == "0") break;
        ims_memo.clear();
        cc_memo.clear();
        int r = classify(s);
        if (r == 0) cout << "0\n";
        else if (r == 2) cout << "2\n";
        else {
            auto [f, t] = find_winning_move(s);
            cout << "1 " << (f + 1) << " " << (t + 1) << "\n";
        }
    }
    return 0;
}
```

## 总结

本题的核心是认识到棋子顺序不变，从而把局面分解为 $\texttt{Nim}$ 分量与 $\texttt{IMS}$ 分量。可靠规则（卡死、一步制胜、可配对 $\texttt{Nim}$）覆盖了大多数局面，剩下少量局面需要识别无限移动结构的三种类型，并用有界搜索处理锁死振荡器与可推进块的区分。关键在于用记忆化缓存 $\texttt{IMS}$ 与 $\texttt{can\_create}$ 的判定结果，使嵌套的有界搜索在 $60$ 孔规模下依然高效，从而避免精确回溯带来的超时。
