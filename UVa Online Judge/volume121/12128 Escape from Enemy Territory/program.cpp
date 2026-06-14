// Escape from Enemy Territory
// UVa ID: 12128
// Verdict: Accepted
// Submission Date: 2026-06-14
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

struct Point {
    int x, y;
    Point(int x_, int y_) : x(x_), y(y_) {}
};

// 多源 BFS 计算每个格子到最近敌军基地的距离
vector<vector<int>> computeNearestDist(int X, int Y, const vector<Point>& enemies) {
    vector<vector<int>> dist(X, vector<int>(Y, -1));
    queue<Point> q;
    for (const auto& e : enemies) {
        dist[e.x][e.y] = 0;
        q.push(e);
    }
    while (!q.empty()) {
        Point p = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[p.x][p.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
    return dist;
}

// 检查在安全距离 >= minDist 的情况下，从起点到终点是否可达，并返回最短路径长度（如果可达）
int bfsWithMinDist(int X, int Y, const Point& start, const Point& goal, 
                   const vector<vector<int>>& nearestDist, int minDist) {
    if (nearestDist[start.x][start.y] < minDist || nearestDist[goal.x][goal.y] < minDist)
        return -1;
    vector<vector<int>> step(X, vector<int>(Y, -1));
    queue<Point> q;
    step[start.x][start.y] = 0;
    q.push(start);
    while (!q.empty()) {
        Point p = q.front(); q.pop();
        if (p.x == goal.x && p.y == goal.y)
            return step[p.x][p.y];
        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i], ny = p.y + dy[i];
            if (nx >= 0 && nx < X && ny >= 0 && ny < Y && step[nx][ny] == -1 && nearestDist[nx][ny] >= minDist) {
                step[nx][ny] = step[p.x][p.y] + 1;
                q.push(Point(nx, ny));
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int T;
    cin >> T;
    while (T--) {
        int N, X, Y;
        cin >> N >> X >> Y;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Point start(x1, y1), goal(x2, y2);
        
        vector<Point> enemies;
        for (int i = 0; i < N; ++i) {
            int ex, ey;
            cin >> ex >> ey;
            enemies.emplace_back(ex, ey);
        }
        
        // 计算每个格子到最近敌军基地的距离
        vector<vector<int>> nearestDist = computeNearestDist(X, Y, enemies);
        
        // 二分查找最大安全距离
        int low = 0, high = X + Y, bestDist = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (bfsWithMinDist(X, Y, start, goal, nearestDist, mid) != -1) {
                bestDist = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        // 在最佳安全距离下，找最短路径长度
        int shortestPath = bfsWithMinDist(X, Y, start, goal, nearestDist, bestDist);
        cout << bestDist << " " << shortestPath << "\n";
    }
    
    return 0;
}
