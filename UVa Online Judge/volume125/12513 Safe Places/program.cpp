#include <bits/stdc++.h>
using namespace std;

using Real = long double;
const Real eps = 1e-10L;

struct Point {
    Real x, y, z;
    Point(Real x = 0, Real y = 0, Real z = 0) : x(x), y(y), z(z) {}
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y, z + p.z); }
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y, z - p.z); }
    Point operator*(Real t) const { return Point(x * t, y * t, z * t); }
    Point operator/(Real t) const { return Point(x / t, y / t, z / t); }
};

struct Plane {
    Point normal;
    Real offset;
};

using Face = vector<Point>;
using Poly = vector<Face>;

Real dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point cross(const Point &a, const Point &b) {
    return Point(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Real length(const Point &p) {
    return sqrtl(dot(p, p));
}

bool samePoint(const Point &a, const Point &b) {
    return length(a - b) <= eps;
}

bool hasVolume(const vector<Point> &pts) {
    int cnt = (int)pts.size(), farId = 0, thirdId = 0;
    Real best = 0, cur;
    Point axis, normal, curNormal;
    if (cnt < 4) return false;
    for (int i = 1; i < cnt; ++i) {
        cur = length(pts[i] - pts[0]);
        if (cur > best) {
            best = cur;
            farId = i;
        }
    }
    if (best <= eps) return false;
    axis = (pts[farId] - pts[0]) / best;
    best = 0;
    for (int i = 1; i < cnt; ++i) {
        curNormal = cross(axis, pts[i] - pts[0]);
        cur = length(curNormal);
        if (cur > best) {
            best = cur;
            thirdId = i;
        }
    }
    if (best <= eps) return false;
    normal = cross(axis, pts[thirdId] - pts[0]);
    normal = normal / length(normal);
    for (int i = 1; i < cnt; ++i) if (fabsl(dot(normal, pts[i] - pts[0])) > eps) return true;
    return false;
}

vector<Plane> buildPlanes(const vector<Point> &pts) {
    vector<Plane> planes;
    int cnt = (int)pts.size();
    if (!hasVolume(pts)) return planes;
    for (int i = 0; i < cnt; ++i) {
        for (int j = i + 1; j < cnt; ++j) {
            for (int h = j + 1; h < cnt; ++h) {
                Point normal = cross(pts[j] - pts[i], pts[h] - pts[i]);
                Real normLen = length(normal), offset, side;
                bool hasPos = false, hasNeg = false, repeated = false;
                if (normLen <= eps) continue;
                normal = normal / normLen;
                offset = dot(normal, pts[i]);
                for (const Point &p : pts) {
                    side = dot(normal, p) - offset;
                    if (side > eps) hasPos = true;
                    if (side < -eps) hasNeg = true;
                    if (hasPos && hasNeg) break;
                }
                if (hasPos && hasNeg) continue;
                if (!hasPos && !hasNeg) continue;
                if (hasPos) {
                    normal = normal * -1;
                    offset = -offset;
                }
                for (const Plane &plane : planes) {
                    if (length(normal - plane.normal) <= eps && fabsl(offset - plane.offset) <= eps) {
                        repeated = true;
                        break;
                    }
                }
                if (!repeated) planes.push_back(Plane{normal, offset});
            }
        }
    }
    return planes;
}

Poly makeBox() {
    vector<Point> pts = {
        Point(0, 0, 0), Point(10, 0, 0),
        Point(10, 10, 0), Point(0, 10, 0),
        Point(0, 0, 10), Point(10, 0, 10),
        Point(10, 10, 10), Point(0, 10, 10)
    };
    return Poly{
        Face{pts[0], pts[1], pts[2], pts[3]},
        Face{pts[4], pts[5], pts[6], pts[7]},
        Face{pts[0], pts[1], pts[5], pts[4]},
        Face{pts[1], pts[2], pts[6], pts[5]},
        Face{pts[2], pts[3], pts[7], pts[6]},
        Face{pts[3], pts[0], pts[4], pts[7]}
    };
}

void appendPoint(Face &face, const Point &p) {
    if (face.empty() || !samePoint(face.back(), p)) face.push_back(p);
}

void clipPoly(Poly &poly, const Plane &plane) {
    Real minSide = numeric_limits<Real>::max(), maxSide = -numeric_limits<Real>::max();
    Poly nextPoly;
    Face cap;
    if (poly.empty()) return;
    for (const Face &face : poly) {
        for (const Point &p : face) {
            Real side = dot(plane.normal, p) - plane.offset;
            minSide = min(minSide, side);
            maxSide = max(maxSide, side);
        }
    }
    if (maxSide <= eps) return;
    if (minSide >= -eps) {
        poly.clear();
        return;
    }
    for (const Face &face : poly) {
        Face nextFace;
        int cnt = (int)face.size();
        for (int i = 0; i < cnt; ++i) {
            Point a = face[i], b = face[(i + 1) % cnt];
            Real sideA = dot(plane.normal, a) - plane.offset, sideB = dot(plane.normal, b) - plane.offset;
            if (fabsl(sideA) <= eps) sideA = 0;
            if (fabsl(sideB) <= eps) sideB = 0;
            if (sideA <= 0) appendPoint(nextFace, a);
            if ((sideA < 0 && sideB > 0) || (sideA > 0 && sideB < 0)) {
                Point inter = a + (b - a) * (sideA / (sideA - sideB));
                appendPoint(nextFace, inter);
            }
        }
        if (nextFace.size() > 1 && samePoint(nextFace.front(), nextFace.back())) nextFace.pop_back();
        for (const Point &p : nextFace) {
            bool repeated = false;
            if (fabsl(dot(plane.normal, p) - plane.offset) > eps * 2) continue;
            for (const Point &q : cap) {
                if (samePoint(p, q)) {
                    repeated = true;
                    break;
                }
            }
            if (!repeated) cap.push_back(p);
        }
        if (nextFace.size() >= 3) nextPoly.push_back(move(nextFace));
    }
    if (cap.size() >= 3) {
        Point center, axis, u, v;
        for (const Point &p : cap) center = center + p;
        center = center / (Real)cap.size();
        axis = fabsl(plane.normal.x) < 0.9L ? Point(1, 0, 0) : Point(0, 1, 0);
        u = cross(plane.normal, axis);
        u = u / length(u);
        v = cross(plane.normal, u);
        sort(cap.begin(), cap.end(), [&](const Point &a, const Point &b) {
            Point da = a - center, db = b - center;
            Real angleA = atan2l(dot(da, v), dot(da, u)), angleB = atan2l(dot(db, v), dot(db, u));
            return angleA < angleB;
        });
        nextPoly.push_back(move(cap));
    }
    poly.swap(nextPoly);
}

Real getVolume(const Poly &poly) {
    Point center;
    int cnt = 0;
    Real volume = 0;
    for (const Face &face : poly) {
        for (const Point &p : face) {
            center = center + p;
            ++cnt;
        }
    }
    if (cnt == 0) return 0;
    center = center / (Real)cnt;
    for (const Face &face : poly) {
        Point a = face[0] - center;
        for (int i = 1; i + 1 < (int)face.size(); ++i) {
            Point b = face[i] - center, c = face[i + 1] - center;
            volume += fabsl(dot(a, cross(b, c))) / 6;
        }
    }
    return volume;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int testCount, comb[6][6] = {};
    for (int i = 0; i <= 5; ++i) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; ++j) comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
    cin >> testCount;
    cout << fixed << setprecision(5);
    while (testCount--) {
        int n, k, m;
        Real answer = 0;
        cin >> n >> k >> m;
        vector<vector<Point>> points(n);
        vector<vector<Plane>> planes(n);
        for (int i = 0; i < m; ++i) {
            int type;
            Real x, y, z;
            cin >> type >> x >> y >> z;
            points[type - 1].push_back(Point(x, y, z));
        }
        for (int i = 0; i < n; ++i) planes[i] = buildPlanes(points[i]);
        for (int mask = 1; mask < (1 << n); ++mask) {
            int count = __builtin_popcount((unsigned int)mask), coef;
            bool valid = true;
            if (count < k) continue;
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) && planes[i].empty()) {
                    valid = false;
                    break;
                }
            }
            if (!valid) continue;
            Poly poly = makeBox();
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) continue;
                for (const Plane &plane : planes[i]) {
                    clipPoly(poly, plane);
                    if (poly.empty()) break;
                }
                if (poly.empty()) break;
            }
            coef = comb[count - 1][k - 1];
            if ((count - k) & 1) coef = -coef;
            answer += coef * getVolume(poly);
        }
        if (answer < eps) answer = 0;
        cout << answer << '\n';
    }
    return 0;
}
