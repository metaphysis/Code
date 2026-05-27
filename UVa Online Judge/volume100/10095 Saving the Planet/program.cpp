// Saving the Planet
// UVa ID: 10095
// Verdict: Accepted
// Submission Date: 2026-05-28
// UVa Run Time: 0.090s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-8;

struct Point {
    double x, y, z;
    Point() : x(0), y(0), z(0) {}
    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
};

double dist2(const Point& a, const Point& b) {
    double dx = a.x - b.x, dy = a.y - b.y, dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

double dist(const Point& a, const Point& b) {
    return sqrt(dist2(a, b));
}

struct Sphere {
    Point c;
    double r;
    Sphere() : c(Point()), r(-1) {}
    Sphere(const Point& c_, double r_) : c(c_), r(r_) {}
    
    bool contains(const Point& p) const {
        return dist2(p, c) <= r * r + EPS;
    }
};

// 由边界点构造最小球
Sphere sphereFromBoundary(Point* boundary, int m) {
    if (m == 0) return Sphere(Point(0, 0, 0), -1);
    if (m == 1) return Sphere(boundary[0], 0);
    if (m == 2) {
        Point c((boundary[0].x + boundary[1].x) / 2,
                (boundary[0].y + boundary[1].y) / 2,
                (boundary[0].z + boundary[1].z) / 2);
        return Sphere(c, dist(boundary[0], boundary[1]) / 2);
    }
    if (m == 3) {
        // 三点外接圆
        double ax = boundary[1].x - boundary[0].x;
        double ay = boundary[1].y - boundary[0].y;
        double az = boundary[1].z - boundary[0].z;
        double bx = boundary[2].x - boundary[0].x;
        double by = boundary[2].y - boundary[0].y;
        double bz = boundary[2].z - boundary[0].z;
        
        double d1 = ax * ax + ay * ay + az * az;
        double d2 = bx * bx + by * by + bz * bz;
        double d3 = ax * bx + ay * by + az * bz;
        double denom = d1 * d2 - d3 * d3;
        
        if (fabs(denom) < EPS) {
            // 共线，取最远两点
            double d12 = dist2(boundary[0], boundary[1]);
            double d13 = dist2(boundary[0], boundary[2]);
            double d23 = dist2(boundary[1], boundary[2]);
            if (d12 >= d13 && d12 >= d23) {
                Point c((boundary[0].x + boundary[1].x) / 2,
                        (boundary[0].y + boundary[1].y) / 2,
                        (boundary[0].z + boundary[1].z) / 2);
                return Sphere(c, sqrt(d12) / 2);
            }
            if (d13 >= d12 && d13 >= d23) {
                Point c((boundary[0].x + boundary[2].x) / 2,
                        (boundary[0].y + boundary[2].y) / 2,
                        (boundary[0].z + boundary[2].z) / 2);
                return Sphere(c, sqrt(d13) / 2);
            }
            Point c((boundary[1].x + boundary[2].x) / 2,
                    (boundary[1].y + boundary[2].y) / 2,
                    (boundary[1].z + boundary[2].z) / 2);
            return Sphere(c, sqrt(d23) / 2);
        }
        
        double u = (d2 * d1 - d3 * d2) / (2 * denom);
        double v = (d1 * d2 - d3 * d1) / (2 * denom);
        Point c(boundary[0].x + u * ax + v * bx,
                boundary[0].y + u * ay + v * by,
                boundary[0].z + u * az + v * bz);
        return Sphere(c, dist(c, boundary[0]));
    }
    // m == 4: 四点外接球
    double a11 = boundary[1].x - boundary[0].x;
    double a12 = boundary[1].y - boundary[0].y;
    double a13 = boundary[1].z - boundary[0].z;
    double a21 = boundary[2].x - boundary[0].x;
    double a22 = boundary[2].y - boundary[0].y;
    double a23 = boundary[2].z - boundary[0].z;
    double a31 = boundary[3].x - boundary[0].x;
    double a32 = boundary[3].y - boundary[0].y;
    double a33 = boundary[3].z - boundary[0].z;
    
    double b1 = (boundary[1].x * boundary[1].x + boundary[1].y * boundary[1].y + boundary[1].z * boundary[1].z -
                 boundary[0].x * boundary[0].x - boundary[0].y * boundary[0].y - boundary[0].z * boundary[0].z) / 2;
    double b2 = (boundary[2].x * boundary[2].x + boundary[2].y * boundary[2].y + boundary[2].z * boundary[2].z -
                 boundary[0].x * boundary[0].x - boundary[0].y * boundary[0].y - boundary[0].z * boundary[0].z) / 2;
    double b3 = (boundary[3].x * boundary[3].x + boundary[3].y * boundary[3].y + boundary[3].z * boundary[3].z -
                 boundary[0].x * boundary[0].x - boundary[0].y * boundary[0].y - boundary[0].z * boundary[0].z) / 2;
    
    double det = a11 * (a22 * a33 - a23 * a32) - a12 * (a21 * a33 - a23 * a31) + a13 * (a21 * a32 - a22 * a31);
    
    if (fabs(det) < EPS) {
        // 退化，用三点球
        return sphereFromBoundary(boundary, 3);
    }
    
    double x0 = (b1 * (a22 * a33 - a23 * a32) - a12 * (b2 * a33 - a23 * b3) + a13 * (b2 * a32 - a22 * b3)) / det;
    double y0 = (a11 * (b2 * a33 - a23 * b3) - b1 * (a21 * a33 - a23 * a31) + a13 * (a21 * b3 - b2 * a31)) / det;
    double z0 = (a11 * (a22 * b3 - b2 * a32) - a12 * (a21 * b3 - b2 * a31) + b1 * (a21 * a32 - a22 * a31)) / det;
    
    Point c(boundary[0].x + x0, boundary[0].y + y0, boundary[0].z + z0);
    return Sphere(c, dist(c, boundary[0]));
}

// Welzl 算法 - 非递归实现
Sphere welzl(vector<Point>& pts) {
    int n = pts.size();
    if (n == 0) return Sphere(Point(0, 0, 0), 0);
    if (n == 1) return Sphere(pts[0], 0);
    
    // 随机打乱
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(pts[i], pts[j]);
    }
    
    Sphere s = sphereFromBoundary(&pts[0], 1);
    s.c = pts[0];
    s.r = 0;
    
    Point boundary[4];
    int bcnt = 1;
    boundary[0] = pts[0];
    
    for (int i = 1; i < n; ++i) {
        if (s.contains(pts[i])) continue;
        
        // 当前点在球外，需要重新计算
        bcnt = 1;
        boundary[0] = pts[i];
        s = sphereFromBoundary(boundary, 1);
        
        for (int j = 0; j < i; ++j) {
            if (s.contains(pts[j])) continue;
            
            bcnt = 2;
            boundary[1] = pts[j];
            s = sphereFromBoundary(boundary, 2);
            
            for (int k = 0; k < j; ++k) {
                if (s.contains(pts[k])) continue;
                
                bcnt = 3;
                boundary[2] = pts[k];
                s = sphereFromBoundary(boundary, 3);
                
                for (int l = 0; l < k; ++l) {
                    if (s.contains(pts[l])) continue;
                    
                    bcnt = 4;
                    boundary[3] = pts[l];
                    s = sphereFromBoundary(boundary, 4);
                }
            }
        }
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(4);
    srand(time(nullptr));
    
    int n;
    while (cin >> n && n) {
        vector<Point> pts(n);
        for (int i = 0; i < n; ++i)
            cin >> pts[i].x >> pts[i].y >> pts[i].z;
        
        Sphere s = welzl(pts);
        cout << s.r << " " << s.c.x << " " << s.c.y << " " << s.c.z << "\n";
    }
    return 0;
}
