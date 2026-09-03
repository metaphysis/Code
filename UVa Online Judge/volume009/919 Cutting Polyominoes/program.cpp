#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    bool operator < (const Point &other) const {
        if (x != other.x)
            return x < other.x;
        return y < other.y;
    }
    bool operator == (const Point &other) const {
        return x == other.x && y == other.y;
    }
};

using Cell = pair<int, int>;

long long crossProduct(const Point &a, const Point &b, const Point &c) {
    return 1LL * (b.x - a.x) * (c.y - a.y) - 1LL * (b.y - a.y) * (c.x - a.x);
}

bool isOnSegment(const Point &a, const Point &b, const Point &p) {
    if (crossProduct(a, b, p) != 0)
        return false;
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

vector<Point> getVertices(const set<Cell> &cells) {
    map<Point, Point> nextPoint;
    for (const Cell &cell : cells) {
        int x = cell.first, y = cell.second;
        if (!cells.count({x, y - 1}))
            nextPoint[{x, y}] = {x + 1, y};
        if (!cells.count({x + 1, y}))
            nextPoint[{x + 1, y}] = {x + 1, y + 1};
        if (!cells.count({x, y + 1}))
            nextPoint[{x + 1, y + 1}] = {x, y + 1};
        if (!cells.count({x - 1, y}))
            nextPoint[{x, y + 1}] = {x, y};
    }
    vector<Point> rawPoints, vertices;
    if (nextPoint.empty())
        return vertices;
    Point start = nextPoint.begin()->first, current = start;
    do {
        rawPoints.push_back(current);
        current = nextPoint[current];
    } while (!(current == start));
    int size = rawPoints.size();
    for (int i = 0; i < size; i++) {
        Point prev = rawPoints[(i - 1 + size) % size], now = rawPoints[i], next = rawPoints[(i + 1) % size];
        if (crossProduct(prev, now, next) != 0)
            vertices.push_back(now);
    }
    return vertices;
}

set<Cell> inflateCells(const set<Cell> &cells, int p, int q) {
    set<Cell> result;
    for (const Cell &cell : cells) {
        int x = cell.first, y = cell.second;
        int left = x + (x > p), right = x + 1 + (x + 1 > p);
        int top = y + (y > q), bottom = y + 1 + (y + 1 > q);
        for (int nx = left; nx < right; nx++)
            for (int ny = top; ny < bottom; ny++)
                result.insert({nx, ny});
    }
    return result;
}

bool isInRectangle(const Point &point, int left, int right, int top, int bottom) {
    return left <= point.x && point.x <= right && top <= point.y && point.y <= bottom;
}

bool checkCut(const set<Cell> &cells, const vector<Point> &vertices, int p, int q, int x, int y) {
    int x1 = p + 1, y1 = q + 1;
    int left = min(x1, x), right = max(x1, x), top = min(y1, y), bottom = max(y1, y);
    if (left == right || top == bottom)
        return false;
    for (int cx = left; cx < right; cx++)
        for (int cy = top; cy < bottom; cy++)
            if (!cells.count({cx, cy}))
                return false;
    Point target = {x, y};
    int targetIndex = -1, size = vertices.size();
    for (int i = 0; i < size; i++)
        if (vertices[i] == target) {
            targetIndex = i;
            break;
        }
    if (targetIndex == -1)
        return false;
    for (int i = 0; i < size; i++)
        if (i != targetIndex && isInRectangle(vertices[i], left, right, top, bottom))
            return false;
    Point pointA = {x, q + 1}, pointB = {p + 1, y};
    Point prev = vertices[(targetIndex - 1 + size) % size], next = vertices[(targetIndex + 1) % size];
    bool hasA = isOnSegment(prev, target, pointA) || isOnSegment(target, next, pointA);
    bool hasB = isOnSegment(prev, target, pointB) || isOnSegment(target, next, pointB);
    return hasA || hasB;
}

void cutCells(set<Cell> &cells, int p, int q, int x, int y) {
    int x1 = p + 1, y1 = q + 1;
    int left = min(x1, x), right = max(x1, x), top = min(y1, y), bottom = max(y1, y);
    for (int cx = left; cx < right; cx++)
        for (int cy = top; cy < bottom; cy++)
            cells.erase({cx, cy});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int r;
    while (cin >> r && r) {
        set<Cell> cells;
        cells.insert({0, 0});
        bool valid = true;
        for (int i = 0; i < r; i++) {
            int p, q, x, y;
            cin >> p >> q >> x >> y;
            if (!valid)
                continue;
            if (!cells.count({p, q})) {
                valid = false;
                continue;
            }
            cells = inflateCells(cells, p, q);
            vector<Point> vertices = getVertices(cells);
            if (!checkCut(cells, vertices, p, q, x, y)) {
                valid = false;
                continue;
            }
            cutCells(cells, p, q, x, y);
        }
        if (valid)
            cout << cells.size() << '\n';
        else
            cout << 0 << '\n';
    }
    return 0;
}
