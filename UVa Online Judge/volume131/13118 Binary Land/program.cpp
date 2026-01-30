// Binary Land
// UVa ID: 13118
// Verdict: Accepted
// Submission Date: 2026-01-18
// UVa Run Time: 1.320s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct State {
    int r1, c1, r2, c2; // (r1,c1): Gurin, (r2,c2): Malon
    State(int a, int b, int c, int d) : r1(a), c1(b), r2(c), c2(d) {}
    bool operator==(const State& other) const {
        return r1 == other.r1 && c1 == other.c1 && r2 == other.r2 && c2 == other.c2;
    }
};

struct StateHash {
    size_t operator()(const State& s) const {
        return ((s.r1 * 41 + s.c1) * 41 + s.r2) * 41 + s.c2;
    }
};

int dr[4] = {-1, 1, 0, 0}; // 北, 南, 东, 西
int dc[4] = {0, 0, 1, -1};

int main() {
    int R, C;
    while (cin >> R >> C) {
        int rL, cL, rG, cG, rM, cM;
        cin >> rL >> cL >> rG >> cG >> rM >> cM;
        // 将坐标从1-based转换为0-based
        rL--; cL--; rG--; cG--; rM--; cM--;
        
        vector<string> maze(R);
        cin.ignore();
        for (int i = 0; i < R; i++) getline(cin, maze[i]);
        
        // BFS
        queue<pair<State, int>> q;
        unordered_set<State, StateHash> visited;
        State start(rG, cG, rM, cM);
        q.push({start, 0});
        visited.insert(start);
        
        int answer = -1;
        while (!q.empty()) {
            State cur = q.front().first;
            int dist = q.front().second;
            q.pop();
            
            // 检查是否到达目标：两只企鹅都在爱心格子
            if (cur.r1 == rL && cur.c1 == cL && cur.r2 == rL && cur.c2 == cL) {
                answer = dist;
                break;
            }
            
            // 尝试四个方向移动
            for (int dir = 0; dir < 4; dir++) {
                int nr1 = cur.r1 + dr[dir], nc1 = cur.c1 + dc[dir];
                int nr2 = cur.r2, nc2 = cur.c2;
                
                // 根据诅咒规则决定另一只企鹅的移动方向
                if (dir == 0 || dir == 1) { // 北或南：另一只企鹅同向移动
                    nr2 = cur.r2 + dr[dir];
                    nc2 = cur.c2 + dc[dir];
                } else if (dir == 2) { // 东：另一只企鹅向西移动
                    nr2 = cur.r2 + dr[3]; // 西
                    nc2 = cur.c2 + dc[3];
                } else { // 西：另一只企鹅向东移动
                    nr2 = cur.r2 + dr[2]; // 东
                    nc2 = cur.c2 + dc[2];
                }
                
                // 检查古林的移动是否有效
                if (nr1 < 0 || nr1 >= R || nc1 < 0 || nc1 >= C || maze[nr1][nc1] == '#') {
                    nr1 = cur.r1; // 不能移动，留在原地
                    nc1 = cur.c1;
                }
                // 检查玛隆的移动是否有效
                if (nr2 < 0 || nr2 >= R || nc2 < 0 || nc2 >= C || maze[nr2][nc2] == '#') {
                    nr2 = cur.r2; // 不能移动，留在原地
                    nc2 = cur.c2;
                }
                
                State next(nr1, nc1, nr2, nc2);
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push({next, dist + 1});
                }
            }
        }
        
        if (answer == -1) cout << "NO LOVE\n";
        else cout << answer << "\n";
    }
    return 0;
}
