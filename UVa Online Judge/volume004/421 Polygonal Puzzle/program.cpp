// Polygonal Puzzle
// UVa ID: 421
// Verdict: Accepted
// Submission Date: 2026-06-13
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0), EPS = 1e-6;

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }
    double length() const { return sqrt(x * x + y * y); }
};

vector<int> getEdgeRatio(const vector<Point>& pts) {
    int m = pts.size();
    vector<double> edges(m);
    double minEdge = 1e9;
    for (int j = 0; j < m; ++j) {
        int nxt = (j + 1) % m;
        edges[j] = (pts[j] - pts[nxt]).length();
        if (edges[j] < minEdge) minEdge = edges[j];
    }
    vector<int> raw(m);
    for (int j = 0; j < m; ++j) raw[j] = (int)round(edges[j] / minEdge);
    int g = raw[0];
    for (size_t i = 1; i < raw.size(); i++) g = __gcd(g, raw[i]);
    for (size_t i = 0; i < raw.size(); i++) raw[i] /= g;
    return raw;
}

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> refEdgeRatio(n);
    vector<vector<Point>> refPts(n, vector<Point>(m));
    for (int i = 0; i < n; ++i) {
        vector<Point> pts(m);
        for (int j = 0; j < m; ++j) {
            double r;
            cin >> r;
            double angle = (90.0 - j * 360.0 / m) * PI / 180.0;
            refPts[i][j] = Point(r * cos(angle), r * sin(angle));
        }
        refEdgeRatio[i] = getEdgeRatio(refPts[i]);
    }
    
    for (int i = 0; i < n; ++i) {
        vector<Point> pts(m);
        for (int j = 0; j < m; ++j) cin >> pts[j].x >> pts[j].y;
        vector<int> obsRatio = getEdgeRatio(pts);
        int bestRef = -1, bestShift = -1;
        for (int refIdx = 0; refIdx < n; ++refIdx) {
            for (int shift = 0; shift < m; ++shift) {
                bool ok = true;
                for (int j = 0; j < m; ++j) {
                    int rp = (j + shift) % m;
                    if (obsRatio[j] != refEdgeRatio[refIdx][rp]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    bestRef = refIdx;
                    bestShift = shift;
                    break;
                }
            }
            if (bestRef != -1) break;
        }
        
        int obsIdx = 0, refIdx = bestShift % m;
        int obsNext = 1 % m, refNext = (refIdx + 1) % m;
        Point obsEdge = pts[obsNext] - pts[obsIdx];
        Point refEdge = refPts[bestRef][refNext] - refPts[bestRef][refIdx];
        double angObs = atan2(obsEdge.y, obsEdge.x);
        double angRef = atan2(refEdge.y, refEdge.x);
        double theta = angObs - angRef;
        while (theta > PI) theta -= 2 * PI;
        while (theta < -PI) theta += 2 * PI;
        double angleDeg = fmod(theta * 180.0 / PI, 360.0);
        if (angleDeg < 0) angleDeg += 360;
        if (fabs(angleDeg - 360.0) < EPS) angleDeg = 0.0;
        printf("%d %.1f\n", bestRef + 1, angleDeg);
    }
    
    return 0;
}
