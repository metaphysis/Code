// Intersection is Not that Easy
// UVa ID: 10709
// Verdict: Accepted
// Submission Date: 2025-11-
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

const double EPS = 1e-8;
const double INF = 1e20;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

Point operator - (Point A, Point B) { return Point(A.x - B.x, A.y - B.y); }
double operator ^ (Point A, Point B) { return A.x * B.y - A.y * B.x; }
double operator * (Point A, Point B) { return A.x * B.x + A.y * B.y; }

bool onSegment(Point p, Point a, Point b) {
    return fabs((a - p) ^ (b - p)) < EPS && (a - p) * (b - p) < EPS;
}

double pointToSegment(Point p, Point a, Point b) {
    if (a.x == b.x && a.y == b.y) return sqrt((p.x - a.x) * (p.x - a.x) + (p.y - a.y) * (p.y - a.y));
    
    Point v1 = b - a, v2 = p - a, v3 = p - b;
    
    if (v1 * v2 < 0) return sqrt(v2.x * v2.x + v2.y * v2.y);
    if (v1 * v3 > 0) return sqrt(v3.x * v3.x + v3.y * v3.y);
    
    return fabs(v1 ^ v2) / sqrt(v1.x * v1.x + v1.y * v1.y);
}

bool segmentsIntersect(Point a1, Point a2, Point b1, Point b2) {
    double c1 = (a2 - a1) ^ (b1 - a1);
    double c2 = (a2 - a1) ^ (b2 - a1);
    double c3 = (b2 - b1) ^ (a1 - b1);
    double c4 = (b2 - b1) ^ (a2 - b1);
    
    if (c1 * c2 < -EPS && c3 * c4 < -EPS) return true;
    
    if (fabs(c1) < EPS && onSegment(b1, a1, a2)) return true;
    if (fabs(c2) < EPS && onSegment(b2, a1, a2)) return true;
    if (fabs(c3) < EPS && onSegment(a1, b1, b2)) return true;
    if (fabs(c4) < EPS && onSegment(a2, b1, b2)) return true;
    
    return false;
}

double pointToLine(Point p, Point a, Point b) {
    Point v1 = b - a, v2 = p - a;
    return fabs(v1 ^ v2) / sqrt(v1.x * v1.x + v1.y * v1.y);
}

bool linesParallel(Point a1, Point a2, Point b1, Point b2) {
    Point v1 = a2 - a1, v2 = b2 - b1;
    return fabs(v1 ^ v2) < EPS;
}

double segmentToSegment(Point a1, Point a2, Point b1, Point b2) {
    if (segmentsIntersect(a1, a2, b1, b2)) return 0.0;
    
    double dist = INF;
    dist = min(dist, pointToSegment(a1, b1, b2));
    dist = min(dist, pointToSegment(a2, b1, b2));
    dist = min(dist, pointToSegment(b1, a1, a2));
    dist = min(dist, pointToSegment(b2, a1, a2));
    
    return dist;
}

double lineToSegment(Point a1, Point a2, Point b1, Point b2) {
    Point v = a2 - a1;
    double c1 = v ^ (b1 - a1);
    double c2 = v ^ (b2 - a1);
    
    if (c1 * c2 < -EPS || fabs(c1) < EPS || fabs(c2) < EPS) {
        return 0.0;
    }
    
    return min(pointToLine(b1, a1, a2), pointToLine(b2, a1, a2));
}

double lineToLine(Point a1, Point a2, Point b1, Point b2) {
    if (!linesParallel(a1, a2, b1, b2)) {
        return 0.0;
    }
    
    return pointToLine(a1, b1, b2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cout << fixed << setprecision(5);
    
    int x1, y1, x2, y2, x3, y3, x4, y4;
    string s1, s2;
    
    while (cin >> x1 >> y1 >> x2 >> y2 >> s1) {
        if (s1 == "END") break;
        
        cin >> x3 >> y3 >> x4 >> y4 >> s2;
        if (s2 == "END") break;
        
        Point a1(x1, y1), a2(x2, y2);
        Point b1(x3, y3), b2(x4, y4);
        
        double result = 0.0;
        
        if (s1 == "L" && s2 == "L") {
            result = lineToLine(a1, a2, b1, b2);
        } else if (s1 == "L" && s2 == "LS") {
            result = lineToSegment(a1, a2, b1, b2);
        } else if (s1 == "LS" && s2 == "L") {
            result = lineToSegment(b1, b2, a1, a2);
        } else {
            result = segmentToSegment(a1, a2, b1, b2);
        }
        
        cout << result << endl;
    }
    
    return 0;
}
