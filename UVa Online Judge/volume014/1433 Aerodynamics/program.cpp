#include <bits/stdc++.h>
using namespace std;

const double Eps = 1e-10;

struct Point3 {
    double x, y, z;
};

struct Point2 {
    double x, y;
    bool operator < (const Point2 &other) const {
        if (fabs(x - other.x) > Eps)
            return x < other.x;
        return y < other.y;
    }
};

double Cross(const Point2 &a, const Point2 &b, const Point2 &c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Point2> GetHull(vector<Point2> points) {
    sort(points.begin(), points.end());
    vector<Point2> uniquePoints;
    for (int i = 0; i < (int)points.size(); i++) {
        if (uniquePoints.empty() || fabs(points[i].x - uniquePoints.back().x) > Eps || fabs(points[i].y - uniquePoints.back().y) > Eps)
            uniquePoints.push_back(points[i]);
    }
    if (uniquePoints.size() <= 1)
        return uniquePoints;
    vector<Point2> hull(2 * uniquePoints.size());
    int size = 0;
    for (int i = 0; i < (int)uniquePoints.size(); i++) {
        while (size >= 2 && Cross(hull[size - 2], hull[size - 1], uniquePoints[i]) <= Eps)
            size--;
        hull[size++] = uniquePoints[i];
    }
    for (int i = (int)uniquePoints.size() - 2, limit = size + 1; i >= 0; i--) {
        while (size >= limit && Cross(hull[size - 2], hull[size - 1], uniquePoints[i]) <= Eps)
            size--;
        hull[size++] = uniquePoints[i];
    }
    hull.resize(size - 1);
    return hull;
}

double GetArea(const vector<Point2> &hull) {
    if (hull.size() < 3)
        return 0.0;
    double area = 0.0;
    for (int i = 0; i < (int)hull.size(); i++) {
        int next = (i + 1) % hull.size();
        area += hull[i].x * hull[next].y - hull[i].y * hull[next].x;
    }
    return fabs(area) * 0.5;
}

double GetSectionArea(const vector<Point3> &points, int z0) {
    vector<Point2> section;
    for (int i = 0; i < (int)points.size(); i++) {
        if (fabs(points[i].z - z0) <= Eps)
            section.push_back({points[i].x, points[i].y});
    }
    for (int i = 0; i < (int)points.size(); i++) {
        for (int j = i + 1; j < (int)points.size(); j++) {
            double left = points[i].z - z0, right = points[j].z - z0;
            if (left * right >= -Eps)
                continue;
            double t = (z0 - points[i].z) / (points[j].z - points[i].z);
            section.push_back({points[i].x + t * (points[j].x - points[i].x), points[i].y + t * (points[j].y - points[i].y)});
        }
    }
    return GetArea(GetHull(section));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, zMin, zMax;
    bool firstCase = true;
    while (cin >> n >> zMin >> zMax) {
        vector<Point3> points(n);
        for (int i = 0; i < n; i++)
            cin >> points[i].x >> points[i].y >> points[i].z;
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        cout << fixed << setprecision(10);
        for (int z0 = zMin; z0 <= zMax; z0++)
            cout << GetSectionArea(points, z0) << '\n';
    }
    return 0;
}
