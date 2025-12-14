// Dora Trip
// UVa ID: 10818
// Verdict: Accepted
// Submission Date: 2025-12-14
// UVa Run Time: 0.190s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 状态结构体：位置(x,y)和访问任务点的掩码mask
struct State {
    int x, y, mask;
    State(int x = 0, int y = 0, int mask = 0) : x(x), y(y), mask(mask) {}
    // 用于map比较，需要定义小于运算符
    bool operator<(const State& other) const {
        if (x != other.x) return x < other.x;
        if (y != other.y) return y < other.y;
        return mask < other.mask;
    }
};

int r, c;                 // 地图行数和列数
vector<string> grid;      // 地图
int sx, sy;               // 起点S的位置
int targetCount;          // 任务点*的数量
vector<pair<int, int>> targets;  // 任务点坐标
int targetIndex[20][20];  // 每个位置如果是*，记录其索引，否则为-1

// 四个方向：E, N, S, W（按字典序排列，保证最先找到的路径字典序最小）
const int dx[4] = {0, -1, 1, 0};
const int dy[4] = {1, 0, 0, -1};
const char dirChar[4] = {'E', 'N', 'S', 'W'};

map<State, pair<State, char>> pre; // 记录前驱状态和移动方向
map<State, int> dist;              // 记录到达状态的最短距离

// 检查坐标(x,y)是否可通行
bool isValid(int x, int y) {
    if (x < 0 || x >= r || y < 0 || y >= c) return false;
    char ch = grid[x][y];
    return ch != '#' && ch != 'X';
}

void solve() {
    // 读取地图
    grid.resize(r);
    cin.ignore(); // 忽略第一行整数后的换行符
    for (int i = 0; i < r; i++) {
        getline(cin, grid[i]);
        // 确保每行长度恰好为c，不足则用空格补齐
        if ((int)grid[i].size() < c) grid[i].append(c - grid[i].size(), ' ');
    }

    // 初始化任务点信息
    targets.clear();
    memset(targetIndex, -1, sizeof(targetIndex));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'S') {
                sx = i, sy = j;
            } else if (grid[i][j] == '*') {
                targetIndex[i][j] = targets.size();
                targets.push_back({i, j});
            }
        }
    targetCount = targets.size();

    // 如果没有任务点，直接输出
    if (targetCount == 0) {
        cout << "Stay home!" << endl;
        return;
    }

    // $\texttt{BFS}$初始化
    pre.clear();
    dist.clear();
    queue<State> q;
    State start(sx, sy, 0);
    dist[start] = 0;
    q.push(start);

    int bestMask = 0;     // 最优掩码（访问任务点最多）
    int bestDist = 1e9;   // 最优路径长度
    State bestState = start; // 最优状态
    bool found = false;   // 是否找到可行解

    while (!q.empty()) {
        State cur = q.front(); q.pop();
        int curDist = dist[cur];

        // 如果当前状态在起点S且不是初始状态（dist>0），则是一条回路
        if (cur.x == sx && cur.y == sy && curDist > 0) {
            int cnt = __builtin_popcount(cur.mask);        // 当前访问任务点数量
            int bestCnt = __builtin_popcount(bestMask);    // 历史最优数量
            // 如果访问更多任务点，或数量相同但路径更短，则更新最优解
            if (cnt > bestCnt || (cnt == bestCnt && curDist < bestDist)) {
                bestMask = cur.mask;
                bestDist = curDist;
                bestState = cur;
                found = true;
            }
        }

        // 向四个方向扩展
        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dx[d];
            int ny = cur.y + dy[d];
            if (!isValid(nx, ny)) continue;

            int newMask = cur.mask;
            // 如果新位置是任务点，更新掩码
            if (targetIndex[nx][ny] != -1) 
                newMask |= (1 << targetIndex[nx][ny]);

            State next(nx, ny, newMask);
            // 如果该状态未访问过，入队
            if (dist.find(next) == dist.end()) {
                dist[next] = curDist + 1;
                pre[next] = {cur, dirChar[d]}; // 记录前驱和方向
                q.push(next);
            }
        }
    }

    // 没有找到可行回路
    if (!found) {
        cout << "Stay home!" << endl;
        return;
    }

    // 从最优状态回溯，重建路径
    string path = "";
    State cur = bestState;
    while (dist[cur] > 0) {
        path += pre[cur].second;   // 方向字符
        cur = pre[cur].first;      // 前驱状态
    }
    reverse(path.begin(), path.end()); // 回溯得到的是逆序，需要反转
    cout << path << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> r >> c && (r || c)) solve();

    return 0;
}
