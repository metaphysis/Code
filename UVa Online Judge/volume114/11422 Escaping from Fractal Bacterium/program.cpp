// Escaping from Fractal Bacterium
// UVa ID: 11422
// Verdict: Accepted
// Submission Date: 2026-07-17
// UVa Run Time: 0.020s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
};

inline double cross(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

inline double dot(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.x - A.x) + (B.y - A.y) * (C.y - A.y);
}

bool pointInTriangle(const Point& P, const Point& A, const Point& B, const Point& C) {
    double d1 = cross(A, B, P);
    double d2 = cross(B, C, P);
    double d3 = cross(C, A, P);
    bool hasPos = (d1 > EPS) || (d2 > EPS) || (d3 > EPS);
    bool hasNeg = (d1 < -EPS) || (d2 < -EPS) || (d3 < -EPS);
    return !(hasPos && hasNeg);
}

bool inEar(const Point& P, const Point& A, const Point& B, const Point& C, int depth) {
    if (depth <= 0) return false;
    double crAB_C = cross(A, B, C);
    double crAB_P = cross(A, B, P);
    if (crAB_C * crAB_P > EPS) return false;
    Point A1, B1;
    A1.x = (2.0 * A.x + B.x) / 3.0;
    A1.y = (2.0 * A.y + B.y) / 3.0;
    B1.x = (A.x + 2.0 * B.x) / 3.0;
    B1.y = (A.y + 2.0 * B.y) / 3.0;
    double dx = B.x - A.x, dy = B.y - A.y;
    double len = hypot(dx, dy);
    double ux = dx / len, uy = dy / len;
    double nx = -uy, ny = ux;
    double sign = (crAB_C > 0) ? 1.0 : -1.0;
    nx = -sign * nx;
    ny = -sign * ny;
    Point M;
    M.x = (A1.x + B1.x) / 2.0;
    M.y = (A1.y + B1.y) / 2.0;
    double h = len * sqrt(3.0) / 6.0;
    Point D;
    D.x = M.x + nx * h;
    D.y = M.y + ny * h;
    if (pointInTriangle(P, A1, B1, D)) return true;
    if (depth == 1) return false;
    double t = dot(A, B, P) / (len * len);
    if (t < 1.0/3.0 - EPS) {
        return inEar(P, A, A1, C, depth - 1);
    } else if (t > 2.0/3.0 + EPS) {
        return inEar(P, B1, B, C, depth - 1);
    } else {
        if (cross(A1, D, B1) * cross(A1, D, P) < -EPS) return inEar(P, A1, D, B1, depth - 1);
        if (cross(D, B1, A1) * cross(D, B1, P) < -EPS) return inEar(P, D, B1, A1, depth - 1);
        return false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while (N--) {
        Point A, B, C, P;
        cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> P.x >> P.y;
        if (pointInTriangle(P, A, B, C)) {
            cout << "The bacterium destroys you within day 1. ESCAPE!!\n";
            continue;
        }
        int ans = -1;
        for (int d = 2; d <= 14; ++d) {
            int depth = d - 1;
            if (inEar(P, A, B, C, depth) ||
                inEar(P, B, C, A, depth) ||
                inEar(P, C, A, B, depth)) {
                ans = d;
                break;
            }
        }
        if (ans == -1) cout << "You are safe :)\n";
        else cout << "The bacterium destroys you within day " << ans << ". ESCAPE!!\n";
    }
    return 0;
}
