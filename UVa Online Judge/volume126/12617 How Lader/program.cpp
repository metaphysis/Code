#include <bits/stdc++.h>
using namespace std;

const long double eps = 1e-10L;

struct Point {
    long double x, y;
    Point() : x(0), y(0) {}
    Point(long double x, long double y) : x(x), y(y) {}
};

Point operator + (Point a, Point b) {
    return Point(a.x + b.x, a.y + b.y);
}

Point operator - (Point a, Point b) {
    return Point(a.x - b.x, a.y - b.y);
}

Point operator * (Point a, long double k) {
    return Point(a.x * k, a.y * k);
}

long double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long double norm2(Point a) {
    return dot(a, a);
}

Point unit(Point a) {
    long double len = sqrtl(norm2(a));
    return a * (1.0L / len);
}

bool hitHole(Point a, Point b, long double r) {
    Point ab = b - a;
    long double k = -dot(a, ab) / norm2(ab);
    if (k < 0) k = 0;
    if (k > 1) k = 1;
    Point p = a + ab * k;
    return norm2(p) <= r * r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tc;
    cin >> tc;
    for (int cs = 1; cs <= tc; cs++) {
        int s, x1, y1, x2, y2, r, speed;
        cin >> s >> x1 >> y1 >> x2 >> y2 >> r >> speed;
        long double h = sqrtl(3.0L) * s / 2.0L;
        vector<Point> ver;
        ver.push_back(Point(-s / 2.0L, h));
        ver.push_back(Point(s / 2.0L, h));
        ver.push_back(Point(s, 0));
        ver.push_back(Point(s / 2.0L, -h));
        ver.push_back(Point(-s / 2.0L, -h));
        ver.push_back(Point(-s, 0));
        Point pos(x1, y1), dir = unit(Point(x2 - x1, y2 - y1));
        bool fall = false;
        while (speed > 0) {
            long double best = 1e100L;
            int edge = -1;
            for (int i = 0; i < 6; i++) {
                Point a = ver[i], b = ver[(i + 1) % 6], v = b - a;
                long double den = cross(dir, v);
                if (fabsl(den) < eps) continue;
                long double dis = cross(a - pos, v) / den;
                long double k = cross(a - pos, dir) / den;
                if (dis > eps && k >= -eps && k <= 1 + eps && dis < best) {
                    best = dis;
                    edge = i;
                }
            }
            Point nxt = pos + dir * best;
            if (hitHole(pos, nxt, r + 1e-6L)) {
                fall = true;
                break;
            }
            bool corner = false;
            for (int i = 0; i < 6; i++) {
                if (norm2(nxt - ver[i]) < 1e-14L) {
                    corner = true;
                    break;
                }
            }
            if (corner) {
                speed -= 2;
                dir = dir * -1.0L;
            } else {
                speed--;
                Point side = ver[(edge + 1) % 6] - ver[edge];
                Point normal = unit(Point(-side.y, side.x));
                dir = dir - normal * (2.0L * dot(dir, normal));
                dir = unit(dir);
            }
            pos = nxt;
        }
        cout << "Case " << cs << ": ";
        if (fall) cout << speed << '\n';
        else cout << "Stops\n";
    }
    return 0;
}
