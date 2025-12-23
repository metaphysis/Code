// The Deadly Olympic Returns
// UVa ID: 10794
// Verdict: Accepted
// Submission Date: 2025-12-17
// UVa Run Time: 0.000s
//
// 版权所有（C）2025，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>
using namespace std;

// 三维点/向量结构体
struct Point3D {
    double x, y, z;
    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    
    // 从输入读取坐标
    void read() { cin >> x >> y >> z; }
    
    // 向量加法
    Point3D operator+(const Point3D& other) const {
        return Point3D(x + other.x, y + other.y, z + other.z);
    }
    
    // 向量减法
    Point3D operator-(const Point3D& other) const {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }
    
    // 向量数乘
    Point3D operator*(double scalar) const {
        return Point3D(x * scalar, y * scalar, z * scalar);
    }
    
    // 向量数除
    Point3D operator/(double scalar) const {
        return Point3D(x / scalar, y / scalar, z / scalar);
    }
};

// 计算向量的点积
double dotProduct(const Point3D& a, const Point3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 计算向量的叉积
Point3D crossProduct(const Point3D& a, const Point3D& b) {
    return Point3D(
        a.y * b.z - a.z * b.y,   // x分量
        a.z * b.x - a.x * b.z,   // y分量
        a.x * b.y - a.y * b.x    // z分量
    );
}

// 计算向量长度的平方
double lengthSquared(const Point3D& v) {
    return dotProduct(v, v);
}

// 计算向量长度
double length(const Point3D& v) {
    return sqrt(lengthSquared(v));
}

// 计算点p到通过点a方向为dir的直线的距离
double pointToLineDistance(const Point3D& p, const Point3D& a, const Point3D& dir) {
    // 如果方向向量长度为0，退化为点到点的距离
    if (lengthSquared(dir) < 1e-12) {
        return length(p - a);
    }
    
    // 向量ap = p - a
    Point3D ap = p - a;
    
    // 计算投影长度比例 t = (ap·dir) / (dir·dir)
    // 但这里我们不需要计算t，直接使用距离公式
    // 距离² = |ap|² - (ap·dir)²/|dir|²
    double distSquared = lengthSquared(ap) - pow(dotProduct(ap, dir), 2) / lengthSquared(dir);
    
    // 防止由于浮点误差导致的负数
    return sqrt(max(0.0, distSquared));
}

int main() {
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    // 设置输出精度：保留4位小数
    cout << fixed << setprecision(4);
    
    for (int caseNo = 1; caseNo <= t; caseNo++) {
        double time;
        cin >> time;
        
        // 读取两枚导弹的起点和终点
        Point3D p1Start, p1End, p2Start, p2End;
        p1Start.read(); p1End.read();
        p2Start.read(); p2End.read();
        
        // 计算速度向量 = (终点 - 起点) / 时间
        Point3D v1 = (p1End - p1Start) / time;
        Point3D v2 = (p2End - p2Start) / time;
        
        // 相对运动：让第一枚导弹静止
        // 相对速度 = v2 - v1
        // 初始相对位置 = p2Start - p1Start
        Point3D relativeVelocity = v2 - v1;
        Point3D relativeStart = p2Start - p1Start;
        
        // 现在问题转化为：求原点(0,0,0)到直线的距离
        // 直线方程：L(t) = relativeStart + relativeVelocity * t
        double minDistance = pointToLineDistance(
            Point3D(0, 0, 0),  // 原点（第一枚导弹位置）
            relativeStart,      // 直线的起点
            relativeVelocity    // 直线的方向
        );
        
        // 输出结果
        cout << "Case " << caseNo << ": " << minDistance << endl;
    }
    
    return 0;
}
