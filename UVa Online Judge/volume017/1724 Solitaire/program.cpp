// Solitaire
// UVa ID: 1724
// Verdict: Accepted
// Submission Date: 2025-10-15
// UVa Run Time: 0.040s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

// 将行列位置编码为单个整数 (0-63)
int encode(int r, int c) { return (r - 1) * 8 + (c - 1); }

// 检查位置是否在棋盘范围内
bool inBoard(int r, int c) { return r >= 1 && r <= 8 && c >= 1 && c <= 8; }

// 状态类型：排序后的 4 个位置整数
typedef vector<int> State;

// 状态哈希函数
struct StateHash {
    size_t operator()(const State& s) const {
        size_t hash = 0;
        for (int pos : s) {
            hash = hash * 131 + pos;
        }
        return hash;
    }
};

// 生成当前状态的所有下一步可能状态
vector<State> getNextStates(const State& current) {
    vector<State> nextStates;
    // 将当前状态转为集合便于快速查找
    set<int> currentSet(current.begin(), current.end());
    // 四个移动方向：下、上、右、左
    const int dr[] = {1, -1, 0, 0};
    const int dc[] = {0, 0, 1, -1};
    
    // 对每个棋子尝试移动
    for (int i = 0; i < 4; i++) {
        int pos = current[i];
        int r = pos / 8 + 1;
        int c = pos % 8 + 1;
        
        // 尝试四个方向
        for (int dir = 0; dir < 4; dir++) {
            // 尝试普通移动：移动到相邻空位
            int nr = r + dr[dir];
            int nc = c + dc[dir];
            if (inBoard(nr, nc)) {
                int newPos = encode(nr, nc);
                if (currentSet.find(newPos) == currentSet.end()) {
                    State newState = current;
                    newState[i] = newPos;
                    sort(newState.begin(), newState.end());
                    nextStates.push_back(newState);
                }
            }
            
            // 尝试跳跃移动：跳过相邻棋子
            int mr = r + dr[dir];
            int mc = c + dc[dir];
            if (inBoard(mr, mc)) {
                int midPos = encode(mr, mc);
                if (currentSet.find(midPos) != currentSet.end()) {
                    int nr = r + 2 * dr[dir];
                    int nc = c + 2 * dc[dir];
                    if (inBoard(nr, nc)) {
                        int newPos = encode(nr, nc);
                        if (currentSet.find(newPos) == currentSet.end()) {
                            State newState = current;
                            newState[i] = newPos;
                            sort(newState.begin(), newState.end());
                            nextStates.push_back(newState);
                        }
                    }
                }
            }
        }
    }
    return nextStates;
}

// 双向 BFS 检查是否能在 8 步内到达目标状态
bool canReach(const State& startState, const State& targetState) {
    if (startState == targetState) return true;
    
    // 使用两个队列和两个 visited 集合
    queue<State> q1, q2;
    unordered_set<State, StateHash> visited1, visited2;
    
    q1.push(startState);
    q2.push(targetState);
    visited1.insert(startState);
    visited2.insert(targetState);
    
    int steps1 = 0, steps2 = 0;
    
    while (!q1.empty() && !q2.empty()) {
        // 从起点方向扩展一层
        if (steps1 + steps2 < 8) {
            int size1 = q1.size();
            for (int i = 0; i < size1; i++) {
                State current = q1.front();
                q1.pop();
                
                vector<State> nextStates = getNextStates(current);
                for (const State& next : nextStates) {
                    if (visited1.find(next) != visited1.end()) continue;
                    
                    // 检查是否在另一方向已经访问过
                    if (visited2.find(next) != visited2.end()) {
                        return true;
                    }
                    
                    visited1.insert(next);
                    q1.push(next);
                }
            }
            steps1++;
        }
        
        // 从终点方向扩展一层
        if (steps1 + steps2 < 8) {
            int size2 = q2.size();
            for (int i = 0; i < size2; i++) {
                State current = q2.front();
                q2.pop();
                
                vector<State> nextStates = getNextStates(current);
                for (const State& next : nextStates) {
                    if (visited2.find(next) != visited2.end()) continue;
                    
                    // 检查是否在另一方向已经访问过
                    if (visited1.find(next) != visited1.end()) {
                        return true;
                    }
                    
                    visited2.insert(next);
                    q2.push(next);
                }
            }
            steps2++;
        }
        
        // 如果总步数超过 8，停止搜索
        if (steps1 + steps2 >= 8) break;
    }
    
    return false;
}

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);
    
    vector<int> start(8), target(8);
    while (cin >> start[0]) {
        for (int i = 1; i < 8; i++) cin >> start[i];
        for (int i = 0; i < 8; i++) cin >> target[i];
        
        State startState, targetState;
        for (int i = 0; i < 4; i++) {
            startState.push_back(encode(start[2 * i], start[2 * i + 1]));
            targetState.push_back(encode(target[2 * i], target[2 * i + 1]));
        }
        
        sort(startState.begin(), startState.end());
        sort(targetState.begin(), targetState.end());
        
        if (canReach(startState, targetState)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
