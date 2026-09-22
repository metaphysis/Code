#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-15L;
const long double sqrtThree = sqrtl(3.0L);

struct Point {
    long double x, y;
    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y};
    }

    Point operator * (long double value) const {
        return {x * value, y * value};
    }

    Point operator / (long double value) const {
        return {x / value, y / value};
    }
};

struct Vec3 {
    long double x, y, z;
};

long double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long double getDist(Point a, Point b) {
    Point diff = a - b;
    return sqrtl(dot(diff, diff));
}

long double dot3(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 cross3(Vec3 a, Vec3 b) {
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

Vec3 normalize3(Vec3 value) {
    long double len = sqrtl(dot3(value, value));
    return {value.x / len, value.y / len, value.z / len};
}

Point getFermat(Point a, Point b, Point c) {
    long double lenA = getDist(b, c), lenB = getDist(a, c), lenC = getDist(a, b);
    if (lenA < eps) return b;
    if (lenB < eps || lenC < eps) return a;
    long double dotA = dot(b - a, c - a), dotB = dot(a - b, c - b), dotC = dot(a - c, b - c);
    if (2.0L * dotA <= -lenB * lenC) return a;
    if (2.0L * dotB <= -lenA * lenC) return b;
    if (2.0L * dotC <= -lenA * lenB) return c;
    long double area = fabsl(cross(b - a, c - a));
    long double sinA = area / (lenB * lenC), sinB = area / (lenA * lenC), sinC = area / (lenA * lenB);
    long double cosA = dotA / (lenB * lenC), cosB = dotB / (lenA * lenC), cosC = dotC / (lenA * lenB);
    long double denA = sinA + sqrtThree * cosA, denB = sinB + sqrtThree * cosB, denC = sinC + sqrtThree * cosC;
    if (denA <= eps) return a;
    if (denB <= eps) return b;
    if (denC <= eps) return c;
    long double weightA = lenA / denA, weightB = lenB / denB, weightC = lenC / denC;
    return (a * weightA + b * weightB + c * weightC) / (weightA + weightB + weightC);
}

long double getTriangleLen(Point a, Point b, Point c) {
    Point center = getFermat(a, b, c);
    return getDist(a, center) + getDist(b, center) + getDist(c, center);
}

long double getMstLen(const vector<Point> &points) {
    int count = points.size();
    vector<long double> minDist(count, 1e100L);
    vector<int> used(count, 0);
    long double answer = 0.0L;
    minDist[0] = 0.0L;
    for (int step = 0; step < count; step++) {
        int vertex = -1;
        for (int i = 0; i < count; i++) {
            if (!used[i] && (vertex == -1 || minDist[i] < minDist[vertex])) vertex = i;
        }
        used[vertex] = 1;
        answer += minDist[vertex];
        for (int i = 0; i < count; i++) {
            if (!used[i]) minDist[i] = min(minDist[i], getDist(points[vertex], points[i]));
        }
    }
    return answer;
}

long double getTopologyLen(Point a, Point b, Point c, Point d) {
    Point middle = (c + d) / 2.0L, diff = d - c;
    Point offset = Point{-diff.y, diff.x} * (sqrtThree / 2.0L);
    long double answer = 1e100L;
    for (int sign = -1; sign <= 1; sign += 2) {
        Point equilateral = middle + offset * sign;
        Point first = getFermat(a, b, equilateral);
        Point second = getFermat(c, d, first);
        long double length = getDist(a, first) + getDist(b, first) + getDist(first, second) + getDist(c, second) + getDist(d, second);
        answer = min(answer, length);
    }
    return answer;
}

long double solveProvince(const vector<Point> &points) {
    int count = points.size();
    if (count == 3) return getTriangleLen(points[0], points[1], points[2]);
    long double answer = getMstLen(points);
    for (int extra = 0; extra < 4; extra++) {
        vector<int> ids;
        for (int i = 0; i < 4; i++) {
            if (i != extra) ids.push_back(i);
        }
        long double baseLen = getTriangleLen(points[ids[0]], points[ids[1]], points[ids[2]]);
        for (int i = 0; i < 3; i++) answer = min(answer, baseLen + getDist(points[extra], points[ids[i]]));
    }
    answer = min(answer, getTopologyLen(points[0], points[1], points[2], points[3]));
    answer = min(answer, getTopologyLen(points[0], points[2], points[1], points[3]));
    answer = min(answer, getTopologyLen(points[0], points[3], points[1], points[2]));
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long double a, b, c, d;
    if (!(cin >> a >> b >> c >> d)) return 0;
    Vec3 normal = normalize3({a, b, c}), reference = {0.0L, 0.0L, 0.0L};
    if (fabsl(normal.x) <= fabsl(normal.y) && fabsl(normal.x) <= fabsl(normal.z)) reference.x = 1.0L;
    else if (fabsl(normal.y) <= fabsl(normal.z)) reference.y = 1.0L;
    else reference.z = 1.0L;
    Vec3 basisX = normalize3(cross3(normal, reference)), basisY = normalize3(cross3(normal, basisX));
    int provinceCount;
    cin >> provinceCount;
    cout << fixed << setprecision(2);
    for (int province = 1; province <= provinceCount; province++) {
        int cityCount;
        cin >> cityCount;
        vector<Point> points(cityCount);
        for (int i = 0; i < cityCount; i++) {
            Vec3 city;
            cin >> city.x >> city.y >> city.z;
            points[i] = {dot3(city, basisX), dot3(city, basisY)};
        }
        cout << "Province # " << province << " : " << solveProvince(points) << '\n';
    }
    return 0;
}
