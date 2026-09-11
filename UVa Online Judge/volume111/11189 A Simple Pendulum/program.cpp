// A Simple Pendulum
// UVa ID: 11189
// Verdict: Accepted
// Submission Date: 2026-07-31
// UVa Run Time: 0.000s

#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

int main() {
    int caseNo = 0;
    double len, T;
    const double PI = acos(-1.0);
    const double g = 981.0;
    const double EPS = 1e-7;
    const double SAME = 0.01;

    while (cin >> len >> T) {
        if (len < 0) break;
        ++caseNo;
        Point v[4];
        for (int i = 0; i < 4; ++i) cin >> v[i].x >> v[i].y;

        // 计算重心（形心）
        double area = 0, cx = 0, cy = 0;
        for (int i = 0; i < 4; ++i) {
            int j = (i + 1) % 4;
            double cross = v[i].x * v[j].y - v[j].x * v[i].y;
            area += cross;
            cx += (v[i].x + v[j].x) * cross;
            cy += (v[i].y + v[j].y) * cross;
        }
        area *= 0.5;
        cx /= (6.0 * area);
        cy /= (6.0 * area);
        Point G(cx, cy);

        double L = g * (T / (2.0 * PI)) * (T / (2.0 * PI));
        // 如果所需有效长度小于绳长，则不可能（AG = L - len < 0）
        if (L + SAME < len) {
            cout << "Pendulum " << caseNo << ": No\n";
            continue;
        }
        double d = L - len;
        if (d < 0) d = 0; // 若非常接近0，则可能无解，但后面距离判断会过滤

        vector<Point> pts;
        for (int i = 0; i < 4; ++i) {
            int j = (i + 1) % 4;
            Point P0 = v[i], P1 = v[j];
            double vx = P1.x - P0.x, vy = P1.y - P0.y;
            double wx = P0.x - G.x, wy = P0.y - G.y;
            double a = vx * vx + vy * vy;
            double b = 2.0 * (wx * vx + wy * vy);
            double c = wx * wx + wy * wy - d * d;
            double disc = b * b - 4.0 * a * c;
            if (disc < -EPS) continue;
            if (disc < 0) disc = 0;
            double sqrtDisc = sqrt(disc);
            double t1 = (-b - sqrtDisc) / (2.0 * a);
            double t2 = (-b + sqrtDisc) / (2.0 * a);
            double ts[2] = {t1, t2};
            for (int k = 0; k < 2; ++k) {
                double t = ts[k];
                if (t < -EPS || t > 1.0 + EPS) continue;
                double px = P0.x + t * vx, py = P0.y + t * vy;
                Point p(px, py);
                double dd = dist(p, G);
                if (fabs(dd - d) < SAME) {
                    // 去重
                    bool dup = false;
                    for (const auto& q : pts) {
                        if (dist(p, q) < SAME) { dup = true; break; }
                    }
                    if (!dup) pts.push_back(p);
                }
            }
        }

        int cnt = pts.size();
        if (cnt == 0)
            cout << "Pendulum " << caseNo << ": No\n";
        else
            cout << "Pendulum " << caseNo << ": Yes " << cnt << "\n";
    }
    return 0;
}
