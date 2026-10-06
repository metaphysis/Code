// Easy Geometry
// UVa ID: 1679
// Verdict: Wrong Answer
// Submission Date: 2026-10-06
// UVa Run Time: 0.570s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const int Iteration = 100;

struct Point {
    long double x, y;
    Point(long double xValue = 0, long double yValue = 0) {
        x = xValue;
        y = yValue;
    }
};

long double minX, maxX, bestArea;
Point bestLeft, bestRight;

long double getSignedArea(const vector<Point> &polygon) {
    long double area = 0;
    int n = polygon.size();
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        area += polygon[i].x * polygon[next].y - polygon[i].y * polygon[next].x;
    }
    return area / 2;
}

void buildChains(const vector<Point> &polygon, vector<Point> &upper, vector<Point> &lower) {
    int n = polygon.size();
    int leftTop = 0, leftBottom = 0, rightTop = 0, rightBottom = 0;
    for (int i = 1; i < n; i++) {
        if (polygon[i].x < polygon[leftTop].x || polygon[i].x == polygon[leftTop].x && polygon[i].y > polygon[leftTop].y)
            leftTop = i;
        if (polygon[i].x < polygon[leftBottom].x || polygon[i].x == polygon[leftBottom].x && polygon[i].y < polygon[leftBottom].y)
            leftBottom = i;
        if (polygon[i].x > polygon[rightTop].x || polygon[i].x == polygon[rightTop].x && polygon[i].y > polygon[rightTop].y)
            rightTop = i;
        if (polygon[i].x > polygon[rightBottom].x || polygon[i].x == polygon[rightBottom].x && polygon[i].y < polygon[rightBottom].y)
            rightBottom = i;
    }
    int current = leftTop;
    while (true) {
        upper.push_back(polygon[current]);
        if (current == rightTop)
            break;
        current = (current - 1 + n) % n;
    }
    current = rightBottom;
    while (true) {
        lower.push_back(polygon[current]);
        if (current == leftBottom)
            break;
        current = (current - 1 + n) % n;
    }
    reverse(lower.begin(), lower.end());
}

long double getY(const vector<Point> &chain, long double x) {
    if (x <= chain.front().x)
        return chain.front().y;
    if (x >= chain.back().x)
        return chain.back().y;
    int left = 0, right = chain.size() - 1;
    while (right - left > 1) {
        int middle = (left + right) / 2;
        if (chain[middle].x <= x)
            left = middle;
        else
            right = middle;
    }
    long double ratio = (x - chain[left].x) / (chain[right].x - chain[left].x);
    return chain[left].y + (chain[right].y - chain[left].y) * ratio;
}

long double updateArea(const vector<Point> &upper, const vector<Point> &lower, long double xLeft, long double xRight) {
    long double upperLeft = getY(upper, xLeft), upperRight = getY(upper, xRight);
    long double lowerLeft = getY(lower, xLeft), lowerRight = getY(lower, xRight);
    long double bottom = max(lowerLeft, lowerRight), top = min(upperLeft, upperRight);
    long double height = top - bottom;
    if (height <= 0)
        return 0;
    long double area = (xRight - xLeft) * height;
    if (area > bestArea) {
        bestArea = area;
        bestLeft = Point(xLeft, bottom);
        bestRight = Point(xRight, top);
    }
    return area;
}

long double searchRight(const vector<Point> &upper, const vector<Point> &lower, long double xLeft) {
    long double left = xLeft, right = maxX, best = 0;
    for (int i = 0; i < Iteration; i++) {
        long double middle = (left + right) / 2, nextMiddle = (middle + right) / 2;
        long double area1 = updateArea(upper, lower, xLeft, middle);
        long double area2 = updateArea(upper, lower, xLeft, nextMiddle);
        best = max(best, max(area1, area2));
        if (area1 < area2)
            left = middle;
        else
            right = nextMiddle;
    }
    best = max(best, updateArea(upper, lower, xLeft, (left + right) / 2));
    return best;
}

void searchLeft(const vector<Point> &upper, const vector<Point> &lower) {
    long double left = minX, right = maxX;
    for (int i = 0; i < Iteration; i++) {
        long double middle = (left + right) / 2, nextMiddle = (middle + right) / 2;
        long double area1 = searchRight(upper, lower, middle);
        long double area2 = searchRight(upper, lower, nextMiddle);
        if (area1 < area2)
            left = middle;
        else
            right = nextMiddle;
    }
    searchRight(upper, lower, (left + right) / 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n) {
        vector<Point> polygon(n);
        for (int i = 0; i < n; i++)
            cin >> polygon[i].x >> polygon[i].y;
        if (getSignedArea(polygon) < 0)
            reverse(polygon.begin(), polygon.end());
        minX = polygon[0].x;
        maxX = polygon[0].x;
        for (int i = 1; i < n; i++) {
            minX = min(minX, polygon[i].x);
            maxX = max(maxX, polygon[i].x);
        }
        vector<Point> upper, lower;
        buildChains(polygon, upper, lower);
        bestArea = -1;
        bestLeft = Point();
        bestRight = Point();
        searchLeft(upper, lower);
        cout << fixed << setprecision(10);
        cout << bestLeft.x << ' ' << bestLeft.y << ' ' << bestRight.x << ' ' << bestRight.y << '\n';
    }
    return 0;
}
