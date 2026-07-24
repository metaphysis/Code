// Normals
// UVa ID: 10631
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.160s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double TWO_PI = 2.0 * PI;
const double EPS = 1e-10;

struct Point {
    double x, y;
};

bool cmpPoint(const Point& a, const Point& b) {
    if (fabs(a.x - b.x) > 1e-9) return a.x < b.x;
    return a.y < b.y;
}

bool samePoint(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y) < 1e-5;
}

// 方程 (1) 的左端函数
double f(double t, double a, double b, double p, double q) {
    double ct = cos(t), st = sin(t);
    return (a * a - b * b) * st * ct - a * p * st + b * q * ct;
}

// 二分法求根（前提：f(l) 与 f(r) 异号或其中之一为 0）
double bisect(double l, double r, double a, double b, double p, double q) {
    double fl = f(l, a, b, p, q), fr = f(r, a, b, p, q);
    if (fabs(fl) < EPS) return l;
    if (fabs(fr) < EPS) return r;
    for (int i = 0; i < 100; ++i) {
        double mid = (l + r) * 0.5;
        double fm = f(mid, a, b, p, q);
        if (fabs(fm) < EPS) return mid;
        if (fl * fm < 0) { r = mid; fr = fm; }
        else { l = mid; fl = fm; }
    }
    return (l + r) * 0.5;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int a_int, b_int, p_int, q_int;
    int caseNo = 1;
    while (cin >> a_int >> b_int >> p_int >> q_int) {
        if (a_int < 0) break;          // 终止条件
        double a = a_int, b = b_int, p = p_int, q = q_int;
        const int N = 200000;           // 采样点数
        double step = TWO_PI / N;
        vector<double> roots;
        for (int i = 0; i < N; ++i) {
            double t1 = i * step;
            double t2 = (i + 1) * step;
            double f1 = f(t1, a, b, p, q);
            double f2 = f(t2, a, b, p, q);
            // 检查左端点是否为根
            if (fabs(f1) < EPS) {
                bool dup = false;
                for (double r : roots)
                    if (fabs(r - t1) < 1e-7) { dup = true; break; }
                if (!dup) roots.push_back(t1);
            }
            // 区间内有根（异号）
            if (f1 * f2 < 0) {
                double root = bisect(t1, t2, a, b, p, q);
                bool dup = false;
                for (double r : roots)
                    if (fabs(r - root) < 1e-7) { dup = true; break; }
                if (!dup) roots.push_back(root);
            }
        }
        // 计算椭圆上的点坐标
        vector<Point> pts;
        for (double t : roots) {
            double x = a * cos(t);
            double y = b * sin(t);
            pts.push_back({x, y});
        }
        // 排序并去重（按距离 < 1e-5 合并）
        sort(pts.begin(), pts.end(), cmpPoint);
        vector<Point> uniquePts;
        for (const Point& pt : pts) {
            bool add = true;
            for (const Point& up : uniquePts) {
                if (samePoint(pt, up)) { add = false; break; }
            }
            if (add) uniquePts.push_back(pt);
        }
        // 输出
        cout << "Case " << caseNo << ":\n";
        cout << fixed << setprecision(5);
        for (const Point& pt : uniquePts) {
            cout << pt.x << " " << pt.y << "\n";
        }
        ++caseNo;
    }
    return 0;
}
