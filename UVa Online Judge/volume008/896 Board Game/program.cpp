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
