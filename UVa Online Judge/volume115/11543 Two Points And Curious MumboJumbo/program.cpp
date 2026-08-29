#include <bits/stdc++.h>
using namespace std;

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

struct Shape {
    Point a, d, b, c;
};

long double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

long double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

long double getLength(Point a) {
    return sqrtl(dot(a, a));
}

Shape makeShape(Point a, Point b) {
    Point u = b - a, n = {-u.y, u.x};
    Point c = a + (u + n) / 3.0L, d = a + (u * 2.0L - n) / 3.0L;
    return {a, d, b, c};
}

bool pointInside(const Shape &shape, Point p) {
    Point v1 = shape.d - shape.a, v2 = shape.b - shape.d, v3 = shape.c - shape.b, v4 = shape.a - shape.c;
    Point w1 = p - shape.a, w2 = p - shape.d, w3 = p - shape.b, w4 = p - shape.c;
    long double e1 = fabsl(cross(v1, w1)), e2 = fabsl(cross(v2, w2)), e3 = fabsl(cross(v3, w3)), e4 = fabsl(cross(v4, w4));
    long double t1 = 1e-12L * getLength(v1) * max(1.0L, getLength(w1));
    long double t2 = 1e-12L * getLength(v2) * max(1.0L, getLength(w2));
    long double t3 = 1e-12L * getLength(v3) * max(1.0L, getLength(w3));
    long double t4 = 1e-12L * getLength(v4) * max(1.0L, getLength(w4));
    return cross(v1, w1) >= -t1 && cross(v2, w2) >= -t2 && cross(v3, w3) >= -t3 && cross(v4, w4) >= -t4;
}

vector<pair<Point, Point>> getChildren(const Shape &shape) {
    Point e = shape.a + (shape.b - shape.a) / 3.0L, f = shape.a + (shape.b - shape.a) * (2.0L / 3.0L);
    vector<pair<Point, Point>> children;
    children.push_back({shape.a, e});
    children.push_back({e, f});
    children.push_back({f, shape.b});
    children.push_back({e, shape.c});
    children.push_back({f, shape.d});
    return children;
}

long double getArea(const Shape &shape) {
    return fabsl(cross(shape.d - shape.a, shape.c - shape.a));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long double xa, ya, xb, yb, xp1, yp1, xp2, yp2;
    while (cin >> xa >> ya >> xb >> yb >> xp1 >> yp1 >> xp2 >> yp2) {
        Point a = {xa, ya}, b = {xb, yb}, p1 = {xp1, yp1}, p2 = {xp2, yp2};
        Shape shape = makeShape(a, b);
        if (!pointInside(shape, p1) || !pointInside(shape, p2)) {
            cout << "-1\n";
            continue;
        }
        for (int level = 0; level < 200; level++) {
            vector<pair<Point, Point>> children = getChildren(shape);
            bool found = false;
            for (const pair<Point, Point> &child : children) {
                Shape nextShape = makeShape(child.first, child.second);
                if (pointInside(nextShape, p1) && pointInside(nextShape, p2)) {
                    shape = nextShape;
                    found = true;
                    break;
                }
            }
            if (!found)
                break;
        }
        cout << fixed << setprecision(4) << (double)getArea(shape) << '\n';
    }
    return 0;
}
