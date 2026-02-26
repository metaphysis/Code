// Marble Game
// UVa ID: 1063
// Verdict: Accepted
// Submission Date: 2026-02-23
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct State {
    vector<pair<int, int>> balls;    // 弹珠位置，(-1, -1)表示已进洞
    vector<int> ballInHole;           // 弹珠进的洞编号，-1表示未进
    vector<bool> holeFilled;          // 洞是否被填
    
    bool operator==(const State& o) const {
        return balls == o.balls && ballInHole == o.ballInHole && holeFilled == o.holeFilled;
    }
};

struct StateHash {
    size_t operator()(const State& s) const {
        size_t h = 0;
        for (auto& p : s.balls) h = h * 31 + (p.first * 10 + p.second);
        for (int v : s.ballInHole) h = h * 31 + (v + 1);
        for (bool b : s.holeFilled) h = h * 31 + b;
        return h;
    }
};

int N, M, W;
vector<pair<int, int>> ballStart, holePos;
set<pair<int, int>> walls[16];
int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

bool hasWall(int r1, int c1, int r2, int c2) {
    return walls[r1 * N + c1].count({r2, c2}) > 0;
}

State move(State s, int dir) {
    bool changed;
    do {
        changed = false;
        // 按移动方向的相反顺序处理
        vector<int> order(M);
        iota(order.begin(), order.end(), 0);
        if (dir == 0) // 北：从下到上
            sort(order.begin(), order.end(), [&](int a, int b) {
                return s.balls[a].first > s.balls[b].first;
            });
        else if (dir == 1) // 南：从上到下
            sort(order.begin(), order.end(), [&](int a, int b) {
                return s.balls[a].first < s.balls[b].first;
            });
        else if (dir == 2) // 西：从右到左
            sort(order.begin(), order.end(), [&](int a, int b) {
                return s.balls[a].second > s.balls[b].second;
            });
        else // 东：从左到右
            sort(order.begin(), order.end(), [&](int a, int b) {
                return s.balls[a].second < s.balls[b].second;
            });
        
        auto newBalls = s.balls;
        for (int idx : order) {
            if (s.ballInHole[idx] != -1) continue; // 已进洞
            
            int r = s.balls[idx].first, c = s.balls[idx].second;
            int nr = r + dr[dir], nc = c + dc[dir];
            
            // 边界检查
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            // 墙检查
            if (hasWall(r, c, nr, nc)) continue;
            
            // 检查目标格是否有其他弹珠
            bool occupied = false;
            for (int j = 0; j < M; j++) {
                if (j == idx) continue;
                if (s.ballInHole[j] != -1) continue; // 已进洞的不占格子
                if (newBalls[j].first == nr && newBalls[j].second == nc) {
                    occupied = true;
                    break;
                }
            }
            if (occupied) continue;
            
            // 检查目标格是否有未填的洞
            int holeIdx = -1;
            for (int j = 0; j < M; j++) {
                if (!s.holeFilled[j] && holePos[j].first == nr && holePos[j].second == nc) {
                    holeIdx = j;
                    break;
                }
            }
            
            if (holeIdx != -1) {
                // 进洞
                newBalls[idx] = {-1, -1};
                s.ballInHole[idx] = holeIdx;
                s.holeFilled[holeIdx] = true;
                changed = true;
            } else {
                // 正常移动
                newBalls[idx] = {nr, nc};
                changed = true;
            }
        }
        s.balls = newBalls;
    } while (changed);
    
    return s;
}

bool isGoal(const State& s) {
    for (int i = 0; i < M; i++)
        if (s.ballInHole[i] != i) return false;
    return true;
}

int solve() {
    State start;
    start.balls = ballStart;
    start.ballInHole.assign(M, -1);
    start.holeFilled.assign(M, false);
    
    queue<pair<State, int>> q;
    q.push({start, 0});
    
    unordered_set<State, StateHash> visited;
    visited.insert(start);
    
    while (!q.empty()) {
        auto [cur, steps] = q.front(); q.pop();
        if (isGoal(cur)) return steps;
        
        for (int d = 0; d < 4; d++) {
            State nxt = move(cur, d);
            if (visited.count(nxt)) continue;
            visited.insert(nxt);
            q.push({nxt, steps + 1});
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int caseNum = 1;
    while (cin >> N >> M >> W) {
        if (N == 0 && M == 0 && W == 0) break;
        
        ballStart.resize(M);
        holePos.resize(M);
        for (int i = 0; i < M; i++) cin >> ballStart[i].first >> ballStart[i].second;
        for (int i = 0; i < M; i++) cin >> holePos[i].first >> holePos[i].second;
        
        for (int i = 0; i < N * N; i++) walls[i].clear();
        for (int i = 0; i < W; i++) {
            int r1, c1, r2, c2;
            cin >> r1 >> c1 >> r2 >> c2;
            walls[r1 * N + c1].insert({r2, c2});
            walls[r2 * N + c2].insert({r1, c1});
        }
        
        int ans = solve();
        cout << "Case " << caseNum++ << ": ";
        if (ans < 0) cout << "impossible\n\n";
        else cout << ans << " moves\n\n";
    }
    return 0;
}
