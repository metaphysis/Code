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

void computeLayer(const vector<Point> &hull, const vector<long double> &prev, vector<long double> &cur, int start, int left, int right, int optLeft, int optRight) {
    if (left > right) return;
    int mid = (left + right) / 2, low = start, begin = max(optLeft, low), end = min(optRight, mid - 1), bestK = begin;
    long double best = -1.0L, value;
    for (int k = begin; k <= end; ++k) {
        value = prev[k] + getDistance(hull[k], hull[mid]);
        if (value > best) {
            best = value;
            bestK = k;
        }
    }
    cur[mid] = best;
    computeLayer(hull, prev, cur, start, left, mid - 1, optLeft, bestK);
    computeLayer(hull, prev, cur, start, mid + 1, right, bestK, optRight);
}

long double getMaxPerimeter(const vector<Point> &hull) {
    int m = hull.size(), i, j, count, first;
    long double answer = -1.0L;
    vector<long double> prev(m), cur(m);
    for (i = 0; i + 4 < m; ++i) {
        for (j = i + 1; j < m; ++j)
            prev[j] = getDistance(hull[i], hull[j]);
        for (count = 3; count <= 5; ++count) {
            fill(cur.begin(), cur.end(), -1.0L);
            first = i + count - 1;
            computeLayer(hull, prev, cur, i + count - 2, first, m - 1, i + count - 2, m - 2);
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
