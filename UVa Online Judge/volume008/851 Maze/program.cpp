// Maze
// UVa ID: 851
// Verdict: Accepted
// Submission Date: 2025-12-30
// UVa Run Time: 6.080s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8;
const int dx[4] = {-1, 1, 0, 0};  // north, south, east, west
const int dy[4] = {0, 0, 1, -1};
const string dirName[4] = {"north", "south", "east", "west"};

struct State {
    long long inMaze;    // 仍在迷宫中的位置集合（位掩码）
    vector<int> path;    // 已执行的移动序列
};

// 将坐标编码为位掩码中的位置
inline int encode(int x, int y, int n) {
    return x * n + y;
}

// 判断格子是否在边界
inline bool isBorder(int x, int y, int n) {
    return x == 0 || x == n - 1 || y == 0 || y == n - 1;
}

// 执行移动指令，返回新的状态掩码
pair<long long, long long> applyMove(long long inMaze, long long escaped, int dir, int n, const vector<string>& grid) {
    long long newInMaze = 0;
    long long newEscaped = escaped;  // 已逃脱的位置保持不变
    
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            if (grid[x][y] != '.') continue;  // 忽略阻塞格子
            int idx = encode(x, y, n);
            
            // 如果这个位置已经逃脱，跳过
            if (escaped & (1LL << idx)) continue;
            
            // 如果这个位置不在当前迷宫中，跳过
            if (!(inMaze & (1LL << idx))) continue;
            
            // 尝试移动
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == '.') {
                // 可移动到新位置
                if (isBorder(nx, ny, n)) {
                    // 到达边界，逃脱
                    newEscaped |= (1LL << encode(nx, ny, n));
                } else {
                    // 仍在迷宫中
                    newInMaze |= (1LL << encode(nx, ny, n));
                }
            } else {
                // 不可移动，留在原地
                if (isBorder(x, y, n)) {
                    // 当前位置已经是边界，逃脱
                    newEscaped |= (1LL << idx);
                } else {
                    // 仍在迷宫中
                    newInMaze |= (1LL << idx);
                }
            }
        }
    }
    
    return {newInMaze, newEscaped};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    bool firstCase = true;
    
    while (t--) {
        if (!firstCase) cout << endl;
        firstCase = false;
        
        int n;
        cin >> n;
        vector<string> grid(n);
        for (int i = 0; i < n; ++i) cin >> grid[i];
        
        // 初始状态：所有可通行位置都在迷宫中（除了已经在边界的）
        long long startInMaze = 0;
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                if (grid[x][y] == '.') {
                    int idx = encode(x, y, n);
                    // 如果开始就在边界，直接逃脱，不在迷宫中
                    if (!isBorder(x, y, n)) {
                        startInMaze |= (1LL << idx);
                    }
                }
            }
        }
        
        // 如果开始时所有位置都已逃脱
        if (startInMaze == 0) {
            // 输出空序列（即无输出）
            continue;
        }
        
        // BFS 搜索
        queue<State> q;
        map<pair<long long, long long>, bool> visited;
        
        q.push({startInMaze, {}});
        visited[{startInMaze, 0}] = true;
        
        vector<int> answer;
        
        while (!q.empty()) {
            State cur = q.front(); q.pop();
            
            // 如果迷宫中已无位置，找到解
            if (cur.inMaze == 0) {
                answer = cur.path;
                break;
            }
            
            // 尝试四种移动
            for (int d = 0; d < 4; ++d) {
                auto [newInMaze, newEscaped] = applyMove(cur.inMaze, 0, d, n, grid);
                
                // 如果移动后状态未访问过
                if (!visited[{newInMaze, newEscaped}]) {
                    visited[{newInMaze, newEscaped}] = true;
                    vector<int> newPath = cur.path;
                    newPath.push_back(d);
                    q.push({newInMaze, newPath});
                }
            }
        }
        
        // 输出答案
        for (int d : answer) {
            cout << dirName[d] << endl;
        }
    }
    
    return 0;
}
