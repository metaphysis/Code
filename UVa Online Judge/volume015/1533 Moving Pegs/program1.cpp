// Moving Pegs
// UVa ID: 1533
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.050s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 棋盘布局（洞编号）：
//        (1)
//      (2) (3)
//    (4) (5) (6)
//  (7) (8) (9) (10)
//(11)(12)(13)(14)(15)

// 所有可能的直线（至少3个洞在一条直线上）
const vector<vector<int>> lines = {
    {1, 2, 4, 7, 11},
    {3, 5, 8, 12},
    {6, 9, 13},
    {4, 5, 6},
    {7, 8, 9, 10},
    {11, 12, 13, 14, 15},
    {1, 3, 6, 10, 15},
    {2, 5, 9, 14},
    {4, 8, 13},
};

struct jump { int mask, bit1, bit2, from, to; };

vector<jump> jumps;

void getPossibleMoves() {
    for (auto line : lines) {
        for (int i = 0; i < line.size(); i++)
            for (int j = i + 2; j < line.size(); j++) {
                jump jmp = jump {0, 0, 0, line[j], line[i]};
                for (int k = i; k <= j; k++) jmp.mask |= 1 << (line[k] - 1);
                for (int k = i + 1; k <= j; k++) jmp.bit1 |= 1 << (line[k] - 1);
                jmp.bit2 = 1 << (line[i] - 1);
                jumps.push_back(jmp);
            }
        for (int i = line.size() - 1; i >= 0; i--)
            for (int j = i - 2; j >= 0; j--) {
                jump jmp = jump {0, 0, 0, line[j], line[i]};
                for (int k = i; k >= j; k--) jmp.mask |= 1 << (line[k] - 1);
                for (int k = i - 1; k >= j; k--) jmp.bit1 |= 1 << (line[k] - 1);
                jmp.bit2 = 1 << (line[i] - 1);
                jumps.push_back(jmp);
            }
    }
    // 按字典序排序：先按from排序，from相同按to排序
    sort(jumps.begin(), jumps.end(), [](const jump& a, const jump& b) {
        if (a.from != b.from) return a.from < b.from;
        return a.to < b.to;
    });
}

struct state {
    int bits;
    vector<pair<int, int>> moves;
};

vector<pair<int, int>> solve(int emptyHole) {
    int end = 1 << (emptyHole - 1);
    unordered_set<int> visited;
    state start;
    start.bits = ~(1 << (emptyHole - 1)) & ((1 << 15) - 1);
    queue<state> q;
    q.push(start);
    visited.insert(start.bits);
    while (!q.empty()) {
        state s = q.front(); q.pop();
        if (s.bits == end) return s.moves;
        for (auto j : jumps) {
            if ((s.bits & j.mask) == j.bit1) {
                state next = {s.bits & (~j.mask) | j.bit2, s.moves};
                next.moves.push_back(make_pair(j.from, j.to));
                if (!visited.count(next.bits)) {
                    visited.insert(next.bits);
                    q.push(next);
                }
            }
        }
    }
    return {};
}

int main() {
    getPossibleMoves();
    int T; cin >> T;
    while (T--) {
        int emptyHole; cin >> emptyHole;
        auto moves = solve(emptyHole);
        if (moves.empty()) cout << "IMPOSSIBLE\n";
        else {
            cout << moves.size() << '\n';
            for (size_t i = 0; i < moves.size(); i++) {
                if (i) cout << ' ';
                cout << moves[i].first << ' ' << moves[i].second;
            }
            cout << '\n';
        }
    }
    return 0;
}
