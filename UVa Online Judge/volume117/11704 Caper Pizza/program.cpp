// Caper Pizza
// UVa ID: 11704
// Verdict: Accepted
// Submission Date: 2026-01-09
// UVa Run Time: 0.150s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-12;

struct Point {
    double angle;
    int type;  // 0 表示酸豆, 1 表示胡椒粒
    Point(double a = 0, int t = 0) : angle(a), type(t) {}
    bool operator < (const Point& other) const {
        return angle < other.angle;
    }
};

bool solve(int c, int p, vector<Point>& points) {
    int targetC = c / 2, targetP = p / 2;
    int n = c + p;
    vector<Point> sorted;
    for (const auto& pt : points) sorted.push_back(pt);
    sort(sorted.begin(), sorted.end());
    // 复制一份并偏移 2π，便于处理循环
    for (int i = 0; i < n; ++i) sorted.push_back(Point(sorted[i].angle + 2 * PI, sorted[i].type));
    int cntC = 0, cntP = 0;
    int right = 0;
    // 初始化窗口 [0, right) 内的计数
    while (right < n && sorted[right].angle < sorted[0].angle + PI + EPS) {
        if (sorted[right].type == 0) cntC++;
        else cntP++;
        right++;
    }
    // 检查初始窗口
    if (cntC == targetC && cntP == targetP) return true;
    // 滑动窗口
    for (int left = 1; left < n; ++left) {
        // 移出 left-1 点
        if (sorted[left - 1].type == 0) cntC--;
        else cntP--;
        // 移入 right 点
        while (right < left + n && sorted[right].angle < sorted[left].angle + PI + EPS) {
            if (sorted[right].type == 0) cntC++;
            else cntP++;
            right++;
        }
        if (cntC == targetC && cntP == targetP) return true;
    }
    return false;
}

int main() {
    int c, p;
    while (cin >> c >> p, c != -1 || p != -1) {
        vector<Point> points;
        double x, y;
        for (int i = 0; i < c; ++i) {
            cin >> x >> y;
            double angle = atan2(y, x);
            if (angle < 0) angle += 2 * PI;  // 转换到 [0, 2π)
            points.push_back(Point(angle, 0));
        }
        for (int i = 0; i < p; ++i) {
            cin >> x >> y;
            double angle = atan2(y, x);
            if (angle < 0) angle += 2 * PI;
            points.push_back(Point(angle, 1));
        }
        bool r = solve(c, p, points);
        cout << (r ? "YES" : "NO") << '\n';
    }
    return 0;
}
