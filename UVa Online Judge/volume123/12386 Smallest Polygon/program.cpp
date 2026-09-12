#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool onSeg(Point a, Point b, Point p) {
    return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) &&
           min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
}

bool isIntersect(Point a, Point b, Point c, Point d) {
    long long c1, c2, c3, c4;
    c1 = cross(a, b, c);
    c2 = cross(a, b, d);
    c3 = cross(c, d, a);
    c4 = cross(c, d, b);
    if (c1 == 0 && onSeg(a, b, c)) return true;
    if (c2 == 0 && onSeg(a, b, d)) return true;
    if (c3 == 0 && onSeg(c, d, a)) return true;
    if (c4 == 0 && onSeg(c, d, b)) return true;
    return (c1 > 0) != (c2 > 0) && (c3 > 0) != (c4 > 0);
}

double getDist(Point a, Point b) {
    long long dx, dy;
    dx = a.x - b.x;
    dy = a.y - b.y;
    return sqrt((double)dx * dx + (double)dy * dy);
}

bool isSimple(vector<Point>& poly) {
    int n, i, j, ni, nj;
    n = poly.size();
    for (i = 0; i < n; i++) {
        ni = (i + 1) % n;
        for (j = i + 1; j < n; j++) {
            nj = (j + 1) % n;
            if (i == j || ni == j || nj == i) continue;
            if (isIntersect(poly[i], poly[ni], poly[j], poly[nj])) return false;
        }
    }
    return true;
}

long long getArea2(vector<Point>& poly) {
    int n, i;
    long long sum;
    n = poly.size();
    sum = 0;
    for (i = 0; i < n; i++)
        sum += poly[i].x * poly[(i + 1) % n].y - poly[i].y * poly[(i + 1) % n].x;
    return llabs(sum);
}

double getPerimeter(vector<Point>& poly) {
    int n, i;
    double sum;
    n = poly.size();
    sum = 0;
    for (i = 0; i < n; i++)
        sum += getDist(poly[i], poly[(i + 1) % n]);
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, i;
    cin >> t;
    while (t--) {
        vector<Point> pts, poly;
        vector<int> ord;
        long long minArea, area;
        double minPer, areaPer, per;
        cin >> n;
        pts.resize(n);
        for (i = 0; i < n; i++)
            cin >> pts[i].x >> pts[i].y;
        ord.resize(n - 1);
        for (i = 0; i < n - 1; i++)
            ord[i] = i + 1;
        minArea = LLONG_MAX;
        minPer = 1e100;
        areaPer = 1e100;
        do {
            poly.clear();
            poly.push_back(pts[0]);
            for (i = 0; i < n - 1; i++)
                poly.push_back(pts[ord[i]]);
            if (!isSimple(poly)) continue;
            area = getArea2(poly);
            per = getPerimeter(poly);
            minPer = min(minPer, per);
            if (area < minArea) {
                minArea = area;
                areaPer = per;
            } else if (area == minArea) {
                areaPer = min(areaPer, per);
            }
        } while (next_permutation(ord.begin(), ord.end()));
        cout << fixed << setprecision(4) << max(0.0, areaPer - minPer) << '\n';
    }
    return 0;
}
