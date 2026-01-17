// Chinese Ink
// UVa ID: 11665
// Verdict: Accepted
// Submission Date: 2026-01-14
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

typedef vector<Point> Polygon;

// 计算叉积 (p1-p0) × (p2-p0)
int cross(const Point& p0, const Point& p1, const Point& p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

// 判断点是否在线段上（包括端点）
bool onSegment(const Point& p, const Point& a, const Point& b) {
    if (min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
        min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y))
        if (cross(p, a, b) == 0) return true;
    return false;
}

// 判断线段 a-b 和 c-d 是否相交（包括端点）
bool segmentsIntersect(const Point& a, const Point& b, const Point& c, const Point& d) {
    int d1 = cross(a, b, c);
    int d2 = cross(a, b, d);
    int d3 = cross(c, d, a);
    int d4 = cross(c, d, b);
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) return true;
    if (d1 == 0 && onSegment(c, a, b)) return true;
    if (d2 == 0 && onSegment(d, a, b)) return true;
    if (d3 == 0 && onSegment(a, c, d)) return true;
    if (d4 == 0 && onSegment(b, c, d)) return true;
    return false;
}

// 射线法判断点是否在多边形内部（包括边界）
bool pointInPolygon(const Point& p, const Polygon& poly) {
    int n = poly.size();
    bool inside = false;
    for (int i = 0; i < n; i++) {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (onSegment(p, a, b)) return true; // 在边上
        if ((a.y > p.y) != (b.y > p.y)) {
            int intersectX = a.x + (p.y - a.y) * (b.x - a.x) / (b.y - a.y);
            if (p.x < intersectX) inside = !inside;
        }
    }
    return inside;
}

// 判断两个多边形是否相交或包含
bool polygonsIntersect(const Polygon& a, const Polygon& b) {
    int na = a.size(), nb = b.size();
    // 边相交检测
    for (int i = 0; i < na; i++)
        for (int j = 0; j < nb; j++)
            if (segmentsIntersect(a[i], a[(i + 1) % na], b[j], b[(j + 1) % nb])) return true;
    // 包含检测：a的顶点在b内，或b的顶点在a内
    for (int i = 0; i < na; i++)
        if (pointInPolygon(a[i], b)) return true;
    for (int i = 0; i < nb; i++)
        if (pointInPolygon(b[i], a)) return true;
    return false;
}

// 并查集
class UnionFind {
public:
    vector<int> parent;
    UnionFind(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) parent[rx] = ry;
    }
    int countComponents() {
        unordered_set<int> comps;
        for (int i = 0; i < parent.size(); i++) comps.insert(find(i));
        return comps.size();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        vector<Polygon> polygons(n);
        for (int i = 0; i < n; i++) {
            int t; vector<int> coords;
            int val;
            while (cin >> val) {
                coords.push_back(val);
                if (cin.peek() == '\n') break;
            }
            t = coords.size() / 2;
            for (int j = 0; j < t; j++) polygons[i].push_back(Point(coords[2 * j], coords[2 * j + 1]));
        }
        UnionFind uf(n);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (polygonsIntersect(polygons[i], polygons[j])) uf.unite(i, j);
        cout << uf.countComponents() << "\n";
    }
    return 0;
}
