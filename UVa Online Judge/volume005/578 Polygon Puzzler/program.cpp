// Polygon Puzzler
// UVa ID: 578
// Verdict: Accepted
// Submission Date: 2018-12-28
// UVa Run Time: 0.050s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

#include <bits/stdc++.h>

using namespace std;

const double EPSILON = 1e-7;

// 三维空间点。
struct point3
{
    double x, y, z;
    point3 (double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
    point3 operator+(const point3 p) { return point3(x + p.x, y + p.y, z + p.z); }
    point3 operator-(const point3 p) { return point3(x - p.x, y - p.y, z - p.z); }
    point3 operator*(double k) { return point3(x * k, y * k, z * k); }
    point3 operator/(double k) { return point3(x / k, y / k, z / k); }
};

// 三维空间直线。
struct line3
{
    point3 a, b;
    line3 (point3 a = point3(0, 0, 0), point3 b = point3(0, 0, 0)): a(a), b(b) {}
};

// 三维空间平面。
struct plane3
{
    point3 a, b, c;
    plane3 (point3 a = point3(0, 0, 0), point3 b = point3(0, 0, 0),
        point3 c = point3(0, 0, 0)): a(a), b(b), c(c) {}
};

// 判断给定的值是否为零值。
bool zero(double x) { return fabs(x) < EPSILON; }

// 向量的模。
double norm(point3 p)
{
    return sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
}

// 三维向量的叉积。
point3 cross(point3 a, point3 b)
{
    point3 r;
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
    return r;
}

// 三维向量的点积。
double dot(point3 a, point3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 向量a，b，c的混合积。其绝对值除以6就是a，b，c三个向量所构成的四面体的体积。
double signedVolume(point3 a, point3 b, point3 c)
{
    return dot(a, cross(b, c));
}

// 平面的法向量。
point3 normalV(plane3 s)
{
    return cross(s.a - s.b, s.b - s.c);
}

// 判断三点是否共线。
bool pointInLine(point3 p1, point3 p2, point3 p3)
{
    return norm(cross(p1 - p2, p2 - p3)) < EPSILON;
}

// 判断四点是否共面。
bool pointOnPlane(point3 a, point3 b, point3 c, point3 d)
{
    return zero(dot(normalV(plane3(a, b, c)), d - a));
}

// 判断点是否在线段上，包括在端点和共线。
bool pointOnLineInclude(point3 p, line3 l)
{
    return zero(norm(cross(p - l.a, p - l.b))) &&
        (l.a.x - p.x) * (l.b.x - p.x) < EPSILON &&
        (l.a.y - p.y) * (l.b.y - p.y) < EPSILON &&
        (l.a.z - p.z) * (l.b.z - p.z) < EPSILON;
}

// 判断点是否在线段上，不包括在端点上。
bool pointOnLineExclude(point3 p, line3 l)
{
    return pointOnLineInclude(p, l) &&
        (!zero(p.x - l.a.x) || !zero(p.y - l.a.y) || !zero(p.z - l.a.z))
        && (!zero(p.x - l.b.x) || !zero(p.y - l.b.y) || !zero(p.z - l.b.z));
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

// 判断两点在线段同侧，点在线段上返回0，不共面无意义。
bool sameSide(point3 p1, point3 p2, line3 l)
{
    return dot(cross(l.a - l.b, p1 - l.b), cross(l.a - l.b, p2 - l.b)) > EPSILON;
}

// 判断两点在线段异侧，点在线段上返回0，不共面无意义。
bool oppositeSide(point3 p1, point3 p2, line3 l)
{
    return dot(cross(l.a - l.b, p1 - l.b), cross(l.a - l.b, p2 - l.b)) < -EPSILON;
}

// 判断两点是否在平面同侧，点在平面上返回0。
bool sameSide(point3 p1, point3 p2, plane3 s)
{
    return dot(normalV(s), p1 - s.a) * dot(normalV(s), p2 - s.a) > EPSILON;
}

// 判断两点是否在平面异侧，点在平面上返回false。
bool oppositeSide(point3 p1, point3 p2, plane3 s)
{
    return dot(normalV(s), p1 - s.a) * dot(normalV(s), p2 - s.a) < -EPSILON;
}

// 判断两条直线是否平行。
bool parallel(line3 u, line3 v)
{
    return norm(cross(u.a - u.b, v.a - v.b)) < EPSILON;
}

// 判断两个平面是否平行。
bool parallel(plane3 u, plane3 v)
{
    return norm(cross(normalV(u), normalV(v))) < EPSILON;
}

// 判断直线与平面是否平行。
bool parallel(line3 l, plane3 s)
{
    return zero(dot(l.a - l.b, normalV(s)));
}

// 判断两条直线是否垂直。
bool perpendicular(line3 u, line3 v)
{
    return zero(dot(u.a - u.b, v.a - v.b));
}

// 判断两个平面是否垂直。
bool perpendicular(plane3 u, plane3 v)
{
    return zero(dot(normalV(u), normalV(v)));
}

// 判断直线与平面是否平行。
bool perpendicular(line3 l, plane3 s)
{
    return norm(cross(l.a - l.b, normalV(s))) < EPSILON;
}

// 判断两条线段是否相交，包括端点相交和部分重合的情形。
bool intersectInclude(line3 u, line3 v)
{
    if (!pointOnPlane(u.a, u.b, v.a, v.b)) return false;
    if (!pointInLine(u.a, u.b, v.a) || !pointInLine(u.a, u.b, v.b))
        return !sameSide(u.a, u.b, v) && !sameSide(v.a, v.b, u);
    return pointOnLineInclude(u.a, v) || pointOnLineInclude(u.b, v) ||
        pointOnLineInclude(v.a, u) || pointOnLineInclude(v.b, u);
}

// 判断两条线段是否相交，不包括端点相交和部分重合的情形。
bool intersectExclude(line3 u, line3 v)
{
    return pointOnPlane(u.a, u.b, v.a, v.b) &&
        oppositeSide(u.a, u.b, v) &&
        oppositeSide(v.a, v.b, u);
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

// 计算两条直线的交点，注意事先判断直线是否共面和平行。
point3 intersection(line3 u, line3 v)
{
    point3 r = u.a;
    double t =
        ((u.a.x - v.a.x) * (v.a.y - v.b.y) - (u.a.y - v.a.y) * (v.a.x - v.b.x))
        / ((u.a.x - u.b.x) * (v.a.y - v.b.y) - (u.a.y - u.b.y) * (v.a.x - v.b.x));
    r.x += (u.b.x - u.a.x) * t;
    r.y += (u.b.y - u.a.y) * t;
    r.z += (u.b.z - u.a.z) * t;
    return r;
}

// 计算直线与平面的交点，注意事先判断是否平行，并保证三点不共线。
point3 intersection(line3 l, plane3 s)
{
    point3 r = normalV(s);
    double t =
        (r.x * (s.a.x - l.a.x) + r.y * (s.a.y - l.a.y) + r.z * (s.a.z - l.a.z)) /
        (r.x * (l.b.x - l.a.x) + r.y * (l.b.y - l.a.y) + r.z * (l.b.z - l.a.z));
    r.x = l.a.x + (l.b.x - l.a.x) * t;
    r.y = l.a.y + (l.b.y - l.a.y) * t;
    r.z = l.a.z + (l.b.z - l.a.z) * t;
    return r;
}

// 计算两个平面交线，注意事先判断是否平行，并保证三点不共线。
line3 intersection(plane3 u, plane3 v)
{
    line3 r;
    r.a = parallel(line3(v.a, v.b), u) ?
        intersection(line3(v.b, v.c), u) : intersection(line3(v.a, v.b), u);
    r.b = parallel(line3(v.c, v.a), u) ?
        intersection(line3(v.b, v.c), u) : intersection(line3(v.c, v.a), u);
    return r;
}

// 计算点到直线的距离。
double pointToLine(point3 p, line3 l)
{
    return norm(cross(p - l.a, l.b - l.a)) / norm(l.a - l.b);
}

// 计算点到平面距离。
double pointToPlane(point3 p, plane3 s)
{
    return fabs(dot(normalV(s), p - s.a)) / norm(normalV(s));
}

// 计算直线到直线距离。
double lineToLine(line3 u, line3 v)
{
    point3 n = cross(u.a - u.b, v.a - v.b);
    return fabs(dot(u.a - v.a, n)) / norm(n);
}

// 计算两直线夹角余弦值。
double cos(line3 u, line3 v)
{
    return dot(u.a - u.b, v.a - v.b) / norm(u.a - u.b) / norm(v.a - v.b);
}

// 计算两平面夹角余弦值。
double cos(plane3 u, plane3 v)
{
    return dot(normalV(u), normalV(v)) / norm(normalV(u)) / norm(normalV(v));
}

// 计算直线平面夹角正弦值。
double sin(line3 l, plane3 s)
{
    return dot(l.a - l.b, normalV(s)) / norm(l.a - l.b) / norm(normalV(s));
}

struct point
{
    double x, y;
    point (double x = 0, double y = 0): x(x), y(y) {}
};

typedef vector<point> polygon;

double getArea(polygon &pg)
{
    double area = 0.0;
    int n = pg.size();
    if (n < 3) return area;
    for (int i = 0, j = 1; i < n; i++, j = (i + 1) % n)
        area += (pg[i].x * pg[j].y - pg[j].x * pg[i].y);
    return fabs(area / 2.0);
}

int main(int argc, char *argv[])
{
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(false);

    int n;
    double xs[1030], ys[1030], zs[1030];

    while (cin >> n, n > 0)
    {
        polygon pg;
        for (int i = 0; i < n; i++)
            cin >> xs[i] >> ys[i] >> zs[i];
            
        plane3 xy(point3(0, 0, 0), point3(1, 0, 0), point3(0, 1, 0));
        plane3 xz(point3(0, 0, 0), point3(1, 0, 0), point3(0, 0, 1));
        plane3 yz(point3(0, 0, 0), point3(0, 1, 0), point3(0, 0, 1));
        plane3 unknown(point3(xs[0], ys[0], zs[0]), point3(xs[1], ys[1], zs[1]), point3(xs[2], ys[2], zs[2]));
        
        double cos_value = 0;
        if (fabs(cos_value = cos(unknown, xy)) > EPSILON)
        {
            for (int i = 0; i < n; i++)
                pg.push_back(point(xs[i], ys[i]));
        }
        else if (fabs(cos_value = cos(unknown, xz)) > EPSILON)
        {
            for (int i = 0; i < n; i++)
                pg.push_back(point(xs[i], zs[i]));
        }
        else if (fabs(cos_value = cos(unknown, yz)) > EPSILON)
        {
            for (int i = 0; i < n; i++)
                pg.push_back(point(ys[i], zs[i]));
        }
        double area = getArea(pg);
        area /= fabs(cos_value);
        cout << fixed << setprecision(3) << area << '\n';
    }

    return 0;
}
