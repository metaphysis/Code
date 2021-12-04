#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

struct point3
{
    double x, y, z;
    point3 (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    point3 operator+(const point3 p) { return point3(x + p.x, y + p.y, z + p.z); }
    point3 operator-(const point3 p) { return point3(x - p.x, y - p.y, z - p.z); }
    point3 operator*(double k) { return point3(x * k, y * k, z * k); }
    point3 operator/(double k) { return point3(x / k, y / k, z / k); }
};

bool zero(double x) { return fabs(x) < EPSILON; }

double norm(point3 p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
}

point3 cross(point3 a, point3 b)
{
    point3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

double dot(point3 a, point3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double mp(point3 a, point3 b, point3 c)
{
    return dot(a, cross(b, c));
}

struct line3
{
    point3 a, b;
    line3 (point3 a = point3(0, 0, 0), point3 b = point3(0, 0, 0)): a(a), b(b) {}
};

typedef line3 segment3;

// 判断三点是否共线。
// 如果点p1，p2，p3共线，则向量p1p2与向量p2p3外积的模为零。
bool collinear(point3 p1, point3 p2, point3 p3)
{
    return norm(cross(p2 - p1, p3 - p2)) < EPSILON;
}

// 判断点是否在线段上，包括在端点上。
bool pointOnSegmentInclude(point3 p, segment3 s)
{
    return collinear(p, s.a, s.b) &&
        (s.a.x - p.x) * (s.b.x - p.x) < EPSILON &&
        (s.a.y - p.y) * (s.b.y - p.y) < EPSILON &&
        (s.a.z - p.z) * (s.b.z - p.z) < EPSILON;
}

// 判断点是否在线段上，不包括在端点上。
bool pointOnSegmentExclude(point3 p, segment3 s)
{
    return pointOnSegmentInclude(p, s) &&
        (!zero(p.x - s.a.x) || !zero(p.y - s.a.y) || !zero(p.z - s.a.z)) &&
        (!zero(p.x - s.b.x) || !zero(p.y - s.b.y) || !zero(p.z - s.b.z));
}

// 判断两点是否在线段的同侧。
// 点在线段上返回false，如果给定的两点和线段不共面则无意义。
bool sameSide(point3 p1, point3 p2, segment3 s)
{
    return dot(cross(s.a - s.b, p1 - s.b), cross(s.a - s.b, p2 - s.b)) > EPSILON;
}

// 判断两点是否在线段的异侧。
// 点在线段上返回false，如果给定的两点和线段不共面则无意义。
bool oppositeSide(point3 p1, point3 p2, segment3 s)
{
    return dot(cross(s.a - s.b, p1 - s.b), cross(s.a - s.b, p2 - s.b)) < -EPSILON;
}

// 判断两条直线是否平行。
bool parallel(line3 u, line3 v)
{
    return norm(cross(u.a - u.b, v.a - v.b)) < EPSILON;
}

// 判断两条直线是否垂直。
bool perpendicular(line3 u, line3 v)
{
    return zero(dot(u.a - u.b, v.a - v.b));
}

// 计算直线到直线距离，即共垂线段的长度。
double lineToLine(line3 u, line3 v)
{
    point3 n = cross(u.a - u.b, v.a - v.b);
    return fabs(dot(u.a - v.a, n)) / norm(n);
}

// 计算两条直线夹角的余弦值。
double cos(line3 u, line3 v)
{
    return dot(u.a - u.b, v.a - v.b) / norm(u.a - u.b) / norm(v.a - v.b);
}

// 利用面积法计算点到直线的距离。
double pointToLine(point3 p, line3 l)
{
    return norm(cross(p - l.a, l.b - l.a)) / norm(l.b - l.a);
}

// 利用三角形与平行四边形的面积比，计算两条直线的交点，注意要事先判断两条直线是否共面和平行。
point3 intersection(line3 u, line3 v)
{
    double k = cross(u.a - v.a, v.a - v.b).z / cross(u.a - u.b, v.a - v.b).z;
    return u.a + (u.b - u.a) * k;
}

// 三维空间平面。
struct plane3
{
    point3 a, b, c;
    plane3 (point3 a = point3(0, 0, 0), point3 b = point3(0, 0, 0),
        point3 c = point3(0, 0, 0)): a(a), b(b), c(c) {}
};

// 平面的法向量。
point3 normalV(plane3 s)
{
    return cross(s.a - s.b, s.b - s.c);
}

// 判断四点是否共面。利用内积判断平面abc的法向量与直线ad是否垂直。
bool coplanar(point3 a, point3 b, point3 c, point3 d)
{
    return zero(dot(normalV(plane3(a, b, c)), d - a));
}

// 判断点是否在空间三角形上，包括在边界上，三点共线则无意义。
bool pointInPlaneInclude(point3 p, plane3 s)
{
    return zero(norm(cross(s.a - s.b, s.a - s.c)) -
        norm(cross(p - s.a, p - s.b)) -
        norm(cross(p - s.b, p - s.c)) - norm(cross(p - s.c, p - s.a)));
}

// 判断点是否在空间三角形上，不包括在边界上，三点共线则无意义。
bool pointInPlaneExclude(point3 p, plane3 s)
{
    return pointInPlaneInclude(p, s) &&
        norm(cross(p - s.a, p - s.b)) > EPSILON &&
        norm(cross(p - s.b, p - s.c)) > EPSILON &&
        norm(cross(p - s.c, p - s.a)) > EPSILON;
}

// 判断两点是否在平面同侧，点在平面上返回false。
bool sameSide(point3 p1, point3 p2, plane3 s)
{
    return dot(normalV(s), p1 - s.a) * dot(normalV(s), p2 - s.a) > EPSILON;
}

// 判断两点是否在平面异侧，点在平面上返回false。
bool oppositeSide(point3 p1, point3 p2, plane3 s)
{
    return dot(normalV(s), p1 - s.a) * dot(normalV(s), p2 - s.a) < -EPSILON;
}

// 判断两条线段是否相交，包括端点相交和部分重合的情形。
bool intersectInclude(line3 u, line3 v)
{
    if (!coplanar(u.a, u.b, v.a, v.b)) return false;
    if (!collinear(u.a, u.b, v.a) || !collinear(u.a, u.b, v.b))
        return !sameSide(u.a, u.b, v) && !sameSide(v.a, v.b, u);
    return pointOnSegmentInclude(u.a, v) || pointOnSegmentInclude(u.b, v) ||
        pointOnSegmentInclude(v.a, u) || pointOnSegmentInclude(v.b, u);
}

// 判断两条线段是否相交，不包括端点相交和部分重合的情形。
bool intersectExclude(line3 u, line3 v)
{
    return coplanar(u.a, u.b, v.a, v.b) &&
        oppositeSide(u.a, u.b, v) &&
        oppositeSide(v.a, v.b, u);
}

// 计算点到平面的有向距离。
double pointToPlane(point3 p, plane3 s)
{
    return dot(normalV(s), p - s.a) / norm(normalV(s));
}

// 计算点到平面的实际距离。
double realPointToPlane(point3 p, plane3 s)
{
    return fabs(pointToPlane(p, s));
}

// 判断直线与平面是否平行。
bool parallel(line3 l, plane3 s)
{
    return zero(dot(l.a - l.b, normalV(s)));
}

// 判断直线与平面是否垂直。
bool perpendicular(line3 l, plane3 s)
{
    return norm(cross(l.a - l.b, normalV(s))) < EPSILON;
}

// 判断直线是否在平面内。
bool in(line3 l, plane3 s)
{
    return coplanar(l.a, s.a, s.b, s.c) && coplanar(l.b, s.a, s.b, s.c);
}

// 计算直线与平面夹角的正弦值。
double sin(line3 l, plane3 s)
{
    return dot(l.a - l.b, normalV(s)) / norm(l.a - l.b) / norm(normalV(s));
}

// 判断线段与空间三角形是否相交，包括交于边界和(部分)包含的情形。
bool intersectInclude(line3 l, plane3 s)
{
    return !sameSide(l.a, l.b, s) &&
        !sameSide(s.a, s.b, plane3(l.a, l.b, s.c)) &&
        !sameSide(s.b, s.c, plane3(l.a, l.b, s.a)) &&
        !sameSide(s.c, s.a, plane3(l.a, l.b, s.b));
}

// 判断线段与空间三角形是否相交，不包括交于边界和(部分)包含的情形。
bool intersectExclude(line3 l, plane3 s)
{
    return oppositeSide(l.a, l.b, s) &&
        oppositeSide(s.a, s.b, plane3(l.a, l.b, s.c)) &&
        oppositeSide(s.b, s.c, plane3(l.a, l.b, s.a)) &&
        oppositeSide(s.c, s.a, plane3(l.a, l.b, s.b));
}

// 利用三棱锥的体积比，计算直线与平面的交点。注意事先判断是否平行，并保证三点不共线。
point3 intersection(line3 l, plane3 s)
{
    point3 r = normalV(s);
    double t = dot(r, s.a - l.a) / dot(r, l.b - l.a);
    r.x = l.a.x + (l.b.x - l.a.x) * t;
    r.y = l.a.y + (l.b.y - l.a.y) * t;
    r.z = l.a.z + (l.b.z - l.a.z) * t;
    return r;
}

// 判断两个平面是否平行。
// 如果平面u和v的法向量的外积的模为零，表明两个平面的法向量平行，因此两个平面也是平行的。
bool parallel(plane3 u, plane3 v)
{
    return norm(cross(normalV(u), normalV(v))) < EPSILON;
}

// 判断两个平面是否垂直。
// 如果平面u和v的法向量的内积为零，表明两个平面的法向量垂直，因此两个平面也是垂直的。
bool perpendicular(plane3 u, plane3 v)
{
    return zero(dot(normalV(u), normalV(v)));
}

// 计算两个平面的交线。
line3 intersection(plane3 u, plane3 v)
{
    line3 r;
    r.a = parallel(line3(v.a, v.b), u) ?
        intersection(line3(v.b, v.c), u) : intersection(line3(v.a, v.b), u);
    r.b = parallel(line3(v.c, v.a), u) ?
        intersection(line3(v.b, v.c), u) : intersection(line3(v.c, v.a), u);
    return r;
}

// 计算两个平面夹角的余弦值。
double cos(plane3 u, plane3 v)
{
    return dot(normalV(u), normalV(v)) / norm(normalV(u)) / norm(normalV(v));
}

int main(int argc, char *argv[])
{
    return 0;
}
