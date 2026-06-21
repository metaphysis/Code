// Gifts Large and Small
// UVa ID: 819
// Verdict: Accepted
// Submission Date: 2026-06-21
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double EPS = 1e-12;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    bool operator<(const Point& o) const {
        return x < o.x - EPS || (fabs(x - o.x) < EPS && y < o.y - EPS);
    }
    bool operator==(const Point& o) const {
        return fabs(x - o.x) < EPS && fabs(y - o.y) < EPS;
    }
};

double cross(const Point& o, const Point& a, const Point& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// 安德鲁单调链求凸包，返回逆时针顺序，无共线点
vector<Point> convexHull(vector<Point> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() <= 1) return pts;
    vector<Point> lower, upper;
    for (auto& p : pts) {
        while (lower.size() >= 2 && cross(lower[lower.size()-2], lower.back(), p) <= EPS)
            lower.pop_back();
        lower.push_back(p);
    }
    for (int i = (int)pts.size() - 1; i >= 0; --i) {
        auto& p = pts[i];
        while (upper.size() >= 2 && cross(upper[upper.size()-2], upper.back(), p) <= EPS)
            upper.pop_back();
        upper.push_back(p);
    }
    lower.pop_back();
    upper.pop_back();
    lower.insert(lower.end(), upper.begin(), upper.end());
    return lower;
}

// 归一化角度到 [0, PI)
double normAng(double a) {
    a = fmod(a, PI);
    if (a < 0) a += PI;
    return a;
}

// 计算给定角度下外接矩形面积
double areaAtAngle(const vector<Point>& hull, double theta) {
    double ux = cos(theta), uy = sin(theta);
    double vx = -uy, vy = ux;
    double minU = 1e100, maxU = -1e100, minV = 1e100, maxV = -1e100;
    for (auto& p : hull) {
        double du = p.x * ux + p.y * uy;
        double dv = p.x * vx + p.y * vy;
        if (du < minU) minU = du;
        if (du > maxU) maxU = du;
        if (dv < minV) minV = dv;
        if (dv > maxV) maxV = dv;
    }
    return (maxU - minU) * (maxV - minV);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, caseNo = 0;
    while (cin >> n && n) {
        vector<Point> poly(n);
        for (int i = 0; i < n; ++i) cin >> poly[i].x >> poly[i].y;
        vector<Point> hull = convexHull(poly);
        int m = hull.size();

        // 收集所有临界角度
        vector<double> angles;
        angles.push_back(0.0);
        angles.push_back(PI);
        for (int i = 0; i < m; ++i) {
            int j = (i + 1) % m;
            double dx = hull[j].x - hull[i].x;
            double dy = hull[j].y - hull[i].y;
            double ang = atan2(dy, dx);
            ang = normAng(ang);
            angles.push_back(ang);
            angles.push_back(normAng(ang + PI / 2.0));
        }
        sort(angles.begin(), angles.end());
        vector<double> uniq;
        for (double a : angles) {
            if (uniq.empty() || a - uniq.back() > EPS)
                uniq.push_back(a);
        }
        // 确保包含 PI
        if (uniq.back() < PI - EPS) uniq.push_back(PI);
        else uniq.back() = PI;

        double minArea = 1e100, maxArea = -1e100;

        // 检查所有端点
        for (double theta : uniq) {
            double a = areaAtAngle(hull, theta);
            minArea = min(minArea, a);
            maxArea = max(maxArea, a);
        }

        // 检查每个区间的内部极值点
        for (size_t i = 0; i + 1 < uniq.size(); ++i) {
            double L = uniq[i], R = uniq[i + 1];
            if (R - L < EPS) continue;
            double mid = (L + R) / 2.0;
            double ux = cos(mid), uy = sin(mid);
            double vx = -uy, vy = ux;

            // 找四个支撑点（取顶点）
            int idxMaxU = 0, idxMinU = 0, idxMaxV = 0, idxMinV = 0;
            double maxU = -1e100, minU = 1e100, maxV = -1e100, minV = 1e100;
            for (int k = 0; k < m; ++k) {
                double du = hull[k].x * ux + hull[k].y * uy;
                double dv = hull[k].x * vx + hull[k].y * vy;
                if (du > maxU) { maxU = du; idxMaxU = k; }
                if (du < minU) { minU = du; idxMinU = k; }
                if (dv > maxV) { maxV = dv; idxMaxV = k; }
                if (dv < minV) { minV = dv; idxMinV = k; }
            }
            Point pmax = hull[idxMaxU], pmin = hull[idxMinU];
            Point qmax = hull[idxMaxV], qmin = hull[idxMinV];

            // W(theta) = a*cos + b*sin
            double a = pmax.x - pmin.x;
            double b = pmax.y - pmin.y;
            // H(theta) = c*cos + d*sin
            double c = qmax.y - qmin.y;
            double d = qmin.x - qmax.x;

            double ac = a * c, bd = b * d;
            double ad = a * d, bc = b * c;
            double K = (ac + bd) / 2.0;
            double P = (ac - bd) / 2.0;
            double Q = (ad + bc) / 2.0;

            if (fabs(P) < EPS && fabs(Q) < EPS) continue; // 常数

            // 解导数零点: Q*cos(2θ) = P*sin(2θ)  => 2θ = atan2(Q, P) + kπ
            double base = atan2(Q, P);
            for (int k = -3; k <= 3; ++k) {
                double theta = (base + k * PI) / 2.0;
                if (theta > L + EPS && theta < R - EPS) {
                    double area = areaAtAngle(hull, theta);
                    minArea = min(minArea, area);
                    maxArea = max(maxArea, area);
                }
            }
        }

        // 防止负零
        if (minArea < 0 && minArea > -1e-9) minArea = 0;
        if (maxArea < 0 && maxArea > -1e-9) maxArea = 0;

        cout << "Gift " << ++caseNo << '\n';
        cout << fixed << setprecision(3) << "Minimum area = " << minArea << '\n';
        cout << "Maximum area = " << maxArea << "\n\n";
    }
    return 0;
}
