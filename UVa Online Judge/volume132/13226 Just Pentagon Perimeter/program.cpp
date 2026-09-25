#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

__int128 cross(const Point &a, const Point &b, const Point &c) {
    return (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
}

long double getDistance(const Point &a, const Point &b) {
    long double dx = (long double)a.x - b.x, dy = (long double)a.y - b.y;
    return sqrtl(dx * dx + dy * dy);
}

vector<Point> getConvexHull(vector<Point> points) {
    int n = points.size(), i;
    vector<Point> hull;
    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });
    for (i = 0; i < n; ++i) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0) hull.pop_back();
        hull.push_back(points[i]);
    }
    int lowerSize = hull.size();
    for (i = n - 2; i >= 0; --i) {
        while ((int)hull.size() > lowerSize && cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0) hull.pop_back();
        hull.push_back(points[i]);
    }
    hull.pop_back();
    return hull;
}

long double getMaxPerimeter(const vector<Point> &hull) {
    int m = hull.size(), i, j, k, count;
    long double answer = -1.0L, best, value;
    int bestK, opt;
    vector<long double> prev(m), cur(m);
    for (i = 0; i + 4 < m; ++i) {
        for (j = i + 1; j < m; ++j)
            prev[j] = getDistance(hull[i], hull[j]);
        for (count = 3; count <= 5; ++count) {
            fill(cur.begin(), cur.end(), -1.0L);
            opt = i + count - 2;
            for (j = i + count - 1; j < m; ++j) {
                best = -1.0L;
                bestK = opt;
                for (k = opt; k < j; ++k) {
                    value = prev[k] + getDistance(hull[k], hull[j]);
                    if (value > best) {
                        best = value;
                        bestK = k;
                    }
                }
                cur[j] = best;
                opt = bestK;
            }
            prev.swap(cur);
        }
        for (j = i + 4; j < m; ++j)
            answer = max(answer, prev[j] + getDistance(hull[j], hull[i]));
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Point> points(n);
        int i;
        for (i = 0; i < n; ++i)
            cin >> points[i].x >> points[i].y;
        vector<Point> hull = getConvexHull(points);
        if (hull.size() < 5) {
            cout << -1 << '\n';
            continue;
        }
        long double answer = getMaxPerimeter(hull);
        cout << fixed << setprecision(2) << answer << '\n';
    }
    return 0;
}
