#include <bits/stdc++.h>
using namespace std;

const double pi = acos(-1.0);
const double eps = 1e-10;

struct Circle {
    double x, y, r;
};

double arcArea(const Circle &c, double left, double right) {
    return 0.5 * (c.r * c.r * (right - left) + c.x * c.r * (sin(right) - sin(left)) - c.y * c.r * (cos(right) - cos(left)));
}

double solveArea(const vector<Circle> &circles) {
    int n = circles.size();
    double ans = 0.0;
    for (int i = 0; i < n; i++) {
        const Circle &cur = circles[i];
        vector<pair<double, double> > segments;
        bool covered = false;
        for (int j = 0; j < n; j++) {
            if (i == j)
                continue;
            const Circle &other = circles[j];
            double dx = other.x - cur.x, dy = other.y - cur.y;
            double dis = hypot(dx, dy);
            if (dis <= eps) {
                if (other.r > cur.r + eps || fabs(other.r - cur.r) <= eps && j < i) {
                    covered = true;
                    break;
                }
                continue;
            }
            if (dis + cur.r <= other.r + eps) {
                if (other.r > cur.r + eps || j < i) {
                    covered = true;
                    break;
                }
                continue;
            }
            if (dis >= cur.r + other.r - eps || dis + other.r <= cur.r + eps)
                continue;
            double mid = atan2(dy, dx);
            double value = (dis * dis + cur.r * cur.r - other.r * other.r) / (2.0 * dis * cur.r);
            value = max(-1.0, min(1.0, value));
            double half = acos(value);
            double left = mid - half, right = mid + half;
            while (left < 0.0) {
                left += 2.0 * pi;
                right += 2.0 * pi;
            }
            while (left >= 2.0 * pi) {
                left -= 2.0 * pi;
                right -= 2.0 * pi;
            }
            if (right <= 2.0 * pi)
                segments.push_back(make_pair(left, right));
            else {
                segments.push_back(make_pair(left, 2.0 * pi));
                segments.push_back(make_pair(0.0, right - 2.0 * pi));
            }
        }
        if (covered)
            continue;
        if (segments.empty()) {
            ans += arcArea(cur, 0.0, 2.0 * pi);
            continue;
        }
        sort(segments.begin(), segments.end());
        vector<pair<double, double> > merged;
        for (const pair<double, double> &segment : segments) {
            if (merged.empty() || segment.first > merged.back().second + eps)
                merged.push_back(segment);
            else
                merged.back().second = max(merged.back().second, segment.second);
        }
        double start = 0.0;
        for (const pair<double, double> &segment : merged) {
            if (segment.first > start + eps)
                ans += arcArea(cur, start, segment.first);
            start = max(start, segment.second);
        }
        if (start < 2.0 * pi - eps)
            ans += arcArea(cur, start, 2.0 * pi);
    }
    return fabs(ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cout << fixed << setprecision(3);
    while (cin >> n && n != 0) {
        vector<Circle> circles(n);
        for (Circle &circle : circles)
            cin >> circle.x >> circle.y >> circle.r;
        cout << solveArea(circles) << '\n';
    }
    return 0;
}
