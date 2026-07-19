// Stopper Stumper
// UVa ID: 823
// Verdict: Accepted
// Submission Date: 2026-07-12
// UVa Run Time: 0.000s
//
// 版权所有（C）2026，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
    Point operator + (const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator - (const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator * (double s) const { return Point(x * s, y * s); }
    double len() const { return sqrt(x * x + y * y); }
    Point normalize() const { double l = len(); if (l < EPS) return *this; return Point(x / l, y / l); }
};

double dot(const Point& a, const Point& b) { return a.x * b.x + a.y * b.y; }
double cross(const Point& a, const Point& b) { return a.x * b.y - a.y * b.x; }
double dist(const Point& a, const Point& b) { return (a - b).len(); }
double pointToLineDist(const Point& p, const Point& a, const Point& b) {
    return fabs(cross(b - a, p - a)) / (b - a).len();
}

struct Stopper {
    double r; // 小圆半径
    double R; // 大圆半径
};

// 全局三角形数据
Point A, B, C;
double a, b, c; // 边长 a=BC, b=CA, c=AB
Point dir[3];   // 三个顶点的内角平分线单位方向
double sinHalf[3]; // sin(θ/2)
Point vert[3];  // 顶点坐标 A,B,C

// 初始化三角形，计算角平分线和半角正弦
void initTriangle(double sideA, double sideB, double sideC) {
    a = sideA; b = sideB; c = sideC;
    // 顶点坐标: A(0,0), B(c,0)
    A = Point(0, 0);
    B = Point(c, 0);
    double cx = (b * b + c * c - a * a) / (2.0 * c);
    double cy = sqrt(b * b - cx * cx);
    C = Point(cx, cy);
    vert[0] = A; vert[1] = B; vert[2] = C;
    // 各顶点的两条邻边单位向量
    Point ab = (B - A).normalize();
    Point ac = (C - A).normalize();
    Point ba = (A - B).normalize();
    Point bc = (C - B).normalize();
    Point ca = (A - C).normalize();
    Point cb = (B - C).normalize();
    dir[0] = (ab + ac).normalize();
    dir[1] = (ba + bc).normalize();
    dir[2] = (ca + cb).normalize();
    // 计算各角余弦和半角正弦
    double cosA = (b * b + c * c - a * a) / (2.0 * b * c);
    double cosB = (c * c + a * a - b * b) / (2.0 * c * a);
    double cosC = (a * a + b * b - c * c) / (2.0 * a * b);
    sinHalf[0] = sqrt((1.0 - cosA) / 2.0);
    sinHalf[1] = sqrt((1.0 - cosB) / 2.0);
    sinHalf[2] = sqrt((1.0 - cosC) / 2.0);
}

// 计算在顶点 idx (0:A,1:B,2:C) 处，半径为 R 的大圆圆心，并检查是否有效（不超出第三边）
bool getCenter(int idx, double R, Point& center) {
    double t = R / sinHalf[idx];
    center = vert[idx] + dir[idx] * t;
    // 检查圆心到第三边的距离 >= R
    int other1 = (idx + 1) % 3, other2 = (idx + 2) % 3;
    double d = pointToLineDist(center, vert[other1], vert[other2]);
    return d >= R - EPS;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int triangleNo = 0;
    int s1, s2, s3;
    while (cin >> s1 >> s2 >> s3) {
        if (s1 == 0 && s2 == 0 && s3 == 0) break;
        Stopper stoppers[3];
        cin >> stoppers[0].r >> stoppers[0].R;
        cin >> stoppers[1].r >> stoppers[1].R;
        cin >> stoppers[2].r >> stoppers[2].R;
        // 直径转半径
        for (int i = 0; i < 3; ++i) {
            stoppers[i].r /= 2.0;
            stoppers[i].R /= 2.0;
        }
        initTriangle(s1, s2, s3);
        bool possible = false;
        int perm[3] = {0, 1, 2};
        do {
            // 预先检查每个塞子放在对应顶点是否有效，无效则跳过该排列
            bool validPerm = true;
            Point center[3];
            for (int i = 0; i < 3; ++i) {
                int stopperIdx = perm[i];
                double R = stoppers[stopperIdx].R;
                if (!getCenter(i, R, center[i])) {
                    validPerm = false;
                    break;
                }
            }
            if (!validPerm) continue;
            // 枚举方向组合 (0:正放, 1:倒放)
            for (int mask = 0; mask < 8; ++mask) {
                double bottomR[3], topR[3];
                for (int i = 0; i < 3; ++i) {
                    int idx = perm[i];
                    bool upright = ((mask >> i) & 1) == 0; // 0正放,1倒放
                    if (upright) {
                        bottomR[i] = stoppers[idx].R;
                        topR[i] = stoppers[idx].r;
                    } else {
                        bottomR[i] = stoppers[idx].r;
                        topR[i] = stoppers[idx].R;
                    }
                }
                // 检查底部三个圆是否两两不相交
                bool bottomOK = true;
                for (int i = 0; i < 3 && bottomOK; ++i)
                    for (int j = i + 1; j < 3; ++j)
                        if (dist(center[i], center[j]) < bottomR[i] + bottomR[j] - EPS) {
                            bottomOK = false;
                            break;
                        }
                if (!bottomOK) continue;
                // 检查顶部三个圆
                bool topOK = true;
                for (int i = 0; i < 3 && topOK; ++i)
                    for (int j = i + 1; j < 3; ++j)
                        if (dist(center[i], center[j]) < topR[i] + topR[j] - EPS) {
                            topOK = false;
                            break;
                        }
                if (topOK) {
                    possible = true;
                    break;
                }
            }
            if (possible) break;
        } while (next_permutation(perm, perm + 3));
        if (triangleNo++) cout << '\n';
        cout << "Triangle number " << triangleNo << ":\n";
        if (possible) cout << "All three stoppers will fit in the triangular space\n";
        else cout << "Stoppers will not fit in the triangular space\n";
    }
    return 0;
}
