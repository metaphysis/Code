#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    bool operator < (const Point &other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

long long cross(const Point &a, const Point &b, const Point &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point> getHull(vector<Point> points) {
    int n = points.size();
    vector<Point> lower, upper, hull;
    sort(points.begin(), points.end());
    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2 && cross(lower[lower.size() - 2], lower.back(), points[i]) <= 0) lower.pop_back();
        lower.push_back(points[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        while (upper.size() >= 2 && cross(upper[upper.size() - 2], upper.back(), points[i]) <= 0) upper.pop_back();
        upper.push_back(points[i]);
    }
    lower.pop_back();
    upper.pop_back();
    hull = lower;
    hull.insert(hull.end(), upper.begin(), upper.end());
    return hull;
}

long double getWidth(const vector<Point> &hull) {
    int m = hull.size();
    if (m <= 2) return 0;
    int j = 1;
    long double answer = numeric_limits<long double>::max();
    for (int i = 0; i < m; i++) {
        int next = (i + 1) % m;
        while (cross(hull[i], hull[next], hull[(j + 1) % m]) > cross(hull[i], hull[next], hull[j])) j = (j + 1) % m;
        long long area = cross(hull[i], hull[next], hull[j]);
        long double dx = hull[next].x - hull[i].x, dy = hull[next].y - hull[i].y;
        long double width = area / sqrtl(dx * dx + dy * dy);
        if (width < answer) answer = width;
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long r;
    while (cin >> n >> r) {
        vector<Point> points, hull;
        points.resize(n);
        for (int i = 0; i < n; i++) cin >> points[i].x >> points[i].y;
        hull = getHull(points);
        cout << fixed << setprecision(15) << getWidth(hull) << '\n';
    }
    return 0;
}
