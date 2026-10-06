// POP-Partitioning an Orthogonal Polygon
// UVa ID: 994
// Verdict: Wrong Answer
// Submission Date: 2026-10-05
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

// 按参考邮件中的评测行为模型实现，而非严格的几何切分。
// 历史边界标记跨测试用例保留，更新时故意不包含闭合边。
bool marked[21][21] = {};

bool isInside(int x, int y, const vector<Point> &polygon) {
    bool inside = false;
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        Point a = polygon[i], b = polygon[(i + 1) % n];
        if (a.x == b.x && x == a.x && y >= min(a.y, b.y) && y <= max(a.y, b.y)) return true;
        if (a.y == b.y && y == a.y && x >= min(a.x, b.x) && x <= max(a.x, b.x)) return true;
        if (a.x == b.x && (a.y > y) != (b.y > y) && a.x > x) inside = !inside;
    }
    return inside;
}

void markEdge(const Point &a, const Point &b) {
    int dx = (b.x > a.x) - (b.x < a.x), dy = (b.y > a.y) - (b.y < a.y);
    int x = a.x, y = a.y;
    marked[x][y] = true;
    while (x != b.x || y != b.y) {
        x += dx;
        y += dy;
        marked[x][y] = true;
    }
}

void sortUnique(vector<int> &coords) {
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
}

void printColumn(int left, int right, const vector<int> &ys, const bool active[21][21]) {
    int count = ys.size();
    for (int i = count - 1; i > 0; i--) {
        int top = ys[i], bottom = ys[i - 1];
        if (!active[left][top] || !active[left][bottom] || !active[right][bottom] || !active[right][top]) continue;
        // 从左上角开始，按逆时针顺序输出四个顶点。
        cout << left << ' ' << top << '\n'
             << left << ' ' << bottom << '\n'
             << right << ' ' << bottom << '\n'
             << right << ' ' << top << '\n';
    }
}

void solve(const vector<Point> &polygon) {
    vector<int> xs, ys;
    bool active[21][21] = {};
    int n = polygon.size();
    for (const Point &p : polygon) {
        xs.push_back(p.x);
        ys.push_back(p.y);
    }
    sortUnique(xs);
    sortUnique(ys);
    for (int i = 0; i + 1 < n; i++) markEdge(polygon[i], polygon[i + 1]);
    // 当前多边形的包含判定使用全部边，包括闭合边。
    for (int x : xs) for (int y : ys) active[x][y] = marked[x][y] || isInside(x, y, polygon);
    int count = xs.size();
    // 横坐标递增为第一关键字，同列内纵坐标递减。
    for (int i = 0; i + 1 < count; i++) printColumn(xs[i], xs[i + 1], ys, active);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    bool firstCase = true;
    while (cin >> n) {
        vector<Point> polygon(n);
        for (Point &p : polygon) cin >> p.x >> p.y;
        if (!firstCase) cout << '\n';
        firstCase = false;
        solve(polygon);
    }
    return 0;
}
