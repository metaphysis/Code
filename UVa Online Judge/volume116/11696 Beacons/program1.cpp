// Beacons
// UVa ID: 11696
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 3.720s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}
};

struct Circle {
    int x, y, r;
    Circle() {}
    Circle(int _x, int _y, int _r) : x(_x), y(_y), r(_r) {}
};

// 返回两点距离平方
inline long long dist2(const Point& a, const Point& b) {
    long long dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 判断线段AB是否被圆C阻挡（纯整数版本）
inline bool blockedByCircle(const Point& a, const Point& b, const Circle& c) {
    long long ax = b.x - a.x, ay = b.y - a.y;
    long long cx = c.x - a.x, cy = c.y - a.y;
    long long dot = cx * ax + cy * ay;
    long long len2 = ax * ax + ay * ay;
    
    // 投影点参数 t = dot / len2
    long long dist2ToLine;
    if (dot <= 0) {
        // 投影在 A 左侧
        dist2ToLine = cx * cx + cy * cy;
    } else if (dot >= len2) {
        // 投影在 B 右侧
        long long dx = c.x - b.x, dy = c.y - b.y;
        dist2ToLine = dx * dx + dy * dy;
    } else {
        // 投影在线段上，计算垂直距离平方
        // 使用叉积：|AB × AC|^2 / |AB|^2
        long long cross = cx * ay - cy * ax;
        dist2ToLine = (cross * cross) / (long double)len2; // 需要浮点除法保持精度
        // 为避免浮点，可以用整数比较：cross^2 < r^2 * len2
        // 但这里直接使用整数比较更精确
        return cross * cross < 1LL * c.r * c.r * len2;
    }
    return dist2ToLine < 1LL * c.r * c.r;
}

// 使用整数比较的版本（推荐，完全避免浮点）
inline bool blockedByCircleInt(const Point& a, const Point& b, const Circle& c) {
    long long ax = b.x - a.x, ay = b.y - a.y;
    long long cx = c.x - a.x, cy = c.y - a.y;
    long long dot = cx * ax + cy * ay;
    long long len2 = ax * ax + ay * ay;
    long long r2 = 1LL * c.r * c.r;
    
    if (dot <= 0) {
        // 投影在 A 左侧
        return (cx * cx + cy * cy) < r2;
    }
    if (dot >= len2) {
        // 投影在 B 右侧
        long long dx = c.x - b.x, dy = c.y - b.y;
        return (dx * dx + dy * dy) < r2;
    }
    // 投影在线段上，用叉积比较：|AB × AC|^2 < r^2 * |AB|^2
    long long cross = cx * ay - cy * ax;
    return cross * cross < r2 * len2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    while (N--) {
        int n, m;
        cin >> n >> m;
        vector<Point> beacons(n);
        for (int i = 0; i < n; ++i)
            cin >> beacons[i].x >> beacons[i].y;
        
        vector<Circle> peaks(m);
        for (int i = 0; i < m; ++i)
            cin >> peaks[i].x >> peaks[i].y >> peaks[i].r;
        
        // 预计算每个山峰的半径平方
        vector<long long> r2(m);
        for (int i = 0; i < m; ++i)
            r2[i] = 1LL * peaks[i].r * peaks[i].r;
        
        // 构建邻接表
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // 快速包围盒筛选：计算线段的外接矩形
                int minX = min(beacons[i].x, beacons[j].x);
                int maxX = max(beacons[i].x, beacons[j].x);
                int minY = min(beacons[i].y, beacons[j].y);
                int maxY = max(beacons[i].y, beacons[j].y);
                
                bool visible = true;
                for (int k = 0; k < m; ++k) {
                    // 包围盒预筛选：山峰圆心必须在线段矩形向外扩展半径的区域内
                    if (peaks[k].x + peaks[k].r < minX || peaks[k].x - peaks[k].r > maxX ||
                        peaks[k].y + peaks[k].r < minY || peaks[k].y - peaks[k].r > maxY) {
                        continue;  // 不可能阻挡，跳过
                    }
                    if (blockedByCircleInt(beacons[i], beacons[j], peaks[k])) {
                        visible = false;
                        break;
                    }
                }
                if (visible) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        
        // BFS 求连通分量数
        vector<bool> visited(n, false);
        int components = 0;
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                components++;
                queue<int> q;
                q.push(i);
                visited[i] = true;
                while (!q.empty()) {
                    int u = q.front(); q.pop();
                    for (int v : adj[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }
            }
        }
        
        cout << components - 1 << '\n';
    }
    return 0;
}
