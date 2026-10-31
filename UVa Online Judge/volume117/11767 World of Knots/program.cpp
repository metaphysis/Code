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
