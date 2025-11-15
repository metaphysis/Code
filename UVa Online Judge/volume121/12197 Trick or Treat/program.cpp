// Trick or Treat
// UVa ID: 12197
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.270s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

double evaluate(const vector<Point>& houses, double X) {
    double maxTime = 0.0;
    for (const auto& house : houses) {
        double dx = house.x - X;
        double dy = house.y;
        double dist = sqrt(dx * dx + dy * dy);
        if (dist > maxTime) {
            maxTime = dist;
        }
    }
    return maxTime;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    while (cin >> n && n != 0) {
        vector<Point> houses(n);
        double minX = 1e9, maxX = -1e9;
        double maxAbsY = 0;

        for (int i = 0; i < n; ++i) {
            cin >> houses[i].x >> houses[i].y;
            if (houses[i].x < minX) minX = houses[i].x;
            if (houses[i].x > maxX) maxX = houses[i].x;
            if (fabs(houses[i].y) > maxAbsY) maxAbsY = fabs(houses[i].y);
        }

        // 搜索区间
        double left = minX - maxAbsY;
        double right = maxX + maxAbsY;

        // 三分搜索
        for (int iter = 0; iter < 100; ++iter) {
            double m1 = left + (right - left) / 3.0;
            double m2 = right - (right - left) / 3.0;
            double t1 = evaluate(houses, m1);
            double t2 = evaluate(houses, m2);
            if (t1 < t2) {
                right = m2;
            } else {
                left = m1;
            }
        }

        double bestX = (left + right) / 2.0;
        double bestTime = evaluate(houses, bestX);

        cout << fixed << setprecision(9) << bestX << " " << bestTime << "\n";
    }

    return 0;
}
