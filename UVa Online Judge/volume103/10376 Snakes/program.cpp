// Snakes
// UVa ID: 10376
// Verdict: Accepted
// Submission Date: 2026-04-28
// UVa Run Time: 0.010s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1100;
const double EPS = 1e-6;

struct Snake { double x, y, r; } snakes[MAXN];

int n, parent[MAXN];
vector<bool> top; // 标记每个连通分量是否与上边界相连

double dist(double x1, double y1, double x2, double y2) {
    return hypot(x1 - x2, y1 - y2);
}

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    int ra = find(a), rb = find(b);
    if (ra != rb) parent[ra] = rb;
}

// 计算在 x = boundaryX 的边界上，未被与上边界连通的圆覆盖的最高点
double findHighest(double boundaryX) {
    vector<pair<double, double>> cover;
    for (int i = 0; i < n; i++) {
        int root = find(i);
        if (!top[root]) continue; // 只考虑与上边界连通的圆
        double dx = abs(boundaryX - snakes[i].x);
        if (dx > snakes[i].r + EPS) continue; // 与边界无交点
        double dy = sqrt(max(0.0, snakes[i].r * snakes[i].r - dx * dx));
        double y1 = min(1000.0, snakes[i].y + dy);
        double y2 = max(0.0, snakes[i].y - dy);
        if (y1 >= y2 - EPS) cover.push_back({y2, y1});
    }
    sort(cover.begin(), cover.end());
    double res = 1000, cur = 1000;
    for (auto& seg : cover) {
        if (cur > seg.second + EPS) res = min(res, cur);
        cur = min(cur, seg.first);
    }
    if (cur > -EPS) res = min(res, cur);
    return res;
}

int main() {
    int t;
    cin >> t;
    for (int caseNum = 0; caseNum < t; caseNum++) {
        if (caseNum > 0) cout << endl;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> snakes[i].x >> snakes[i].y >> snakes[i].r;
        
        // 初始化并查集
        for (int i = 0; i < n; i++) parent[i] = i;
        
        // 合并所有相交的圆
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (dist(snakes[i].x, snakes[i].y, snakes[j].x, snakes[j].y) <= snakes[i].r + snakes[j].r + 1e-9)
                    unite(i, j);
        
        // 标记每个连通分量是否连接上下边界
        top.assign(n, false);
        vector<bool> bottom(n, false);
        for (int i = 0; i < n; i++) {
            int root = find(i);
            if (snakes[i].y + snakes[i].r >= 1000 - EPS) top[root] = true;
            if (snakes[i].y - snakes[i].r <= 0 + EPS) bottom[root] = true;
        }
        
        // 检查是否存在连接上下边界的连通分量
        bool blocked = false;
        for (int i = 0; i < n; i++)
            if (find(i) == i && top[i] && bottom[i]) { blocked = true; break; }
        
        if (blocked) {
            cout << "Bill will be bitten." << endl;
            continue;
        }
        
        // 找到最靠北的入口和出口
        double entryY = findHighest(0);
        double exitY = findHighest(1000);
        
        printf("Bill enters at (0.00, %.2f) and leaves at (1000.00, %.2f).\n", entryY, exitY);
    }
    return 0;
}
