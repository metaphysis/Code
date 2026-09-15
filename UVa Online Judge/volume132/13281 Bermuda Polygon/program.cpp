#include <bits/stdc++.h>
using namespace std;

struct Point {
    long double x, y;
    int id;
};

long double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

Point toPoint(int lat, int lon, int id) {
    const long double pi = acosl(-1.0L);
    long double latRad = lat * pi / 180.0L, lonRad = lon * pi / 180.0L;
    long double x = cosl(lonRad) / sinl(lonRad), y = sinl(latRad) / (cosl(latRad) * sinl(lonRad));
    return {x, y, id};
}

vector<Point> getHull(vector<Point> points) {
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    });
    int n = points.size(), size = 0;
    const long double eps = 1e-12L;
    vector<Point> hull(2 * n);
    for (int i = 0; i < n; ++i) {
        while (size >= 2 && cross(hull[size - 2], hull[size - 1], points[i]) <= eps)
            --size;
        hull[size++] = points[i];
    }
    int startSize = size;
    for (int i = n - 2; i >= 0; --i) {
        while (size > startSize && cross(hull[size - 2], hull[size - 1], points[i]) <= eps)
            --size;
        hull[size++] = points[i];
    }
    hull.resize(size - 1);
    return hull;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int dataCount;
    cin >> dataCount;
    while (dataCount--) {
        int n;
        cin >> n;
        vector<Point> points;
        for (int i = 0; i < n; ++i) {
            int lat, lon;
            cin >> lat >> lon;
            points.push_back(toPoint(lat, lon, i));
        }
        vector<Point> hull = getHull(points);
        if (hull.size() < 3 || hull.size() == points.size()) {
            cout << "inconclusive\n";
            continue;
        }
        vector<int> answer;
        for (const Point& point : hull)
            answer.push_back(point.id);
        sort(answer.begin(), answer.end());
        for (int i = 0; i < static_cast<int>(answer.size()); ++i) {
            if (i > 0)
                cout << ' ';
            cout << answer[i];
        }
        cout << '\n';
    }
    return 0;
}
