struct point {
    double x, y;

    point (double x = 0, double y = 0): x(x), y(y) {}

    point operator + (point p) { return point(x + p.x, y + p.y); };
    point operator - (point p) { return point(x - p.x, y - p.y); };
    point operator * (double a) { return point(a * x, a * y); };
    point operator / (double a) { return point(x / a, y / a); };

    bool operator < (const point &p) const {
        return x != p.x ? x < p.x : y < p.y;
    }

    bool operator == (const point &p) const {
        return fabs(x - p.x) < EPSILON && fabs(y - p.y) < EPSILON;
    }
};

struct segment {
    point p1, p2;
};

typedef segment line;

double dot(point a, point b) { return a.x * b.x + a.y * b.y; }
double cross(point a, point b) { return a.x * b.y - b.x * a.y; }
double norm(point p) { return p.x * p.x + p.y * p.y; };
double abs(point p) { return sqrt(norm(p)); };

double getDist(point a, point b)
{
    return abs(a - b);
}

double getDistPL(point p, line l)
{
    return fabs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}

double getDistPS1(point p, segment s)
{
    double cosa = norm(p - s.p1) + norm(s.p1 - s.p2) - norm(p - s.p2);
    double cosb = norm(p - s.p2) + norm(s.p1 - s.p2) - norm(p - s.p1);
    if (cosa >= 0 && cosb >= 0) return getDistPL(p, s);
    return min(abs(p - s.p1), abs(p - s.p2));
}

double getDistPS2(point p, segment s)
{
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
    return getDistPL(p, s);
}

point project(point p, segment s)
{
    point base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / norm(base);
    return s.p1 + base * r;
}

point project(point p, point p1, point p2)
{
    point base = p2 - p1;
    double r = dot(p - p1, base) / norm(base);
    return p1 + base * r;
}
