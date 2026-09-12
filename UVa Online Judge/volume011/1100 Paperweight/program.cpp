#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8;

inline int dcmp(double x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

struct Point3 {
    double x, y, z;
    Point3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    bool operator < (const Point3 &u) const {
        return dcmp(x - u.x) < 0 || (dcmp(x - u.x) == 0 && dcmp(y - u.y) < 0) || (dcmp(x - u.x) == 0 && dcmp(y - u.y) == 0 && dcmp(z - u.z) < 0);
    }
    bool operator > (const Point3 &u) const { return u < *this; }
    bool operator == (const Point3 &u) const { return !(u < *this || *this < u); }
    bool operator != (const Point3 &u) const { return !(*this == u); }
    Point3 operator + (const Point3 &u) const { return Point3(x + u.x, y + u.y, z + u.z); }
    Point3 operator - (const Point3 &u) const { return Point3(x - u.x, y - u.y, z - u.z); }
    Point3 operator * (const double u) const { return Point3(x * u, y * u, z * u); }
    Point3 operator / (const double u) const { return Point3(x / u, y / u, z / u); }
    void read() { scanf("%lf%lf%lf", &x, &y, &z); }
};

typedef Point3 Vector3;

namespace Vectorial {
double getDot(Vector3 a, Vector3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
double getLength(Vector3 a) { return sqrt(getDot(a, a)); }
double getAngle(Vector3 a, Vector3 b) { return acos(getDot(a, b) / getLength(a) / getLength(b)); }
Vector3 getCross(Vector3 a, Vector3 b) { return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }

Vector3 getNormal(Point3 a, Point3 b, Point3 c) {
    Vector3 u = a - b, v = b - c;
    Vector3 k = getCross(u, v);
    return k / getLength(k);
}

double getDistancePointToPlane(Point3 p, Point3 p0, Vector3 v) {
    return fabs(getDot(p - p0, v));
}

Point3 getPlaneProjection(Point3 p, Point3 p0, Vector3 v) {
    return p - v * getDot(p - p0, v);
}
}

namespace Linear {
using namespace Vectorial;

double getDistancePointToLine(Point3 p, Point3 a, Point3 b) {
    Vector3 v1 = b - a, v2 = p - a;
    return getLength(getCross(v1, v2)) / getLength(v1);
}

double getDistancePointToSegment(Point3 p, Point3 a, Point3 b) {
    if (a == b) return getLength(p - a);
    Vector3 v1 = b - a, v2 = p - a, v3 = p - b;
    if (dcmp(getDot(v1, v2)) < 0) return getLength(v2);
    else if (dcmp(getDot(v1, v3)) > 0) return getLength(v3);
    else return getLength(getCross(v1, v2)) / getLength(v1);
}

bool getPointLineToLine(Point3 a, Vector3 u, Point3 b, Vector3 v, double &s) {
    double p = getDot(u, u) * getDot(v, v) - getDot(u, v) * getDot(u, v);
    if (dcmp(p) == 0) return false;
    double q = getDot(u, v) * getDot(v, a - b) - getDot(v, v) * getDot(u, a - b);
    s = p / q;
    return true;
}

double getDistanceLineToLine(Point3 a, Vector3 u, Point3 b, Vector3 v) {
    double s, t;
    bool flag1 = getPointLineToLine(a, u, b, v, s);
    bool flag2 = getPointLineToLine(b, v, a, u, t);
    if (flag1 && flag2) {
        Point3 p = a + u * s, q = b + v * t;
        return getLength(p - q);
    }
    return 0;
}

double getDistanceSegmentToSegment(Point3 a, Point3 b, Point3 c, Point3 d) {
    double s, t;
    bool flag1 = getPointLineToLine(a, b - a, c, d - c, s);
    bool flag2 = getPointLineToLine(c, d - c, a, b - a, t);
    if (flag1 && flag2 && dcmp(s) > 0 && dcmp(s - 1) < 0 && dcmp(t) > 0 && dcmp(t - 1) < 0) {
        Vector3 u = b - a, v = d - c;
        Point3 p = a + u * s, q = b + v * t;
        return getLength(p - q);
    } else {
        double ans = 1e20;
        ans = min(ans, getDistancePointToSegment(a, c, d));
        ans = min(ans, getDistancePointToSegment(b, c, d));
        ans = min(ans, getDistancePointToSegment(c, a, b));
        ans = min(ans, getDistancePointToSegment(d, a, b));
        return ans;
    }
}
}

namespace Triangular {
using namespace Vectorial;

double getArea(Point3 a, Point3 b, Point3 c) { return getLength(getCross(b - a, c - a)); }

bool onTriangle(Point3 p, Point3 a, Point3 b, Point3 c) {
    double area1 = getArea(p, a, b);
    double area2 = getArea(p, b, c);
    double area3 = getArea(p, c, a);
    return dcmp(area1 + area2 + area3 - getArea(a, b, c)) == 0;
}

bool haveIntersectionTriSeg(Point3 p0, Point3 p1, Point3 p2, Point3 a, Point3 b, Point3 &p) {
    Vector3 v = getCross(p1 - p0, p2 - p0);
    if (dcmp(getDot(v, b - a)) == 0) return false;
    else {
        double t = getDot(v, p0 - a) / getDot(v, b - a);
        if (dcmp(t) < 0 || dcmp(t - 2) > 0) return false;
        p = a + (b - a) * t;
        return onTriangle(p, p0, p1, p2);
    }
}
}

struct Face {
    int v[3];
    Face(int a = 0, int b = 0, int c = 0) {
        v[0] = a; v[1] = b; v[2] = c;
    }
    Vector3 normal(Point3 *p) const { return Vectorial::getCross(p[v[1]] - p[v[0]], p[v[2]] - p[v[0]]); }
    int canSee(Point3 *p, int i) const { return Vectorial::getDot(p[i] - p[v[0]], normal(p)) > 0 ? 1 : 0; }
};

namespace Polygonal {
using namespace Vectorial;

double getVolume(Point3 a, Point3 b, Point3 c, Point3 d) { return fabs(getDot(d - a, getCross(b - a, c - a)) / 6); }
int visible[1005][1005];
double rand01() { return rand() / (double)RAND_MAX; }
double randEps() { return (rand01() - 0.5) * eps; }
Point3 addNoise(Point3 p) { return Point3(p.x + randEps(), p.y + randEps(), p.z + randEps()); }

vector<Face> convexHull3D(Point3 *origin, int n, Point3 *point) {
    for (int i = 0; i < n; i++) point[i] = addNoise(origin[i]);
    memset(visible, -1, sizeof(visible));
    vector<Face> faces;
    faces.push_back(Face(0, 1, 2));
    faces.push_back(Face(2, 1, 0));
    for (int i = 3; i < n; i++) {
        vector<Face> nextFaces;
        for (int j = 0; j < faces.size(); j++) {
            Face &face = faces[j];
            int result = face.canSee(point, i);
            if (!result) nextFaces.push_back(face);
            for (int k = 0; k < 3; k++) visible[face.v[k]][face.v[(k + 1) % 3]] = result;
        }
        for (int j = 0; j < faces.size(); j++) {
            for (int k = 0; k < 3; k++) {
                int a = faces[j].v[k], b = faces[j].v[(k + 1) % 3];
                if (visible[a][b] != visible[b][a] && visible[a][b])
                    nextFaces.push_back(Face(a, b, i));
            }
        }
        faces = nextFaces;
    }
    return faces;
}

Point3 getCenter(const vector<Face> &faces, Point3 *point) {
    int n = faces.size();
    double sumV = 0, sumX = 0, sumY = 0, sumZ = 0;
    for (int i = 0; i < n; i++) {
        double volume = getVolume(Point3(0, 0, 0), point[faces[i].v[0]], point[faces[i].v[1]], point[faces[i].v[2]]);
        sumV += volume;
        sumX += (point[faces[i].v[0]].x + point[faces[i].v[1]].x + point[faces[i].v[2]].x) * volume;
        sumY += (point[faces[i].v[0]].y + point[faces[i].v[1]].y + point[faces[i].v[2]].y) * volume;
        sumZ += (point[faces[i].v[0]].z + point[faces[i].v[1]].z + point[faces[i].v[2]].z) * volume;
    }
    return Point3(sumX / sumV / 4, sumY / sumV / 4, sumZ / sumV / 4);
}
}

using namespace Linear;
using namespace Triangular;
using namespace Polygonal;

Point3 point[5], fPoint, gPoint;
vector<Point3> flat;

Point3 getWeight() {
    double volumeA = getVolume(point[0], point[1], point[2], point[3]);
    double volumeB = getVolume(point[0], point[1], point[2], point[4]);
    Point3 centerA = (point[0] + point[1] + point[2] + point[3]) / 4;
    Point3 centerB = (point[0] + point[1] + point[2] + point[4]) / 4;
    return (centerA * volumeA + centerB * volumeB) / (volumeA + volumeB);
}

bool sameSide(Point3 a, Point3 b, Point3 c) {
    Point3 normal = getCross(b - a, c - a);
    bool plus = false, minus = false;
    flat.clear();
    flat.push_back(a);
    flat.push_back(b);
    flat.push_back(c);
    for (int i = 0; i < 5; i++) {
        if (point[i] == a || point[i] == b || point[i] == c) continue;
        double value = getDot(point[i] - a, normal);
        if (dcmp(value) < 0) minus = true;
        else if (dcmp(value) > 0) plus = true;
        else flat.push_back(point[i]);
    }
    if (plus && minus) return false;
    return true;
}

bool pointInArea(Point3 p) {
    int n = flat.size();
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (onTriangle(p, flat[i], flat[j], flat[k]))
                    return true;
    return false;
}

bool balance(Point3 p) {
    if (!pointInArea(p)) return false;
    int n = flat.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            Point3 pi = flat[i], pj = flat[j];
            int k;
            for (k = 0; k < n; k++)
                if (k != i && k != j)
                    break;
            Point3 pk = flat[k];
            bool plus = false, minus = false;
            Point3 normal = getCross(getCross(pj - pi, pk - pi), pj - pi);
            for (int x = 0; x < n; x++)
                if (x != i && x != j) {
                    double value = getDot(normal, flat[x] - pi);
                    if (dcmp(value) > 0) plus = true;
                    else if (dcmp(value) < 0) minus = true;
                }
            if (plus && minus) continue;
            if (dcmp(getDistancePointToLine(p, pi, pj) - 0.2) < 0) return false;
        }
    }
    return true;
}

void solve() {
    double ansMax = 0, ansMin = 1e10;
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            for (int k = j + 1; k < 5; k++) {
                if (sameSide(point[i], point[j], point[k])) {
                    Point3 center = getPlaneProjection(gPoint, point[i], getNormal(point[i], point[j], point[k]));
                    if (balance(center)) {
                        double distance = getDistancePointToPlane(fPoint, point[i], getNormal(point[i], point[j], point[k]));
                        ansMax = max(ansMax, distance);
                        ansMin = min(ansMin, distance);
                    }
                }
            }
        }
    }
    printf("%.5lf %.5lf\n", ansMin, ansMax);
}

int main() {
    int caseNum = 1;
    double x, y, z;
    while (scanf("%lf%lf%lf", &x, &y, &z) == 3) {
        point[0] = Point3(x, y, z);
        for (int i = 1; i < 5; i++) point[i].read();
        fPoint.read();
        gPoint = getWeight();
        printf("Case %d: ", caseNum++);
        solve();
    }
    return 0;
}
