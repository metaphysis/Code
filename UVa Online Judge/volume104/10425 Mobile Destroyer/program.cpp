// Mobile Destroyer
// UVa ID: 10425
// Verdict: Accepted
// Submission Date: 2025-11-11
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

struct Point3D {
    int x, y, z;
    Point3D(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
};

struct Sphere {
    Point3D center;
    int radius;
    Sphere(int x = 0, int y = 0, int z = 0, int r = 0) : center(x, y, z), radius(r) {}
};

// 计算两点距离平方
int squaredDistance(const Point3D& a, const Point3D& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    int dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

// 判断点是否在球内（包括边界）
bool isInsideSphere(const Point3D& p, const Sphere& s) {
    return squaredDistance(p, s.center) <= s.radius * s.radius;
}

int main() {
    string caseName;
    while (cin >> caseName) {
        int x1, y1, z1, r1, x2, y2, z2, r2, xp, yp, zp;
        cin >> x1 >> y1 >> z1 >> r1 >> x2 >> y2 >> z2 >> r2 >> xp >> yp >> zp;

        Sphere s1(x1, y1, z1, r1);
        Sphere s2(x2, y2, z2, r2);
        Point3D phone(xp, yp, zp);

        bool inSphere1 = isInsideSphere(phone, s1);
        bool inSphere2 = isInsideSphere(phone, s2);

        // 计算公共切平面方程的值
        int planeValue = 2 * (x2 - x1) * xp +
                         2 * (y2 - y1) * yp +
                         2 * (z2 - z1) * zp +
                         (x1*x1 + y1*y1 + z1*z1 - r1*r1 -
                          x2*x2 - y2*y2 - z2*z2 + r2*r2);

        bool onPlane = (planeValue == 0); // 整数运算，直接判断是否为0

        bool destroyed = (inSphere1 || inSphere2) && !onPlane;

        // 输出
        cout << caseName << endl;
        cout << (inSphere1 ? "y" : "n") << endl;
        cout << (inSphere2 ? "y" : "n") << endl;
        cout << (destroyed ? "y" : "n") << endl;
    }

    return 0;
}
