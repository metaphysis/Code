#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    bool operator < (const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

long long cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point> getHull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end(), [](const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y;
    }), p.end());
    if (p.size() <= 2) return p;
    vector<Point> hull;
    for (const Point& point : p) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), point) <= 0)
            hull.pop_back();
        hull.push_back(point);
    }
    int lowerSize = hull.size();
    for (int i = (int)p.size() - 2; i >= 0; i--) {
        while ((int)hull.size() > lowerSize && cross(hull[hull.size() - 2], hull.back(), p[i]) <= 0)
            hull.pop_back();
        hull.push_back(p[i]);
    }
    hull.pop_back();
    return hull;
}

long long getMaxArea(const vector<Point>& hull) {
    int m = hull.size();
    long long ans = 0;
    for (int i = 0; i < m - 2; i++) {
        int k = i + 2;
        for (int j = i + 1; j < m - 1; j++) {
            if (k <= j) k = j + 1;
            while (k + 1 < m && cross(hull[i], hull[j], hull[k]) <= cross(hull[i], hull[j], hull[k + 1]))
                k++;
            ans = max(ans, cross(hull[i], hull[j], hull[k]));
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Point> p(n);
        for (Point& point : p)
            cin >> point.x >> point.y;
        vector<Point> hull = getHull(p);
        long long area2 = getMaxArea(hull);
        cout << area2 / 2 << (area2 % 2 ? ".5\n" : ".0\n");
    }
    return 0;
}
