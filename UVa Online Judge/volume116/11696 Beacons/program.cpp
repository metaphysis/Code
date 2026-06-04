// Beacons
// UVa ID: 11696
// Verdict: Accepted
// Submission Date: 2026-06-04
// UVa Run Time: 14.490s
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

double dist2(const Point& a, const Point& b) {
    int dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// 点到线段的最短距离平方
double pointToSegmentDist2(const Point& p, const Point& a, const Point& b) {
    double ax = b.x - a.x, ay = b.y - a.y;
    double t = ((p.x - a.x) * ax + (p.y - a.y) * ay) / (ax * ax + ay * ay);
    if (t < 0) return dist2(p, a);
    if (t > 1) return dist2(p, b);
    double projX = a.x + t * ax, projY = a.y + t * ay;
    double dx = p.x - projX, dy = p.y - projY;
    return dx * dx + dy * dy;
}

// 判断线段AB是否被圆C阻挡
bool blockedByCircle(const Point& a, const Point& b, const Circle& c) {
    double d2 = pointToSegmentDist2(Point(c.x, c.y), a, b);
    return d2 < 1.0 * c.r * c.r - 1e-8;
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

        // 构建邻接表
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                bool visible = true;
                for (int k = 0; k < m; ++k) {
                    if (blockedByCircle(beacons[i], beacons[j], peaks[k])) {
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
