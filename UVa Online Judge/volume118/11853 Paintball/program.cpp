// Paintball
// UVa ID: 11853
// Verdict: Accepted
// Submission Date: 2025-10-30
// UVa Run Time: 0.010s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net
//
// https://blog.csdn.net/metaphysis/article/details/154141383

#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;
const double W = 1000.0;

struct Circle {
    double x, y, r;
};

double dist(double x1, double y1, double x2, double y2) {
    return hypot(x1 - x2, y1 - y2);
}

bool circlesIntersect(const Circle& a, const Circle& b) {
    return dist(a.x, a.y, b.x, b.y) < a.r + b.r + eps;
}

int parent[1005];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) parent[a] = b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n) {
        vector<Circle> enemies(n);
        for (int i = 0; i < n; i++) {
            cin >> enemies[i].x >> enemies[i].y >> enemies[i].r;
        }

        // ===== 第一步：用并查集判断是否存在通路 =====
        for (int i = 0; i < n; i++) parent[i] = i;
        
        // 合并相交的圆
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (circlesIntersect(enemies[i], enemies[j])) {
                    unite(i, j);
                }
            }
        }

        // 检查每个连通分量是否同时接触上边界和下边界
        vector<bool> top(n, false), bottom(n, false);
        for (int i = 0; i < n; i++) {
            int root = find(i);
            if (enemies[i].y + enemies[i].r > W - eps) top[root] = true;
            if (enemies[i].y - enemies[i].r < eps) bottom[root] = true;
        }

        bool impossible = false;
        for (int i = 0; i < n; i++) {
            if (parent[i] == i && top[i] && bottom[i]) {
                impossible = true;
                break;
            }
        }

        if (impossible) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        // ===== 第二步：寻找最北入口和出口 =====
        vector<bool> visited(n, false);
        double leftBlock = W;  // 左边界阻挡的最南端，初始为最北
        double rightBlock = W; // 右边界阻挡的最南端，初始为最北

        // BFS 从接触上边界的圆开始扩展阻挡区域
        vector<int> queue;
        for (int i = 0; i < n; i++) {
            if (enemies[i].y + enemies[i].r > W - eps) { // 接触上边界
                visited[i] = true;
                queue.push_back(i);
            }
        }

        // BFS 扩展阻挡区域
        for (int idx = 0; idx < queue.size(); idx++) {
            int u = queue[idx];
            const Circle& c = enemies[u];

            // 更新左边界阻挡
            if (c.x - c.r < eps) { // 接触左边界
                double dy = sqrt(max(0.0, c.r * c.r - c.x * c.x)); // 避免数值误差
                double bottomY = c.y - dy;
                if (bottomY < leftBlock) {
                    leftBlock = bottomY;
                }
            }

            // 更新右边界阻挡
            if (c.x + c.r > W - eps) { // 接触右边界
                double dx = W - c.x;
                double dy = sqrt(max(0.0, c.r * c.r - dx * dx)); // 避免数值误差
                double bottomY = c.y - dy;
                if (bottomY < rightBlock) {
                    rightBlock = bottomY;
                }
            }

            // 扩展相邻圆
            for (int v = 0; v < n; v++) {
                if (!visited[v] && circlesIntersect(c, enemies[v])) {
                    visited[v] = true;
                    queue.push_back(v);
                }
            }
        }

        // 确定入口和出口坐标
        double enterY, exitY;
        
        if (leftBlock > W - eps) {
            // 没有圆阻挡左边界，入口可以是 (0, 1000)
            enterY = W;
        } else {
            // 阻挡区域最南端就是最北入口
            enterY = leftBlock;
            // 如果阻挡区域延伸到 y = 0 以下，入口只能是0
            if (enterY < 0) enterY = 0;
        }
        
        if (rightBlock > W - eps) {
            // 没有圆阻挡右边界，出口可以是 (1000, 1000)
            exitY = W;
        } else {
            // 阻挡区域最南端就是最北出口
            exitY = rightBlock;
            // 如果阻挡区域延伸到 y = 0 以下，出口只能是 0
            if (exitY < 0) exitY = 0;
        }

        // 输出结果
        cout << fixed << setprecision(2)
             << 0.00 << " " << enterY << " "
             << W << " " << exitY << "\n";
    }

    return 0;
}
