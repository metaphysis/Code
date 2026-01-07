// 3D Triangles
// UVa ID: 11275
// Verdict: Accepted
// Submission Date: 2026-01-03
// UVa Run Time: 0.040s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Point3 operator+(const Point3& p) const { return Point3(x + p.x, y + p.y, z + p.z); }
    Point3 operator-(const Point3& p) const { return Point3(x - p.x, y - p.y, z - p.z); }
    Point3 operator*(double t) const { return Point3(x * t, y * t, z * t); }
    double dot(const Point3& p) const { return x * p.x + y * p.y + z * p.z; }
    Point3 cross(const Point3& p) const { return Point3(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x); }
};

// 判断点P是否在三角形P0,P1,P2内（含边界）
bool pointInTriangle(const Point3& P, const Point3& P0, const Point3& P1, const Point3& P2) {
    // 如果点P与三角形的每个顶点都在另外两个顶点组成的边的同一侧，则P在三角形内
    // 判断P和P0是否在边P1-P2的同一侧
    Point3 normal1 = (P2 - P1).cross(P - P1), normal2 = (P2 - P1).cross(P0 - P1);
    if (normal1.dot(normal2) < EPS) return false;
    // 判断P和P1是否在边P0-P2的同一侧
    normal1 = (P2 - P0).cross(P - P0), normal2 = (P2 - P0).cross(P1 - P0);
    if (normal1.dot(normal2) < EPS) return false;
    // 判断P和P2是否在边P0-P1的同一侧
    normal1 = (P1 - P0).cross(P - P0), normal2 = (P1 - P0).cross(P2 - P0);
    if (normal1.dot(normal2) < EPS) return false;
    return true;
}

// 判断三角形(P0,P1,P2)与线段(A,B)是否相交，返回交点P
bool triSegIntersection(const Point3& P0, const Point3& P1, const Point3& P2,
                       const Point3& A, const Point3& B, Point3& P) {
    // 计算三角形法向量
    Point3 n = (P1 - P0).cross(P2 - P0);
    // 如果线段与平面平行（点积接近0）
    double denom = n.dot(B - A);
    if (fabs(denom) <= EPS) return false; // 平行，无交点
    // 计算参数t
    double t = n.dot(P0 - A) / denom;
    // 检查交点是否在线段上
    if (t + EPS < 0 || t - 1 - EPS > 0) return false;
    // 计算交点
    P = A + (B - A) * t;
    // 检查交点是否在三角形内
    return pointInTriangle(P, P0, P1, P2);
}

// 判断两个三角形是否相交
bool triTriIntersection(Point3* T1, Point3* T2) {
    Point3 P;
    // 检查三角形T2的每条边是否与三角形T1相交
    for (int i = 0; i < 3; i++)
        if (triSegIntersection(T1[0], T1[1], T1[2], T2[i], T2[(i + 1) % 3], P))
            return true;
    // 检查三角形T1的每条边是否与三角形T2相交
    for (int i = 0; i < 3; i++)
        if (triSegIntersection(T2[0], T2[1], T2[2], T1[i], T1[(i + 1) % 3], P))
            return true;
    return false;
}

int main() {
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        Point3 tri1[3], tri2[3];
        for (int i = 0; i < 3; i++) cin >> tri1[i].x >> tri1[i].y >> tri1[i].z;
        for (int i = 0; i < 3; i++) cin >> tri2[i].x >> tri2[i].y >> tri2[i].z;
        cout << (triTriIntersection(tri1, tri2) ? 1 : 0) << '\n';
    }
    return 0;
}
