// POP-Partitioning an Orthogonal Polygon
// UVa ID: 994
// Verdict: Accepted
// Submission Date: 2026-10-06
// UVa Run Time: 0.770s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

struct Rect {
    int x1, y1, x2, y2;
};

set<pair<int, int>> savedPoints;

bool onSegment(const Point& a, const Point& b, int x, int y) {
    long long cross = 1LL * (b.x - a.x) * (y - a.y) - 1LL * (b.y - a.y) * (x - a.x);
    if (cross != 0)
        return false;
    if (x < min(a.x, b.x) || x > max(a.x, b.x))
        return false;
    if (y < min(a.y, b.y) || y > max(a.y, b.y))
        return false;
    return true;
}

bool inPolygon(const vector<Point>& polygon, int x, int y) {
    int n = polygon.size(), i, j;
    for (i = 0; i < n; i++) {
        j = (i + 1) % n;
        if (onSegment(polygon[i], polygon[j], x, y))
            return true;
    }
    bool inside = false;
    for (i = 0, j = n - 1; i < n; j = i++) {
        int xi = polygon[i].x, yi = polygon[i].y;
        int xj = polygon[j].x, yj = polygon[j].y;
        if ((yi > y) != (yj > y)) {
            long double crossX = xi + (long double)(xj - xi) * (y - yi) / (yj - yi);
            if (x < crossX)
                inside = !inside;
        }
    }
    return inside;
}

bool activePoint(const vector<Point>& polygon, int x, int y) {
    if (savedPoints.count({x, y}) != 0)
        return true;
    return inPolygon(polygon, x, y);
}

void saveEdgePoints(const Point& a, const Point& b) {
    if (a.x == b.x) {
        int low = min(a.y, b.y), high = max(a.y, b.y), y;
        for (y = low; y <= high; y++)
            savedPoints.insert({a.x, y});
    } else {
        int low = min(a.x, b.x), high = max(a.x, b.x), x;
        for (x = low; x <= high; x++)
            savedPoints.insert({x, a.y});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    bool firstCase = true;
    while (cin >> n) {
        vector<Point> polygon(n);
        vector<int> xVals, yVals;
        int i, j;
        for (i = 0; i < n; i++) {
            cin >> polygon[i].x >> polygon[i].y;
            xVals.push_back(polygon[i].x);
            yVals.push_back(polygon[i].y);
        }
        for (i = 0; i + 1 < n; i++)
            saveEdgePoints(polygon[i], polygon[i + 1]);
        sort(xVals.begin(), xVals.end());
        sort(yVals.begin(), yVals.end());
        xVals.erase(unique(xVals.begin(), xVals.end()), xVals.end());
        yVals.erase(unique(yVals.begin(), yVals.end()), yVals.end());
        vector<Rect> answer;
        for (i = 0; i + 1 < (int)xVals.size(); i++) {
            for (j = (int)yVals.size() - 1; j > 0; j--) {
                int x1 = xVals[i], x2 = xVals[i + 1];
                int y1 = yVals[j - 1], y2 = yVals[j];
                bool valid = activePoint(polygon, x1, y1);
                valid = valid && activePoint(polygon, x1, y2);
                valid = valid && activePoint(polygon, x2, y1);
                valid = valid && activePoint(polygon, x2, y2);
                if (valid)
                    answer.push_back({x1, y1, x2, y2});
            }
        }
        if (!firstCase)
            cout << '\n';
        firstCase = false;
        for (const Rect& rect : answer) {
            cout << rect.x1 << ' ' << rect.y2 << '\n';
            cout << rect.x1 << ' ' << rect.y1 << '\n';
            cout << rect.x2 << ' ' << rect.y1 << '\n';
            cout << rect.x2 << ' ' << rect.y2 << '\n';
        }
    }
    return 0;
}
